#include <stdio.h>

#ifdef ADD

#include "add.h"

#endif

#ifdef SUB

#include "sub.h"

#endif


#ifdef MUL

#include "mul.h"

#endif


#ifdef DIV

#include "div.h"

#endif

int main(void)
{
#ifdef ADD

	printf("3 + 7 = %d\n", add(3, 7));

#endif /*ADD(x, y)*/

#ifdef SUB

	printf("3 - 1 = %d\n", sub(3, 1));

#endif /*SUB*/

#ifdef MUL

	printf("3 * 2 = %d\n", mul(3, 2));

#endif /*MUL*/

#ifdef DIV

	printf("5 / 2 = %d\n", div(5, 2));

#endif /*DIV*/

#ifdef DEBUG

	printf("hello world\n");

#endif /*DEBUG*/
	return 0;
}
