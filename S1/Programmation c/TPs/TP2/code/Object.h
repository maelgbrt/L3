#ifndef OBJECT_H
#define OBJECT_H

#include "Element.h"
#include "Joueur.h"
#include "Entite.h"

/**
 * @file Object.h
 * @brief Définition des structures et des fonctions liées aux objets et à l'inventaire.
 */

/**
 * @enum Effet
 * @brief Représente les différents effets possibles d'un objet.
 */
typedef enum {
    SOIN,         /**< Effet de soin */
    MALUS,        /**< Effet de malus */
    ENDURANCE,    /**< Effet sur l'endurance */
} Effet;

/**
 * @struct Object
 * @brief Représente un objet dans le jeu (quantité, nom, effet, valeur).
 */
typedef struct Object {
    TypeElement type;   /**< Type de l'élément (doit être TYPE_OBJET) */
    int nb_element;     /**< Quantité de cet objet */
    char *nm_object;    /**< Nom de l'objet */
    Effet effet;        /**< Effet de l'objet */
    int val;            /**< Valeur numérique de l'effet */
} Object;

/**
 * @brief Affiche les informations d'un objet.
 * @param o Pointeur vers l'objet à afficher.
 */
void afficherObject(Object *o);

/**
 * @brief Initialise et alloue dynamiquement un nouvel objet.
 * @return Un pointeur vers l'objet initialisé.
 */
Object *initialiserObject(void);

/**
 * @brief Ajoute un objet dans l'inventaire d'un joueur.
 * @param j Pointeur vers le joueur.
 * @param o Pointeur vers l'objet à ajouter.
 */
void ajouterObjectInInventaire(Joueur *j, Object *o);

/**
 * @brief Supprime un objet de l'inventaire d'un joueur.
 * @param joueur Pointeur vers le joueur.
 * @param o Pointeur vers l'objet à supprimer.
 */
void supprimerObjectInventaire(Joueur *joueur, Object *o);

/**
 * @brief Affiche l'inventaire et permet au joueur de choisir un objet.
 * @param j Pointeur vers le joueur.
 * @return Un pointeur vers l'objet choisi, ou NULL si annulé/invalide.
 */
Object *choisirObjet(Joueur *j);

/**
 * @brief Applique l'effet d'un objet sur une entité cible.
 * @param j Pointeur vers le joueur propriétaire.
 * @param obj Pointeur vers l'objet à utiliser.
 * @param cible Pointeur vers l'entité cible de l'objet.
 * @return 1 si l'objet a été utilisé, 0 sinon.
 */
int utiliserObjet(Joueur *j, Object *obj, Entité *cible);

#endif