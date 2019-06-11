#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define HASH_MAX 29
#define TAILLE_MAX 25

typedef struct cellule
{
	char *mot;
	char *traduction;
	struct cellule *suivant;
} cellule_t;

typedef struct table_maj {
	cellule_t* sous_table;
	int taille;
} table_maj_t;

typedef struct liste
{
	struct liste *premier;
} liste_t;


unsigned int hash_string(const char *str);
void lecture_fichier(char *nom_fichier, table_maj_t * tab_maj);
void traduction_fichier(char * nomFichier, table_maj_t * tab_maj);
void ajout_valeur(table_maj_t * tab_maj, char * cle, char * val);
void init_tab(table_maj_t * tab);
void affiche_sous_tables(table_maj_t * tab_maj);
int RechercheCle(table_maj_t * tab_maj, char * cle, cellule_t ** adresse);
int RechercheCleSousTable(cellule_t ** premier, char * cle, cellule_t ** adresse);
int RecherchePrec(cellule_t ** premier, char * cle, cellule_t *** prec);
void tailleMoyenne(table_maj_t * tab_maj);
