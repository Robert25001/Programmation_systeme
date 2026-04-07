import os

def main():
    pwd = os.getenv("PWD")
    
    while True:
        texte = input("Saisir un nom de fichier (taper 'quitter' pour arrêter): ")
        
        if repertoire == "quitter":
            return 0

        fils = os.fork()

        if fils == 0:
            os.execlp("vim", "vim", "-r", texte, None)

        elif fils > 0:
            os.wait()
    
if __name__ == "__main__":
    main()