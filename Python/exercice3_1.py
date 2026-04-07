import sys

def main():
    
    if len(sys.argv) != 3:
        print("argument invalide")
        return 0
    
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    
    print(f"Leur somme: {a + b}")
        

if __name__ == "__main__":
    main()