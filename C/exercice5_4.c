#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;

int *T1, *T2 ;
int n_T1, n_T2 ;

void* thread_generate_tableau(void* arg)
{
	srand(time(NULL)) ;
	int n = (int)arg ;
	int *tableau = malloc((n+1)*sizeof(int)) ;
	for (int i = 0; i < n; i++)
	{
		tableau[i] = rand() % 100 ;
	}
	printf("j'arrive a remplir le tableau de taille %d\n", n);
	pthread_exit((void*)tableau) ; 
}

//on appelle ce thread en c)
void* thread_verification_annulation(void* arg)
{
	char a ;
	while (1)
	{
		pthread_mutex_lock(&my_mutex) ;
		scanf("%c", &a) ;
		pthread_mutex_unlock(&my_mutex) ;	
		if (a == 'a')
		{
			printf("Annulation de programme\n") ;
			exit (0) ;
		}
	}
}

void* thread_verification_inclusion_tableau(void* arg)
{
	int resultat = 0 ;
	int j = 0 ;

	for (int i = 0; i <= n_T2 - n_T1; ++i)
	{
		for (j = 0; j < n_T1; ++j)
		{
			if (T2[i + j] != T1[j])
			{
				break ;
			}
		}
		if (j == n_T1)
		{
			resultat = 1 ;
			pthread_exit((void*)resultat) ;
		}
		sleep(2) ;
	}
	pthread_exit((void*)resultat) ;
}

int main(int argc, char const *argv[])
{
	pthread_t thread_1, thread_2 , thread_3;

	n_T1 = 4 ;
	n_T2 = 6 ;

	//pour la question c)
	pthread_create(&thread_3, NULL, thread_verification_annulation, (void*)NULL) ;
	pthread_create(&thread_1, NULL, thread_generate_tableau, (void*)n_T1) ;
	pthread_create(&thread_2, NULL, thread_generate_tableau, (void*)n_T2) ;

	sleep(2) ;

	pthread_join(thread_1, (void**)&T1) ;
	pthread_join(thread_2, (void**)&T2) ;

	int resultat = 0 ;
	pthread_create(&thread_1, NULL, thread_verification_inclusion_tableau, (void*)NULL) ;
	pthread_join(thread_1, (void*)&resultat) ;

	printf("T1 --> ");
	for (int i = 0; i < n_T1; ++i)
	{
		printf("%d ", T1[i]);
	}
	printf("\n") ;

	sleep(2) ;

	printf("T2 --> ");
	for (int i = 0; i < n_T2; ++i)
	{
		printf("%d ", T2[i]);
	}
	printf("\n") ;
	
	sleep(2) ;

	if (resultat == 1)
	{
		printf("T1 inclu dans T2\n") ;
	}
	else
	{
		printf("T1 n'est pas dans T2\n");
	}

	printf("\n") ;
	return 0;
}