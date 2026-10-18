#include <stdio.h>
#include "DataGame.h"

void main () {
    printf("Hello World");

    DataGame * game1;
    initialiser(&game1);

    afficher(game1);

    Element e1;
    e1.nom = "GOVital";
    e1.description = "Todd se traine sur la table";
    e1.Force = 5;
    e1.action = POTION;

    ajouter(&game1,e1);

    afficher(game1);


    Element e2;
    e2.nom = "Bombe";
    e2.description = "Issam explose";
    e2.Force = -7;
    e2.action = ATTAQUER;

    ajouter(&game1,e2);


    afficher(game1);
    
    supprimer(&game1,e2);
    
    afficher(game1);
}