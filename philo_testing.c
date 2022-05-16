#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
void *ft_secs()
{
	int time1;
	int time2;
	struct timeval cur_time;

	gettimeofday(&cur_time, NULL);
	time1 = cur_time.tv_usec;
	while(1)
	{
		gettimeofday(&cur_time, NULL);
		time2 = cur_time.tv_usec;
		printf("secs pass:%d\n", (time2 - time1) / 1000);
		sleep(1);

	}
}
int	main(int argc, char **argv)
{
	struct timeval cur_time;
	int diff, time1, time2;
	long long time_in_mill;
	long long time_in_mill2;
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;d
	gettimeofday(&cur_time, NULL);
	time1 = cur_time.tv_sec;
	time2 = cur_time.tv_sec;
	time_in_mill = (cur_time.tv_sec) * 1000 + (cur_time.tv_usec) / 1000;
	int i = 0;
	pthread_create(&t1, NULL, ft_secs, NULL);

	// while(1)
	// {
	// 	gettimeofday(&cur_time, NULL);
	// 	time2 = cur_time.tv_sec;
	// 	printf("time %d", time2);
	// 	sleep(1);

	// }
	// gettimeofday(&cur_time, NULL);
	// time_in_mill2 =(cur_time.tv_sec) * 1000 + (cur_time.tv_usec) / 1000;

	// printf("%lld\n", time_in_mill2 - time_in_mill);
	sleep(100);
}