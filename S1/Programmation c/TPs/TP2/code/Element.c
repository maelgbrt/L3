#include "Element.h"

int elements_egaux(Element a, Element b) {
    return (strcmp(a.nom, b.nom) == 0 && strcmp(a.description, b.description) == 0 && (a.action ==  b.action));
}


void afficherElement(Element e){
    printf("\n--- Element ----\n");
    printf("Nom de l'element : %s\n",e.nom);
    printf("Nom de l'element : %s\n",e.description);
    // printf("Nom de l'element : %s\n",e.action);
}