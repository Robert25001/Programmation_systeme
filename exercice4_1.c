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
	pipe(descripteur_1) ;//pour la transmission de valeur retourner au fils
	pipe(descripteur_2) ;//pour la chaine de fils à père
	fils = fork() ;
	if (fils == 0)
	{
		printf("Saisir un mot: ");
		scanf("%s", chaine) ;//le fils saisit un mot au clavier
		close(descripteur_2[0]) ;
		write(descripteur_2[1], chaine, 50) ;

		int resultat ;
		close(descripteur_1[1]) ;
		read(descripteur_1[0], &resultat, sizeof(int)) ;
		printf("resultat: %d\n", resultat);
	}
	else if (fils > 0)//dans le père
	{
		int valeur ;
		close(descripteur_2[1]) ;
		read(descripteur_2[0], chaine_recu, 50) ;
		
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
		close(descripteur_1[0]) ;
		write(descripteur_1[1], &valeur, sizeof(int)) ;
		wait(NULL) ;
	}
	return 0;
}