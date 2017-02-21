#ifndef BIBL_H
#define BIBL_H

typedef struct livre{
	int num;
	char *titre;
	char *auteur;
	struct livre* suiv;
} s_livre;

typedef struct biblio{
	s_livre * L; /*Liste chainee des livres*/
	int nbliv; /*Nombre de livres dans la liste*/
	}Biblio;

	
void initialise_biblio(Biblio* B);

s_livre* creer_livre( int num, char* tit, char* aut );

void insertion_livre( s_livre* liv, Biblio* bibli );

void lecture_n_entree(char *nomfic,int n,Biblio *B);

int recherche_ouv_num(int n,Biblio* B);

void recherche_ouv_titre(char* titre,Biblio* B);

void recherche_livre_par_auteur(char* auteur, Biblio* B);

void suppression_ouvrage(int n,Biblio* B);

void cherche_double(Biblio* B,Biblio* bis);

void afficher_biblio(Biblio* B);

void supprimer_biblio(Biblio* B);

#endif
