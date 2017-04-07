#include <stdio.h>

void function(int a, int b, int c)
{
	/* 5 byte size but this is 2 words = 8 bytes (on 32 bit) */
	char buffer1[5];
	int *ret;

	/* add 3*WORDSIZE +1 */
	ret = (int *)(&buffer1[0] + 13);

	/* address-difference is 10 bytes. */
	(*ret) += 10;
}

int main()
{
	int x;

	x = 0;
	function(1,2,3);
	x = 1;
	printf("%d\n",x);
	return 0;
}
