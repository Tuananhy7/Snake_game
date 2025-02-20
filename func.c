#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "main.h"

extern int snake_life;
extern uint8_t map[MAP_ROW][MAP_COL];
char input;
/* gen number [MOVING_LEFT-MOVING_DOWN]*/
char snake_direction=0;

/*init head snake*/
struct snake *snake_head = NULL;

static int count=0;

void reset_map(void)
{
    int i,j;
    for(i=1;i<MAP_ROW;i++)
    {
        for(j=1;j<MAP_COL;j++)
        {
            map[i][j]=' ';
        }
    }
}

void create_new_snake(void)
{
    /*init moving direction of snake*/ 
    //srand(time(0));
    //snake_direction=(rand() % 4);
    snake_direction=MOVING_RIGHT;
    snake_head=add_node_snake(snake_head, 7, 7);
    snake_head=add_node_snake(snake_head, 7, 8);
    map[7][7]=SNAKE_BLOCK;
    map[7][8]=SNAKE_BLOCK;
}

void init_map(void)
{
    int i=0,j=0;
    int col=0;
    for(i=0;i<=MAP_ROW;i++)
    {
        for(j=0;j<=MAP_COL;j++)
        {
            if(i>0&&i<MAP_ROW&&j>0&&j<MAP_COL) 
                map[i][j]=EMPTY_BLOCK; 
            else 
                map[i][j]=WALL_BLOCK;
        }
    }
    create_new_snake();
}
void display_map(void)
{
     char pri_char=' ';
     int i=0,j=0;
     // clear terminal
     printf("\033[H\033[J");
     // print map...
    for(i=0;i<=MAP_ROW;i++)
    {
        for(j=0;j<=MAP_COL;j++)
        {
            if(map[i][j]==SNAKE_BLOCK)
                pri_char='*';
            else if(map[i][j]==WALL_BLOCK)
                pri_char='#';
            else if(map[i][j]==EMPTY_BLOCK)
                pri_char=' ';
            else if(map[i][j]==EAT_BLOCK)
                pri_char='X';

            printf("%c",pri_char);
        }
        printf("\n");
    }
    printf("time:%d|| snake_dir:%d\n",++count,snake_direction);
    
}
void snake_run(char snake_direction)
{
    snake_head=appear_snake(snake_head, snake_direction);

    if(map[snake_head->x][snake_head->y] == WALL_BLOCK)
    {
        printf("gave over!!!\n");
        snake_life=DIE_SNAKE;
        map[snake_head->x][snake_head->y]=SNAKE_BLOCK;
    }
    map[snake_head->x][snake_head->y]=SNAKE_BLOCK;

}

void control_snake_run(void)
{
    //Keypress Event Handler
   struct termios info;
   tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
   info.c_lflag &= ~ICANON;      /* disable canonical mode */
   info.c_cc[VMIN] = 0;          /* set 1 wait until at least one keystroke available */
   info.c_cc[VTIME] = 0;         /* no timeout */
   tcsetattr(0, TCSANOW, &info); /* set immediately */

    if (ferror(stdin)) { /* there was an error... */ }
        clearerr(stdin);
    /* clear stdin to avoid you've reached EOF*/

    char input = getchar();

    if('a'==input)
         snake_direction=MOVING_LEFT;
    else if('d'==input)
        snake_direction=MOVING_RIGHT;
    else if('w'==input)
        snake_direction=MOVING_UP;
    else if('s'==input)
        snake_direction=MOVING_DOWN;

    snake_run(snake_direction);

    tcgetattr(0, &info);
    info.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &info);
}

struct location_food *gen_randum_number(int row_min, int row_max, int col_min, int col_max)
{
    struct location_food *food;

    srand(time(0));
    food->row= row_min + (rand() % (row_max-row_min));
    food->col= col_min + (rand() % (col_max-col_min));
    return food;
}

struct location_food *check_snake_gen_food(struct location_food *snake_food, int limit)
{
    struct location_food *food;
    int i=0;
    for(i=(food->row-limit) ;i<(food->row+limit); i++)
    {
        if(map[food->row][food->col]==SNAKE_BLOCK)
            return NULL;
    }

    for(i=(food->col-limit) ;i<(food->col+limit); i++)
    {
        if(map[food->col][food->col]==SNAKE_BLOCK)
            return NULL;
    }
    return food;
}

struct location_food * gen_food_ramdum(void)
{
    struct location_food *snake_food=(struct location_food *)malloc(sizeof(struct location_food));
    
    snake_food=gen_randum_number(10, MAP_ROW, 10, MAP_COL);
    while(1)
    {
        snake_food=gen_randum_number(10, MAP_ROW, 10, MAP_COL);
        snake_food=check_snake_gen_food(snake_food, 4);
        if(NULL != snake_food) break;
    }
    printf("location = x: %d || y: %d\n",snake_food->row,snake_food->col);
    map[snake_food->row][snake_food->col]=EAT_BLOCK;

    return snake_food;
}

void food_appear_randum(void)
{
    
}


