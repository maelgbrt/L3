#include <stdio.h>
#include <stdlib.h>
#include "../DataGame.h"
#include "../Element.h" 
#include "../Action.h" 

int main() {

    // ####################################
    // Equipe alliée
    // ####################################

    Equipe allies = { .nb_membre = 2 };
    Entité *a1 = malloc(sizeof(Entité));
    Entité *a2 = malloc(sizeof(Entité));
    if (a1 == NULL || a2 == NULL) {
        return 1;
    }
    initialiseEntite(a1);
    initialiseEntite(a2);
    allies.membres[0] = *a1;
    allies.membres[1] = *a2;

    remplirEntite(a1, "Aya", MAGE, 60, 30, true);
    remplirEntite(a2, "Enzo", GUERRIER, 100, 50, true);
        

    // ####################################
    // Equipe ennemie
    // ####################################

    Equipe ennemis = { .nb_membre = 2 };
    Entité *e1 = malloc(sizeof(Entité));
    Entité *e2 = malloc(sizeof(Entité));
    if (e1 == NULL || e2 == NULL){
        return 1;
    }
    initialiseEntite(e1);
    initialiseEntite(e2);
    ennemis.membres[0] = *e1;
    ennemis.membres[1] = *e2;
    remplirEntite(e1, "ADA", GUERRIER, 50, 20, false);
    remplirEntite(e2, "OCaml", MAGE, 40, 40, false);

    // ###################################
    // Objets
    // ###################################

    Object *ob1 = creerObjet("Potion", 3, SOIN, 10);
    Object *ob2 = creerObjet("Poison", 2, MALUS, 15);
    Object *ob3 = NULL;
    ob1 = creerObjet("Potion",3 , SOIN, 10);
    ob2 = creerObjet("Poison",2 , MALUS, 15);


// ###################################
//              Element
// ###################################

// -------- element_egaux
    // 2 Entités égales
    int egal = elements_egaux(e1,  e1);

    // 2 Entités différentes
    int pasEgal = elements_egaux(e1,  e2);

    // 2 Entités à NULL
    int entNULL = elements_egaux(NULL,  NULL);
    
    // 1 Entité à NULL
    int uneNULL = elements_egaux(e1, NULL);

    // paa le même type
    int mauvType = elements_egaux(a1, ob1);


// -------- afficherElement

    // Afficher un Element
    afficherElement(ob1);
    afficherElement(a1);

    // Afficher un Element NULL
    afficherElement(ob3);

}