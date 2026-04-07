import os
import sys
import time

numero_fils = 0

def main():
    global numero_fils
    
    for i in range(1, 6):
        numero_fils += 1
        pid_fils = os.fork()
        
        if pid_fils == 0:
            print(f"je suis le fils {numero_fils}")
            return
    
    for i in range(1, 6):
        os.wait()

if __name__ == "__main__":
    main()