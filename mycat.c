#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	char temp[1];
	int i,*fd=(int*)malloc(sizeof(int));
	for(i=1;i<argc;i++){
		fd=realloc(fd,sizeof(int));
		fd[i]=open(argv[i],O_RDONLY);
		if(fd[i]<0){
			printf("cat: %s: No such file or directory",argv[i]);
			continue;
		}
		while(read(fd[i],temp,1)==1)
                write(1,temp,1);
		
	}
	if(argc==1)
	{
		while(read(0,temp,1)==1)
			write(1,temp,1);
	}
}
