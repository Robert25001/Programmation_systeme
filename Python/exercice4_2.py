import os
import sys
import time

def main():
    pipe_1 = os.pipe()
    pipe_2 = os.pipe() 
    
    pid = os.fork()
    
    if pid == 0:
        saved_stdin = os.dup(0)  
        saved_stdout = os.dup(1) 
        
        # Saisie utilisateur
        chaine = input("Saisir un mot: ")
        
        os.close(pipe_1[0])     
        os.dup2(pipe_1[1], 1)
        os.close(pipe_1[1])
        
        # Envoyer la chaîne vers le père
        print(chaine)
        sys.stdout.flush()
        os.close(1)                    # Fermer stdout pour débloquer
        
        os.close(pipe_2[1])         
        os.dup2(pipe_2[0], 0)
        os.close(pipe_2[0])
        
        resultat = int(input())
        
        os.dup2(saved_stdout, 1)
        os.close(saved_stdout)
        os.close(saved_stdin)
        
        print(f"resultat: {resultat}")
        
    else:
        os.close(pipe_1[1])
        os.dup2(pipe_1[0], 0)
        os.close(pipe_1[0])
        
        # Lire la chaîne envoyée par le fils
        chaine_recu = input()
        
        # Recherche du mot dans le fichier
        nom_fichier = "fichier"
        valeur = 0
        
        with open(nom_fichier, 'r') as f:
            chaine_trouve = f.readline()

        mots = chaine_trouve.split()

        for mot in mots:
            if mot.startswith(chaine_recu) == 1:
                valeur = 1
                break
        
        os.close(pipe_2[0])
        os.dup2(pipe_2[1], 1)
        os.close(pipe_2[1])
        
        # Envoyer le résultat
        print(valeur)
        sys.stdout.flush()
        os.close(1) # Fermer stdout pour débloquer
        
        # Attendre la fin du fils
        os.wait()

if __name__ == "__main__":
    main()