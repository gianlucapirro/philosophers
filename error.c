#include <errors.h>
#include <stdio.h>

int p_error(char *msg, int errorcode)
{
    printf("%s\n", msg);
    return (errorcode);
}
