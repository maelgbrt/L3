#ifndef ENTITE_H
#define ENTITE_H
#include "DataGame.h"
#include "Element.h"
#include <stdio.h>


/**
 * @brief Représente la classe d'une entité.
 */
typedef enum {
    AUCUNNE,      /**< Aucune classe (équivalent de NULL) */
    MAGE,         /**< Classe mage */
    GUERRIER,     /**< Classe guerrier */
} Classe;



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

void afficherEntite(Entité*  e);

Entité* initialiseEntite(void);

bool entiteVivante(Entité * e);

#endif