#include <assert.h>
void f( char* str)
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

void testRevertString(void) {
  char simple_string[] = "Hello";
  char str_with_odd_chars_num[] = "abc";
  char str_with_even_chars_num[] = "abcd";

  f(simple_string);
  assert(0 == strcmp(simple_string, "olleH"));

  f(str_with_odd_chars_num);
   assert(0 == strcmp(str_with_odd_chars_num, "cba"));

  f(str_with_even_chars_num);
   assert(0 == strcmp(str_with_even_chars_num, "dcba"));
}

int main()
{
	testRevertString();
#if 0
	char *s=strdup("12345");
	f(s);
	printf("rev - %s\n", s);
#endif
}
