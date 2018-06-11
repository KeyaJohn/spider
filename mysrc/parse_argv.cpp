/*************************************************************************
	> File Name: parse_argv.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月07日 星期四 23时56分34秒
 ************************************************************************/
#include "deamon.h"

void version()
{
    printf("VERSION: SPIDER 1.0\n");
    exit(1);
}

void help_info()
{
    printf("Usage: ./spider [Options]\n"
           "\nOptions:\n"
           "  -h\t: this help\n"
           "  -v\t: print spiderq's version\n"
           "  -d\t: run program as a daemon process\n\n");
    exit(1);
}

int parse_argv(int argc,char *argv[])
{
    char ch;
    while( (ch = getopt(argc,(char*const *)argv,"vhd")) != -1 ) 
    {
        switch( ch )
        {
            case 'v':
                version();
                break;
            case 'd':
                if ( 0 == deamon() )
                {
                    deamon();
                }
                else
                {
                    printf("deamon err!\n");
                    return -1;
                }
                break;
            case 'h':
                help_info();
                break;
            default:
                break;
        }
    }
    return 0;
}

