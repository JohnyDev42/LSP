#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
void *producer1(void *arg);
void *producer2(void *arg);
void *consumer1(void *arg);
void *consumer2(void *arg);

char buffer[5];
sem_t empty,full;
pthread_mutex_t prod,cons;

int main()
{
	pthread_t a_thread,b_thread,c_thread,d_thread;
	void * thread_result;
	int res;
	res=pthread_mutex_init(&prod,NULL);
	if(res!=0){
		perror("mutex");
	}
	pthread_mutex_init(&cons,NULL);
	res=sem_init(&empty,0,0);
	if(res!=0){
		perror("semaphre inialization");
		exit(EXIT_FAILURE);
	}
	sem_init(&full,0,5);

	res=pthread_create(&a_thread,NULL,producer1,NULL);
	if(res!=0){
		perror("thread creation failed");
		exit(EXIT_FAILURE);
	}
	res=pthread_create(&b_thread,NULL,producer2,NULL);
	if(res!=0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	} 
	res=pthread_create(&c_thread,NULL,consumer1,NULL);
	if(res!=0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	res=pthread_create(&d_thread,NULL,consumer2,NULL);
	if(res!=0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	printf("Wait for thread join\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	res=pthread_join(b_thread,&thread_result);
	if(res!=0){
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}
	res=pthread_join(c_thread,&thread_result);
	printf("Thread joined \n");
	exit(EXIT_SUCCESS);
}
void *producer1(void *arg)
{
	int in=0;
	char ch='A';
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&prod);
		buffer[in]=ch;
		in=(in+1)%5;
		ch++;
		if(in==0)
		{
			ch='A';
			printf("p1:%s\n",buffer);
		}
	//	pthread_mutex_unlock(&prod);
		sem_post(&full);
		pthread_mutex_unlock(&prod);
	}
	pthread_exit("exit");
}
void *producer2(void *arg)
{
	int in=0;
	char ch='a';
	while(1)
	{
		sem_wait(&empty);
		pthread_mutex_lock(&prod);
		buffer[in]=ch;
		in=(in+1)%5;
		ch++;
		if(in==0)
		{
			ch='a';
			printf("p2:%s\n",buffer);
		}
	//	sleep(1);
	//	pthread_mutex_unlock(&prod);
		sem_post(&full);
		pthread_mutex_unlock(&prod);
	}
	pthread_exit("exit");
}
void *consumer1(void *arg)
{
	int out=0;
	char temp[5];
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&prod);
		temp[out]=buffer[out];
		out=(out+1)%5;
		if(out==0)
		{
			printf("\tc1:%s\n",buffer);
		}
	//	sleep(1);
	//	pthread_mutex_unlock(&prod);
		sem_post(&empty);
		pthread_mutex_unlock(&prod);
	}
	pthread_exit("exit");
}
void *consumer2(void *arg)
{
	int out=0;
	char temp[5];
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&prod);
		temp[out]=buffer[out];
		out=(out+1)%5;
		if(out==0)
		{
			printf("\tc2:%s\n",buffer);
		}
	//	pthread_mutex_unlock(&prod);
		sem_post(&empty);
		pthread_mutex_unlock(&prod);
	}
	pthread_exit("exit");
}
