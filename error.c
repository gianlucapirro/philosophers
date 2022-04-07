#include <errors.h>
#include <utils.h>
#include <stdio.h>
#include <gettime.h>

/**
 * prints a msg and returns its corrosponding errorcode
 * 
 * @param msg 
 * @param errorcode 
 * @return errorcode 
 */
int p_error(char *msg, int errorcode)
{
    printf("%s\n", msg);
    return (errorcode);
}

/**
 * checks if there is invalid input, if so 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int error(int argc, char *argv[])
{
    int     i;

    if (!(argc == 5 || argc == 6))
        return (p_error("Error: please only give 5 or 6 arguments", WRONG_AMOUNT_OF_ARGUMENTS));
    i = 1;
    while (i < argc)
    {
        if(input(argv[i]) == false)
            return (p_error("Error: input is negative, not a long int or not an int", INT_OVERFLOW));
        i++;
    }
    return (0);
}