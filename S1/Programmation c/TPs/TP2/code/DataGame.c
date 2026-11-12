#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataGame.h"

/**
 * @file DataGame.c
 * @brief Implémentation des fonctions de gestion de la liste chaînée générale.
 */

/**
 * @brief Initialise la liste chaînée en mettant son pointeur à NULL.
 * @param d Pointeur vers le pointeur de la liste à initialiser
 */
void initialiser(DataGame **d) {
    if (d != NULL) {
        *d = NULL;
    }
}

/**
 * @brief Affiche l'élément stocké dans le nœud de la liste.
 * @param d La structure DataGame contenant l'élément à afficher
 */
void afficher(DataGame d){
    afficherElement(d.element);
}

/**
 * @brief Ajoute un nouvel élément en tête de la liste chaînée.
 * @param d Pointeur vers le pointeur de la liste
 * @param elmt Pointeur vers l'élément à ajouter
 */
void ajouter(DataGame **d, void *elmt)
{
    DataGame *NouveauNoeud = malloc(sizeof(DataGame));
    if (NouveauNoeud == NULL){
        return;
    }

    NouveauNoeud->element = elmt;
    NouveauNoeud->suivant = *d;
    *d = NouveauNoeud;
}

/**
 * @brief Recherche et supprime un élément spécifique de la liste chaînée.
 * @param d Pointeur vers le pointeur de la liste
 * @param elmt Pointeur vers l'élément à supprimer
 */
void supprimer(DataGame **d, void *elmt) {
    DataGame *courant = *d;
    DataGame *precedent = NULL;

    while (courant != NULL && !elements_egaux(courant->element, elmt)) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) return;

    if (precedent == NULL) {
        *d = courant->suivant;
    } 
    else {
        precedent->suivant = courant->suivant;
    }
    free(courant);
}