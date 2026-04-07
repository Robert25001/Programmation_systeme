import os
import sys
import time

def main():
    tube = os.pipe()
    
    pid = os.fork()
    
    if pid == 0:
        os.close(tube[1])  # Fermer l'extrémité écriture
        
        nomfich_bytes = os.read(tube[0], 50)
        nomfich = nomfich_bytes.decode().rstrip('\x00')
        os.close(tube[0])
        os.execvp("python3", ["python3", "exercice4_32.py", nomfich])
        
    else:
        nomfich = "/tmp/test.txt"
        
        os.close(tube[0])  # Fermer l'extrémité lecture
        os.write(tube[1], nomfich.encode())
        os.close(tube[1])
        
        try:
            os.mkfifo(nomfich, 0o644)
        except FileExistsError:
            print(f"Le FIFO {nomfich} existe déjà")
        except OSError as e:
            print(f"Erreur création FIFO: {e}")
            sys.exit(1)
        
        fd = os.open(nomfich, os.O_WRONLY)
        
        message = "coucou\n"
        os.write(fd, message.encode())
        os.close(fd)
        
        os.wait()
        
        #os.unlink(nomfich)

if __name__ == "__main__":
    main()