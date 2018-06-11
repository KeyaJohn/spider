#include <stdio.h>
#include "url.h"
#include <sys/epoll.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <getopt.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include "spider.h"
#include "threads.h"
#include "qstring.h"
 
int g_epfd;
Config *g_conf;
extern int g_cur_thread_num;

static int set_nofile(rlim_t limit);
static void daemonize();
//static void stat(int sig);
//static int set_ticker(int second);

static void version()
{
    printf("Version: spider 1.0\n");
    exit(1);
}

static void usage()
{
    printf("Usage: ./spider [Options]\n"
            "\nOptions:\n"
            "  -h\t: this help\n"
            "  -v\t: print spiderq's version\n"
            "  -d\t: run program as a daemon process\n\n");
    exit(1);
}

int main(int argc, char  *argv[]) 
{
    struct epoll_event events[10];
    int daemonized = 0;
    char ch;

    /* 解析命令行参数 */
    while ((ch = getopt(argc, (char* const*)argv, "vhd")) != -1) 
    {
        switch(ch) 
        {
            case 'v':
                version();
                break;
            case 'd':
                daemonized = 1;
                break;
            case 'h':
            case '?':
            default:
                usage();
        }
    }

    /* 解析日志 */
    g_conf = initconfig();
    loadconfig(g_conf);

    /* s设置 fd num to 1024 */
    set_nofile(1024); 

    /* 载入处理模块 */
    vector<char *>::iterator it = g_conf->modules.begin();
    for(; it != g_conf->modules.end(); it++) 
    {
        dso_load(g_conf->module_path, *it); 
    } 

    /* 添加爬虫种子 */
    if (g_conf->seeds == NULL) 
    {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "We have no seeds!");
    } 
    else 
    {
        int c = 0;
        printf("seeds is :%s\n",g_conf->seeds);
        char ** splits = strsplit(g_conf->seeds, ',', &c, 0);
        while (c--) 
        {
            Surl * surl = (Surl *)malloc(sizeof(Surl));
            surl->url = url_normalized(strdup(splits[c]));
            surl->level = 0;
            surl->type = TYPE_HTML;
            if (surl->url != NULL)
                push_surlqueue(surl);
        }
    }	

    /* 守护进程模式 */
    if (daemonized)
        daemonize();

    /* 设定下载路径 */
    if( chdir("../download") != 0)
    {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "change dir fail!");
        return 0;
    }

    /* 启动用于解析DNS的线程 */
    int err = -1;
    if ((err = create_thread(urlparser, NULL, NULL, NULL)) < 0) 
    {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "Create urlparser thread fail: %s", strerror(err));
    }

    /* waiting seed ourl ready */
/* 
    int try_num = 1;
    while(try_num < 8 && is_ourlqueue_empty())
        usleep((10000 << try_num++));//为什么这样呢？
    if (try_num >= 8) 
    {
        SPIDER_LOG(SPIDER_LEVEL_ERROR, "NO ourl! DNS parse error?");
    }
*/
    sleep(3);
    /*设置定时器*/
    /*printf("定时器的时间间隔为 :%d\n",g_conf->stat_interval);
    if (g_conf->stat_interval > 0) 
    {
        printf("进入stat_interval > 0\n");
        signal(SIGALRM, stat);
        set_ticker(g_conf->stat_interval);
    }*/

    /* begin create epoll to run */
    g_epfd = epoll_create(g_conf->max_job_num);

    /*while(ourl_num++ < g_conf->max_job_num) //g_conf->max_job_num = 1
    {
        //向epoll中加入监听文件描述符
        if (attach_epoll_task() < 0 )
            break;
    }
    */
    pthread_t pid;
    if( pthread_create(&pid,NULL,attach_epoll_task,NULL) != 0 )
    {
        printf("create thread faile!\n\n") ;
        return 0;
    }

    /* epoll wait */
    int n, i;
    while(1) 
    {
        n = epoll_wait(g_epfd, events, 10, 2000);
        printf("epoll:%d\n",n);
        //超时处理
        if (n == -1)
            printf("epoll errno:%s\n",strerror(errno));
        fflush(stdout);

        //epoll出错处理
        if (n <= 0) 
        {
            if (g_cur_thread_num <= 0 && is_ourlqueue_empty() && is_surlqueue_empty()) 
            {
                sleep(1);
                if (g_cur_thread_num <= 0 && is_ourlqueue_empty() && is_surlqueue_empty())
                    break;
            }
        }
        //epoll成功返回文件描述符处理
        for (i = 0; i < n; i++) 
        {
            evso_arg * arg = (evso_arg *)(events[i].data.ptr);
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN))) 
            {
                SPIDER_LOG(SPIDER_LEVEL_WARN, "epoll fail, close socket %d",arg->fd);
                close(arg->fd);
                continue;
            }
            //从epoll中删除该文件描述符
            //由于删除会释放空间
            epoll_ctl(g_epfd, EPOLL_CTL_DEL, arg->fd, &events[i]); /* del event */

            //printf("hello epoll:event=%d\n",events[i].events);
            //fflush(stdout);
            //sleep(3);
            //接受服务器发送过来的消息
            //create_thread(recv_response, arg, NULL, NULL);
            pthread_t pid;
            int rv = pthread_create(&pid,NULL,recv_response,arg);
            if( rv != 0 )
            {
                printf("create thread faile!\n\n") ;
                return 0;
            }
        }
    }

    SPIDER_LOG(SPIDER_LEVEL_DEBUG, "Task done!");
    close(g_epfd);

    return 0;
}

