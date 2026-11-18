#ifndef DATAGAME_H
#define DATAGAME_H

/**
 * @file DataGame.h
 * @brief Définition de la structure et des fonctions de la liste chaînée générique du jeu.
 */

/**
 * @struct DataGame
 * @brief Représente un maillon de la liste chaînée générique.
 */
typedef struct DataGame
{
    void *element;              /**< Pointeur vers la donnée stockée (type générique) */
    struct DataGame *suivant;   /**< Pointeur vers le maillon suivant de la liste */
} DataGame;

/**
 * @brief Initialise et alloue dynamiquement un nouveau maillon de liste chaînée.
 * @return Un pointeur vers le maillon initialisé, ou NULL en cas d'échec.
 */
DataGame *initialiser(void);

/**
 * @brief Affiche l'élément stocké dans le maillon de la liste.
 * @param d La structure DataGame contenant l'élément à afficher.
 */
void afficher(DataGame d);

/**
 * @brief Ajoute un élément générique en tête de la liste chaînée.
 * @param d Pointeur vers le pointeur de la tête de la liste.
 * @param elmt Pointeur vers l'élément à ajouter.
 */
void ajouter(DataGame **d, void *elmt);

/**
 * @brief Recherche un élément spécifique dans la liste chaînée.
 * @param d Pointeur vers la tête de la liste.
 * @param elmt Pointeur vers l'élément recherché.
 * @return Un pointeur vers l'élément trouvé, ou NULL s'il n'est pas présent.
 */
void *chercher(DataGame *d, void *elmt);

/**
 * @brief Recherche et supprime un élément spécifique de la liste chaînée.
 * @param d Pointeur vers le pointeur de la tête de la liste.
 * @param elmt Pointeur vers l'élément à supprimer.
 */
void supprimer(DataGame **d, void *elmt);

#endif