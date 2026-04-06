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
	char* texte = malloc(50) ;
	pid_t fils ;
	while (1)
	{
		printf("Saisir un nom de repertoire:(taper quitter pour arrêter): ");
		scanf("%s", texte) ;
		if (strncmp(texte, "quitter", 7) == 0)
		{
			return (0) ;
		}
		fils = fork() ;
		if (fils == 0)
		{
			execlp("vim", "vim", texte, NULL) ;
		}
		else
		{
			wait(NULL) ;
		}
	}
	return 0;
}