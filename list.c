#include <list.h>
#include <philosophers.h>
#include <unistd.h>

t_philosphers	*phil_init(void)
{
	t_philosphers	*
}

void	phil_add(t_philosphers **head_ref)
{
	t_philosphers	*new_phil;
    /* 1. allocate node */
    new_phil = (t_philosphers *)malloc(sizeof(t_philosphers));
 
    /* 2. put in the data  */
    new_phil->philNr = (*head_ref)->philNr + 1;
 
    /* 3. Make next of new node as head and previous as NULL */
    new_phil->next = (*head_ref);
    new_phil->prev = NULL;
 
    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_phil;
 
    /* 5. move the head to point to the new node */
    (*head_ref) = new_phil;
}