#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibl.h"
#include "tableHachage.h"
#include "entree_sortie.h"
#define TMAX 41

void menu(void)
{
	printf("--------------------MENU--------------------\n");
	printf("|0: QUITTER LE MENU\n");
	printf("|1: RECHERCHER UN OUVRAGE PAR SON NUMERO\n");
	printf("|2: RECHERCHER UN OUVRAGE PAR SON TITRE\n");
	printf("|3: LISTER LES OUVRAGES D'UN AUTEUR\n");
	printf("|4: INSERTION D'UN NOUVEL OUVRAGE\n");
	printf("|5: AFFICHER LA BIBLIOTHEQUE\n");
}
	
int main(int argc,char* *argv)
{
	
	int ch;
	char* nomfic=strdup(argv[1]);
	int n; //Num de l'ouvrage
	int nblignes;
	Biblio B,bis;
	tableHachage_t* tH = initTableHachage( 10 );
	char auteur[TMAX];
	char titre[TMAX];
	if( argc != 3) {
		printf( "Erreur format: %s <NomFichier_Biblio.txt><nbLigneALire>", argv[0] );
		return 1;
	}
	nblignes = atoi( argv[2] );

	printf( "Lecture \n" );

	hach_lecture_n_entree( nomfic, nblignes, tH );

	do{

		menu();
		scanf( "%d", &ch );

		switch(ch){

			case 1:
				printf( "Saisir le numero de l'ouvrage\n" );
				scanf ("%d", &n );
				int bool=hach_recherche_ouv_num( n, tH );
				printf( "%d", bool );
				break;

			case 2:
				printf( "Saisir le titre de l'ouvrage\n" );
				scanf( "%s", titre );
				hach_recherche_ouv_titre( titre, tH );
				break;

			case 3:
				printf( "Saisir le nom de l'auteur\n" );
				scanf( "%s", auteur );
				hach_recherche_livre_par_auteur( auteur, tH );
				break;

			case 4:
				printf( "Saisir le nom de l'auteur\n" );
				scanf( "%s", auteur );
				printf( "Saisir le titre\n" );
				scanf( "%s", titre );
				s_livre*li = creer_livre( tH->nE+1, titre, auteur );
				hach_insertion_livre( li, tH );
				break;

			case 5:
				hach_afficher_biblio( tH );
				break;
		}




	} while( ch != 0 );

	printf( "FIN\n" );
	return 0;
	
}