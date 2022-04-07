#include <philosophers.h>
#include <utils.h>

void    data_init(t_data *data, int argc, char *argv[])
{
    data->numberOfPhils = ft_atoi(argv[1]);
    data->timeToDie = ft_atoi(argv[2]);
    data->timeToEat = ft_atoi(argv[3]);
    data->timeToSleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->notepme = ft_atoi(argv[5]);
    else
        data->notepme = 0;
}