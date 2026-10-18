#ifndef ELEMENT_H
#define ELEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum action {
    ATTAQUER,
    FUIR,
    POTION
} Action; 

typedef struct Element {
    char *nom;
    char *description;
    Action action;
    int Force; // négatif pour dégâts et positif pour ajouter pv
} Element;

// Prototypes uniquement (terminés par un point-virgule)
int elements_egaux(Element a, Element b);
void afficherElement(Element e);

#endif