#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void ouch(int signo){
	printf("OUCH!! I got a signal no.%d\n",signo);
	signal(SIGKILL,SIG_DFL);
	signal(SIGINT,SIG_DFL);
}
int main()
{
	signal(SIGKILL,ouch);
	while(1){
		printf("Hello ! World...\n");
		sleep(1);
	}
}
