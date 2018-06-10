#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	char buff[50];
	printf("$");
	fgets(buff,50,stdin);
	system(buff);
}
