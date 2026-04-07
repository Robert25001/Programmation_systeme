#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define PORT        9999
#define BUFFER_SIZE 256

void traite_connexion(int sock_client)
{
    struct sockaddr_in info_client;
    socklen_t longueur = sizeof(info_client);

    if (getpeername(sock_client,(struct sockaddr*)&info_client,&longueur) < 0)
    {
        perror("Erreur getpeername");
        return;
    }

    char ip_client[50];
    strcpy(ip_client, inet_ntoa(info_client.sin_addr));
    printf("Connexion de : %s\n", ip_client);

    time_t maintenant = time(NULL);
    struct tm *date   = localtime(&maintenant);

    int annee = date->tm_year + 1900;
    int mois  = date->tm_mon  + 1;
    int jour  = date->tm_mday;

    char nom_fichier[200];
    sprintf(nom_fichier, "/home/save/%s_%04d_%02d_%02d.txt",ip_client, annee, mois, jour);
    printf("Sauvegarde dans : %s\n", nom_fichier);

    system("mkdir -p /home/save") ;

    FILE *fp = fopen(nom_fichier, "w");

    if (fp == NULL)
    {
        perror("Erreur création fichier sauvegarde");
        return;
    }

    char buffer[BUFFER_SIZE];
    int  n;

    while ((n = read(sock_client, buffer, BUFFER_SIZE)) > 0)
    {
        fwrite(buffer, 1, n, fp);
    }

    printf("Fichier sauvegardé avec succès.\n");
    fclose(fp);
}

int main(void)
{
    int sock_ecoute = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ecoute < 0)
    {
        perror("Erreur socket");
        exit(1);
    }

    struct sockaddr_in adresse;
    memset(&adresse, 0, sizeof(adresse));
    adresse.sin_family      = AF_INET;
    adresse.sin_port        = htons(PORT);
    adresse.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_ecoute,(struct sockaddr*)&adresse,sizeof(adresse)) < 0)
    {
        perror("Erreur bind");
        exit(1);
    }

    listen(sock_ecoute, 5);
    printf("Serveur en attente sur le port %d...\n", PORT);

    while (1)
    {
        struct sockaddr_in adresse_client;
        socklen_t longueur = sizeof(adresse_client);

        int sock_client = accept(sock_ecoute,(struct sockaddr*)&adresse_client,&longueur);
        if (sock_client < 0)
        {
            perror("Erreur accept");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0)
        {
            close(sock_ecoute);
            traite_connexion(sock_client);
            close(sock_client);
            exit(0);
        }
        else
        {
            close(sock_client);
        }
    }

    return 0;
}