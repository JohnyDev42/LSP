#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
int alarm_fired=0;
void ding(int sig){
	alarm_fired=1;
}
int main()
{
	pid_t pid;
	printf("Alarm Program started>>>");
	pid=fork();
	switch(pid)
	{
		case -1:fprintf(stderr,"fork failed");
			exit(1);
		case 0://fprintf(stdin,"I am Child:PID=%d\n",getpid());
		       printf("I am sleeping for 5sec:%d\n",getpid());
	//	       sleep(5);
		       kill(getpid(),SIGALRM);
		       exit(0);
	}
	/* if we got here we are parent process */
	printf("Waiting for Alarm for go off\n");
	(void)signal(SIGALRM,ding);
//	pause();
	if(alarm_fired)
		printf("Ding!!!\n");
	printf("Done!\n");
	exit(0);
}
