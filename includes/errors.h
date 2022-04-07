#ifndef ERRORS_H
# define ERRORS_H

typedef	enum	e_error {
	SUCCES,
	WRONG_AMOUNT_OF_ARGUMENTS,
	INT_OVERFLOW,
	MALLOC_FAILED,
	MUTEX_FAILED,
	PHILOSOPHER_FAIL
}	t_error;

int p_error(char *msg, int errorcode);
int error(int argc, char *argv[]);

#endif