void * attach_epoll_task(void *argv)
{
    struct epoll_event ev;
    int sock_rv;
    int sockfd;

    while( 1 )
    {
        //pthread_mutex_lock(&oq_lock);
        //此处不需要枷锁原因是该出出栈函数内部已经枷锁,否则则出现死锁
/*        Url * ourl = pop_ourlqueue();
        printf("\n\n==============从队列 ourl_queue 中取出一个ourl:%s加入epoll=============\n\n",ourl->domain);
        //pthread_mutex_unlock(&oq_lock);
        if (ourl == NULL) 
        {
            SPIDER_LOG(SPIDER_LEVEL_WARN, "====Pop ourlqueue fail!");
            return NULL;
        }
*/
        pthread_mutex_lock(&oq_lock);
        //如果没有队列中没有url，则会阻塞这里
        while (ourl_queue.empty()) 
        {
            pthread_cond_wait(&oq_cond, &oq_lock);
        }
        Url* ourl = ourl_queue.front();
        ourl_queue.pop();
        pthread_mutex_unlock(&oq_lock);

        //与该url建立连接
        if ((sock_rv = build_connect(&sockfd, ourl->ip, ourl->port)) < 0) 
        {
            SPIDER_LOG(SPIDER_LEVEL_WARN, "Build socket connect fail: %s", ourl->ip);
            return NULL;
        }
        //设置该sockfd为非阻塞
        set_nonblocking(sockfd);

        //发送请求头
        if ((sock_rv = send_request(sockfd, ourl)) < 0) 
        {
            SPIDER_LOG(SPIDER_LEVEL_WARN, "Send socket request fail: %s", ourl->ip);
            return NULL;
        } 

        evso_arg * arg = (evso_arg *)calloc(1, sizeof(evso_arg));
        arg->fd = sockfd;
        arg->url = ourl;
        ev.data.ptr = arg;
        ev.events = EPOLLIN | EPOLLET;
        if (epoll_ctl(g_epfd, EPOLL_CTL_ADD, sockfd, &ev) == 0) 
        {
            /* add event */
            printf("\n\n==============从队列 ourl_queue 中取出一个ourl:%s加入epoll=============\n\n",ourl->domain);
            //SPIDER_LOG(SPIDER_LEVEL_DEBUG, "Attach an epoll event success!");
        } 
        else 
        {
            SPIDER_LOG(SPIDER_LEVEL_WARN, "Attach an epoll event fail!");
            return NULL;
        }
        g_cur_thread_num++; 
    }
    return 0;
}

static int set_nofile(rlim_t limit)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) 
    {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "getrlimit fail");
        return -1;
    }
    if (limit > rl.rlim_max) 
    {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "limit should NOT be greater than %lu", rl.rlim_max);
        return -1;
    }
    rl.rlim_cur = limit;
    if (setrlimit(RLIMIT_NOFILE, &rl) < 0) 
    {
        SPIDER_LOG(SPIDER_LEVEL_WARN, "setrlimit fail");
        return -1;
    }
    return 0;
}

static void daemonize()
{
    int fd;
    if (fork() != 0) 
        exit(0);

    setsid();
    SPIDER_LOG(SPIDER_LEVEL_INFO, "Daemonized...pid=%d", (int)getpid());	

    /* redirect stdin|stdout|stderr to /dev/null */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) 
    {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO)
            close(fd);
    }

    /* redirect stdout to logfile */
    if (g_conf->logfile != NULL && (fd = open(g_conf->logfile, O_RDWR | O_APPEND | O_CREAT, 0)) != -1) 
    {
        dup2(fd, STDOUT_FILENO);
        if (fd > STDERR_FILENO)
            close(fd);
    }
}

/*static int set_ticker(int second)
{
    struct itimerval itimer;
    itimer.it_interval.tv_sec = (long)second;
    itimer.it_interval.tv_usec = 0;
    itimer.it_value.tv_sec = (long)second;
    itimer.it_value.tv_usec = 0;

    return setitimer(ITIMER_REAL, &itimer, NULL);
    //该函数是一个定时器，
    //第一个参数是类型，ITIMER表示的是以真实的系统时间来计算
    //参数2为定时的相隔时间
    //struct itimerval 
    //{
    //    struct timeval 
    //    {
    //         time_t tv_sec;
    //         useconds_t tv_usec;
    //    }it_value,it_interval;
    //};
}
*/
/*
static void stat(int sig)
{
    SPIDER_LOG(SPIDER_LEVEL_DEBUG, 
            "cur_thread_num=%d\tsurl_num=%d\tourl_num=%d",
            g_cur_thread_num,
            get_surl_queue_size(),
            get_ourl_queue_size());
}
*/
