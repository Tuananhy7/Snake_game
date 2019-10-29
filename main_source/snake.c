#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "main.h"

extern uint8_t map[MAP_ROW][MAP_COL];
extern int snake_eat_food;


struct snake *node_snake_create(int x, int y)
{
    struct snake *new_node_snake;
    new_node_snake = ( struct snake * )malloc(sizeof(struct snake));
    new_node_snake->x=x;
    new_node_snake->y=y;
    new_node_snake->next=NULL;
    return new_node_snake;
}

struct snake *add_node_snake( struct snake *head, int x, int y)
{
    struct snake *add=node_snake_create(x, y);
    if(NULL==head)
    {
        head=add;
    }
    else
    {
        add->next=head;
        head=add;
    }
}

struct snake *appear_snake(struct snake *head, char move_type)
{
    delete_snake_tail(head);
    head=add_node_snake(head, head->x, head->y);

    if(MOVING_LEFT==move_type)
        head->y--;
    else if(MOVING_RIGHT==move_type)
        head->y++;
    else if(MOVING_UP==move_type)
        head->x--;
    else if(MOVING_DOWN==move_type)
        head->x++;
    if(snake_eat_food == SNAKE_EAT)
    {
        head=add_node_snake(head, head->x, head->y);
        snake_eat_food = SNAKE_RUN;
    }
    return head;
}

void delete_snake_tail(struct snake *head)
{
    struct snake *tail=NULL;
    tail=head;

    while(tail->next->next != NULL)
    {
        /*node final*/  
        tail=tail->next;
    }
    map[tail->next->x][tail->next->y]=EMPTY_BLOCK;
    tail->next=NULL; 
}

