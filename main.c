#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibl.h"
#include "entree_sortie.h"
#define TMAX 41

void menu(void)
{
	printf("--------------------MENU--------------------\n");
	printf("|0: QUITTER LE MENU\n");
	printf("|1: RECHERCHER UN OUVRAGE PAR SON NUMERO\n");
	printf("|2: RECHERCHER UN OUVRAGE PAR SON TITRE\n");
	printf("|3: LISTER LES OUVRAGES D'UN AUTEUR\n");
	printf("|4: SUPPRIMER UN LIVRE\n");
	printf("|5: LISTER LES DOUBLONS\n");
	printf("|6: INSERTION D'UN NOUVEL OUVRAGE\n");
	printf("|7: AFFICHER LA BIBLIOTHEQUE\n");
	printf("|8: SUPPRIMER LA BIBLIOTHEQUE\n");
}
	 
int main(int argc,char* *argv)
{
	
	int ch;
	int i= 0;
	char* nomfic=strdup(argv[1]);
	int n; //Num de l'ouvrage
	int nblignes;
	Biblio B,bis;
	initialise_biblio(&B);
	char auteur[TMAX];
	char titre[TMAX];
	if(argc!=3){
		printf("Erreur format: %s <NomFichier_Biblio.txt><nbLigneALire>",argv[0]);
		return 1;
	}
	nblignes=atoi(argv[2]);
	printf("Lecture \n");
	lecture_n_entree(nomfic,nblignes,&B);

	do{

		menu();
		scanf("%d",&ch);

		switch(ch){

			case 1:
				printf("Saisir le numero de l'ouvrage\n");
				scanf("%d",&n);
				int bool=recherche_ouv_num(n,&B);
				printf("%d",bool);
				break;

			case 2:
				printf("Saisir le titre de l'ouvrage\n");
				scanf("%s",titre);
				recherche_ouv_titre(titre,&B);
				break;
			case 3:
				
				printf("Saisir le nom de l'auteur\n");
				scanf("%s",auteur);
				recherche_livre_par_auteur(auteur,&B);
				
				break;
			case 4:
				printf("Saisir le numero de l'ouvrage\n");
				scanf("%d",&n);
				suppression_ouvrage(n,&B);
				break;
			case 5:
				cherche_double(&B,&bis);
				afficher_biblio(&bis);
				supprimer_biblio(&bis);
				break;
			case 6:
				printf("Saisir le nom de l'auteur\n");
				scanf("%s",auteur);
				printf("Saisir le titre\n");
				scanf("%s",titre);
				s_livre*li=creer_livre(B.nbliv+1,titre,auteur);
				insertion_livre(li,&B);
				break;
			case 7:
				afficher_biblio(&B);
				break;
			case 8:
				supprimer_biblio(&B);
				break;


		}




	}while(ch!=0);

	printf("FIN\n");
	return 0;
	
}
