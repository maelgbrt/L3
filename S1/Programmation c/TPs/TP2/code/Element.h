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

typedef struct Object {
    TypeElement type; 
    int nb_element;
    char * nm_object;
} Object;

typedef struct Entité {
    char * nom;
    char * classe;
    int pt_vie;
    int pt_endurance;
    DataGame * actions; // Fonctionne maintenant grâce à la déclaration anticipée
    bool allie;
    TypeElement type; 
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

bool elements_egaux(void *elmt1, void *elmt2);

#endif