#ifndef ACTION_H
#define ACTION_H

#include "Element.h"
#include "Entite.h"
#include "Joueur.h"

/**
 * @file Action.h
 * @brief Définition des types de fonctions et des actions de combat.
 */

/**
 * @brief Type de pointeur de fonction représentant une attaque sur une entité.
 * @param e Pointeur vers l'entité cible de l'attaque.
 */
typedef void (*attaque)(Entité *e);

/**
 * @brief Type de pointeur de fonction représentant une compétence spéciale.
 * @param e Pointeur vers l'entité utilisant ou recevant la compétence.
 */
typedef void (*competence)(Entité *e);

/**
 * @struct ActionStruct
 * @brief Représente une action de jeu (nom, fonction d'attaque et type).
 */
typedef struct action {
    char nom[50];          /**< Nom de l'action */
    attaque attaque;       /**< Pointeur vers la fonction d'attaque correspondante */
    TypeElement type;      /**< Type de l'élément */
} ActionStruct;

/**
 * @brief Action de combat : Coup de poing.
 * @param e Pointeur vers l'entité subissant l'attaque.
 */
void coup_de_poing(Entité *e);

/**
 * @brief Action de combat : Utilisation de lacrymogène.
 * @param e Pointeur vers l'entité cible.
 */
void lacrymos(Entité *e);

/**
 * @brief Action de combat : Coup de matraque.
 * @param e Pointeur vers l'entité cible.
 */
void coup_de_mattraque(Entité *e);

/**
 * @brief Action de combat : Utilisation d'une poubelle en feu.
 * @param e Pointeur vers l'entité cible.
 */
void poubelle_en_feu(Entité *e);

/**
 * @brief Action défensive : Permet à l'entité de se défendre.
 * @param e Pointeur vers l'entité qui se défend.
 */
void defendre(Entité *e);

/**
 * @brief Affiche les informations d'une action.
 * @param action Pointeur vers l'action à afficher.
 */
void afficherAttaque(ActionStruct *action);

/**
 * @brief Initialise et alloue dynamiquement une structure d'action.
 * @return Un pointeur vers l'ActionStruct initialisée.
 */
ActionStruct *initialiserAction(void);

#endif