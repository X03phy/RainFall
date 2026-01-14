#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char c[68]; // Not sure with that size


void m(void *param_1, int param_2, char *param_3, int param_4, int param_5)
{
	time_t t;

	t = time(NULL);
	printf("%s - %d\n", c, t);
}


int main(int argc, char **argv)
{
	int *a;
	int *b;
	FILE *f;

	a = malloc(8);
	a[0] = 1;
	a[1] = malloc(8);

	b = malloc(8);
	b[0] = 2;
	b[1] = malloc(8);

	strcpy((char *)a[1], argv[1]);
	strcpy((char *)b[1], argv[2]);

	f = fopen("/home/user/level8/.pass", "r");
	fgets(c, 0x44, f);

	puts("~~");
	return (0);
}
