#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void *ma_fonction_thread(void *arg)
{
	int *tableau = (int *)arg;
	int n = tableau[0] ;
	printf("affichage des contenus de tableau passé en paramètre\n");
	for (int i = 1; i <=n; ++i)
	{
		printf("%d ", tableau[i]);
	}
	printf("\n");
	pthread_exit(NULL); 
}

int main(int argc, char const *argv[])
{
	int ret ;
	int tableau[] = {5, 2, 4, 6, 8, 10} ;
	pthread_t my_thread ;
	ret = pthread_create(&my_thread, NULL, ma_fonction_thread, (void*)tableau) ;
	if (ret != 0)
	{
		fprintf(stderr, "erreur de création du thread\n");
		exit(1) ;
	}
	pthread_join(my_thread, NULL) ;
	return 0;
}