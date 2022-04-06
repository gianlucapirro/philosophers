#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <philosophers.h>
#include <errors.h>

int main(int argc, char *argv[])
{
	t_data	data;

	data_init(&data, argc, argv);
	return (0);
}