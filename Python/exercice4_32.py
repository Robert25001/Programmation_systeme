import os
import sys
import time

def main():
    if len(sys.argv) != 2:
        print("Utilisation: python script.py <nom_fichier>")
        return 1
    
    nom_fichier = sys.argv[1]
    
    with open(nom_fichier, 'r') as f:
        chaine = f.readline().strip()
        print(chaine)
            
    os.unlink(nom_fichier)

if __name__ == "__main__":
    main()