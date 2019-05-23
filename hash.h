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

typedef struct liste
{
	struct liste *premier;
} liste_t;


unsigned int hash_string(const char *str);
void lecture_fichier(char *nom_fichier, cellule_t **tab_maj);
void crea_sous_table(cellule_t **tab_maj, char *cle, char* val);
void init_tab(cellule_t **tab);

