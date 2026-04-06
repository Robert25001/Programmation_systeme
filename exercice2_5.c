#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

int main()
{
	srand(time(NULL)) ;
	time_t debut, fin ;
	debut = time(NULL) ;

	pid_t fils;
	int i = 0 ;
	for (i = 1; i <= 2; ++i)
	{
		fils = fork() ;
		if (fils == -1)
		{
			perror("Erreur de fork\n") ;
			exit(errno) ;
		}
		else if (fils == 0)
		{
			int temps = (rand() % 10) + 1 ;
			printf("je suis le fils %d\n", i);
			sleep(temps) ;
			printf("fils %d terminé après %d second\n", i, temps);
			return (0) ;
		}
	}
	for (i = 1; i <= 2; ++i)
	{
		wait(NULL) ;
	}
	fin = time(NULL) ;
	printf("La durée totale d'execution est %ld\n", fin - debut);
	return (0) ;
}