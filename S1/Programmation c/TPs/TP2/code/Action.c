#include "Action.h"
#include "DataGame.h"
#include "Element.h"
#include <stdio.h>


// LES ATTAQUES

void coup_de_poing(Entité * e){
    e->pt_vie -= 10;
}

void lacrymos(Entité * e){
    e->pt_vie -= 20;   
}

void coup_de_mattraque(Entité * e){
    e->pt_vie -= 30;
}

void poubelle_en_feu(Entité * e){
    int val = rand()%10;
    if(val < 5){
        e->pt_vie -= 40;
    }
}


// FUIR
void fuir(Entité * e){
    printf("Vous avez fuis c pas bien");
    e->aura -= 100;
    // prévoir de relancer un nouveu combat
}

// DEFENDRE
void defendre (Entité * e){
    e->pt_endurance += 10;
}



void utiliserCompetence(Entité *e1, Entité *e2){
    if (e1->classe == 0 ){ // Mage
        printf("Vous avez utilisé l'attque suprapuissante de l'autra incroyable");
    }else if (e1->classe == 1) //Guerrier
    {
        printf("Vous avez utilisé le coup d'épee supra mega puissant");
    }else{ //Voleur de Cirano
        printf("gOGO POWER RANGERS");
    }
    e1->aura += 10;
    e2->pt_vie = 0;
}

// renvoie l'adresse du pointeur qui désigne un noeud
DataGame **chercherObjet(DataGame **tete, const char *nom_objet)
{
    for (DataGame **pp = tete; *pp != NULL; pp = &(*pp)->suivant) {
        Object *o = (Object *)(*pp)->element;
        if (o != NULL && o->type == TYPE_OBJET && strcmp(o->nm_object, nom_objet) == 0) {
            return pp; // j->Inventaire si obj en tete, suivant du noeud précédent sinon
        }
    }
    return NULL;
}

void utiliserObject(Joueur *j, const char *nom, Entité *cible){

    DataGame **pp = chercherObjet(&j->Inventaire, nom);
    if ((pp = NULL)) {
        printf("Vous n'avez pas de %s.\n", nom);
    }

    Object *o = (Object *)(*pp)->element;
    if (o->nb_element <= 0) {
        printf("Pas assez de %S dans l'inventaire.\n", nom);
    }

    if (o->effet == SOIN){
        cible->pt_vie += o->val;
    }
    else if (o->effet == MALUS){
        cible->pt_vie -= o->val;
    }
    else if (o->effet == ENDURANCE){
        cible->pt_endurance += o->val;
    }

    o->nb_element -=1;
    printf("Vous avez utilisé %S.\n", nom);

    // supression de la liste
    if (o->nb_element == 0) {
        DataGame *a_liberer = *pp;
        *pp = a_liberer->suivant;
        free(o);
        free(a_liberer);
    }
} 