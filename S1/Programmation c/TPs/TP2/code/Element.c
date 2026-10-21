#include "Element.h"
#include <cinttypes>
#include <stdio.h>

// int elements_egaux(Element a, Element b) {
//     return (strcmp(a.nom, b.nom) == 0 && strcmp(a.description, b.description) == 0 && (a.action ==  b.action));
// }


// void afficherElement(Element e){
//     printf("\n--- Element ----\n");
//     printf("Nom de l'element : %s\n",e.nom);
//     printf("Nom de l'element : %s\n",e.description);
//     // printf("Nom de l'element : %s\n",e.action);
// }


void initialiserJoueur(Joueur *j) {
    char *nom;
    printf("Nom : \n");
    scanf("%s", *nom);

    j->nom = nom;
    j->niveau = 0;
    j->XP = 0;
    j->Object = NULL;
    
    j->Caracteristiques[0] = 10;
    j->Caracteristiques[1] = 5;
    j->Caracteristiques[2] = 5;
    j->Caracteristiques[3] = 10;
}
