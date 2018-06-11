/* Thread Synchonization using Signals */

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<pthread.h>
char buf[26];
sigset_t set;

pthread_t a_thread,b_thread;
void produ(int signo)
{
	sleep(1);
}
void consu(int signo)
{
//	printf("Buffer Empty\n");
//	sleep(1);
}
void *producer(void *arg)
{
	int in=0;
	char ch='A';
	signal(SIGUSR2,produ);
	while(1)
	{
		buf[in]=ch;
		in=(in+1)%26;
		if(in==0)
		{
			printf("pro:%s\n",buf);
			ch='A';
			pthread_kill(b_thread,SIGUSR1);
			pause();
		}
		else
			ch++;
	}


}
void *consumer(void *arg)
{
	int out=0;
	char buff[26];
	signal(SIGUSR1,consu);
		while(1)
		{
			buff[out]=buf[out];
			out=(out+1)%26;
			if(out==0){
				printf("\tcon:%s\n",buff);
				pthread_kill(a_thread,SIGUSR2);
				pause();
			}
		}
	
}
int main()
{
	int res;
	void *thread_result;

//	signal(SIGUSR2,consu);
//	signal(SIGUSR1,produ);
	res=pthread_create(&a_thread,NULL,producer,NULL);
	if(res!=0){
		perror("Thread create");
		exit(EXIT_FAILURE);
	}
	res=pthread_create(&b_thread,NULL,consumer,NULL);
	if(res!=0)
	{
		perror("thread create");
		exit(0);
	}
	printf("Waiting for thread to join\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0){
		perror("thread join");
		exit(EXIT_FAILURE);
	}

	res=pthread_join(b_thread,&thread_result);
	if(res!=0){
		perror("thread join");
		exit(EXIT_FAILURE);
	}
	printf("Thread Joined\n");
	exit(EXIT_SUCCESS);
}
