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
    printf("Nom : \n");
    scanf("%s", j->nom);
    j->niveau = 1;
    j->XP = 100;
    j->Inventaire= NULL;

// RESPONSABILITÉ HANIA BOUDJAJ NE ME LIÉE PAS A CE CODE MEDIOCRE
    j->Caracteristiques[0] = 10; //FORCE
    j->Caracteristiques[1] = 5; //VITESSE
    j->Caracteristiques[2] = 5; //CHANCE
    j->Caracteristiques[3] = 10; //AGILITE
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
// void ajouterMembreInEquipe(Equipe *equipe, Entité membre) {
//     if (equipe != NULL) {
//         if (equipe->nb_membre >= 6) {
//             printf("L'équipe est pleine !\n");
//             return;
//         }

//         for (int i = 0; i < 6; i++) {
//             if (equipe->membres[i].nom == NULL) {
//                 equipe->membres[i] = membre; 
//                 equipe->nb_membre++;
//                 return;
//             }
//         }
//     }
// }

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
    printf("Object : %s | restant : %d | Effet : %d\n", o->nm_object, o->nb_element,o->effet);
}

void afficherEntite(Entité * e){
    printf("\n=============%s==============\n",e->nom);
    printf("= Aura : %d \n",e->aura);
    printf("= Classe : %d, Pt de Vie : %d \n",e->classe,e->pt_vie);
    printf("= Est un allie : %b, Pt endurance : %d \n",e->allie,e->pt_endurance);
    printf("=================================\n\n");

}
void afficherTableauMocheDeHania(int * c){
    printf("========Caracteristique==========\n");
     printf("= Force : %d\n", c[0]);
     printf("= Vitesse : %d\n", c[1]);
     printf("= Chance : %d\n", c[2]);
     printf("= Agilité : %d\n", c[3]);
}
void afficherJoueur(Joueur * j){
    printf("============Joueur===============\n");
    printf("= Joueur : %s \n", j->nom);
    printf("= XP : %d \n", j->XP);
    printf("= Niveau : %d \n", j->niveau);
    afficherTableauMocheDeHania(j->Caracteristiques);
    afficherInventaire(j->Inventaire);
    printf("=================================\n\n");
}


void ajouterEquipe(Equipe * e, Entité * ent) {
    if (e->nb_membre < MAX_MEMBRES) {
        e->membres[e->nb_membre] = ent; 
        e->nb_membre += 1;            
    }
    else {
        printf("Vous avez déjà 6 membres dans l'équipe.\n"); 
    }
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
        else if (*typeElmt == TYPE_ENTITE)
        {   
            afficherEntite(elmt);
        }
    }
}


bool entiteVivante(Entité *e) {
    if (e == NULL) {
        return false;
    }
    return e->pt_vie > 0; 
}

bool equipeVivante(Equipe e) {
    for (int i = 0; i < MAX_MEMBRES; i++) {
        if (e.membres[i] != NULL && entiteVivante(e.membres[i])) {
            return true; 
        }
    }
    return false; 
}

void afficherEquipe(Equipe * e){
    printf("============Mon Equipe===============\n");

    for (int i = 0; i<e->nb_membre;i++){
        afficherEntite(e->membres[i]);
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

Object *creerObjet(const char *nom, int quantite, int effet, int val) {
    Object *o = malloc(sizeof(*o));
    if (o == NULL) {
        return NULL;
    }

    o->type = TYPE_OBJET;
    o->nb_element = quantite;
    o->nm_object = (char *)nom;
    o->effet = effet;
    o->val = val;
    return o;
}

void remplirEntite(Entité *e, const char *nom, Classe c, int pv, int endu, bool allie) {
    e->type = TYPE_ENTITE;
    e->nom = (char *)nom;
    e->classe = c;
    e->pt_vie = pv;
    e->pt_endurance = endu;
    e->actions = NULL;
    e->allie = allie;
    e->aura = 0;
}

// bool equipeVivante(const Equipe *eq) {
//     for (int i = 0; i < eq->nb_membre; i++)
//         if (eq->membres[i].pt_vie > 0) {
//             return true;
//         }
//     return false;
// }

// Entité *premierVivant(Equipe *eq) {
//     for (int i = 0; i < eq->nb_membre; i++)
//         if (eq->membres[i].pt_vie > 0) {
//             return &eq->membres[i];
//         }
//     return NULL;
// }

int afficherInventaire(DataGame *inv) {
    int n = 0;
    for (DataGame *cur = inv; cur != NULL; cur = cur->suivant) {
        n++;
        printf("%d. ", n);
        afficher(*cur);
    }
    return n;
}

Object *objetNumero(DataGame *inv, int num) {
    int n = 0;
    for (DataGame *cur = inv; cur != NULL; cur = cur->suivant) {
        if (++n == num) {
            return (Object *)cur->element;
        }
    }
    return NULL;
}