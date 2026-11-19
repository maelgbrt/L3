#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdbool.h>

/**
 * @file Element.h
 * @brief Définition des types de base et des constantes globales du jeu.
 */

#define MAX_CARACTERISTIQUE 4 /**< Nombre maximum de caractéristiques */
#define MAX_MEMBRES   6       /**< Nombre maximum de membres par équipe */
#define PV_MAX        100     /**< Points de vie maximum par défaut */

/**
 * @enum TypeElement
 * @brief Représente le type d'un élément générique du jeu.
 */
typedef enum {
    TYPE_OBJET,     /**< Élément de type Objet */
    TYPE_ENTITE,    /**< Élément de type Entité */
    TYPE_ACTION,    /**< Élément de type Action */
    TYPE_INVENTAIRE /**< Élément de type Inventaire */
} TypeElement;

/**
 * @brief Affiche un élément générique selon son type réel.
 * @param elmt Pointeur vers l'élément générique à afficher.
 */
void afficherElement(void *elmt);

/**
 * @brief Compare deux éléments génériques pour vérifier s'ils sont égaux.
 * @param elmt1 Premier élément.
 * @param elmt2 Deuxième élément.
 * @return true si les éléments sont équivalents, false sinon.
 */
bool elements_egaux(void *elmt1, void *elmt2);

#endif