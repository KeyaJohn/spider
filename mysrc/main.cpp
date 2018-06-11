/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月07日 星期四 23时05分55秒
 ************************************************************************/
#include "deamon.h"
#include "parse_argv.h"
char *url = NULL;

using namespace std;

int main(int argc,char *argv[])
{
     
    parse_argv(argc,argv);
   
    
    //获取首要的url
    url = "www.qq.com";
    if( url != NULL ) 
    {
        print("having no url!");
        return 0; 
    }
    
    

    while(1)
    {
       sleep(1);
    }
    return 0;
}
