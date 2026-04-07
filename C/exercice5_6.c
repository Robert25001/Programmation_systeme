#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#define N 100

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;

double tableau[N] ;

void* thread_remplacement(void* arg)
{
	srand(time(NULL)) ;
	int temps ;
	for (int i = 1; i < 99; ++i)
	{
		pthread_mutex_lock(&my_mutex) ;
		tableau[i] = (tableau[i-1]+tableau[i]+tableau[i+1]) / 3 ;
		pthread_mutex_unlock(&my_mutex) ;
		temps = rand() % 3 + 1 ;
		sleep(temps) ;
	}
	pthread_exit(NULL) ;
}

void* thread_affiche_tableau(void* arg)
{
	while (1)
	{
		sleep(4) ;
		printf("Affichage tableau: \n");
		pthread_mutex_lock(&my_mutex) ;
		for (int i = 0; i < N; ++i)
		{
			printf("tableau[%d] = %.3lf\n", i, tableau[i]);
		}
		pthread_mutex_unlock(&my_mutex) ;
		printf("\n");
	}
	pthread_exit(NULL) ;
}

int main(int argc, char const *argv[])
{
	srand(time(NULL)) ;

	tableau[0] = 0 ;
	tableau[99] = 0 ;

	for (int i = 1; i < 99; ++i)
	{
		tableau[i] = rand() % 101 ;
	}

	pthread_t thread_1, thread_2 ;

	pthread_create(&thread_1, NULL, thread_remplacement, (void*)NULL) ;
	pthread_create(&thread_2, NULL, thread_affiche_tableau, (void*)NULL) ;

	pthread_join(thread_1, NULL) ;
	pthread_join(thread_2, NULL) ;
	return 0;
}