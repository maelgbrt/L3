#ifndef JOUEUR_H
#define JOUEUR_H

#include "DataGame.h"
#include <stdio.h>

/**
 * @file Joueur.h
 * @brief Définition de la structure du joueur et des fonctions associées.
 */

/**
 * @struct Joueur
 * @brief Représente le joueur (nom, niveau, XP, inventaire et caractéristiques).
 */
typedef struct Joueur {
    char nom[50];                /**< Nom du joueur */
    int niveau;                  /**< Niveau actuel du joueur */
    int XP;                      /**< Points d'expérience */
    DataGame *Inventaire;        /**< Inventaire sous forme de liste chaînée */
    int Caracteristiques[4];     /**< Tableau des caractéristiques principales */
} Joueur;

/**
 * @brief Affiche les informations d'un joueur.
 * @param j Pointeur vers le joueur à afficher.
 */
void afficherJoueur(Joueur *j);

/**
 * @brief Initialise et alloue dynamiquement un nouveau joueur.
 * @return Un pointeur vers le joueur initialisé, ou NULL en cas d'échec.
 */
Joueur *initialiserJoueur(void);

#endif