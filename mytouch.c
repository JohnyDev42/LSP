#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<utime.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int i,fd;
	char a;
	if(argc<2){
		perror("Error");
		exit(0);
	}
	for(i=1;i<argc;i++){
//		fd=open(argv[i],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
		fd=openat(AT_FDCWD, argv[i], O_WRONLY|O_CREAT|O_NOCTTY|O_NONBLOCK, 0666);
//		utimensat(0,NULL,NULL,0);
		utime(argv[i],0); 
		close(0);
	}
}
