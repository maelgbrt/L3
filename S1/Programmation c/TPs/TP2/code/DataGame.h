#ifndef DATAGAME_H
#define DATAGAME_H




// Defintition d'une liste chainée
typedef struct DataGame
{
    void * element;
    struct DataGame * suivant;
}DataGame;

void initialiser(DataGame **d);

void afficher(DataGame d);

void ajouter(DataGame **d, void * elmt);


// void *chercher(DataGame *d, void * elmt);

// void supprimer(DataGame **d, void *  elmt);


// int chercherByAction(DataGame *d,Action action){
#endif