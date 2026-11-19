#include "Entite.h"
#include <stdlib.h>
#include <string.h>

/**
 * @file Entite.c
 * @brief Implémentation des fonctions de base pour la manipulation d'une entité.
 */

/**
 * @brief Affiche les informations d'une entité.
 * @param e Pointeur vers l'entité à afficher.
 */
void afficherEntite(Entité *e) {
    if (e == NULL) return;
    printf("\n=============%s==============\n", e->nom);
    printf("= Aura : %d \n", e->aura);
    printf("= Classe : %d, Pt de Vie : %d \n", e->classe, e->pt_vie);
    printf("= Est un allie : %d, Pt endurance : %d \n", e->allie, e->pt_endurance);
    printf("=================================\n\n");
}

/**
 * @brief Initialise et alloue dynamiquement une nouvelle entité.
 * @return Un pointeur vers l'entité initialisée, ou NULL en cas d'échec.
 */
Entité* initialiseEntite(void) {
    Entité *entite = malloc(sizeof(Entité));
    if (entite != NULL) {
        *entite = (Entité) {
            .actions = NULL,
            .type = TYPE_ENTITE,
            .nom = NULL,
            .classe = AUCUNNE,
            .pt_vie = 0,
            .pt_endurance = 0,
            .allie = false,
            .aura = 0
        };
    }
    return entite;
}

/**
 * @brief Vérifie si une entité est vivante.
 * @param e Pointeur vers l'entité à vérifier.
 * @return true si les points de vie sont supérieurs à 0, false sinon.
 */
bool entiteVivante(Entité *e) {
    if (e == NULL) return false;
    return e->pt_vie > 0; 
}

/**
 * @brief Remplit les champs d'une entité existante.
 * @param e Pointeur vers l'entité à remplir.
 * @param nom Nom de l'entité.
 * @param c Classe de l'entité.
 * @param pv Points de vie initiaux.
 * @param endu Points d'endurance initiaux.
 * @param allie Vrai si l'entité est alliée, faux sinon.
 */
void remplirEntite(Entité *e, const char *nom, Classe c, int pv, int endu, bool allie) {
    if (e == NULL) return;
    e->type = TYPE_ENTITE;
    e->nom = (char *)nom; // Correction de l'assignation de chaîne
    e->classe = c;
    e->pt_vie = pv;
    e->pt_endurance = endu;
    e->actions = NULL;
    e->allie = allie;
    e->aura = 0;
}