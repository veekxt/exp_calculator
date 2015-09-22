/***

Edit by Xie Tao
wlzhizhen@163.com
2015-06-18
(((34.12+(3/(3.456-8.7)+9)*(5/2-7)-(-7))/3+9)+9)*2
add(add(1,min(add(3,4),add(7,8))),7,6)-3*max(2,3,4,add(4.3,pow(2,3),5.2,4),9,4)/2

***/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "my_str.h"
#include "my_fun.h"
#include "other_fun.h"
#define MAXBUF 1000

int is_print_to=1;
double cac_easy(char *s);
const char all_czf[20]= {'+','-','*','/',/* '%' */};
typedef enum {notczf,suanshu,fun} type_czf;

//存放子表达式
typedef struct str_exp_s
{
    int n;//表达式将替换的位置
    int m;
    char *target;
    char s[1000];//表达式，对于函数是参数列表
    char fun_name[20];//函数名
}*str_exp;

//函数声明，功能在定义处说明
int isShuzi(char a);
type_czf isczf(char *chp);
void format(char *S,char *tmp);
double cac_easy(char *s);
type_czf what_type(char ch);
int zjpd(char *S);
int ysj(char a,char b);
void  float_jh(char *S);
int tiqu_from_fun(char *S,int i,str_exp aexp);
int tiqu_from_czf(char *S,int i,str_exp aexp);
void replace(str_exp aexp,type_czf what);
int tiqu(char *S);

//数字判断
int isShuzi(char a)
{
    if((a<='9'&&a>='0') || a=='.')return 1;
    return 0;
}

//操作符判定
type_czf isczf(char *chp)
{
    if((*chp>='a' && *chp<='z')||(*chp>='A' && *chp<='Z'))
    {
        return fun;// 函数，仅由字母构成
    }
    for(int i=0; all_czf[i]!=0; i++)
    {
        if(*chp==all_czf[i])
        {
            if(*chp=='-')
            {
                if(*(chp-1)=='('){return notczf;}
            }
            {return suanshu;}// 内置二元操作符
        }
    }
    {return notczf;}
}
//格式化简单表达式
//5+8-->(5)+(8)
void format(char *S,char *tmp)
{
    int len=strlen(S);
    tmp[0]='(';
    int j=1;//j:tmp下标
    for(int i=0; i<len; i++)
    {
        if(isShuzi(S[i]) || (S[i]=='-' &&S[i-1]=='('))
        {
            for(;;)
            {
                tmp[j++]=S[i++];
                if(isShuzi(S[i])==0)break;
            }
        }
        if(isczf(&S[i])==suanshu)
        {
            tmp[j++]=')';
            tmp[j++]=S[i];
            tmp[j++]='(';
        }
    }
    tmp[j++]=')';
    tmp[j++]=0;
}

//计算简单的已经格式化表达式
//形式如：(2)+(4),(5)*(7.3)之类
double cac_easy(char *s)
{
    char zuo_s[20];//存放左边的数
    char you_s[20];//存放右边的数
    char ch;//操作符
    char *tmp;//临时，放zuo_s和you_s
    int flag_fen=0;//分割标记，当前是左面的值还是右边，默认是左0。
    for(int i=0;;)
    {
        if(flag_fen==0) tmp=zuo_s;//如果不是第一个字符则是右边的数。
        else tmp=you_s;
        int j=i+1;
        for(; s[j]!=')'; j++) //逐个读取直到遇到‘）’
        {
            tmp[j-i-1]=s[j];//左边的数字存在zuo_s中
        }
        tmp[j-i-1]=0;
        flag_fen=1;
        if(tmp==you_s)break;
        ch=s[i=j+1];
        i=i+1;
    }
    switch(ch)
    {
    case '+':
        return atof(zuo_s)+atof(you_s);
        break;
    case '-':
        return atof(zuo_s)-atof(you_s);
        break;
    case '*':
        return atof(zuo_s)*atof(you_s);
        break;
    case '/':
        return atof(zuo_s)/atof(you_s);
        break;
        /*扩展实例：取余
    case '%':
        return (int)atof(zuo_s)%(int)atof(you_s);
        break;
        //other:
        // case '/':
        // return atof(zuo_s)/atof(you_s);
        // break;
        */
    }
    return -1.0;
}

//操作符类型判断，已丢弃，集成到isczf中
type_czf what_type(char ch)
{
    for(int i=0;all_czf[i]!=0;++i)
    {
        if(ch==all_czf[i])return suanshu;
    }
    return fun;
}

//优先级判定
int ysj(char a,char b)
{
    int a_int=1;
    int b_int=1;
    if(a=='-'  ||  a=='+')a_int=0;//只有“+”和“-”优先级最低，其余都一样
    if(b=='-'  ||  b=='+')b_int=0;
    return b_int-a_int;             //b>a,返回正数b<a，返回负数，相同是零
}

//是否进行计算判定
//参数包含一个操作符两边的表达式,后一个操作符

int zjpd(char *S)
{
    int geshu_cz=0;//保存操作符个数
    int len=strlen(S);//字符串长度
    char czf=0;//保存操作符
    for(int i=0; i<len-1; i++)
    {
        int flag_is_czf=0;
        type_czf tmp;
        for(;isczf(&S[i]);)
        {
            tmp=isczf(&S[i]);
            flag_is_czf=1;//标记找到一个操作符
            czf=S[i++];//保存最后一个操作符
            if(tmp!=isczf(&S[i]))break;
        }
        if(flag_is_czf==1){i--;geshu_cz++;}//操作符个数计数
    }
    if(geshu_cz==0)return 2;//返回2表示没有任何操作符
    if(geshu_cz>1)return 0;//包含两个以上操作符一定不是最简
    else
    {
        if(ysj(czf,S[len-1])>0)return 0;//考虑优先级，5+(-8)/ 这样的表达式不该计算5+(-8),后面是除法
        else return 1;
    }
}

