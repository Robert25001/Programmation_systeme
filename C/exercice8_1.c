#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>

#define PORT 33000
#define MAX_PRODUITS 100
#define MAX_NOM 256

 // a)
typedef struct
{
    char nom[MAX_NOM];
    float prix;
} Produit;

// b)
int charger_base_donnees(char *fichier, Produit *produits, int max_produits)
{
    FILE *fp;
    char ligne[200];
    int count = 0;
    
    fp = fopen(fichier, "r") ;

    if (fp == NULL)
    {
        perror("Erreur ouverture fichier");
        return (-1);
    }
    
    while (fgets(ligne, sizeof(ligne), fp) != NULL && count < max_produits)
    {
        if (sscanf(ligne, "%s %f", produits[count].nom, &produits[count].prix) == 2) {
            count++;
        }
    }
    
    fclose(fp);
    return count;
}

// c)
Produit* chercher_produit(Produit *produits, int nb_produits, char *nom)
{
    for (int i = 0; i < nb_produits; i++)
    {
        if (strcasecmp(produits[i].nom, nom) == 0)
        {
            return &produits[i];
        }
    }
    return NULL;
}

// d)
Produit produits[MAX_PRODUITS] ;
int nb_produits = 0 ;

void traite_client(int sock)
{
    char bufferR[MAX_NOM] ;
    char bufferW[MAX_NOM] ;
    char nom_produit[MAX_NOM] ;
    int quantite;
    Produit *p;
    float total;
    
    sprintf(bufferW, "Bienvenue! Entrez nom produit et quantite (ex: pomme 5): ") ;
    write(sock, bufferW, strlen(bufferW));
    
    while (1)
    {
        memset(bufferR, 0, MAX_NOM) ;
        int nb = read(sock, bufferR, MAX_NOM) ;
        if (nb <= 0)
        {
            break;
        }
        
        bufferR[nb-1] = '\0';
        
        if (sscanf(bufferR, "%s %d", nom_produit, &quantite) == 2)
        {
            p = chercher_produit(produits, nb_produits, nom_produit);
            if (p != NULL)
            {
                total = p->prix * quantite;
                sprintf(bufferW, "Produit: %s, Quantite: %d, Total: %.2f Ar\n", nom_produit, quantite, total);
            }
            else
            {
                sprintf(bufferW, "Produit '%s' non trouve\n", nom_produit);
            }
        }
        else
        {
            sprintf(bufferW, "Format incorrect. Utilisez: nom_produit quantite\n");
        }
        write(sock, bufferW, strlen(bufferW));
    }
    
    close(sock);
    exit(0);
}

int main() {
    int sock_contact, sock_connectee;
    struct sockaddr_in adresse;
    socklen_t longueur;
    pid_t pid_fils;
    
    nb_produits = charger_base_donnees("produits.txt", produits, MAX_PRODUITS);
    printf("%d produits charges\n", nb_produits);
    
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
        longueur = sizeof(adresse);
        sock_connectee = accept(sock_contact, (struct sockaddr*)&adresse, &longueur) ;
        if (sock_connectee < 0)
        {
            perror("Erreur accept");
            continue;
        }
        
        pid_fils = fork() ;

        if (pid_fils == 0)
        {
            close(sock_contact);
            traite_client(sock_connectee);
        }
        else
        {
            close(sock_connectee);
        }
    }
    
    close(sock_contact);
    return (0) ;
}

// e)
void traite_client_multiproduits(int sock)
{
    char bufferR[MAX_NOM] ;
    char bufferW[MAX_NOM] ;
    char ligne[MAX_NOM] ;
    char nom_produit[MAX_NOM] ;
    int quantite ;
    Produit *p ;
    float total_general = 0;
    
    sprintf(bufferW, "Entrez vos commandes (une par ligne, 'fin' pour terminer):\n");
    write(sock, bufferW, strlen(bufferW)) ;
    
    while (1)
    {
        memset(bufferR, 0, MAX_NOM) ;
        int nb = read(sock, bufferR, MAX_NOM) ;

        if (nb <= 0)
        {
            break;
        }

        bufferR[nb-1] = '\0';
        
        if (strcasecmp(bufferR, "fin") == 0)
        {
            sprintf(bufferW, "Total general: %.2f Ar\n", total_general) ;
            write(sock, bufferW, strlen(bufferW));
            break ;
        }
        
        if (sscanf(bufferR, "%s %d", nom_produit, &quantite) == 2)
        {
            p = chercher_produit(produits, nb_produits, nom_produit) ;
            if (p != NULL)
            {
                float total = p->prix * quantite ;
                total_general += total ;
                continue ;
            }
            else 
            {
                sprintf(bufferW, "Produit '%s' non trouve\n", nom_produit);
            }
        }
        else
        {
            sprintf(bufferW, "Format: nom_produit quantite\n");
        }
        write(sock, bufferW, strlen(bufferW));
    }
}

// f)
//on implemente cette fonction dans traite_client
void sauvegarder_commande(int sock, char *client_ip, char *commande, float total)
{
    char nom_fichier[100] ;
    FILE *fp ;
    time_t t ;
    struct tm *tm_info ;
    
    time(&t) ;
    tm_info = localtime(&t) ;
    
    sprintf(nom_fichier, "./commande_%04d%02d%02d_%02d%02d%02d.txt",
            tm_info->tm_year + 1900, tm_info->tm_mon + 1, tm_info->tm_mday,
            tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);
    
    
    fp = fopen(nom_fichier, "w") ;

    if (fp != NULL)
    {
        fprintf(fp, "Client IP: %s\n", client_ip) ;
        fprintf(fp, "Date: %s", ctime(&t)) ;
        fprintf(fp, "Commande: %s\n", commande) ;
        fprintf(fp, "Total: %.2f Ar\n", total) ;
        fclose(fp);
    }
}