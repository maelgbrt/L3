#include "Inventaire.h"

void afficherInventaire(DataGame *inv) {
    int n = 0;
    for (DataGame *cur = inv; cur != NULL; cur = cur->suivant) {
        n++;
        printf("%d. ", n);
        afficher(*cur);
    }
}

DataGame * initialiserInventaire(){
    DataGame * inventaire = malloc(sizeof(DataGame));
    if(inventaire!=NULL){
        return inventaire;
    }
}