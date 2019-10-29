#ifndef SNAKE_H
#define SNAKE_H
enum wall_snake_empty_eat
{
    EMPTY_BLOCK,
    WALL_BLOCK,
    SNAKE_BLOCK,
    EAT_BLOCK
};

enum snake_status
{
    LIVE_SNAKE,
    DIE_SNAKE,
    SNAKE_EAT,
    SNAKE_RUN
};

struct snake
{
    int x;
    int y;
    struct snake *next;
};

struct snake *node_snake_create(int x, int y);
struct snake *add_node_snake( struct snake * head, int x, int y);
struct snake *appear_snake(struct snake *head, char move_type);
void delete_snake_tail(struct snake *head);


#endif