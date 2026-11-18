#include "Inventaire.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file Inventaire.c
 * @brief Implémentation des fonctions de gestion de l'inventaire sous forme de liste chaînée.
 */

/**
 * @brief Affiche l'ensemble des éléments contenus dans l'inventaire.
 * @param inv Pointeur vers la tête de la liste chaînée de l'inventaire (`DataGame`).
 */
void afficherInventaire(DataGame *inv) {
    int n = 0;
    for (DataGame *cur = inv; cur != NULL; cur = cur->suivant) {
        n++;
        printf("%d. ", n);
        afficher(*cur);
    }
}

/**
 * @brief Initialise et alloue dynamiquement une nouvelle structure d'inventaire (`DataGame`).
 * @return Un pointeur vers l'élément initialisé, ou NULL en cas d'échec d'allocation.
 */
DataGame *initialiserInventaire(void) {
    DataGame *inventaire = malloc(sizeof(DataGame));
    if (inventaire != NULL) {
        inventaire->element = NULL;
        inventaire->suivant = NULL;
        return inventaire;
    }
    return NULL;
}