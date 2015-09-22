#ifndef MY_FUN_H_INCLUDED
#define MY_FUN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "my_str.h"

double fun_jisuan(char *fun_name,char *list_arg);
char *ext_arg(char *arg,char *tmp);
double cal_add(char *S);
double cal_sin(char *S);
double cal_cos(char *S);
double cal_pow(char *S);
double cal_max(char *S);
double cal_min(char *S);
double cal_sqrt(char *S);
double fun_rgb_hex(char *S);
int cal_rand(char *S);
int  m_n_rand(int m,int n);
#endif // MY_FUN_H_INCLUDED
