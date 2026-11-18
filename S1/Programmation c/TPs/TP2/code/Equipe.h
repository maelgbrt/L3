#ifndef EQUIPE_H
#define EQUIPE_H
#include "Entite.h"
#include <stdio.h>

/**
 * @brief Représente une équipe composée de plusieurs entités.
 */
typedef struct Equipe {
    Entité *membres[6];        /**< Tableau des membres de l'équipe (max 6) */
    int nb_membre;            /**< Nombre actuel de membres dans l'équipe */
} Equipe;

void afficherEquipe(Equipe * e);

void ajouterEquipe(Equipe * e, Entité * ent);

bool equipeVivante(const Equipe  eq);

Equipe * initialierEquipe();

Entité * premierEnnemie(Equipe * e);


// FUIR
/**
 * @brief Permet à une entité de fuir, ce qui réduit son aura.
 * @param e Pointeur vers l'entité qui fuit
 */
void fuir(Equipe *e);
#endif