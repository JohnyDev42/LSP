 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <fcntl.h>
#include<stdio.h>
int main(int argc,char *argv[]){
	int i,fd;
	struct stat buf;

	for(i=1;i<argc;i++){
		fd=open(argv[i],O_RDWR);
		lstat(argv[i],&buf);
		fstat(fd,&buf);
	//	lstat(fd,&buf);
		printf("%ld\t%s\n",buf.st_blocks/2,argv[i]);
	}
}
