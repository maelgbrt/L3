#include "Equipe.h"

/**
 * @brief Affiche l'ensemble des membres d'une équipe.
 * @param e Pointeur vers l'équipe à afficher.
 */
void afficherEquipe(Equipe *e){
    if (e == NULL) return;

    printf("============Mon Equipe===============\n");

    for (int i = 0; i < e->nb_membre; i++) {
        if (e->membres[i] != NULL) {
            afficherEntite(e->membres[i]); 
        }
    }
}

/**
 * @brief Vérifie si une équipe possède encore au moins un membre vivant.
 * @param e L'équipe à vérifier (passage par valeur).
 * @return true si au moins un membre est vivant, false sinon.
 */
bool equipeVivante(Equipe e) {
    for (int i = 0; i < MAX_MEMBRES; i++) {
        if (e.membres[i] != NULL && entiteVivante(e.membres[i])) {
            return true; 
        }
    }
    return false; 
}

/**
 * @brief Ajoute une entité à une équipe si elle n'est pas pleine.
 * @param e Pointeur vers l'équipe.
 * @param ent Pointeur vers l'entité à ajouter.
 */
void ajouterEquipe(Equipe *e, Entité *ent) {
    if (e->nb_membre < MAX_MEMBRES) {
        e->membres[e->nb_membre] = ent; 
        e->nb_membre += 1;            
    }
    else {
        printf("Vous avez déjà 6 membres dans l'équipe.\n"); 
    }
}

/**
 * @brief Initialise et alloue dynamiquement une équipe.
 * @return Un pointeur vers l'équipe initialisée, ou NULL en cas d'échec.
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

/**
 * @brief Récupère la première entité ennemie de l'équipe.
 * @param e Pointeur vers l'équipe ennemie.
 * @return Un pointeur vers la première entité.
 */
Entité * premierEnnemie(Equipe *e){
    return e->membres[0];
}

/**
 * @brief Permet à l'équipe de fuir (met les PV du premier membre à 0).
 * @param e Pointeur vers l'équipe qui fuit.
 */
void fuir(Equipe *e){
    if (e->membres[0] != NULL) {
        e->membres[0]->pt_vie = 0; 
    }
}