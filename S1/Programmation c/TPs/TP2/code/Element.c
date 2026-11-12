#include "Element.h"

// int elements_egaux(Element a, Element b) {
//     return (strcmp(a.nom, b.nom) == 0 && strcmp(a.description, b.description) == 0 && (a.action ==  b.action));
// }


// void afficherElement(Element e){
//     printf("\n--- Element ----\n");
//     printf("Nom de l'element : %s\n",e.nom);
//     printf("Nom de l'element : %s\n",e.description);
//     // printf("Nom de l'element : %s\n",e.action);
// }

/**
 * @file Element.c
 * @brief Implémentation des fonctions liées aux éléments (Objets, Entités, Joueur, Équipe).
 */

/**
 * @brief Initialise un pointeur d'objet à NULL.
 * @param object Pointeur vers l'objet à initialiser
 */
void initialiserObject(Object **object){
    if(object!= NULL){
        *object = NULL;
    }
}

/**
 * @brief Initialise un pointeur d'équipe à NULL.
 * @param equipe Pointeur vers l'équipe à initialiser
 */
void initialierEquipe(Equipe **equipe){
    if(equipe!= NULL){
        *equipe = NULL;
    }
}

/**
 * @brief Initialise les champs de base d'une entité.
 * @param Entité Pointeur vers l'entité à initialiser
 */
void initialiseEntite(Entité *Entité){
    if(Entité !=NULL){
        Entité->allie = false;
        Entité->classe = AUCUNNE;
        Entité->pt_endurance= 0;
    }
}

/**
 * @brief Initialise le joueur principal en demandant son nom.
 * @param j Pointeur vers le joueur à initialiser
 */
void initialiserJoueur(Joueur *j) {
    char *nom;
    printf("Nom : \n");
    scanf("%s", nom);

    j->nom = nom;
    j->niveau = 0;
    j->XP = 0;
    j->Inventaire= NULL;

// RESPONSABILITÉ HANIA BOUDJAJ NE ME LIÉE PAS A CE CODE MEDIOCRE
    j->Caracteristiques[0] = 10;
    j->Caracteristiques[1] = 5;
    j->Caracteristiques[2] = 5;
    j->Caracteristiques[3] = 10;
}

/**
 * @brief Ajoute un objet dans l'inventaire du joueur.
 * @param j Pointeur vers le joueur
 * @param o Pointeur vers l'objet à ajouter
 */
void ajouterObjectInInventaire(Joueur *j, Object *o) {
    if (j != NULL && o != NULL) {
        ajouter(&(j->Inventaire), o);
    }
}

/**
 * @brief Ajoute un membre dans l'équipe si de la place est disponible.
 * @param equipe Pointeur vers l'équipe
 * @param membre L'entité à ajouter
 */
void ajouterMembreInEquipe(Equipe *equipe, Entité membre) {
    if (equipe != NULL) {
        if (equipe->nb_membre >= 6) {
            printf("L'équipe est pleine !\n");
            return;
        }

        for (int i = 0; i < 6; i++) {
            if (equipe->membres[i].nom == NULL) {
                equipe->membres[i] = membre; 
                equipe->nb_membre++;
                return;
            }
        }
    }
}

/**
 * @brief Supprime un objet de l'inventaire.
 * @param joueur Pointeur vers le joueur
 * @param o Pointeur vers l'objet à supprimer
 */
void supprimerObjectInventaire(Joueur *joueur, Object *o){
    if(joueur != NULL && o != NULL){
            
    }
}

/**
 * @brief Affiche les informations d'un objet.
 * @param o Pointeur vers l'objet à afficher
 */
void afficherObject(Object *o){
    printf("l'object : %s | restant : %d", o->nm_object, o->nb_element);
}

/**
 * @brief Affiche un élément générique (objet ou entité).
 * @param elmt Pointeur vers l'élément générique
 */
void afficherElement(void *elmt){
    if(elmt != NULL){
        TypeElement *typeElmt = (TypeElement *)elmt;

        if (*typeElmt == TYPE_OBJET){
            afficherObject(elmt);
        }
    }
}

/**
 * @brief Compare deux éléments génériques pour vérifier s'ils sont égaux.
 * @param elmt1 Premier élément
 * @param elmt2 Deuxième élément
 * @return true si les éléments sont équivalents, false sinon
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