#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<dirent.h>
int main(int argc,char *argv[]){
	int i,fd1,fd2,nread;
	char temp[1024];
//	fd1=open(argv[1],O_RDONLY);
//	fd2=open(argv[2],O_WRONLY|O_CREAT|O_EXCL|O_TRUNC,S_IRUSR|S_IWUSR);
	if(argc==1){
		write(1,"cp: missing file operand\n",20);
		exit(0);
	}
	else
	if(argc==2)
	{
		printf("cp: missing destination file operand after '%s'",argv[1]);
		exit(0);
	}
	else
		
	if(argc>2)
	{
		for(i=1;i<argc-1;i++){
			fd1=open(argv[i],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
			if(fd1<0){
				perror("Error");
				exit(0);
			}
			close(fd1);
		}
	}
	if(argc>3){
		DIR *pointer=NULL;
		pointer=opendir(argv[argc-1]);
		if(pointer==NULL){
			perror("Error");
			exit(0);
		}
		fd2=dirfd(pointer);
		if(fd>0){
			for(i=1;i<argc-1;i++){
				while(read())
			}
		}	
	}
	while((nread=read(fd1,temp,sizeof(temp)))>0)
		write(fd2,temp,nread);
	exit(0);
}
