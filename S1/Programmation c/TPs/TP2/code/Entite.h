#ifndef ENTITE_H
#define ENTITE_H

#include "DataGame.h"
#include "Element.h"
#include <stdio.h>
#include <stdbool.h>

/**
 * @file Entite.h
 * @brief Définition des structures, des classes et des fonctions liées aux entités du jeu.
 */

/**
 * @enum Classe
 * @brief Représente la classe d'une entité.
 */
typedef enum {
    AUCUNNE,      /**< Aucune classe */
    MAGE,         /**< Classe mage */
    GUERRIER,     /**< Classe guerrier */
} Classe;

/**
 * @struct Entité
 * @brief Représente une entité du jeu (allié ou ennemi).
 */
typedef struct Entité {
    TypeElement type;         /**< Type de l'élément (doit être TYPE_ENTITE) */
    char *nom;                /**< Nom de l'entité */
    Classe classe;            /**< Classe du personnage */
    int pt_vie;               /**< Points de vie actuels */
    int pt_endurance;         /**< Points d'endurance actuels */
    DataGame *actions;        /**< Liste des actions disponibles */
    bool allie;               /**< Vrai si c'est un allié, faux sinon */
    int aura;                 /**< Niveau d'aura */
} Entité;

/**
 * @brief Affiche les informations d'une entité.
 * @param e Pointeur vers l'entité à afficher.
 */
void afficherEntite(Entité *e);

/**
 * @brief Initialise et alloue dynamiquement une nouvelle entité.
 * @return Un pointeur vers l'entité initialisée.
 */
Entité* initialiseEntite(void);

/**
 * @brief Vérifie si une entité est encore vivante (points de vie > 0).
 * @param e Pointeur vers l'entité à vérifier.
 * @return true si l'entité est vivante, false sinon.
 */
bool entiteVivante(Entité *e);

#endif