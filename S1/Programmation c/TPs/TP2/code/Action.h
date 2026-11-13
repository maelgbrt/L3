#ifndef ACTION_H
#define ACTION_H

#include "Element.h"

/**
 * @file Action.h
 * @brief Définition des types de fonctions, des actions de combat et des interactions du jeu.
 */

/**
 * @brief Type de pointeur de fonction représentant une attaque sur une entité.
 * @param e Pointeur vers l'entité cible de l'attaque
 */
typedef void (*attaque)(Entité *e);

/**
 * @brief Type de pointeur de fonction représentant une compétence spéciale.
 * @param e Pointeur vers l'entité utilisant ou recevant la compétence
 */
typedef void (*competence)(Entité *e);

/**
 * @brief Action de combat : Coup de poing.
 * @param e Pointeur vers l'entité subissant l'attaque
 */
void coup_de_poing(Entité *e);

/**
 * @brief Action de combat : Utilisation de lacrymogène.
 * @param e Pointeur vers l'entité cible
 */
void lacrymos(Entité *e);

/**
 * @brief Action de combat : Coup de matraque.
 * @param e Pointeur vers l'entité cible
 */
void coup_de_mattraque(Entité *e);

/**
 * @brief Action de combat : Utilisation d'une poubelle en feu.
 * @param e Pointeur vers l'entité cible
 */
void poubelle_en_feu(Entité *e);

/**
 * @brief Action défensive : Permet à l'entité de se défendre.
 * @param e Pointeur vers l'entité qui se défend
 */
void defendre(Entité *e);

/**
 * @brief Action de fuite : Permet à l'entité de tenter de fuir le combat.
 * @param e Pointeur vers l'entité qui fuit
 */
void fuir(Entité *e);

/**
 * @brief Permet d'utiliser une compétence entre deux entités.
 * @param e1 Pointeur vers l'entité initiatrice
 * @param e2 Pointeur vers l'entité cible de la compétence
 */
void utiliserCompetence(Entité *e1, Entité *e2);

/**
 * @brief Recherche un objet spécifique dans une liste chaînée d'éléments.
 * @param tete Pointeur vers la tête de la liste chaînée (DataGame)
 * @param nom_objet Le nom de l'objet recherché
 * @return Un double pointeur vers le nœud contenant l'objet, ou NULL s'il n'est pas trouvé
 */
DataGame **chercherObjet(DataGame **tete, const char *nom_objet);

/**
 * @brief Permet à un joueur d'utiliser un objet sur une entité cible.
 * @param j Pointeur vers le joueur qui utilise l'objet
 * @param nom Le nom de l'objet à utiliser
 * @param cible Pointeur vers l'entité cible de l'objet
 */
void utiliserObject(Joueur *j, const char *nom, Entité *cible);

int menuObjet(Joueur *j, Entité *cible);

#endif