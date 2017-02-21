GCC_FLAGS = -Wall
all: main mainHachage

entree_sortie.o	: entree_sortie.c
	gcc $(GCC_FLAGS) -c entree_sortie.c

bibl.o	: bibl.c
	gcc $(GCC_FLAGS) -c bibl.c

tableHachage.o : tableHachage.c
	gcc $(GCC_FLAGS) -c tableHachage.c

main.o	: main.c
	gcc $(GCC_FLAGS) -c main.c

main		: bibl.o main.o entree_sortie.o
	gcc $(GCC_FLAGS) -o main main.o bibl.o entree_sortie.o 

mainHachage: bibl.o tableHachage.o mainHachage.o entree_sortie.o
	gcc $(GCC_FLAGS) -o mainHachage mainHachage.o tableHachage.o bibl.o entree_sortie.o 

clean	:
	rm -f entree_sortie.o bibl.o tableHachage.o mainHachage.o main.o main mainHachage



