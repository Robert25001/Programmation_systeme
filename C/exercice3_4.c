#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

int main()
{
	char* repertoire = malloc(50) ;
	char *pwd = getenv("PWD") ;
	pid_t fils ;
	while (1)
	{
		printf("Saisir un nom de repertoire:(taper quitter pour arrêter): ");
		scanf("%s", repertoire) ;
		if (strncmp(repertoire, "quitter", 7) == 0)
		{
			return (0) ;
		}
		fils = fork() ;
		if (fils == 0)
		{
			execlp("cp", "cp", "-r", pwd, repertoire, NULL) ;
		}
		else if (fils > 0)
		{
			wait(NULL) ;
		}
	}
	return 0;
}