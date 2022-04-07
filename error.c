#include <errors.h>
#include <utils.h>
#include <stdio.h>

int p_error(char *msg, int errorcode)
{
    printf("%s\n", msg);
    return (errorcode);
}

int error(int argc, char *argv[])
{
    int     i;
    char    *str;

    if (!(argc == 5 || argc == 6))
        return (p_error("Error: please only give 5 or 6 arguments", WRONG_AMOUNT_OF_ARGUMENTS));
    i = 1;
    while (i < argc)
    {
        str = ft_itoa(ft_atoi(argv[i]));
        if (ft_strncmp(str, "-", 1) == 0)
        {
            free(str);
            return(p_error("Error: please dont fill in a negative number", 1));
        }
        if (ft_strncmp(str, argv[i], ft_strlen(argv[i])) != 0)
        {
            free (str);
            return(p_error("Error: wrong input or int overflow", INT_OVERFLOW));
        }
        free(str);
        i++;
    }
    return (0);
}