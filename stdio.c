#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
// #include <stdlib.h>
#include  "stdio.h"
#include  "terminal.h"
// #include  <math.h>

int pow(int p,int q)
{
    if (q == 0)
        return 1;
    
    int n = 1;
    for (int i = 0; i < q; i++)
    {
        n*=p;
    }
    
    return n;
}
int selfputcharint(int arg_int)
{
    int amount  =0;
    if(arg_int<0)
    {
        terminal_putchar('-');
        arg_int*=-1;
        amount++;
    }
    if(arg_int ==0 )
    {
        terminal_putchar('0');
        amount++;
    }
    else
    {
        int size_int = 0;
        while (pow(10,size_int)<=arg_int)size_int++;
        amount+=size_int;
        for (int j = size_int-1; j >=0 ; --j)
        {
            terminal_putchar(((int)(arg_int/pow(10,j))%10) + '0');
        }
    }
    return amount;
}
int my_printf(char *mask,...)
{
    int il_mark = 0;
    if(mask != NULL)
    {
        va_list arg;
        va_start(arg,mask);
        int i = 0;
        while (*(mask + i) != '\0')
        {
            if(*(mask + i) == '%' && *(mask + i+1) !='\0')
            {
                if(*(mask + i+1) == 'd')
                {
                    int arg_int = va_arg(arg,int);
                    il_mark+=selfputcharint(arg_int);
                    ++i;

                }else if(*(mask + i+1) == 'f')
                {
                    double arg_doble =  va_arg(arg, double);
                    int r = selfputcharint((int)arg_doble);
                    if(arg_doble<0)arg_doble*=-1;
                    terminal_putchar('.');
                    arg_doble -= (int)arg_doble;
                    for (int j = 1; j <= 5; ++j)
                    {
                        arg_doble*=10;
                        int r = (int)(arg_doble)%10;
                        terminal_putchar( r+ '0');
                        arg_doble-=r;
                    }

                    il_mark+=6+r;
                    ++i;
                }else if(*(mask + i+1) == 's')
                {
                    char *c  = va_arg(arg, char*);
                    int s =0;
                    while (*(c+s) !='\0')
                    {
                        terminal_putchar(*(c+s));
                        s++;
                    }
                    il_mark+= s;
                    ++i;
                }

            }else
            {
                terminal_putchar(*(mask + i));
                il_mark++;
            }
            ++i;
        }
        va_end(arg);
        return  il_mark;
    }
    return 0;
}