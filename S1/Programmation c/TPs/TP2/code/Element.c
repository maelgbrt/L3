#include "Element.h"
#include <stddef.h>  // Pour NULL
#include <string.h>  // Pour strcmp
#include "Object.h"
#include "Entite.h"
#include "Action.h"     // Si afficherAttaque est défini ici
#include "Inventaire.h" // Si afficherInventaire est défini ici

/**
 * @file Element.c
 * @brief Implémentation des fonctions liées aux éléments génériques (Objets, Entités, Joueur, Équipe).
 */

/**
 * @brief Affiche un élément générique (objet, entité, action ou inventaire) selon son type.
 * @param elmt Pointeur vers l'élément générique.
 */
void afficherElement(void *elmt) {
    if (elmt != NULL) {
        TypeElement *typeElmt = (TypeElement *)elmt;

        if (*typeElmt == TYPE_OBJET) {
            afficherObject(elmt);
        } else if (*typeElmt == TYPE_ENTITE) {   
            afficherEntite(elmt);
        } else if (*typeElmt == TYPE_ACTION) {
            afficherAttaque(elmt);
        } else if (*typeElmt == TYPE_INVENTAIRE) {
            afficherInventaire(elmt);
        }
    }
}

/**
 * @brief Compare deux éléments génériques pour vérifier s'ils sont égaux.
 * @param elmt1 Premier élément.
 * @param elmt2 Deuxième élément.
 * @return true si les éléments sont équivalents, false sinon.
 */
bool elements_egaux(void *elmt1, void *elmt2) {
    if (elmt1 == NULL || elmt2 == NULL) {
        return elmt1 == elmt2;
    }

    TypeElement *type1 = (TypeElement *)elmt1;
    TypeElement *type2 = (TypeElement *)elmt2;

    if (*type1 != *type2) {
        return false;
    }

    if (*type1 == TYPE_OBJET) {
        Object *o1 = (Object *)elmt1;
        Object *o2 = (Object *)elmt2;
        if (o1->nm_object != NULL && o2->nm_object != NULL) {
            return strcmp(o1->nm_object, o2->nm_object) == 0;
        }
        return false;
    } 
    else if (*type1 == TYPE_ENTITE) {
        Entité *e1 = (Entité *)elmt1;
        Entité *e2 = (Entité *)elmt2;
        if (e1->classe != AUCUNNE && e2->classe != AUCUNNE) {
            return e1->classe == e2->classe;
        }
    }

    return false;
}