#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	pid_t pid_fils ;
	pid_fils = fork() ;
	if (pid_fils == -1)
	{
		perror("Problème dans fork\n") ;
		exit (errno) ;
	}
	else if (pid_fils == 0)
	{
		printf("je suis le fils\n") ;
	}
	else
	{
		printf("je suis le père\n") ;
		wait(NULL) ;
		printf("fils terminé\n");
	}
	return (0) ;
}