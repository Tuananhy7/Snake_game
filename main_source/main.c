#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>
#include "main.h"

pthread_mutex_t mutex;
uint8_t map[MAP_ROW][MAP_COL];
int snake_life = LIVE_SNAKE;
long int speed_level=0;

void select_level(void)
{
	printf("pick level: (1) (2) (3) (4) (5)\n");
	char c = getchar();
	c=c-48;
	if(c==1) speed_level=100000;
	else if(c==2) speed_level=80000;
	else if(c==3) speed_level=60000;
	else if(c==4) speed_level=50000;
	else if(c==5) speed_level=35000;
	else speed_level=200000;
}

void *display(void *arg)
{
	pthread_mutex_lock(&mutex);
	display_map();
	pthread_mutex_unlock(&mutex);
	//usleep(3000);
	return NULL;
}

void *control(void *arg)
{
	pthread_mutex_lock(&mutex);
    control_snake_run();
	pthread_mutex_unlock(&mutex);
	usleep(speed_level);
	return NULL;
}

void *food_randum(void *arg)
{
	pthread_mutex_lock(&mutex);
    food_appear_randum();
	pthread_mutex_unlock(&mutex);
	//usleep(1000);
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
    pthread_t thread_id[3];
	int i=0;
	snake_life = LIVE_SNAKE;
	select_level();
	init_map();
		while(snake_life != DIE_SNAKE)
		{
			pthread_mutex_init(&mutex, NULL);
			pthread_create(&thread_id[0], NULL, display, NULL);
            pthread_create(&thread_id[1], NULL, control, NULL);
			pthread_create(&thread_id[2], NULL, food_randum, NULL);
            for (i = 0; i < 3; i++)
            {
                pthread_join(thread_id[i], NULL);
            }
			pthread_mutex_destroy(&mutex);
		}
	pthread_mutex_destroy(&mutex);
	return 0;
}
