#include "Action.h"
#include "DataGame.h"
#include "Element.h"
#include <stdio.h>

/**
 * @file Action.c
 * @brief Implémentation des actions de combat, des compétences et de la gestion des objets.
 */

// LES ATTAQUES

/**
 * @brief Inflige des dégâts de coup de poing à une entité.
 * @param e Pointeur vers l'entité subissant l'attaque
 */
void coup_de_poing(Entité * e){
    e->pt_vie -= 10;
}

/**
 * @brief Inflige des dégâts de lacrymogène à une entité.
 * @param e Pointeur vers l'entité subissant l'attaque
 */
void lacrymos(Entité * e){
    e->pt_vie -= 20;   
}

/**
 * @brief Inflige des dégâts de coup de matraque à une entité.
 * @param e Pointeur vers l'entité subissant l'attaque
 */
void coup_de_mattraque(Entité * e){
    e->pt_vie -= 30;
}

/**
 * @brief Inflige des dégâts avec une poubelle en feu selon une probabilité aléatoire.
 * @param e Pointeur vers l'entité subissant l'attaque
 */
void poubelle_en_feu(Entité * e){
    int val = rand()%10;
    if(val < 5){
        e->pt_vie -= 40;
    }
}


// FUIR
/**
 * @brief Permet à une entité de fuir, ce qui réduit son aura.
 * @param e Pointeur vers l'entité qui fuit
 */
void fuir(Entité * e){
    printf("Vous avez fuis c pas bien");
    e->aura -= 100;
    // prévoir de relancer un nouveu combat
}

/**
 * @brief Permet à une entité de se défendre pour augmenter son endurance.
 * @param e Pointeur vers l'entité qui se défend
 */
void defendre (Entité * e){
    e->pt_endurance += 10;
}

/**
 * @brief Utilise une compétence spéciale en fonction de la classe de l'entité.
 * @param e1 Pointeur vers l'entité initiatrice
 * @param e2 Pointeur vers l'entité cible
 */
void utiliserCompetence(Entité *e1, Entité *e2){
    if (e1->classe == 0 ){ // Mage
        printf("Vous avez utilisé l'attque suprapuissante de l'autra incroyable");
    }else if (e1->classe == 1) //Guerrier
    {
        printf("Vous avez utilisé le coup d'épee supra mega puissant");
    }else{ //Voleur de Cirano
        printf("gOGO POWER RANGERS");
    }
    e1->aura += 10;
    e2->pt_vie = 0;
}

/**
 * @brief Recherche un objet dans une liste chaînée et renvoie l'adresse de son pointeur de nœud.
 * @param tete Pointeur vers la tête de la liste chaînée
 * @param nom_objet Le nom de l'objet recherché
 * @return Un double pointeur vers le nœud contenant l'objet, ou NULL s'il n'est pas trouvé
 */
DataGame **chercherObjet(DataGame **tete, const char *nom_objet)
{
    for (DataGame **pp = tete; *pp != NULL; pp = &(*pp)->suivant) {
        Object *o = (Object *)(*pp)->element;
        if (o != NULL && o->type == TYPE_OBJET && strcmp(o->nm_object, nom_objet) == 0) {
            return pp; // j->Inventaire si obj en tete, suivant du noeud précédent sinon
        }
    }
    return NULL;
}

/**
 * @brief Permet à un joueur d'utiliser un objet de son inventaire sur une cible.
 * @param j Pointeur vers le joueur
 * @param nom Le nom de l'objet à utiliser
 * @param cible Pointeur vers l'entité cible
 */
void utiliserObject(Joueur *j, const char *nom, Entité *cible){

    DataGame **pp = chercherObjet(&j->Inventaire, nom);
    if (pp == NULL) { // Correction de l'affectation en comparaison
        printf("Vous n'avez pas de %s.\n", nom);
        return;
    }

    Object *o = (Object *)(*pp)->element;
    if (o->nb_element <= 0) {
        printf("Pas assez de l'élément dans l'inventaire.\n");
        return;
    }

    if (o->effet == SOIN){
        cible->pt_vie += o->val;
    }
    else if (o->effet == MALUS){
        cible->pt_vie -= o->val;
    }
    else if (o->effet == ENDURANCE){
        cible->pt_endurance += o->val;
    }

    o->nb_element -= 1;
    printf("Vous avez utilisé l'objet.\n");

    // suppression de la liste si épuisé
    if (o->nb_element == 0) {
        DataGame *a_liberer = *pp;
        *pp = a_liberer->suivant;
        free(o);
        free(a_liberer);
    }
}