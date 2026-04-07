import os
import sys
import struct
import time

def main():
    descripteur_1 = os.pipe() 
    descripteur_2 = os.pipe()
    
    pid = os.fork()
    
    if pid == 0:
        chaine = input("Saisir un mot: ")
        os.close(descripteur_2[0])
        os.write(descripteur_2[1], chaine.encode())
        
        os.close(descripteur_1[1])
        data = os.read(descripteur_1[0], 4)
        resultat = struct.unpack('i', data)[0]
        
        print(f"resultat: {resultat}")
        
    else:
        os.close(descripteur_2[1])
        
        chaine_recu_bytes = os.read(descripteur_2[0], 50)
        chaine_recu = chaine_recu_bytes.decode('utf-8').rstrip('\x00')

        nom_fichier = "fichier"
        with open(nom_ficier, 'r') as f:
            chaine_trouve = f.readline()

        mots = chaine_trouve.split()

        valeur = 0
        for mot in mots:
            if mot.startswith(chaine_recu) == 1:
                valeur = 1
                break
        
        os.close(descripteur_1[0])
        os.write(descripteur_1[1], struct.pack('i', valeur))

        os.wait()        
        

if __name__ == "__main__":
    main()