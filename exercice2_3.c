#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main()
{
	pid_t pid_fils ;
	int i = 0 ;
	for (i = 1; i <= 5; ++i)
	{
		pid_fils = fork() ;
		if (pid_fils == -1)
		{
			perror("Problème dans fork lors de création de fils\n") ;
			exit (errno) ;
		}
		else if (pid_fils == 0)
		{
			//printf("je suis le fils %d\n", i) ;
			break ;
		}
	}
	for (i = 1; i <= 5; ++i)
	{
		wait(NULL) ;
	}
	return (0) ;
}