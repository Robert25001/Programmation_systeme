import os
import sys
import time

def main():
    
    fils_1 = os.fork()
    
    if fils_1 == -1:
        print("Problème dans fork lors de création de fils 1")
        sys.exit(1)
    
    elif fils_1 == 0:
        print("je suis le fils 1")
    
    else:
        print("je suis le père")
        
        os.wait()
        print("fils 1 terminé")
        
        fils_2 = os.fork()
        
        if fils_2 == -1:
            print("Problème dans fork lors de création de fils 2")
            sys.exit(1)
        
        elif fils_2 == 0:
            print("je suis le fils 2")
        
        else:
            os.wait()
            print("fils 2 terminé")

if __name__ == "__main__":
    main()