#include "revert_string.h"

void RevertString(char *str)
{
	int strlength = 0;
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
    }
}

