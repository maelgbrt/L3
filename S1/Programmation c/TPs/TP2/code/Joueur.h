#ifndef JOUEUR_H
#define JOUEUR_H
#include "DataGame.h"
#include <stdio.h>


typedef struct Joueur {
    char nom[50];                /**< Nom du joueur */
    int niveau;               /**< Niveau actuel du joueur */
    int XP;                   /**< Points d'expérience */
    DataGame *Inventaire;     /**< Inventaire sous forme de liste chaînée */
    int Caracteristiques[4];  /**< Tableau des caractéristiques principales */
} Joueur;


void afficherJoueur(Joueur * j);

Joueur * initialiserJoueur();

#endif