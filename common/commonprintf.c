#include <unistd.h>
#include "common.h"

int main(int argc, char **argv){

	printf("Here are some common formatters used in printf \n");
	printf("'\\n' will create a new-line as is about to happen now-\n");
	int i = 25;
	printf("%%d will print an int such as this: %d", i);
	long j = 35000000000;
	printf("%%ld will print a long int such as this: %ld -which was just printed.", j);
	char *s = "the string in question";
	printf("%%s will print a char * array (String) such as this: %s", s);
	void *a = sbrk(20);
	printf("%%p will print a void * or generic pointer like this: %p.",a);

	return 0;
}
