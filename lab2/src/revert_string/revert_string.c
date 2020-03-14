#include "revert_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
void RevertString(char *str)
{
	/*int strlength = 0;
    while (*(strlength+str)!=0)
    {
        ++strlength;
    }
    int i;
    for (i=0; i<(strlength-1)/2; i++)
    {
        char temporary = *(str+i);
        *(str+i) = *(str+strlength-i-1);
        *(str+strlength-i-1) = temporary;
    }*/
    char *temp = malloc(sizeof(char)*(strlen(str)+1));
    int a = sizeof(char)*(strlen(str));
    strcpy(temp,str);
    int i;
    for (i=0; i<a; i++)
    {
        str[i]=temp[a-i-1];

    }
    str[a+1]='\0';
    free(temp);
}

