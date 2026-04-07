import sys

def main():
    os.execlp("vim", "vim", sys.argv[1], None)

if __name__ == "__main__":
    main()