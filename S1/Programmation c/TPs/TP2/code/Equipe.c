#include "Equipe.h"

void afficherEquipe(Equipe * e){
    if (e == NULL) return;

    printf("============Mon Equipe===============\n");

    for (int i = 0; i < e->nb_membre; i++) {
        if (e->membres[i] != NULL) {
            afficherEntite(e->membres[i]); 
        }
    }
}



bool equipeVivante(Equipe e) {
    for (int i = 0; i < MAX_MEMBRES; i++) {
        if (e.membres[i] != NULL && entiteVivante(e.membres[i])) {
            return true; 
        }
    }
    return false; 
}




void ajouterEquipe(Equipe * e, Entité * ent) {
    if (e->nb_membre < MAX_MEMBRES) {
        e->membres[e->nb_membre] = ent; 
        e->nb_membre += 1;            
    }
    else {
        printf("Vous avez déjà 6 membres dans l'équipe.\n"); 
    }
}





/**
 * @brief Initialise un pointeur d'équipe à NULL.
 * @param equipe Pointeur vers l'équipe à initialiser
 */
Equipe* initialierEquipe(void) {
    Equipe *e = malloc(sizeof(Equipe));
    if (e != NULL) {
        e->nb_membre = 0;
        
        // Initialiser toutes les cases du tableau de membres à NULL
        for (int i = 0; i < MAX_MEMBRES; i++) {
            e->membres[i] = NULL;
        }
    }
    return e;
}


Entité *  premierEnnemie(Equipe * e){
    return e->membres[0];
}

void fuir(Equipe * e){
 if (e->membres[0] != NULL) {
                e->membres[0]->pt_vie = 0; 
            }
        }