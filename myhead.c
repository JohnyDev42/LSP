#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main(int argc,char *argv[]){
	int i,fd,line;
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
		for(line=0;line<10&&(read(fd,&a,1));){
			if(a=='\n')
				line++;
			write(1,&a,1);
		}
	}
}
