/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** queue
*/

#include "list.h"
#include "queue.h"
#include <stdio.h>

unsigned int queue_get_size(queue_t queue)
{
    return (list_get_size(queue));
}

bool queue_is_empty(queue_t queue)
{
    return (list_is_empty(queue));
}

bool queue_push(queue_t *queue_ptr, void *elem)
{
    return (list_add_elem_at_front(queue_ptr, elem));
}

bool queue_pop(queue_t *queue_ptr)
{
    return (list_del_elem_at_back(queue_ptr));
}

void queue_clear(queue_t *queue_ptr)
{
    return (list_clear(queue_ptr));
}

void *queue_front(queue_t queue)
{
    return (list_get_elem_at_back(queue));
}

int main ( void )
{
queue_t queue = NULL ;
int i = 5;
int j = 4;
int * data = NULL ;
queue_push (& queue , & i ) ;
queue_push (& queue , & j ) ;
data = ( int *) queue_front ( queue ) ;
printf ("%d\n", * data ) ;
queue_clear (& queue ) ;
return (0) ;
}
/*
int main ( void )
{
queue_t queue = NULL ;
int i = 5;
int j = 4;
int * data = NULL;
queue_push(&queue, &i);
queue_push(&queue, &j);
data = (int *)queue_front(queue);
printf("%d\n", *data);
queue_clear (&queue);
return (0);
}*/