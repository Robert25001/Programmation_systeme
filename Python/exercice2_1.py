import os
import sys
import time

def main():
    
    pid_fils = os.fork()
    
    if pid_fils == -1:  # Erreur
        print("Problème dans fork")
        sys.exit(1)
    
    elif pid_fils == 0:  # Processus fils
        print("je suis le fils")
    
    else:  # Processus père
        print("je suis le père")
        
        # wait
        os.wait()
        print("fils terminé")

if __name__ == "__main__":
    main()