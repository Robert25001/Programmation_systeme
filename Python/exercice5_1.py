import threading
import time

def ma_fonction_thread(tableau):
    n = tableau[0]
    print("affichage des contenus de tableau passé en paramètre")
    
    for i in range(1, n + 1):
        print(f"{tableau[i]} ", end="")
    print()

def main():
    tableau = [5, 2, 4, 6, 8, 10]
    
    my_thread = threading.Thread(target=ma_fonction_thread, args=(tableau,))
    
    my_thread.start()
    
    my_thread.join()

if __name__ == "__main__":
    main()