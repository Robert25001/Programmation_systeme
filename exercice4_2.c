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
	pid_t fils ;
	char *nom_fich = "fichier", chaine[50], chaine_trouve[100], chaine_recu[50] ;
	char *sous_chaine ;
	int descripteur_1[2], descripteur_2[2] ;
	int saved_in, saved_out ;

	pipe(descripteur_1) ;//pour la transmission de valeur retourner au fils
	pipe(descripteur_2) ;//pour la chaine de fils à père
	fils = fork() ;
	if (fils == 0)
	{
		saved_out = dup(1) ;
		saved_in = dup(0) ;

		scanf("%s", chaine) ;//le fils saisit un mot au clavier

		close(descripteur_1[0]) ;
		dup2(descripteur_1[1], 1) ;
		close(descripteur_1[1]) ;
		puts(chaine) ;//envoie le mot saisi vers le père
		fflush(stdout) ;
		close(1) ;//débloque le père

		close(descripteur_2[1]) ;
		dup2(descripteur_2[0], 0) ;
		close(descripteur_2[0]) ;

		int resultat ;
		scanf("%d", &resultat) ;

		dup2(saved_out, 1) ;
		close(saved_out) ;
		close(saved_in) ;
		
		printf("resultat: %d\n", resultat);
	}
	else if (fils > 0)//dans le père
	{
		int valeur = 0 ;

		close(descripteur_1[1]) ;
		dup2(descripteur_1[0], 0) ;
		close(descripteur_1[0]) ;
		scanf("%s", chaine_recu) ;

		FILE* f = fopen(nom_fich, "r") ;
		fgets(chaine_trouve, 100, f  ) ;
		fclose(f) ;

		sous_chaine = strtok(chaine_trouve, " \n") ;
		while (sous_chaine != NULL)
		{
			if (strncmp(chaine_recu, sous_chaine, strlen(chaine_recu)) == 0)
			{
				valeur = 1 ;
				break ;
			}
			sous_chaine = strtok(NULL ," ") ;
		}

		close(descripteur_2[0]) ;
		dup2(descripteur_2[1], 1) ;
		close(descripteur_2[1]) ;
		printf("%d", valeur) ;//envoie la valeur retourner vers le fils
		fflush(stdout) ;
		close(1) ;//débloque le fils

		wait(NULL) ;
	}
	return 0;
}