#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT        9999
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage : %s chemin_fichier\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Erreur ouverture fichier");
        exit(1);
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("Erreur socket");
        exit(1);
    }

    struct sockaddr_in adresse ;
    memset(&adresse, 0, sizeof(adresse));
    adresse.sin_family = AF_INET;
    adresse.sin_port   = htons(PORT);
    inet_aton("127.0.0.1", &adresse.sin_addr) ;

    if (connect(sock, (struct sockaddr*)&adresse, sizeof(adresse)) < 0)
    {
        perror("Erreur connect");
        exit(1);
    }
    printf("Connecté au serveur. Envoi de : %s\n", argv[1]);

    char buffer[BUFFER_SIZE];
    int  n;

    while ((n = fread(buffer, 1, BUFFER_SIZE, fp)) > 0)
    {
        write(sock, buffer, n);
    }

    printf("Fichier envoyé.\n");

    fclose(fp);
    close(sock);
    return 0;
}