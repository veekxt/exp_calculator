#ifndef MY_STR_H_INCLUDED
#define MY_STR_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define \
swap(type_t,a,b)\
{type_t tmp_s_w_a_p_h_ = (type_t)(a);\
(a)=(type_t)(b);\
(b)=tmp_s_w_a_p_h_;\
}
void str_del_char(char *S,int n);
void str_del_char_ch(char *S,char ch);
void str_add_char(char *S,int n,char a);
void str_delete(char *S,int n,int m);
void str_rep(char *S,char *ADD,int n,int m);
void str_del_some_char(char *S,char *del);
char* str_rev(char* s);
void  float_jh(char *S);
#endif // MY_STR_H_INCLUDED
