#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bibl.h"
#include "entree_sortie.h"
#define TMAX 41
#define LMAX 100000

// TOUT MARCHE SAUF DOUBLON
void initialise_biblio(Biblio* bib)
{

		bib->L=NULL;
		bib->nbliv=0;
}

s_livre* creer_livre( int num, char* tit, char* aut ) 
{

	s_livre* li = (s_livre*)malloc(sizeof(s_livre));

	if( li ) {
		li->num = num;
		li->titre = strdup(tit);
		li->auteur = strdup(aut);
		li->suiv = NULL;
	}

	return li;
}

void insertion_livre( s_livre* liv, Biblio* bibli )
{

	liv->suiv = bibli->L;
	bibli->L = liv;
	bibli->nbliv++;
}

void lecture_n_entree(char *nomfic,int n,Biblio *B)
{

	FILE* F;
	int i;
	int num;
	char* titre= (char*) malloc(TMAX*sizeof(char));
	char* auteur= (char*) malloc(TMAX*sizeof(char));

	int test=B->nbliv;


	if(titre==NULL || auteur==NULL){
		printf("Erreur lors de l'allocation de titre ou auteur\n");
		return;
	}
	
	if(n<=0){

		printf("n trop petit\n");
		return; 


	}

	s_livre* li=NULL;


	if(((F=fopen(nomfic,"r"))==NULL)){
		printf("Le fichier %s n'existe pas.\n",nomfic);
		return;
	}

	for(i=0;i<n;i++){

		num = GetEntier(F);


		GetChaine(F, TMAX, titre);


		GetChaine(F, TMAX, auteur);

		li=creer_livre(num,titre,auteur);
		insertion_livre(li,B);
	}


	if(test+n!= B->nbliv){
		printf("Erreur dans l'insertion des livres dans la bibliothèque\n");
	}


}


int recherche_ouv_num(int n,Biblio* B)
{
	s_livre* courant = B->L;
	
	while(courant!=NULL){
		
		if(courant->num==n){
			printf("Livre trouvé! Titre: %s  Auteur:%s Num:%d\n",courant->titre,courant->auteur,courant->num);
			return 1;
		}
		courant=courant->suiv;
	}
	printf("Le livre dont le numéro d'ouvrage est:%d n'a pas été trouvé.\n",n);
	return 0;
}
	
void recherche_ouv_titre(char* titre,Biblio* B)
{
	int i;
	s_livre* courant = B->L;
	for (i = 0; i <B->nbliv; i++){
		if(strcmp(titre,courant->titre)==0){
			printf("Livre trouvé. Auteur: %s num: %d\n",courant->auteur,courant->num);
			return;
		}
		courant=courant->suiv;
	}
	
	printf("Le livre dont le titre est:%s n'a pas été trouvé.\n",titre);
}
	
void recherche_livre_par_auteur(char* auteur, Biblio* B)
{
	
	int bool=0;
	s_livre* courant = B->L;
	while(courant!=NULL) {
		
		if(strcmp(auteur,courant->auteur)==0){
			printf("Titre: %s num: %d\n",courant->titre,courant->num);
			bool=1;		
		}
		courant = courant->suiv;
	}	
	if(bool==0) {
		printf("L'auteur n'est pas dans la bibliothèque\n");
	}
	

}
	
	

void suppression_ouvrage(int n,Biblio* B)
{
	
	
	
	s_livre* courant =B->L;
	
	
	
		if(courant->num==n){ //Si le livre se trouve en première position
			s_livre* tmp=B->L->suiv;
			free(courant->auteur);
			free(courant->titre);
			free(courant);
			if(courant==NULL)printf("Ouvrage %d supprimé de la bibliotheque\n",n);
			courant=tmp;
			B->nbliv--;
			return;
		}
		
		while(courant){
		if(courant->suiv->num==n){
			s_livre* tmp=courant->suiv->suiv;
			free(courant->suiv->auteur);
			free(courant->suiv->titre);
			free(courant->suiv);
			courant->suiv=tmp;
			B->nbliv--;
			return;
			}
		courant=courant->suiv;
	}
	printf("Le livre dont le numéro d'ouvrage est:%d n'a pas été trouvé.\n",n);
}



void cherche_double(Biblio* B,Biblio* bis)
{
	//ne marche pas
	initialise_biblio(bis);
	s_livre* courant=B->L;
	if(!courant->suiv){
		printf("La bibliotheque contient seulement 1 livre\n");
		return;
		}
	s_livre* tmp=courant->suiv;
	while(courant){
		
		while(tmp){
			if((strcmp(tmp->auteur,courant->auteur))==0 && (strcmp(tmp->titre,courant->titre)==0)){
				insertion_livre(courant,bis);
				printf("le livre %s par l'auteur %s a été trouvé en double.\n",tmp->titre,tmp->auteur);
			}
			tmp=tmp->suiv;
		}
		courant=courant->suiv;
				
	}
	

	
}
	
void afficher_biblio(Biblio* B)
{	
	s_livre* courant = B->L;
	if(B==NULL || B->nbliv==0){
		printf("La bibliothèque est vide\n");
		return;
	}
	while(courant!=NULL){
		printf("Num:%d Titre:%s Auteur:%s\n",courant->num,courant->titre,courant->auteur);
		courant=courant->suiv;
	}
}


void supprimer_biblio(Biblio* B){

	s_livre* courant=B->L;

	while(B->nbliv!=0){

		suppression_ouvrage(courant->num,B);
		courant=courant->suiv;

	}
	//free(B);



}


		
