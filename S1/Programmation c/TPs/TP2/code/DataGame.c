#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DataGame.h"

void initialiser(DataGame **d) {
    if (d != NULL) {
        *d = NULL;
    }
}



void afficher(DataGame *d){
    if(d!=NULL){
        afficherElement(d->element);
    }
}

void ajouter(DataGame **d, Element elmt)
{
    DataGame *NouveauNoeud = malloc(sizeof(DataGame));
    if (NouveauNoeud == NULL){
        return;
    };

    NouveauNoeud->element = elmt;
    NouveauNoeud->suivant = *d;
    *d = NouveauNoeud;
}

Element *chercher(DataGame *d, Element elmt) {
    while (d != NULL) {
        if (elements_egaux(d->element, elmt)) {
            return &(d->element); 
        }
        d = d->suivant; 
    }
    return NULL; 
}

// int chercherByAction(DataGame *d,Action action){
//     while(d!=NULL){
//         if(d->element.action ==  action){
//            afficherElement(d->element); 
//         }
//     }
// }



void supprimer(DataGame **d, Element elmt) {

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





