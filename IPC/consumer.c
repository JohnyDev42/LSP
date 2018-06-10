
       #include <fcntl.h>           /* For O_* constants */
       #include <sys/stat.h>        /* For mode constants */
       #include <semaphore.h>

#include <stdio.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
sem_t bin_sem;
int main()
{
	sem_t * res;
	int shmid;
	char *msg;
	res=sem_open("mysem",O_CREAT|O_EXCL,0666,2);
	if(res==SEM_FAILED){
		perror("semopen");
	}
	    sem_unlink ("mysem"); 
	if((shmid=shmget(10,1024,0))==-1) {
		perror("shmget");
		exit(1);
	}
	sem_wait(res);
	msg=shmat(shmid,0,0);
	
	printf("Data written in the shared memory is:%s\n",msg);
	sem_post(res);
	getchar();
	shmdt(msg);
}
	
/**/	
