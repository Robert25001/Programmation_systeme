#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int numero_fils = 0 ;

int main()
{
	pid_t pid_fils ;
	int i = 0 ;
	for (i = 1; i <= 5; ++i)
	{
		numero_fils++ ;
		pid_fils = fork() ;
		if (pid_fils == 0)
		{
			printf("je suis le fils %d\n", numero_fils) ;
			return (0) ;
		}
	}
	for (i = 1; i <= 5; ++i)
	{
		wait(NULL) ;
	}
	return (0) ;
}