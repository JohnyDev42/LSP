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
	fd2=open(argv[2],O_WRONLY|O_TRUNC|O_EXCL);
//	for(i=1;i)
	if(fd1&&!(argc<3))
	{
		printf("cp: missing destination file operand after %s",argv[1]);
		exit(0);
	}
	if(fd1<0)
	{
		perror("cp:");
		exit(0);
	}
	if(fd2<0)
	{
		creat(argv[2],S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
	}
	fd2=open(argv[2],O_WRONLY);	
	while((nread=read(fd1,temp,sizeof(temp)))>0)
		write(fd2,temp,nread);
	close(fd1);
	close(fd2);
	exit(0);
}
