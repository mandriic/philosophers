#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <libc.h>

typedef struct s_data
{
	pthread_mutex_t mutex;
	int argument;
}t_data;

void *func_thread(void *vars)
{

	
	t_data *temp = vars; 
	while(1)
	{
	 pthread_mutex_lock(&temp->mutex);
		printf("iter %d\n", temp->argument);

		pthread_mutex_unlock(&temp->mutex);
	


	}
}

void *func_thread_2(void *vars)
{
	t_data *temp = vars;

	while(temp->argument < 1001)
	{
	pthread_mutex_lock(&temp->mutex);

		temp->argument = temp->argument + 1;
			 pthread_mutex_unlock(&temp->mutex);
	sleep(1);

	}
}

int main(int argc, char *argv[])
{
	int i;
	struct timeval cur_time;
	t_data vars;
	int time_start;
	int time_cur;


	i = 1;

 	pthread_mutex_init(&vars.mutex, 0);
	vars.argument = 2;
	gettimeofday(&cur_time, NULL);
	time_start = cur_time.tv_usec;
	printf ("Year now %ld \n", cur_time.tv_sec/60/60/24/364 + 1970);

	if (argc > 1)
	{
		while (argv[i])
		{
			gettimeofday(&cur_time, NULL);
			time_cur = cur_time.tv_usec;
			printf("input %s, time pass %d ms\n", argv[i++], time_cur - time_start);
		}
	}
	pthread_t thread_1;
	pthread_t thread_2;
	

	pthread_create (&thread_1, NULL, &func_thread, &vars);
	pthread_create (&thread_2, NULL, &func_thread_2, &vars);
	sleep(10);

	return (0);
}
