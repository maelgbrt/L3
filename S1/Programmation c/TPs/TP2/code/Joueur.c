#include "Joueur.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file Joueur.c
 * @brief Implémentation de la gestion du joueur, de ses caractéristiques et de son affichage.
 */

/**
 * @brief Affiche les informations complètes d'un joueur.
 * @param j Pointeur vers le joueur à afficher.
 */
void afficherJoueur(Joueur *j) {
    if (j == NULL) return;
    printf("============Joueur===============\n");
    printf("= Joueur : %s \n", j->nom);
    printf("= XP : %d \n", j->XP);
    printf("= Niveau : %d \n", j->niveau);
    afficherTableauMocheDeHania(j->Caracteristiques);
    afficherInventaire(j->Inventaire);
    printf("=================================\n\n");
}

/**
 * @brief Initialise et alloue dynamiquement un nouveau joueur en demandant son nom.
 * @return Un pointeur vers le joueur initialisé, ou NULL en cas d'échec d'allocation.
 */
Joueur *initialiserJoueur(void) {
    Joueur *j = malloc(sizeof(Joueur));
    if (j != NULL) {
        printf("Nom : \n");
        scanf("%49s", j->nom); // Limité à 49 caractères pour éviter les dépassements de tampon
        j->niveau = 1;
        j->XP = 100;
        j->Inventaire = NULL;

        // Caractéristiques initiales
        j->Caracteristiques[0] = 10; // FORCE
        j->Caracteristiques[1] = 5;  // VITESSE
        j->Caracteristiques[2] = 5;  // CHANCE
        j->Caracteristiques[3] = 10; // AGILITE
    }
    return j;
}

/**
 * @brief Affiche les caractéristiques du joueur.
 * @param c Tableau d'entiers représentant les caractéristiques.
 */
void afficherTableauMocheDeHania(int *c) {
    if (c == NULL) return;
    printf("========Caracteristique==========\n");
    printf("= Force : %d\n", c[0]);
    printf("= Vitesse : %d\n", c[1]);
    printf("= Chance : %d\n", c[2]);
    printf("= Agilité : %d\n", c[3]);
}