#ifndef ERROR_H_
#define ERROR_H_

#define SOCKETERROR (-1)

// check_err handles errors if they return SOCKETERROR. When an error
// is encountered it prints the error message `msg` and exits with  EXIT_FAILURE.
// Otherwise it returns the `exp`.
int check_err(int exp, const char *msg);

#endif // ERROR_H_
