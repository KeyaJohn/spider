/*************************************************************************
	> File Name: parse_argv.h
	> Author: 
	> Mail: 
	> Created Time: 2018年06月07日 星期四 23时49分51秒
 ************************************************************************/

#ifndef _PARSE_ARGV_H
#define _PARSE_ARGV_H
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void version();
void help_info();
int parse_argv(int argc,char *argv[]);

#endif
