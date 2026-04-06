#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	if (argc < 3 || argc > 3)
	{
		printf("argument invalide\n") ;
		return (0) ;
	}
	int a = atoi(argv[1]) , b = atoi(argv[2]) ;
	printf("Leur somme: %d\n", a + b);
	return 0;
}