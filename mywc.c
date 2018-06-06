#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	char c,p=' ';
	int i,fd,tline=0,tword=0,tbyte=0;
	for(i=1;i<argc;i++){

		int line=0,word=0,byte=0;
		fd=open(argv[i],O_RDONLY);
		if(fd==-1){
			perror("wc");
			continue;
		}
		while(read(fd,&c,1)){
			if(c=='\n')
				line++;
			if(((c==' ')||(c=='\n'))&&(!((p==' ')||(p=='\n'))))
			{	word++;
		 		//printf("%dw\n",word);
			}
			p=c;
			byte++;
		}
		printf("%d  %d  %d  %s\n",line,word,byte,argv[i]);
		tline+=line;
		tword+=word;
		tbyte+=byte;
	}
	if(argc>2)
		printf("%d  %d  %d  total\n",tline,tword,tbyte);
}

