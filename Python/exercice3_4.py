import os

def main():
    pwd = os.getenv("PWD")
    
    while True:
        repertoire = input("Saisir un nom de répertoire (taper 'quitter' pour arrêter): ")
        
        if repertoire == "quitter":
            return 0

        fils = os.fork()

        if fils == 0:
            os.execlp("cp", "cp", "-r", pwd, repertoire, None)

        elif fils > 0:
            os.wait()
    
if __name__ == "__main__":
    main()