#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include <stdio.h>
#include "DataGame.h"

/**
 * @file Inventaire.h
 * @brief Définition des fonctions de gestion de l'inventaire.
 */

/**
 * @brief Initialise et alloue dynamiquement une nouvelle structure d'inventaire.
 * @return Un pointeur vers l'élément initialisé (`DataGame`), ou NULL en cas d'échec.
 */
DataGame *initialiserInventaire(void);

/**
 * @brief Affiche l'ensemble des éléments présents dans l'inventaire.
 * @param inventaire Pointeur vers la tête de la liste chaînée de l'inventaire.
 */
void afficherInventaire(DataGame *inventaire);

#endif