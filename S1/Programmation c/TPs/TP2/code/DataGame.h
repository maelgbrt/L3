#ifndef DATAGAME_H
#define DATAGAME_H

/**
 * @file DataGame.h
 * @brief Définition de la liste chaînée générale pour tout type.
 */

/**
 * @brief Structure représentant un maillon de la liste chaînée.
 */
typedef struct DataGame
{
    void *element;          /**< Pointeur vers la donnée stockée */
    struct DataGame *suivant; /**< Pointeur vers l'élément suivant de la liste */
} DataGame;

/**
 * @brief Initialise la liste chaînée.
 * @param d Pointeur vers le pointeur de la liste à initialiser
 */
void initialiser(DataGame **d);

/** 
 * @brief Affiche la liste chaînée.
 * @param d La liste à afficher
 */
void afficher(DataGame d);

/**
 * @brief Ajoute un élément de type void dans notre liste chaînée.
 * @param d Pointeur vers la liste
 * @param elmt L'élément à ajouter
 */
void ajouter(DataGame **d, void *elmt);

void *chercher(DataGame *d, void * elmt);

void supprimer(DataGame **d, void *  elmt);

// int chercherByAction(DataGame *d,Action action)
#endif