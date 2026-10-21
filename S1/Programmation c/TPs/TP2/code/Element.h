#ifndef ELEMENT_H
#define ELEMENT_H



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "DataGame.h"

// typedef enum Caracteristiques {
//     FORCE, 
//     VITESSE,
//     CHANCE,
//     AGILITE 
// } Caracteristiques;

//     FORCE, 
//     VITESSE,
//     CHANCE,
//     AGILITE 



typedef struct Joueur{
    char * nom;
    int niveau;
    int XP;
    DataGame * Object;
    int Caracteristiques[4];

    
}Joueur;

typedef struct Entite
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

typedef struct Object
{
    int nb_restant;
    char * nm_object;
};

// Initialise un objet à vide
void initialiserObject(Object obj);

// Initialise une entité à vide
void initialiserEntite(Entite);

// Initialise l'équipe à vide
void initialiserEquipe(Equipe eq);

// Initialise un joueur à vide
void initialiserJoueur(Joueur *j);


#endif