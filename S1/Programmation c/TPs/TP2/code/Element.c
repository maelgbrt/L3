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

void initialiserObject(Object **object){
    if(object!= NULL){
        *object = NULL;
    }
}

void initialierEquipe(Equipe **equipe){
    if(equipe!= NULL){
        *equipe = NULL;
    }
}

void initialiseEntite(Entité *Entité){
    if(Entité !=NULL){
        Entité->allie = NULL;
        Entité->classe = AUCUNNE;
        Entité->pt_endurance= 0;
}
};

void initialiserJoueur(Joueur *j) {
    char *nom;
    printf("Nom : \n");
    scanf("%s", nom);

    j->nom = nom;
    j->niveau = 0;
    j->XP = 0;
    j->Inventaire= NULL;


//RESPONSABILITÉ HANIA BOUDJAJ NE ME LIÉE PAS A CE CODE MEDIOCRE
    j->Caracteristiques[0] = 10;
    j->Caracteristiques[1] = 5;
    j->Caracteristiques[2] = 5;
    j->Caracteristiques[3] = 10;
}

void ajouterObjectInInventaire(Joueur *j, Object *o) {
    if (j != NULL && o != NULL) {
        ajouter(&(j->Inventaire), o);
    }
}

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

void supprimerObjectInventaire(Joueur * joueur,Object * o){
    if(joueur!=NULL && o != NULL){
            
    }
}

void afficherObject(Object * o){
    printf("l'object : %s | restant : %d",o->nm_object,o->nb_element);
}

void afficherElement(void * elmt){
    if(elmt!= NULL){
        TypeElement *typeElmt = (TypeElement * )elmt;

        if (*typeElmt == TYPE_OBJET){
            afficherObject(elmt);
        }
    }
}

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

Object *creerObjet(const char *nom, int quantite, int effet) {
    Object *o = malloc(sizeof(*o));
    if (o == NULL) {
        return NULL;
    }

    o->type = TYPE_OBJET;
    o->nb_element = quantite;
    o->nm_object = (char *)nom;
    o->effet = effet;
    
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

bool equipeVivante(const Equipe *eq) {
    for (int i = 0; i < eq->nb_membre; i++)
        if (eq->membres[i].pt_vie > 0) {
            return true;
        }
    return false;
}

Entité *premierVivant(Equipe *eq) {
    for (int i = 0; i < eq->nb_membre; i++)
        if (eq->membres[i].pt_vie > 0) {
            return &eq->membres[i];
        }
    return NULL;
}