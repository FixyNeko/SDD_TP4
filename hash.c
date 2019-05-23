#include "hash.h"

unsigned int hash_string(const char *str)
{ 
	unsigned int hash = 5381;                /*  fonction de hachage de D.J. Bernstein*/
	const char *s;
	for (s = str; *s; s++)
 		hash = ((hash << 5) + hash) + tolower(*s);
	return (hash & 0x7FFFFFFF)%HASH_MAX;
}

void lecture_fichier(char *nom_fichier, cellule_t **tab_maj)
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
        	printf("%s", cle);//debug
        	printf(" %s\n", val);//debug
        	crea_sous_table(tab_maj,cle,val);
        }
        fclose(fichier);
    }
}

void crea_sous_table(cellule_t **tab_maj, char *cle, char* val)
{
	int index_maj = hash_string(cle);
	cellule_t *cellule =(cellule_t*)malloc(sizeof(cellule_t));
	tab_maj[index_maj] = cellule;
	cellule->mot=cle;
	cellule->traduction=val;
	cellule->suivant = NULL;
}

void init_tab(cellule_t **tab)
{
	int i;
	for(i=0; i<HASH_MAX; i++)
	{
		tab[i] = NULL;
	}
}

void affiche_sous_table(cellule_t **tab_maj)
{
	int i = 0;
	char *mot_actuel;
	cellule_t *cellule_cour;	
	while(tab_maj[i] == NULL)
	{
		i++;
	}
	cellule_cour = tab_maj[i];
	mot_actuel = cellule_cour->mot;
	printf("le mot est %s",mot_actuel);
}

int main()
{
	printf("%d\n",hash_string("hello"));
	printf("%d\n",hash_string("bye"));
	printf("%d\n",hash_string("sorry"));
	cellule_t * tab_maj[HASH_MAX];
	init_tab(tab_maj);
	lecture_fichier("mots.txt", tab_maj);
	affiche_sous_table(tab_maj);
	return 0;
}
