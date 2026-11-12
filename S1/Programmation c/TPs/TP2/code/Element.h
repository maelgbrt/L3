#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "DataGame.h"
// Définition des types possibles
typedef enum {
    TYPE_OBJET,
    TYPE_ENTITE
} TypeElement;

typedef enum {
    AUCUNNE, // équivalent de NULL
    MAGE,
    GUERRIER,
}Classe;

typedef enum {
    SOIN,
    MALUS,
    ENDURANCE,
}Effet;

typedef struct Object {
    TypeElement type; 
    int nb_element;
    char * nm_object;
    Effet effet;
    int val;
} Object;

typedef struct Entité {
    TypeElement type;
    char * nom;
    Classe classe;
    int pt_vie;
    int pt_endurance;
    DataGame * actions; // Fonctionne maintenant grâce à la déclaration anticipée
    bool allie;
    int aura;
} Entité;

typedef struct Equipe {
    Entité membres[6];
    int nb_membre;
} Equipe;

typedef struct Joueur {
    char * nom;
    int niveau;
    int XP;
    DataGame * Inventaire; // Fonctionne aussi ici
    int Caracteristiques[4];
} Joueur;


void afficherElement(void * elmt);

void afficherObject(Object * o);

bool elements_egaux(void *elmt1, void *elmt2);

Object *creerObjet(const char *nom, int quantite, int effet);

void remplirEntite(Entité *e, const char *nom, Classe c, int pv, int endu, bool allie);

bool equipeVivante(const Equipe *eq);

Entité *premierVivant(Equipe *eq);




#endif