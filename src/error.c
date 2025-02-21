#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

// check_err handles errors if they return SOCKETERROR. When an error
// is encountered it prints the error message `msg` and exits with  EXIT_FAILURE.
// Otherwise it returns the `exp`.
int check_err(int exp, const char *msg)
{
	if (exp == SOCKETERROR) {
		perror(msg);
		exit(EXIT_FAILURE);
	}

	return exp;
}
