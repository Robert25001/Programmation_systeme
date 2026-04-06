#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	pid_t fils_1, fils_2 ;
	fils_1 = fork() ;
	if (fils_1 == -1)
	{
		perror("Problème dans fork lors de création de fils 1\n") ;
		exit (errno) ;
	}
	else if (fils_1 == 0)
	{
		printf("je suis le fils 1\n") ;
	}
	else
	{
		printf("je suis le père\n") ;
		wait(NULL) ;
		printf("fils 1 terminé\n");
		fils_2 = fork() ;
		if (fils_2 == -1)
		{
			perror("Problème dans fork lors de création de fils 2\n") ;
			exit (errno) ;
		}
		else if (fils_2 == 0)
		{
			printf("je suis le fils 2\n") ;
		}
		else
		{
			wait(NULL) ;
			printf("fils 2 terminé\n");

		}
	}
	return (0) ;
}