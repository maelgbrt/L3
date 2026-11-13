#include <stdbool.h>
#include <stdio.h>
#include "DataGame.h"
#include "Element.h"
#include "Action.h"

int main () {
    /**
     * @brief test de dioxygen
     * 
     * @param test1 entier
     * @param test2 entier
     * @return bienveillance pas comme ces duex connards
     */
    
     
    Joueur joueur = { 
        .nom = "bily boy", 
        .niveau = 1, 
        .XP = 0, 
        .Inventaire = NULL }; 

    ajouter(&joueur.Inventaire, creerObjet(
        "Potion",
        3,
        SOIN,
        20));

    
    Equipe allies = { .nb_membre = 2 };
    remplirEntite(&allies.membres[0], "Issam", MAGE, 60, 30, true);
    remplirEntite(&allies.membres[1], "Todd", GUERRIER, 100, 50, true);
    
    Equipe ennemis = { .nb_membre = 2 };
    remplirEntite(&ennemis.membres[0], "ADA", GUERRIER, 50, 20, false);
    remplirEntite(&ennemis.membres[1], "OCaml", MAGE, 40, 40, false);
    
    bool quitter = false;

    while (!quitter && equipeVivante(&allies) && equipeVivante(&ennemis)) {
        Entité *allie_courant = premierVivant(&allies);
        Entité *cible = premierVivant(&ennemis);

        printf("\n%s (%d PV) contre %s (%d PV)\n",
               allie_courant->nom, allie_courant->pt_vie, cible->nom, cible->pt_vie);
        printf("1. Attaquer  2. Objet  3. Compétence  4. Fuir  5.  Quitter\n> ");

        int choix;
        if (scanf("%d", &choix) != 1) break;

        switch (choix) {
            case 1:
                cible->pt_vie -= 1;  // changer pour avoir le choix de l'attaque                    
                printf("%s inflige 15 dégâts.\n", allie_courant->nom);
                break;
            case 2:
                if (menuObjet(&joueur, allie_courant) != 0) {
                continue;   // on redemande une action sans passer au tour suivant
                }
                break;
            case 3:
                utiliserCompetence(allie_courant, cible);
                break;
            case 4:
                fuir(allie_courant);
                break;
            case 5:
                quitter = true;
                break;
            default:
                printf("Choix invalide.\n");
        }

        if (!quitter && equipeVivante(&ennemis)) {
            Entité *ennemi = premierVivant(&ennemis);
            allie_courant = premierVivant(&allies);
            if(allie_courant != NULL) {
                // todo : gestion attaques ennemis mais pr l'instant je suis dans le déni
                allie_courant->pt_vie -= 50;
                printf("%s attaque %s : 1 dégât.\n", ennemi->nom, allie_courant->nom);
            }
        }
    }

    if (!equipeVivante(&ennemis)) {
        printf("\nVictoire ! ദ്ദി◝ ⩊ ◜.ᐟ\n");
    } else {
        printf("\nDéfaite... ｡° ૮₍°´ᯅ`°₎ა °｡\n");
    }
    while(joueur.Inventaire != NULL) {
        DataGame *suivant = joueur.Inventaire->suivant;
        free(joueur.Inventaire->element);
        free(joueur.Inventaire);
        joueur.Inventaire = suivant;
    }
    return 0;
}