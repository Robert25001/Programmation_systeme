#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void *ma_fonction_thread(void *arg)
{
	srand(time(NULL)) ;
	int n = 5 ;
	int *tableau = malloc((n+1)*sizeof(int)) ;
	tableau[0] = n ;
	for (int i = 1; i <=n; i++)
	{
		tableau[i] = rand() % 100 ;
	}
	printf("j'arrive a remplir le tableau\n");
	pthread_exit((void*)tableau) ; 
}

int main(int argc, char const *argv[])
{
	int ret ;
	pthread_t my_thread ;
	ret = pthread_create(&my_thread, NULL, ma_fonction_thread, NULL) ;
	if (ret != 0)
	{
		fprintf(stderr, "erreur de création du thread\n");
		exit(1) ;
	}
	int *tableau ;
	pthread_join(my_thread, (void**)&tableau) ;
	for (int i = 1; i <= tableau[0]; ++i)
	{
		printf("%d ", tableau[i]);
	}
	printf("\n");
	return 0;
}