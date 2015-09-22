#include <stdio.h>
#include "other_fun.h"
#include "my_fun.h"
//这渣渣英语
//不用在意
extern int is_print_to;

void other(char *S)
{
    if(strcmp(S,":h")==0)
    {
        puts("===Help===");
        puts("Some Command: ");
        puts(":q  #Qiut");
        puts(":st off  #Do not print the process of calculor");
        puts(":st on  #Print the process of calculor");
        puts(":ls fun  #List the function you can use");
    }
    else
    if(strcmp(S,":q")==0)
    {
        exit(0);
    }
    else
    if(strcmp(S,":st on")==0)
    {
        is_print_to=1;
    }
    else
    if(strcmp(S,":st off")==0)
    {
        is_print_to=0;
    }
    else
    if(strcmp(S,":ls fun")==0)
    {
        puts("\nadd(a1,a2,...)  #return sum of args");
        puts("max(a1,a2,...)  #return MAX value of args");
        puts("min(a1,a2,...)  #return MIN value of args");
        puts("sin(a1)  #return sin(a1),the same with sin() in C");
        puts("cos(a1)  #return sin(a1),the same with cos() in C");
        puts("pow(a1,a2)  #return a1 ^ a2 ,the same with pow() in C");
        puts("sqrt(a1)  #return sqrt(a1) ,the same with sqrt() in C");
        puts("rand(a1,a2)  #return random between a1 and a2 (include)");
        puts("rgb_hex(r,g,b)  #convent rgb to hex");
        puts("i will buchong if have time");
        puts("");
    }
    else
    {
        printf("Can't find command : \"%s\"\n",S+1);
    }

}
