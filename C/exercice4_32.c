#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int fd ;
	FILE *fp ;
	char chaine[50] ;
	fd = open(argv[1], O_RDONLY) ;
	fp = fdopen(fd, "r") ;
	fscanf(fp, "%s\n", chaine) ;
	puts(chaine) ;
	unlink(argv[1]) ;
	return 0;
}