import sys
import os

def main():
    
    if len(sys.argv) != 2:
        print("argument invalide")
        return 0
    
    pwd = os.getenv("PWD")
    
    os.execlp("cp", "cp", "-r", pwd, sys.argv[1], None)

if __name__ == "__main__":
    main()