#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	int fd ;
	pid_t fils ;
	int tube[2] ;

	pipe(tube) ;
	fils = fork() ;

	if (fils == 0)
	{
		char nomfich[50] ;
		close(tube[1]) ;
		read(tube[0], nomfich, sizeof(nomfich)) ;
		close(tube[0]) ;

		char *arg[] = {"exercice4_32", nomfich, NULL} ;
		execvp("./exercice4_32", arg) ;
	}
	else if (fils > 0)
	{
		char *nomfich = "/tmp/test.txt" ;
		close(tube[0]) ;
		write(tube[1], nomfich, sizeof(nomfich)) ;
		close(tube[1]) ;
		

		FILE *fp ;
		
		if (mkfifo(nomfich, 0644) != 0)
		{
			perror("Problème de création du noeud de tube") ;
			exit (1) ;
		}

		fd = open(nomfich, O_WRONLY) ;
		fp = fdopen(fd, "w") ;
		fprintf(fp, "coucou\n") ;

		wait(NULL) ;

		//unlink(nomfich) ;

	}
	
	return 0;
}