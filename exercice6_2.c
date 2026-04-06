#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char**argv)
{
	DIR* dir ;
	struct stat st; /* pour récupérer les informations sur un fichier */
	struct dirent *ent;
	char chemin[1024] ;

	if (argc == 1)
	{
		fprintf(stderr, "Usage : %s nom_de_repertoire\n", argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; ++i)
	{
		dir = opendir(argv[i]) ;
		if (dir == NULL)
		{
			fprintf(stderr, "Erreur d'ouverture du réperoire %s\n",argv[i]);
			fprintf(stderr, "Droits inssufisant ou répertoire incorrect\n");
			continue ;
		}
		printf("Répertoire %s:\n", argv[i]);
		while ((ent = readdir(dir)) != NULL)
		{
			snprintf(chemin, sizeof(chemin), "%s/%s", argv[i], ent->d_name) ;
			if (stat(chemin, &st)!= 0)
			{
				perror("Erreur d'accès au fichier\n");
				continue ;
			}
			if (st.st_size >= (1024*1024))
			{
				printf("%s : UID du propriétaire du fichier %d, taille: %.2f Mo\n", ent->d_name, st.st_uid, (float)st.st_size/(1024*1024));
			}
		}
	}
	
	return 0;
}