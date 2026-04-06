#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	execlp("vim", "vim", argv[1], NULL) ;
	return 0;
}