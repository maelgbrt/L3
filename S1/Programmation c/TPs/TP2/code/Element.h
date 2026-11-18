#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>

#define MAX_CARACTERISTIQUE 4
#define MAX_MEMBRES   6
#define PV_MAX        100

/**
 * @file Element.h
 * @brief Définition des types de base du jeu.
 */

typedef enum {
    TYPE_OBJET,   
    TYPE_ENTITE,   
    TYPE_ACTION,
    TYPE_INVENTAIRE
} TypeElement;

void afficherElement(void *elmt);
bool elements_egaux(void *elmt1, void *elmt2);

#endif