//基于函数提取表达式
int tiqu_from_fun(char *S,int i,str_exp aexp)
{
    aexp->target=S;
    aexp->n=i;
    char *list_arg=aexp->s;
    int tmp_xb;
//保存函数名
    for(tmp_xb=0;S[i]!='(';i++)
    {
        aexp->fun_name[tmp_xb++]=S[i];
    }
    aexp->fun_name[tmp_xb++]=0;
//保存参数列表
    for(int tm_fun_list=0,flag_pare=0;;i++)
    {
        if(S[i]=='(')flag_pare++;else
        if(S[i]==')')flag_pare--;

        if(flag_pare==0){list_arg[tm_fun_list++]=')';list_arg[tm_fun_list++]=0;aexp->m=i;break;}
        list_arg[tm_fun_list++]=S[i];
    }
    return 1;
}
//基于操作符提取表达式
//从某操作符两边提取完整表达式
//（6-8）*7+2 中，对于 * 向左找到（6-8），向右找到7+
//读取右边的操作符意义在于判断优先级
//为了统一，即使向右读取最后是字符串结束或者是一个），也要添加一个 +
int tiqu_from_czf(char *S,int i,str_exp aexp)
{
    int flag_pare=0;
    int where_czf=i;
    int tmp_xb=0;
    for(;;)
    {
        //找左边的表达式
        i--;
        if(S[i]=='(')flag_pare+=1;
        if(S[i]==')')flag_pare-=1;
        if(flag_pare==1 || (flag_pare==0 &&S[i]==','))
        {
            aexp->s[tmp_xb]=0;
            aexp->n=i+1;
            break;
        }
        else
        if(i==0)
        {
            aexp->s[tmp_xb++]=S[i];
            aexp->s[tmp_xb]=0;
            aexp->n=i;
            break;
        }
        else
        if(isczf(&S[i])==suanshu &&flag_pare == 0 )
        {
            aexp->s[tmp_xb]=0;
            aexp->n=i+1;
            break;
        }
        aexp->s[tmp_xb++]=S[i];
    }
    str_rev(aexp->s);
    i=where_czf;
    aexp->s[tmp_xb++]=S[i];
    flag_pare=0;

    for(;;)
    {
        //找右边的表达式
        i=i+1;
        if(S[i]==')')flag_pare++;else
        if(S[i]=='(')flag_pare--;
        if(flag_pare == 1 || (flag_pare==0 &&S[i]==','))
        {
            aexp->s[tmp_xb++]='+';
            aexp->s[tmp_xb++]=0;
            aexp->m=i-1;
            break;
        }
        if(i==strlen(S)-1)
        {
            aexp->s[tmp_xb++]=S[i];
            aexp->s[tmp_xb++]='+';
            aexp->s[tmp_xb++]=0;
            aexp->m=i;
            break;
        }
        if(isczf(&S[i])==suanshu && flag_pare == 0)
        {
            aexp->s[tmp_xb++]=S[i];
            aexp->s[tmp_xb++]=0;
            aexp->m=i-1;
            break;
        }
        aexp->s[tmp_xb++]=S[i];
    }
    return 1;
}
//字符串替换，使用计算结果替换原字符串
void replace(str_exp aexp,type_czf what)
{
    char tmp[1000];
    if(what==suanshu)
    {
        //对于算术运算，删除最后一个多余字符
        str_del_char(aexp->s,strlen(aexp->s)-1);
        format(aexp->s,tmp);
    }
    //计算
    sprintf(tmp,"%.12f",what==suanshu?cac_easy(tmp):fun_jisuan(aexp->fun_name,aexp->s));
    //简化运算结果
    float_jh(tmp);
    //为负数加括号
    if(tmp[0]=='-')sprintf(aexp->s,"(%s)",tmp);
    else sprintf(aexp->s,"%s",tmp);
    //替换
    str_rep(aexp->target,aexp->s,aexp->n,aexp->m);
    //输出替换结果
    if(is_print_to==1)printf("To==>  %s\n",aexp->target);
}

//提取最左，最简表达式并替换
int tiqu(char *S)
{
    int len_S=strlen(S);
    struct str_exp_s aexp;
    aexp.target=S;
    int ismin=1;//标记是否已经最简
    for(int i=0;i<len_S;)
    {
        switch(isczf(&S[i]))
        {
        case suanshu:
            ismin=0;//只要有操作符就不是最简
            tiqu_from_czf(S,i,&aexp);
            if(zjpd(aexp.s)==1)
            {
                replace(&aexp,suanshu);
                return ismin;
            }else i++;
            break;
        case fun:
            ismin=0;
            tiqu_from_fun(S,i,&aexp);
            if(zjpd(aexp.s)==2)
            {
                replace(&aexp,fun);
                return ismin;
            }else i++;
            break;
        case notczf:
            i++;
            break;
        }
    }
    return ismin;
}

int main(void)
{
    srand((unsigned)time(NULL));
    char input[MAXBUF];
    puts("Welcom,you can use :q to quit and use :h to help");
    for(;;)
    {
        puts("Input a Exp :");
        fgets(input,MAXBUF,stdin);
        //冒号开头的不是表达式
        if(input[0]==':')
        {
            str_del_some_char(input,"\n\r");
            other(input);
            continue;
        }
        //删除空白符、换行符
        str_del_some_char(input,"\n \r\t");
        for(;;)
        {
            if(tiqu(input)==1)break;
        }
        str_del_some_char(input,"()");
        float_jh(input);
        printf("Value : %s \n",input);
    }
    return 0;
}
