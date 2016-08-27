#include <stdio.h>
/* not sure whether needed; better safe than sorry. */
#include <stdint.h>

void function()
{
	/* just some pointer */
	char buffer1[5];
	uintptr_t *ret;

	/* we need to add 3 times the size of an address:
	 *  - the address of buffer1[0] itself: sizeof(char *)
	 *  - the size of ret: sizeof(uintptr_t *)
	 *  - the size of the pushed base pointer: sizeof(void *)
	 */
	ret = (uintptr_t *)(&buffer1[0] + 3*sizeof(void *));
	/* 64-bit code is different, we skip 3 bytes here */
	(*ret) += 3;
}

int main()
{
	int x;

	x = 0;
	function();
	x = 1;
	printf("%d\n",x);
	return 0;
}
