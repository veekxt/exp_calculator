#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "my_str.h"
#include "my_fun.h"

//从字符指针提取一个参数，返回下一个参数起始点
//参数形式应该如： 4,-5,567 用逗号分割的没有多余字符
char *ext_arg(char *arg,char *tmp)
{
    int i;
    for(i=0;;i++)//读取字符直到遇到逗号或结束符
    {
        if(*(arg+i)==',' || *(arg+i)==0)
        {
            tmp[i]=0;
            return *(arg+i)==0?(arg+i):arg+i+1;
        }
        tmp[i]=*(arg+i);
    }
    return NULL;
}
//根据函数名不同选择函数
//函数名不可带数字
double fun_jisuan(char *fun_name,char *list_arg)
{
    str_del_char_ch(list_arg,'(');
    str_del_char_ch(list_arg,')');

    if(strcmp(fun_name,"add")==0)
    {
        return (double)cal_add(list_arg);//要自行实现的函数
    }

    //添加自己想要的函数，用这些例子的格式添加
    if(strcmp(fun_name,"sin")==0)
    {
        return (double)cal_sin(list_arg);
    }

    if(strcmp(fun_name,"cos")==0)
    {
        return (double)cal_cos(list_arg);
    }

    if(strcmp(fun_name,"pow")==0)
    {
        return (double)cal_pow(list_arg);
    }

    if(strcmp(fun_name,"max")==0)
    {
        return (double)cal_max(list_arg);
    }

    if(strcmp(fun_name,"min")==0)
    {
        return (double)cal_min(list_arg);
    }

    if(strcmp(fun_name,"sqrt")==0)
    {
        return (double)cal_sqrt(list_arg);
    }

    if(strcmp(fun_name,"rand")==0)
    {
        return (double)cal_rand(list_arg);
    }
    if(strcmp(fun_name,"rgb_hex")==0)
    {
        return (double)fun_rgb_hex(list_arg);
    }

    return -1.0;
}

//实现自定义函数
//S的格式是逗号分隔的参数，如 -2,3,5.7,32
//可以自行决定如何读取参数并计算结果
//不过已经封装了一个函数ext_arg用来取参数。
//ext_arg用法：它使用第一个参数做起点，读取一个参数，
//放到第二个参数中，返回下一个参数的起点
//下面演示了读取所有参数并相加的例子
double cal_add(char *S)
{
    char *tmp=S;//不能直接使用S
    char arg[50];
    double sum=0;
    for(;strcmp(tmp,"")!=0;)
    {
        tmp=ext_arg(tmp,arg);
        sum+=atof(arg);
    }
    return sum;
}
//各个参数最大值
double cal_max(char *S)
{
    char *tmp=S;//不能直接使用S
    char arg[50];
    tmp=ext_arg(tmp,arg);
    double max=atof(arg);
    for(;strcmp(tmp,"")!=0;)
    {
        tmp=ext_arg(tmp,arg);
        max=atof(arg)>max?atof(arg):max;
    }
    return max;
}

//各个参数最小值
double cal_min(char *S)
{
    char *tmp=S;//不能直接使用S
    char arg[50];
    tmp=ext_arg(tmp,arg);
    double min=atof(arg);
    for(;strcmp(tmp,"")!=0;)
    {
        tmp=ext_arg(tmp,arg);
        min=atof(arg)>min?min:atof(arg);
    }
    return min;
}

double cal_sin(char *S)
{
    char *tmp=S;
    char arg[50];
    double sum=0;
    tmp=ext_arg(tmp,arg);
    sum=sin(atof(arg));
    return sum;
}

double cal_cos(char *S)
{
    char *tmp=S;
    char arg[50];
    double sum=0;
    tmp=ext_arg(tmp,arg);
    sum=cos(atof(arg));
    return sum;
}

double cal_pow(char *S)
{
    char *tmp=S;
    char arg[50];
    double arg1=0,arg2=0;

    tmp=ext_arg(tmp,arg);
    arg1=(atof(arg));

    tmp=ext_arg(tmp,arg);
    arg2=(atof(arg));

    return pow(arg1,arg2);
}

double cal_sqrt(char *S)
{
    char *tmp=S;
    char arg[50];
    double arg1=0;

    tmp=ext_arg(tmp,arg);
    arg1=(atof(arg));

    return sqrt(arg1);
}

int  m_n_rand(int m,int n)
{
    if(n<m)swap(int,m,n);
    return m+rand()%(n-m+1);
}
int cal_rand(char *S)
{
    char *tmp=S;
    char arg[50];
    int arg1=0,arg2=0;

    tmp=ext_arg(tmp,arg);
    arg1=(atoi(arg));

    tmp=ext_arg(tmp,arg);
    arg2=(atoi(arg));
    return m_n_rand(arg1,arg2);
}

//不一定要算一个值，也可以做其他事
double fun_rgb_hex(char *S)
{
    char *tmp=S;
    char arg[50];
    int args[3]={0,0,0};
    for(int i=0;i<3;i++)
    {
        tmp=ext_arg(tmp,arg);
        args[i]=(atoi(arg));
    }
    printf("\nRgb(%s) to Hex is %#x\n\n",S,(args[0]<<16)+(args[1]<<8)+args[2]);
    return (args[0]<<16)+(args[1]<<8)+args[2];
}
