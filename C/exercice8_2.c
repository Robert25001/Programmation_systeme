#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX 256
#define PORT 33000
#define FICHIER_AUTH "add_autoris.txt"

// a)
//retourne 1 si trouver, 0 sinon
int est_ip_autorisee(char *ip)
{
    FILE *fp ;
    char ligne[MAX];
    
    fp = fopen(FICHIER_AUTH, "r") ;

    if (fp == NULL)
    {
        printf("Fichier %s non trouve, acces refuse\n", FICHIER_AUTH);
        return 0;
    }
    
    while (fgets(ligne, sizeof(ligne), fp) != NULL)
    {
        ligne[strcspn(ligne, "\n")] = '\0';  //remplaçant \n par \0
        if (strcmp(ligne, ip) == 0)
        {
            fclose(fp);
            return 1;
        }
    }
    
    fclose(fp);
    return 0;
}

void traite_connection(int sock, struct sockaddr_in *client)
{
    char bufferW[MAX];
    char *client_ip = inet_ntoa(client->sin_addr) ;
    
    if (est_ip_autorisee(client_ip) == 0)
    {
        sprintf(bufferW, "Acces refuse: IP %s non autorisee\n", client_ip) ;
        write(sock, bufferW, strlen(bufferW)) ;
        close(sock) ;
        return ;
    }
    
    sprintf(bufferW, "Bienvenue! Votre IP %s est autorisee\n", client_ip);
    write(sock, bufferW, strlen(bufferW));

    close(sock);
}

int main()
{
    int sock_contact, sock_connectee ;
    struct sockaddr_in adresse, client_addr;
    socklen_t longueur;
    pid_t pid_fils;
    
    sock_contact = socket(AF_INET, SOCK_STREAM, 0) ;
    if (sock_contact < 0)
    {
        perror("Erreur socket");
        return -1;
    }
    
    memset(&adresse, 0, sizeof(adresse));
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(PORT);
    adresse.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(sock_contact, (struct sockaddr*)&adresse, sizeof(adresse)) < 0)
    {
        perror("Erreur bind");
        return -1;
    }
    
    listen(sock_contact, 5);
    printf("Serveur en ecoute sur le port %d\n", PORT);
    
    while (1)
    {
        longueur = sizeof(client_addr);
        sock_connectee = accept(sock_contact, (struct sockaddr*)&client_addr, &longueur) ;

        if (sock_connectee < 0)
        {
            perror("Erreur accept");
            continue;
        }
        
        pid_fils = fork() ;

        if (pid_fils == 0)
        {
            close(sock_contact);
            traite_connection(sock_connectee, &client_addr);
            exit(0);
        }
        else
        {
            close(sock_connectee);
        }
    }
    
    return 0;
}

// b)
//retourne 1 si trouver, 0 sinon
char* est_ip_autorisee(char *ip)
{
    FILE *fp ;
    char ligne[MAX] ;
    char ip_tmp[MAX] ;
    char nom[MAX] ;
    
    fp = fopen(FICHIER_AUTH, "r") ;

    if (fp == NULL)
    {
        printf("Fichier %s non trouve, acces refuse\n", FICHIER_AUTH);
        return NULL;
    }
    
    while (fgets(ligne, sizeof(ligne), fp) != NULL)
    {
        sscanf(ligne, "%s %s", ip_tmp, nom) ;
        if (strncmp(ip_tmp, ip, strlen(ip)) == 0)
        {
            fclose(fp) ;
            return (nom) ;
        }
    }
    
    fclose(fp);
    return NULL;
}

void traite_connection(int sock, struct sockaddr_in *client)
{
    char bufferW[MAX];
    char *nom ;
    char *client_ip = inet_ntoa(client->sin_addr) ;
    
    nom = est_ip_autorisee(client_ip) ;

    if ( nom == NULL)
    {
        sprintf(bufferW, "Acces refuse: IP %s non autorisee\n", client_ip) ;
        write(sock, bufferW, strlen(bufferW)) ;
        close(sock) ;
        return ;
    }
    
    sprintf(bufferW, "Bienvenue %s! Votre IP %s est autorisee\n", nom, client_ip);
    write(sock, bufferW, strlen(bufferW));

    close(sock);
}