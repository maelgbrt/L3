#include "Action.h"
#include "DataGame.h"
#include "Element.h"
#include "Object.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file Action.c
 * @brief Implémentation des actions de combat, des compétences et des structures d'action.
 */

/**
 * @brief Inflige des dégâts de coup de poing à une entité.
 * @param e Pointeur vers l'entité subissant l'attaque.
 */
void coup_de_poing(Entité *e) {
    e->pt_vie -= 10;
}

/**
 * @brief Inflige des dégâts de lacrymogène à une entité.
 * @param e Pointeur vers l'entité subissant l'attaque.
 */
void lacrymos(Entité *e) {
    e->pt_vie -= 20;   
}

/**
 * @brief Inflige des dégâts de coup de matraque à une entité.
 * @param e Pointeur vers l'entité subissant l'attaque.
 */
void coup_de_mattraque(Entité *e) {
    e->pt_vie -= 30;
}

/**
 * @brief Inflige des dégâts avec une poubelle en feu selon une probabilité aléatoire.
 * @param e Pointeur vers l'entité subissant l'attaque.
 */
void poubelle_en_feu(Entité *e) {
    int val = rand() % 10;
    if (val < 5) {
        e->pt_vie -= 40;
    }
}

/**
 * @brief Initialise et alloue dynamiquement une structure d'action.
 * @return Un pointeur vers l'ActionStruct initialisée, ou NULL en cas d'échec.
 */
ActionStruct *initialiserAction(void) {
    ActionStruct *a = malloc(sizeof(ActionStruct));
    if (a != NULL) {
        a->type = TYPE_ACTION;
        a->nom[0] = '\0';
        a->attaque = NULL;
    }
    return a;
}

/**
 * @brief Affiche le nom d'une attaque.
 * @param action Pointeur vers l'ActionStruct à afficher.
 */
void afficherAttaque(ActionStruct *action) {
    if (action != NULL) {
        printf("%s", action->nom);
    }
}

/**
 * @brief Permet à une entité de se défendre pour augmenter son endurance.
 * @param e Pointeur vers l'entité qui se défend.
 */
void defendre(Entité *e) {
    if (e != NULL) {
        e->pt_endurance += 10;
    }
}

/**
 * @brief Utilise une compétence spéciale en fonction de la classe de l'entité.
 * @param e1 Pointeur vers l'entité initiatrice.
 * @param e2 Pointeur vers l'entité cible.
 */
void utiliserCompetence(Entité *e1, Entité *e2) {
    if (e1 == NULL || e2 == NULL) return;

    if (e1->classe == 0) { // Mage
        printf("Vous avez utilisé l'attaque supra-puisssante de l'aura incroyable !\n");
    } else if (e1->classe == 1) { // Guerrier
        printf("Vous avez utilisé le coup d'épée supra méga puissant !\n");
    } else { // Voleur de Cyrano
        printf("GOGO POWER RANGERS !\n");
    }
    e1->aura += 10;
    e2->pt_vie = 0;
}