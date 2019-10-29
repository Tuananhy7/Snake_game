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
	usleep(80000);
	return NULL;
}

void *food_randum(void *arg)
{
	pthread_mutex_lock(&mutex);
    food_appear_randum();
	pthread_mutex_unlock(&mutex);
	usleep(1000);
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex, NULL);
    pthread_t thread_id[3];
	int i=0;
	snake_life = LIVE_SNAKE;
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
