#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;

int compt ;

void* thread_iteration(void* arg)
{
	int compteur_max = (int)arg ;
	srand(time(NULL)) ;
	int temps ;

	while (1)
	{
		pthread_mutex_lock(&my_mutex) ;
		if (compt > compteur_max)
		{
			exit (0) ;
		}
		compt++ ;
		pthread_mutex_unlock(&my_mutex) ;
		temps = rand() % 5 + 1 ;
		sleep(temps) ;
	}
}

void* thread_affiche_compteur(void* arg)
{
	int compteur_max = (int)arg ;

	while(1)
	{
		pthread_mutex_lock(&my_mutex) ;
		if (compt > compteur_max)
		{
			exit (0) ;
		}
		printf("compteur: %d\n", compt) ;
		pthread_mutex_unlock(&my_mutex) ;
		sleep(2) ;
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("Utilisation: %s nombre\n", argv[0]) ;
		return (0) ;
	}

	pthread_t thread_1, thread_2 ;
	int compteur_max = atoi(argv[1]) ;

	pthread_create(&thread_1, NULL, thread_iteration, (void*)compteur_max) ;
	pthread_create(&thread_2, NULL, thread_affiche_compteur, (void*)compteur_max) ;

	pthread_join(thread_1, NULL) ;
	pthread_join(thread_2, NULL) ;

	return 0;
}