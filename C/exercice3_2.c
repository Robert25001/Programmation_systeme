#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("argument invalide\n") ;
		return (0) ;
	}
	char *pwd = getenv("PWD") ;
	execlp("cp", "cp", "-r", pwd, argv[1], NULL) ;
	return 0;
}