import os
import sys
import time
import random
import signal

def main():
   
    random.seed(int(time.time()))
    debut = time.time()
    
    for i in range(1, 3):
        pid_fils = os.fork()
        
        if pid_fils == -1: 
            print(f"Erreur de fork pour fils {i}")
            sys.exit(1)
        
        elif pid_fils == 0: 
            temps = random.randint(1, 10)
            print(f"je suis le fils {i}")
            
            time.sleep(temps)
            
            print(f"fils {i} terminé après {temps} secondes")
            return 
    
    for i in range(1, 3):
        os.wait() ;
    
    fin = time.time()
    print(f"La durée totale d'exécution est {int(fin - debut)} secondes")

if __name__ == "__main__":
    main()