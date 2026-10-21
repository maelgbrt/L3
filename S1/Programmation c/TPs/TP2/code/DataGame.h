#ifndef DATAGAME_H
#define DATAGAME_H
#include "Element.h"


// Defintition d'une liste chainée
typedef struct DataGame
{
    void * element;
    DataGame *suivant;
}DataGame;

void initialiser(DataGame **d);

void afficher(DataGame d);

void ajouter(DataGame **d, Element elmt);

Element *chercher(DataGame *d, Element elmt);

void supprimer(DataGame **d, Element elmt);


// int chercherByAction(DataGame *d,Action action){
#endif