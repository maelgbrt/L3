#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataGame.h"
#include "Element.h"

/**
 * @file DataGame.c
 * @brief Implémentation des fonctions de gestion de la liste chaînée générale du jeu.
 */

/**
 * @brief Initialise et alloue dynamiquement un nœud pour la liste chaînée.
 * @return Un pointeur vers le nouveau nœud initialisé, ou NULL en cas d'échec.
 */
DataGame *initialiser(void) {
    DataGame *d = malloc(sizeof(DataGame));
    if (d != NULL) {
        d->element = NULL;
        d->suivant = NULL;
        return d;
    }
    return NULL;
}

/**
 * @brief Affiche l'élément stocké dans le nœud de la liste.
 * @param d La structure DataGame contenant l'élément à afficher.
 */
void afficher(DataGame d) {
    afficherElement(d.element);
}

/**
 * @brief Ajoute un nouvel élément en tête de la liste chaînée.
 * @param d Pointeur vers le pointeur de la tête de la liste.
 * @param elmt Pointeur vers l'élément à ajouter.
 */
void ajouter(DataGame **d, void *elmt) {
    DataGame *NouveauNoeud = malloc(sizeof(DataGame));
    if (NouveauNoeud == NULL) {
        return;
    }

    NouveauNoeud->element = elmt;
    NouveauNoeud->suivant = *d;
    *d = NouveauNoeud;
}

/**
 * @brief Recherche et supprime un élément spécifique de la liste chaînée.
 * @param d Pointeur vers le pointeur de la tête de la liste.
 * @param elmt Pointeur vers l'élément à supprimer.
 */
void supprimer(DataGame **d, void *elmt) {
    if (d == NULL || *d == NULL) return;

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

/**
 * @brief Recherche un élément spécifique dans la liste chaînée.
 * @param d Pointeur vers la tête de la liste.
 * @param elmt Pointeur vers l'élément recherché.
 * @return Un pointeur vers l'élément trouvé, ou NULL s'il n'est pas présent.
 */
void *chercher(DataGame *d, void *elmt) {
    if (elmt == NULL) {
        return NULL;
    }

    for (DataGame *cur = d; cur != NULL; cur = cur->suivant) {
        if (elements_egaux(elmt, cur->element)) {
            return cur->element;
        }
    }
    return NULL;
}