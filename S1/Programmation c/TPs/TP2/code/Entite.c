#include "Entite.h"


/**
 * @file Entite.c
 * @brief Définition des fonctions de base pour la manipulation d'une entité
 */

/**
 * @brief Affiche une Entité.
 * @param Entité L'entité à afficher
 */
void afficherEntite(Entité *e){
    printf("\n=============%s==============\n",e->nom);
    printf("= Aura : %d \n",e->aura);
    printf("= Classe : %d, Pt de Vie : %d \n",e->classe,e->pt_vie);
    printf("= Est un allie : %b, Pt endurance : %d \n",e->allie,e->pt_endurance);
    printf("=================================\n\n");
}

/**
 * @brief Initialise une entité.
 * @param Entité Pointeur vers l'entité à initialiser
 */

Entité* initialiseEntite(void) {
    Entité *entite = malloc(sizeof(Entité));
    if (entite != NULL) {
        *entite = (Entité) {
            .actions = NULL,
            .type = TYPE_ENTITE
        };
    }
    return entite;
}

bool entiteVivante(Entité * e) {
    return e->pt_vie > 0; 
}


void remplirEntite(Entité *e, const char *nom, Classe c, int pv, int endu, bool allie) {
    e->type = TYPE_ENTITE;
    e->nom = nom[50];
    e->classe = c;
    e->pt_vie = pv;
    e->pt_endurance = endu;
    e->actions = NULL;
    e->allie = allie;
    e->aura = 0;
}