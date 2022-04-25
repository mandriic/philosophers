#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>   
#include <sys/types.h> 
#include <stdlib.h>
// #define SEM_MUTEX_NAME ""
sem_t *mutex_sem;
void ft_philosofo(int proc, sem_t *sem)
{
	int i = 0;

	sem_wait(sem);
	sleep(1);


	while (i++ < 30)
		printf("proc%d %d pid %d ppid %d \n",proc, i, getpid(), getppid());
	sleep(3);
	sem_post(sem);

}
// void ft_philosofo2(int *vars)
// {
// 	int i = 0;

// 	while (i++ != 10)
// 		printf("im filosofo.%d %d\n", getpid(), vars[0]);
// 	sleep(1);
// }
int main(void)
{
	int proc[10];
	int first_f;
	int second_f;
	int	vars[10];
	vars[1] = 1;
	vars[2] = 2;
	vars[3] = 3;
	int		test = 0;
			sem_t *mutex_sem;
			sem_t *mutex_sem4;
			// sem_t sem2;


	int i = 0;
mutex_sem4 = sem_open ("sem", O_CREAT | O_EXCL, 0644, 1);
// mutex_sem = sem_open ("/sem-mutex", O_CREAT,  0);
sem_unlink ("sem");  
first_f = fork();
	if (first_f == 0)
	{
		while (i != 3)
		{
			proc[i] = fork();
			if (proc[i] == 0)
			{
				break ;
			}
			// printf("PROCESES!!!!!!!%d\n", proc[i]);
		i++;
		}
		ft_philosofo(proc[i], mutex_sem4);
	}

	else
	{
		sleep(1);
	

	// sem_wait(mutex_sem4);
	// printf("i am philosofo n %d take fork\n", getpid());
	// sleep(1);
	//  sem_post(mutex_sem4);
	// // 
	sem_close(mutex_sem4);

	// // sem_wait(mutex_sem);
	// // printf("i am philosofo n %d take fork\n", getpid());
	// //  sem_post(mutex_sem);
	// //  sem_destroy(mutex_sem);
	 sem_destroy(mutex_sem4);

		// sleep(5);
		// 		return(0);

		
	// }
	 printf("im ,main %d\n", getpid());


	// sleep(10);
	exit(0);
	}
	
		
return (0);

}