#include <stdio.h>
#include <unistd.h>

int main(void)
{
   execl("sequential_min_max"," ","100","10",NULL);
	return 0;
}

