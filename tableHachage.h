#ifndef TABLE_HACHAGE_H
#define TABLE_HACHAGE_H


typedef struct cell{
	int clef;
	//int num;
	// Pointeur sur un livre ? ou Les infos du livre dans la cellule
	s_livre *L;
	struct cell *suivant;
} cell_t;

typedef struct {
	int nE;
	int m;
	cell_t **T;
} tableHachage_t;

tableHachage_t* initTableHachage( int m );

int fonctionClef( char* nom );

int fonctionHachage( int clef, int m );

void hach_insertion_livre( s_livre* liv, tableHachage_t* Biblio );

void hach_lecture_n_entree(char *nomfic,int n, tableHachage_t* t);

int hach_recherche_ouv_num( int n, tableHachage_t* tH);

int hach_recherche_ouv_titre( char* titre, tableHachage_t* tH);

void hach_recherche_livre_par_auteur(char* auteur, tableHachage_t* tH );

void hach_afficher_biblio( tableHachage_t* tH );


#endif