#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataGame.h"

void initialiser(DataGame **d) {
    if (d != NULL) {
        *d = NULL;
    }
}

void afficher(DataGame d){
        afficherElement(d.element);
}

void ajouter(DataGame **d, void * elmt)
{
    DataGame *NouveauNoeud = malloc(sizeof(DataGame));
    if (NouveauNoeud == NULL){
        return;
    };

    NouveauNoeud->element = elmt;
    NouveauNoeud->suivant = *d;
    *d = NouveauNoeud;
}

void supprimer(DataGame **d, void * elmt) {

    DataGame *courant = *d;
    DataGame *precedent = NULL;

    while (courant != NULL && !elements_egaux(courant->element, elmt)) {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant == NULL) return;

    if (precedent == NULL) {
        *d = courant->suivant;
    } 
    else {
        precedent->suivant = courant->suivant;
    }
    free(courant);

}





