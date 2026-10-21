#ifndef ELEMENT_H
#define ELEMENT_H



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "DataGame.h"

typedef enum Caracteristiques {
    FORCE,
    VITESSE,
    CHANCE,
    AGILITE
} Caracteristiques;


typedef struct Joueur{
    char * nom;
    int niveau;
    int XP;
    DataGame * Inventaire;
    Caracteristiques Caracteristiques;
    
}Joueur;

typedef struct Entité
{
    char * classe;
    int pt_vie;
    int pt_endurance;
    DataGame * actions;
    bool allie;
}Entité;

typedef struct Equipe{
    DataGame * membres;
    int nb_membre;
}Equipe;

typedef struct Inventaire
{
    int nb_restant;
    char * nm_object;
};

initialiserInventaire();


#endif