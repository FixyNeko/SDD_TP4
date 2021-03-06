#include "hash.h"

unsigned int hash_string(const char *str)
{
	unsigned int hash = 5381;                /*  fonction de hachage de D.J. Bernstein*/
	const char *s;
	for (s = str; *s; s++)
 		hash = ((hash << 5) + hash) + tolower(*s);
	return (hash & 0x7FFFFFFF)%HASH_MAX;
}

void lecture_fichier(char *nom_fichier, table_maj_t * tab_maj)
{
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX];
	char* cle;
	char* val;
    fichier = fopen(nom_fichier, "r");
    if (fichier != NULL)
    {
    	while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
        	cle = strtok(chaine,";");
        	val = strtok(NULL,"\n");
        	printf("%s %s\n", cle, val);//debug
        	ajout_valeur(tab_maj,cle,val);
        }
        fclose(fichier);
    }
}

void traduction_fichier(char * nomFichier, table_maj_t * tab_maj) {
	FILE* fichier = NULL;
	char chaine[TAILLE_MAX];
	int i;

	cellule_t * retour = NULL;
	int trouve;

    fichier = fopen(nomFichier, "r");

    if (fichier != NULL)
    {
    	while (fgets(chaine, TAILLE_MAX, fichier) != NULL)
        {
			for(i = 0; i < TAILLE_MAX; i++) { // boucle enlevant le \n en fin de chaine
				if(chaine[i] == '\n'){
					chaine[i] = '\0';
					break;
				}
			}

        	trouve = RechercheCle(tab_maj, chaine, &retour);
			printf("%s : %s\n", chaine, trouve? retour->traduction : "[mot non trouvé]");
        }
        fclose(fichier);
    }
}

void ajout_valeur(table_maj_t * tab_maj, char *cle, char* val)
{
	int index_maj = hash_string(cle);

	cellule_t ** prec;

	if(!RecherchePrec(&(tab_maj[index_maj].sous_table), cle, &prec)) {
		cellule_t * cellule = (cellule_t*) malloc(sizeof(cellule_t));

		cellule->mot = (char*) malloc((strlen(cle) + 1) * sizeof(char));
		strcpy(cellule->mot, cle);
		cellule->traduction = (char*) malloc((strlen(val) + 1) * sizeof(char));
		strcpy(cellule->traduction, val);

		cellule->suivant = *prec;
		*prec = cellule;

		tab_maj[index_maj].taille++;
	}
}

void init_tab(table_maj_t * tab_maj)
{
	int i;
	for(i=0; i<HASH_MAX; i++)
	{
		tab_maj[i].sous_table = NULL;
		tab_maj[i].taille = 0;
	}
}

void affiche_sous_tables(table_maj_t * tab_maj)
{
	int i, j;
	cellule_t * cellule_cour;

	for(i = 0; i < HASH_MAX; i++) {
		cellule_cour = tab_maj[i].sous_table;
		for(j = 0; j < tab_maj[i].taille; j++) {
			printf("%s : %s\n", cellule_cour->mot, cellule_cour->traduction);
			cellule_cour = cellule_cour->suivant;
		}
	}
}

int RechercheCle(table_maj_t * tab_maj, char * cle, cellule_t ** adresse) {
	return RechercheCleSousTable(&(tab_maj[hash_string(cle)].sous_table), cle, adresse);
}

int RechercheCleSousTable(cellule_t ** premier, char * cle, cellule_t ** adresse) {
	cellule_t ** prec = NULL;
	int result;
	result = RecherchePrec(premier, cle, &prec);
	if(result)
		*adresse = *prec;
	return result;
}

int RecherchePrec(cellule_t ** premier, char * cle, cellule_t *** prec) {
	cellule_t * cour = *premier;
	*prec = premier; /* pointeur sur son précedant */

	while(cour != NULL && strcmp(cour->mot, cle) < 0) {
		*prec = &(cour->suivant);
		cour = cour->suivant;
	}

	return (cour != NULL);
}

void tailleMoyenne(table_maj_t * tab_maj) {
	int moyenne = 0, elements = 0;
	int i;

	for(i = 0; i < HASH_MAX; i++) {
		if(tab_maj[i].taille != 0) {
			moyenne += tab_maj[i].taille;
			elements++;
		}
	}
	moyenne /= elements;
	printf("\ntaille moyenne d'une sous table: %d\n", moyenne);
}

int main()
{
	table_maj_t tab_maj[HASH_MAX];

	init_tab(tab_maj);
	lecture_fichier("mots.txt", tab_maj);
	//affiche_sous_tables(tab_maj);

	traduction_fichier("aTraduire.txt", tab_maj);

	tailleMoyenne(tab_maj);

	return 0;
}
