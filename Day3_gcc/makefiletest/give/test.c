#include <stdio.h>

//// ADD

#include "add.h"

////

//// SUB

#include "sub.h"

////


//// MUL

#include "mul.h"

////


// DIV

#include "div.h"

//

int main(void)
{
// ADD

	printf("3 + 7 = %d\n", add(3, 7));

// /*ADD(x, y)

// SUB

	printf("3 - 1 = %d\n", sub(3, 1));

// /*SUB

// MUL

	printf("3 * 2 = %d\n", mul(3, 2));

// /*MUL

// DIV

	printf("5 / 2 = %d\n", div(5, 2));

// /*DIV

// DEBUG

	printf("hello world\n");

// /*DEBUG
	return 0;
}
