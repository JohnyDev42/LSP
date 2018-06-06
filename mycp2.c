#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc,char *argv[]){
	int fd1,fd2,nread;
	char temp[1024];
	fd1=open(argv[1],O_RDONLY);
	fd2=open(argv[2],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	
	if(fd1&&!(argc==3))
	{
		printf("cp: missing destination file operand after %s",argv[1]);
		exit(0);
	}
	if(fd1<0)
	{
		printf("cp: cannot stat %s: No such file or directory",argv[1]);
		exit(0);
	}
	while(nread=read(fd1,temp,sizeof(temp))>0)
		write(fd2,temp,nread);
	exit(0);
}
