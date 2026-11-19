#ifndef EQUIPE_H
#define EQUIPE_H
#include "Entite.h"
#include <stdio.h>

/**
 * @file Equipe.h
 * @brief Gestion des équipes d'entités pour le jeu de rôle.
 */

/**
 * @struct Equipe
 * @brief Représente une équipe composée de plusieurs entités[cite: 1].
 */
typedef struct Equipe {
    Entité *membres[6];        /**< Tableau des membres de l'équipe (max 6)[cite: 1] */
    int nb_membre;            /**< Nombre actuel de membres dans l'équipe */
} Equipe;

/**
 * @brief Affiche les informations de l'équipe et de ses membres.
 * @param e Pointeur vers l'équipe à afficher.
 */
void afficherEquipe(Equipe *e);

/**
 * @brief Ajoute une entité à l'équipe.
 * @param e Pointeur vers l'équipe.
 * @param ent Pointeur vers l'entité à ajouter.
 */
void ajouterEquipe(Equipe *e, Entité *ent);

/**
 * @brief Vérifie si l'équipe possède encore des membres vivants.
 * @param eq L'équipe à vérifier (passée par constante).
 * @return true si l'équipe est vivante, false sinon.
 */
bool equipeVivante(const Equipe eq);

/**
 * @brief Initialise et alloue dynamiquement une nouvelle équipe.
 * @return Un pointeur vers l'équipe initialisée.
 */
Equipe* initialierEquipe(void);

/**
 * @brief Récupère le premier ennemi de l'équipe.
 * @param e Pointeur vers l'équipe ennemie.
 * @return Pointeur vers l'entité ennemie.
 */
Entité* premierEnnemie(Equipe *e);

/**
 * @brief Permet à l'équipe de fuir.
 * @param e Pointeur vers l'équipe qui tente de fuir.
 */
void fuir(Equipe *e);

#endif