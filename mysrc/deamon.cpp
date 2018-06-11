/*************************************************************************
	> File Name: deamon.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年06月07日 星期四 23时59分44秒
 ************************************************************************/
#include "deamon.h"

int deamon()
{
    pid_t pid = 0;
    if( (pid = fork()) == -1)
    {
        return -1;
    }
    else if ( pid > 0 )
    {
        exit(0);
    }
     
    setsid();

    if( chdir("/") != 0 )
    {
        return -1;
    }
    
    umask(0);

    for(int i=0; i<3; i++)    
    {
        close(i);
    }
    return 0;
}
