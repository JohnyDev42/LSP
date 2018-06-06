#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc,char *argv[]){
	int i,fd,line,line1;
	char a;

	for(i=1;i<argc;i++){
		fd=open(argv[i],O_RDONLY);
		if(argc>2){
			printf("==>%s<==\n",argv[i]);
		}
		if(fd<0){
			perror("Error");
			continue;
		}
		for(line=0;read(fd,&a,1);){
			if(a=='\n')
				line++;
		}
		close(fd);
		fd=open(argv[i],O_RDONLY);
		
		for(line1=0;read(fd,&a,1);){
			if(a=='\n')
				line1++;
			if(line1>line-10)
			write(1,&a,1);
		}
//		printf("%d\n",line1);
	}
}
