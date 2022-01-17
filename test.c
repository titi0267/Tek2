/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD04pm-timothe.coniel
** File description:
** test
*/

#include "int_list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/queue.h>

unsigned int int_list_get_size (int_list_t list)
{
    unsigned int len = 0;
    int_list_t head = list;

    for (;head != NULL; head = head->next)
        len++;
    return (len);
}

bool int_list_is_empty(int_list_t list)
{
    if (list == NULL)
        return (true);
    else
        return (false);
}

void int_list_dump(int_list_t list)
{
    int_list_t head = list;

    for (; head != NULL; head = head->next)
        printf("%d\n", head->value);
}

bool int_list_add_elem_at_front(int_list_t *front_ptr, int elem)
{
    int_list_t new_node = malloc(sizeof(int_list_t));

    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    new_node->next = (*front_ptr);
    (*front_ptr) = new_node;
    return (true);
}

bool int_list_add_elem_at_back(int_list_t *front_ptr, int elem)
{
    int_list_t new_node = malloc(sizeof(int_list_t));
    int_list_t last_node = (*front_ptr);
    
    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    if (last_node == NULL)
        last_node = new_node;
    else {
        while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = new_node;
    }
    return (true);
}

bool int_list_add_elem_at_position(int_list_t *front_ptr, int elem, unsigned int position)
{
    int_list_t new_node = malloc(sizeof(int_list_t));
    int_list_t last_node;
    
    if (new_node == NULL)
        return (false);
    new_node->value = elem;
    if (front_ptr == NULL || position == 0)
        int_list_add_elem_at_front(front_ptr, elem);
    else {
        for (;last_node != NULL; position--, last_node = last_node->next) {
            if (position == 0) {
                new_node->next = last_node->next; 
                last_node->next = new_node;
                break;
            }
        }
        if (last_node == NULL)
            return (false);
        last_node->next = new_node;
    }
    return (true);
}

int int_list_get_elem_at_front(int_list_t list)
{
    int_list_t head = list;
    
    if (head == NULL)
        return (0);
    else
        return (head->value);
}

int int_list_get_elem_at_back(int_list_t list)
{
    int_list_t last_node = list;
    
    if (last_node == NULL)
        return (0);
    else
        for (;last_node != NULL; last_node = last_node->next);
    return (last_node->value);
}

int int_list_get_elem_at_position(int_list_t list, unsigned int position)
{
    int_list_t last_node = list;
    
    if (last_node == NULL || position == 0)
        return (int_list_get_elem_at_front(list));
    else {
        for (;last_node != NULL; position--, last_node = last_node->next) {
            if (position == 0) {
                break;
            }
        }
    }
    return (last_node->value);
}

bool int_list_del_elem_at_front(int_list_t *front_ptr)
{
    /*int_list_t del_node = (*front_ptr);

    if (del_node == NULL)
        return (false);
    
  /*Moving head to the next node
    *del_node = (*head)->next;
  
  /*Deleting the first node
  free(tmp);*/
}

bool int_list_del_elem_at_back(int_list_t *front_ptr)
{

}

bool int_list_del_elem_at_position(int_list_t *front_ptr, unsigned int position)
{

}

void int_list_clear(int_list_t *front_ptr)
{

}

/*
static void populate_list ( int_list_t * list_head )
{
int_list_add_elem_at_back ( list_head , 5) ;
int_list_add_elem_at_back ( list_head , 42) ;
int_list_add_elem_at_back ( list_head , 3) ;
}
static void test_size ( int_list_t list_head )
{
printf (" There are %u elements in the list \n", int_list_get_size ( list_head ) ) ;
int_list_dump ( list_head ) ;
}
static void test_del ( int_list_t * list_head )
{
int_list_del_elem_at_back ( list_head ) ;
printf (" There are %u elements in the list \n", int_list_get_size (* list_head ) ) ;
int_list_dump (* list_head ) ;
}
int main ( void )
{
int_list_t list_head = NULL ;
populate_list (& list_head ) ;
test_size ( list_head ) ;
test_del (& list_head ) ;
int_list_clear (& list_head ) ;
return 0;
}*/