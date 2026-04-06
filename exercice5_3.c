#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;

typedef struct
{
	int *tableau ;
	int n ;
	int x ;
} TypeTableau ;

TypeTableau tab ;

void *thread_initialise(void *arg)
{
	srand(time(NULL)) ;

	pthread_mutex_lock(&my_mutex) ;

	tab.n = (int)arg ;
	tab.tableau = malloc(tab.n * sizeof(int)) ;
	for (int i = 0; i < tab.n; i++)
	{
		tab.tableau[i] = rand() % 100 ;
	}

	for (int i = 0; i < tab.n; i++)
	{
		printf("%d ", tab.tableau[i]);
	}
	printf("\n");

	pthread_mutex_unlock(&my_mutex) ;

	pthread_exit(NULL) ; 
}

void *thread_verification(void *arg)
{
	int ret = 0 ;

	pthread_mutex_lock(&my_mutex) ;

	for (int i = 0; i < tab.n; ++i)
	{
		if (tab.tableau[i] == tab.x)
		{
			ret = 1 ;
			pthread_exit((void*)ret) ;
			pthread_mutex_unlock(&my_mutex) ;

		}
	}

	pthread_mutex_unlock(&my_mutex) ;

	pthread_exit((void*)ret) ;
}

int main(int argc, char const *argv[])
{
	int ret ;
	pthread_t my_thread ;
	int n = 5 ;

	ret = pthread_create(&my_thread, NULL, thread_initialise, (void*)n) ;
	if (ret != 0)
	{
		fprintf(stderr, "erreur de création du thread\n");
		exit(1) ;
	}

	pthread_mutex_lock(&my_mutex) ;

	printf("entrez un entier x: ");
	scanf("%d", &tab.x) ;

	pthread_mutex_unlock(&my_mutex) ;

	pthread_join(my_thread, NULL) ;

	ret = pthread_create(&my_thread, NULL, thread_verification, NULL) ;
	if (ret != 0)
	{
		fprintf(stderr, "erreur de création du thread\n");
		exit(1) ;
	}
	pthread_join(my_thread, (void*)&ret) ;

	printf("resultat: %d\n", ret);
	return 0;
}