#include "Object.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @file Object.c
 * @brief Implémentation de la gestion des objets et de l'inventaire.
 */

/**
 * @brief Affiche les informations d'un objet.
 * @param o Pointeur vers l'objet à afficher.
 */
void afficherObject(Object *o) {
    if (o == NULL) return;
    printf("Object : %s | restant : %d | Effet : %d\n", o->nm_object, o->nb_element, o->effet);
}

/**
 * @brief Initialise et alloue dynamiquement un nouvel objet.
 * @return Un pointeur vers l'objet initialisé, ou NULL en cas d'échec.
 */
Object *initialiserObject(void) {
    Object *o = malloc(sizeof(Object));
    if (o != NULL) {
        o->type = TYPE_OBJET;
        o->nb_element = 0;
        o->val = 0;
        o->nm_object = NULL;
    }
    return o;
}

/**
 * @brief Ajoute un objet dans l'inventaire d'un joueur.
 * @param j Pointeur vers le joueur.
 * @param o Pointeur vers l'objet à ajouter.
 */
void ajouterObjectInInventaire(Joueur *j, Object *o) {
    if (j != NULL && o != NULL) {
        ajouter(&(j->Inventaire), o);
    }
}

/**
 * @brief Supprime un objet de l'inventaire d'un joueur.
 * @param joueur Pointeur vers le joueur.
 * @param o Pointeur vers l'objet à supprimer.
 */
void supprimerObjectInventaire(Joueur *joueur, Object *o) {
    if (joueur != NULL && o != NULL) {
        // Logique de suppression à implémenter selon votre gestion de liste chaînée DataGame
    }
}

/**
 * @brief Affiche l'inventaire et retourne l'objet choisi.
 * @param j Pointeur vers le joueur dont on consulte l'inventaire.
 * @return Un pointeur vers l'objet choisi, ou NULL si annulé / invalide.
 */
Object *choisirObjet(Joueur *j) {
    if (j == NULL || j->Inventaire == NULL) {
        printf("Votre inventaire est vide !\n");
        return NULL;
    }

    printf("\n====== INVENTAIRE DE %s ======\n", j->nom);

    int index = 1;
    for (DataGame *c = j->Inventaire; c != NULL; c = c->suivant, index++) {
        Object *obj = (Object *)(c->element);
        if (obj != NULL)
            printf("%d - %s (Quantité : %d, Valeur : %d)\n",
                   index, obj->nm_object, obj->nb_element, obj->val);
    }

    int choix;
    printf("Choisissez un objet à utiliser (0 pour annuler) : ");
    if (scanf("%d", &choix) != 1) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf("Saisie invalide.\n");
        return NULL;
    }
    if (choix == 0) {
        printf("Utilisation d'objet annulée.\n");
        return NULL;
    }

    index = 1;
    for (DataGame *c = j->Inventaire; c != NULL; c = c->suivant, index++) {
        if (index == choix) {
            Object *obj = (Object *)(c->element);
            if (obj != NULL && obj->nb_element > 0)
                return obj;
            break;
        }
    }

    printf("Objet invalide ou épuisé.\n");
    return NULL;
}

/**
 * @brief Applique l'effet d'un objet sur une entité cible.
 * @param j Pointeur vers le joueur propriétaire de l'objet.
 * @param obj Pointeur vers l'objet à utiliser.
 * @param cible Pointeur vers l'entité cible.
 * @return 1 si l'objet a été utilisé avec succès, 0 sinon.
 */
int utiliserObjet(Joueur *j, Object *obj, Entité *cible) {
    if (j == NULL || obj == NULL || cible == NULL)
        return 0;

    switch (obj->effet) {
    case SOIN:
        cible->pt_vie += obj->val;
        printf("✨ %s récupère %d PV grâce à %s !\n", cible->nom, obj->val, obj->nm_object);
        break;
    case ENDURANCE:
        cible->pt_endurance += obj->val;
        printf("⚡ %s récupère %d points d'endurance grâce à %s !\n", cible->nom, obj->val, obj->nm_object);
        break;
    case MALUS:
        cible->pt_vie -= obj->val;
        printf("⚠️ Aïe ! %s subit %d dégâts de %s.\n", cible->nom, obj->val, obj->nm_object);
        break;
    default:
        printf("Effet d'objet inconnu.\n");
        return 0;
    }

    obj->nb_element--;
    if (obj->nb_element <= 0)
        supprimerObjectInventaire(j, obj); // ne plus toucher à obj après

    return 1;
}