#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_str.h"

//删除指定位置字符
void str_del_char(char *S,int n)
{
    int len=strlen(S);
    for(int i=n; i<len; i++)
    {
        S[i]=S[i+1];
    }
}

//在S中删除ch
void str_del_char_ch(char *S,char ch)
{
    int flag_well=1;
    for(;;)
    {
        int len=strlen(S);
        flag_well=1;
        for(int i=0;i<len;i++)
        {
            if(S[i]==ch)
            {
                flag_well=0;
                str_del_char(S,i);
                break;
            }
        }
        if(flag_well==1)break;
    }
}

//前插一个字符
void str_add_char(char *S,int n,char a)
{
    int len=strlen(S);
    for(int i=len; i>=n; i--)
    {
        S[i+1]=S[i];
    }
    S[n]=a;
}

//删除S的n到m位置
void str_delete(char *S,int n,int m)
{
    if(n>m)
    {
        swap(int,n,m);
    }
    for(int i=0; i<=m-n; i++)
    {
        //注意总是删除同一位置，删除之后S变了
        str_del_char(S,n);
    }
}

//在S的n处插入ADD
void str_add(char *S,char *ADD,int n)
{
    int add_len=strlen(ADD);
    for(int i=add_len-1; i>=0; i--)
    {
        //注意总是添加在同一位置
        str_add_char(S,n,ADD[i]);
    }
}
//使用ADD替换S的n,m位置
void str_rep(char *S,char *ADD,int n,int m)
{
    str_delete(S,n,m);
    str_add(S,ADD,n);
}
//从字符串删除一些字符，这些字符由del字符串指定
void str_del_some_char(char *S,char *del)
{
    for(int i=0;i<strlen(del);i++)
        str_del_char_ch(S,del[i]);
}

//字符串逆置
//某处找的一个实现
//不想自己写了
char* str_rev(char* s)
{
    char* h = s;    
    char* t = s;
    char ch;
    while(*t++){};
    t--;
    t--;
    while(h < t)
    {
        ch = *h;
        *h++ = *t;
        *t-- = ch;
    }
    return (s);
}

//简化浮点数，去掉多余的0
void  float_jh(char *S)
{
    int len=strlen(S);
    int flag_double=0;
    for(int i=0; i<len; i++)
    {
        if(S[i]=='.')flag_double=1;
    }
    if(flag_double==1)
    {
        for(int i=len-1; i>0; i--)
        {
            if(S[i]=='0')
            {
                str_del_char(S,i);
                S[i]=S[i+1];
                if(S[i-1]=='.')
                {
                    str_del_char(S,i-1);
                    break;
                }
            }else break;
        }
    }
}
