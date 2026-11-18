#ifndef OBJECT_H
#define OBJECT_H
#include "Element.h"
#include "Joueur.h"
#include "Entite.h"

typedef enum {
    SOIN,         /**< Effet de soin */
    MALUS,        /**< Effet de malus */
    ENDURANCE,    /**< Effet sur l'endurance */
} Effet;


typedef struct Object {
    TypeElement type;   /**< Type de l'élément (doit être TYPE_OBJET) */
    int nb_element;     /**< Quantité de cet objet */
    char *nm_object;    /**< Nom de l'objet */
    Effet effet;        /**< Effet de l'objet */
    int val;            /**< Valeur numérique de l'effet */
} Object;


void afficherObject(Object *o);

Object *initialiserObject();

void ajouterObjectInInventaire(Joueur *j, Object *o);

void supprimerObjectInventaire(Joueur *joueur, Object *o);


Object *choisirObjet(Joueur *j);
int utiliserObjet(Joueur *j, Object *obj, Entité *cible);
#endif