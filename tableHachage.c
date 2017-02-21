#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bibl.h"
#include "entree_sortie.h"
#include "tableHachage.h"
#define TMAX 41
#define LMAX 100000

cell_t* initialise_cell() 
{
	cell_t *tmp = (cell_t*)malloc(sizeof(cell_t));
	if( tmp == NULL ) {
		printf("Erreur lors de l'allocation de la cellule");
		return NULL;
	}
	tmp->clef = 0;
	tmp->L = NULL;
	tmp->suivant = NULL;
	return tmp;
}

void supprimer_cell( cell_t* cell ) 
{
	if(  cell->L != NULL ){
		free( cell->L );
	}
	free( cell );
}

void hach_supprimer_livre( tableHachage_t* tH, int n ) 
{
	int i;
	for( i = 0; i < tH->m; i++ ) {
		while( tH->T[i]->L != NULL ) {
			if( tH->T[i]->L->num == n ) {
				cell_t* tmp = 
				return 1;
			}
			tH->T[i] = tH->T[i]->suivant;
		}

	}
	
	printf("Le livre dont le numéro d'ouvrage est:%d n'a pas été trouvé.\n",n);
	return 0;
}

tableHachage_t* initTableHachage( int m ) 
{
	tableHachage_t* th = (tableHachage_t*)malloc(sizeof( tableHachage_t) );

	if( th == NULL ) {
		printf("Erreur lors de l'allocation de la table de hachage\n");
		return NULL;
	}
	int i;
	th->nE = 0;
	th->m = m;
	th->T = ( cell_t** )malloc( sizeof( cell_t* ) * m );
	if( th->T == NULL ) {
		printf("Erreur lors de l'allocation des cases de la table de hachage\n");
		return NULL;
	}
	for( i = 0; i < m; i++ ) {
		th->T[i] = initialise_cell();
	}
	return th;
}

//On pourrait aussi additionner le nom et le titre pour etre plus specifique
int fonctionClef( char* nom ) 
{

	int val = 0;
	int i = 0;
	while( nom[i] != '\0' ) {
		//fprintf(stderr, "1--\n" );
		val += (int)nom[i];
		i++;
	}
	return val;
}

int fonctionHachage( int clef, int m ) 
{	
	int tmp;
	double A = (sqrt(5) - 1)/2;
	tmp = (int)(clef * A);
	tmp = (int)(m * ( clef * A - tmp ));
	return tmp;
}

void hach_insertion_livre( s_livre* liv, tableHachage_t* Bib )
{
	if( !liv ) return;

	int clef =  fonctionClef( liv->auteur );
	int position = fonctionHachage( clef, Bib->m );

	cell_t* new = initialise_cell();
	new->clef = clef;
	new->L = liv;
	new->suivant = Bib->T[position];
	Bib->T[position] = new;

	Bib->nE++;
}

void hach_lecture_n_entree(char *nomfic,int n, tableHachage_t* t)
{

	FILE* F;
	int i;
	int num;
	char* titre = ( char* ) malloc( TMAX * sizeof( char ) );
	char* auteur = ( char* ) malloc( TMAX * sizeof( char ) );

	int test=t->nE;


	if( titre == NULL || auteur == NULL) {
		printf("Erreur lors de l'allocation de titre ou auteur\n");
		return;
	}
	
	if( n <= 0) {

		printf("n trop petit\n");
		return; 
	}

	s_livre* li=NULL;

	if( ( ( F = fopen( nomfic, "r" ) ) == NULL ) ) {
		printf( "Le fichier %s n'existe pas.\n", nomfic );
		return;
	}

	for( i = 0; i < n; i++ ) {

		num = GetEntier( F );
		

		GetChaine( F, TMAX, titre) ;


		GetChaine( F, TMAX, auteur );
		li = creer_livre( num, titre, auteur );

		hach_insertion_livre( li, t );
	}


	if( test + n != t->nE ) {
		printf("Erreur dans l'insertion des livres dans la bibliothèque\n");
	}


}

int hach_recherche_ouv_num( int n, tableHachage_t* tH ) 
{
	int i;
	for( i = 0; i < tH->m; i++ ) {
		while( tH->T[i]->L != NULL ) {
			if( tH->T[i]->L->num == n ) {
				printf("Livre trouvé! Titre: %s  Auteur:%s Num:%d\n",tH->T[i]->L->titre,tH->T[i]->L->auteur,tH->T[i]->L->num);
				return 1;
			}
			tH->T[i] = tH->T[i]->suivant;
		}

	}
	
	printf("Le livre dont le numéro d'ouvrage est:%d n'a pas été trouvé.\n",n);
	return 0;
}
int hach_recherche_ouv_titre( char* titre, tableHachage_t* tH ) 
{
	int i;
	for( i = 0; i < tH->m; i++ ) {
		while( tH->T[i]->L != NULL ) {
			if( strcmp(titre,tH->T[i]->L->titre) == 0 ) {
				printf("Livre trouvé! Titre: %s  Auteur:%s Num:%d\n",tH->T[i]->L->titre,tH->T[i]->L->auteur,tH->T[i]->L->num);
				return 1;
			}
			tH->T[i] = tH->T[i]->suivant;
		}

	}
	
	printf("Le livre dont le titre est:%s n'a pas été trouvé.\n",titre);
	return 0;
}

void hach_recherche_livre_par_auteur(char* auteur, tableHachage_t* tH )
{
	
	int bool = 0;
	int clef =  fonctionClef( auteur );
	int i = fonctionHachage( clef, tH->m );
	while( tH->T[i]->L != NULL ) {
		if( strcmp( auteur, tH->T[i]->L->auteur ) == 0 ) {

			printf("Titre: %s num: %d\n",tH->T[i]->L->titre,tH->T[i]->L->num);
			bool = 1;	
		}

		tH->T[i] = tH->T[i]->suivant;
	}
	if( bool == 0 ) {
		printf("L'auteur n'est pas dans la bibliothèque\n");
	}
	

}

void hach_afficher_biblio( tableHachage_t* tH )
{	
	if( tH == NULL || tH->nE == 0) {
		printf("La bibliothèque est vide\n");
		return;
	}
	int i;
	int cpt = 0;
	for( i = 0; i < tH->m; i++ ) {
		cell_t* tmp = tH->T[i];
		while( tmp->L != NULL ) {
			printf("Titre: %s  Auteur:%s Num:%d\n",tmp->L->titre,tmp->L->auteur,tmp->L->num);
			tmp = tmp->suivant;
			cpt++;
		}
	}
	printf( "cpt = %d\n", cpt );
}
	
	
