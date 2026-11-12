#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "DataGame.h"

/**
 * @file Element.h
 * @brief Définition des structures et types de base du jeu (Objets, Entités, Équipe, Joueur).
 */

/**
 * @brief Représente le type d'un élément (Objet ou Entité).
 */
typedef enum {
    TYPE_OBJET,   /**< L'élément est un objet */
    TYPE_ENTITE   /**< L'élément est une entité (personnage) */
} TypeElement;

/**
 * @brief Représente la classe d'une entité.
 */
typedef enum {
    AUCUNNE,      /**< Aucune classe (équivalent de NULL) */
    MAGE,         /**< Classe mage */
    GUERRIER,     /**< Classe guerrier */
} Classe;

/**
 * @brief Représente l'effet d'un objet.
 */
typedef enum {
    SOIN,         /**< Effet de soin */
    MALUS,        /**< Effet de malus */
    ENDURANCE,    /**< Effet sur l'endurance */
} Effet;

/**
 * @brief Représente un objet dans le jeu.
 */
typedef struct Object {
    TypeElement type;   /**< Type de l'élément (doit être TYPE_OBJET) */
    int nb_element;     /**< Quantité de cet objet */
    char *nm_object;    /**< Nom de l'objet */
    Effet effet;        /**< Effet de l'objet */
    int val;            /**< Valeur numérique de l'effet */
} Object;

/**
 * @brief Représente une entité (personnage, ennemi, etc.).
 */
typedef struct Entité {
    TypeElement type;         /**< Type de l'élément (doit être TYPE_ENTITE) */
    char *nom;                /**< Nom de l'entité */
    Classe classe;            /**< Classe du personnage */
    int pt_vie;               /**< Points de vie actuels */
    int pt_endurance;         /**< Points d'endurance actuels */
    DataGame *actions;        /**< Liste des actions disponibles (déclaration anticipée) */
    bool allie;               /**< Vrai si c'est un allié, faux sinon */
    int aura;                 /**< Niveau d'aura */
} Entité;

/**
 * @brief Représente une équipe composée de plusieurs entités.
 */
typedef struct Equipe {
    Entité membres[6];        /**< Tableau des membres de l'équipe (max 6) */
    int nb_membre;            /**< Nombre actuel de membres dans l'équipe */
} Equipe;

/**
 * @brief Représente le joueur principal.
 */
typedef struct Joueur {
    char *nom;                /**< Nom du joueur */
    int niveau;               /**< Niveau actuel du joueur */
    int XP;                   /**< Points d'expérience */
    DataGame *Inventaire;     /**< Inventaire sous forme de liste chaînée */
    int Caracteristiques[4];  /**< Tableau des caractéristiques principales */
} Joueur;

/**
 * @brief Affiche un élément générique de type void.
 * @param elmt Pointeur vers l'élément à afficher
 */
void afficherElement(void *elmt);

/**
 * @brief Affiche les détails d'un objet.
 * @param o Pointeur vers l'objet à afficher
 */
void afficherObject(Object *o);

/**
 * @brief Vérifie si deux éléments génériques sont égaux.
 * @param elmt1 Premier élément
 * @param elmt2 Deuxième élément
 * @return true si les éléments sont égaux, false sinon
 */
bool elements_egaux(void *elmt1, void *elmt2);

#endif