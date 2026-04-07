import os
import sys
import time

def main():
    
    for i in range(1, 6):
        pid_fils = os.fork()
        
        if pid_fils == -1:
            print(f"Problème dans fork lors de création de fils {i}")
            sys.exit(1)
        
        elif pid_fils == 0:
            print(f"je suis le fils {i}")
            return 
            
    for i in range(1, 6):
        os.wait()

if __name__ == "__main__":
    main()