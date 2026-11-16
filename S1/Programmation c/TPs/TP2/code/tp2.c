#include <stdbool.h>
#include <stdio.h>
#include "DataGame.h"
#include "Element.h"
#include "Action.h"

int main () {
    Joueur * jPrincipal = malloc(sizeof(Joueur));
    if (jPrincipal == NULL) {
        printf("Erreur d'allocation\n");
        return 1;
    }

    initialiserJoueur(jPrincipal);
    afficherJoueur(jPrincipal);

    printf("ANNONCE : vous avez obtenu une potion\n");
    Object * o = creerObjet("Potion",1,1,50);
    afficherObject(o);

    printf("ANNONCE : Un membre a rejoint votre equipe\n");

  DataGame * m2_liste_action = malloc(sizeof(DataGame));
    if (m2_liste_action != NULL) {
    // On stocke l'adresse de la fonction (SANS les parenthèses)
    m2_liste_action->element = coup_de_mattraque; 
    m2_liste_action->suivant = NULL;
}

  DataGame * m1_liste_action = malloc(sizeof(DataGame));
    if (m1_liste_action != NULL) {
    m1_liste_action->element = coup_de_poing; 
    m1_liste_action->suivant = m2_liste_action;
}


    Entité *e1 = malloc(sizeof(Entité));
    initialiseEntite(e1);
    *e1 = (Entité){ 
        .allie = true,
        .nom = "Toad",
        .classe = MAGE,
        .pt_endurance = 12,
        .pt_vie = 80,
        .actions=m1_liste_action
    };
    afficherEntite(e1);


    Equipe * equipeAllie = malloc(sizeof(Equipe));
    equipeAllie->nb_membre = 0;
    
    ajouterEquipe(equipeAllie,e1);
    
    afficherEquipe(equipeAllie);

    Equipe * equipeAdverse = malloc(sizeof(Equipe));
    equipeAdverse->nb_membre = 0;


    printf("ANNONCE : Vous rencontrez un adversaire\n");

    Entité *e2 = malloc(sizeof(Entité));
    initialiseEntite(e2);
    *e2 = (Entité){ 
        .allie = false,
        .nom = "Gerald",
        .classe = GUERRIER,
        .pt_endurance = 1,
        .pt_vie = 157,
    };

    ajouterEquipe(equipeAdverse,e2);


    while (equipeVivante(*equipeAllie)&& equipeVivante(*equipeAdverse)){

        printf("\n=================================\n");
        printf("\n=             COMBAT            =\n");
        printf("\n=================================\n");
        printf("Un combat commence.\n");
        if (equipeAdverse->membres[0]!= NULL){
            printf("Vous affrontez : \n");
            afficherEntite(equipeAdverse->membres[0]);
        }else{
            printf("Aucun ennemie a affronter.");
        }
        
        // Le menu
        int choix;
        printf("\n====== A VOUS DE JOUER ======\n");
        printf("1 - Attaquer\n");
        printf("2 - Utiliser un objet\n");
        printf("3 - Attaque Spécial\n");
        printf("4 - Fuir\n");
        printf("5 - Quitter le jeu\n");

        printf("Que voulez vous faire ? \n");
        scanf("%d",&choix);
        switch (choix)
        {
        case 1:
        printf("Vous avez decider d'attaquer. \n");
            afficherEquipe(equipeAllie);
            printf("Qui voulez vous utilisez ?\n");
            for (int i = 0; i<equipeAllie->nb_membre; i++){
                printf("%d - %s (%d PV)\n",i+1,equipeAllie->membres[i]->nom,equipeAllie->membres[i]->pt_vie);
            }
            int choix_joueur;
            scanf("%d",&choix_joueur);
            Entité * e_choix = equipeAllie->membres[choix_joueur-1];
            afficherEntite(e_choix);
            DataGame *courant = e_choix->actions;
            int num_action = 1;
            
            while (courant != NULL) {
                printf("%d - Action disponible\n", num_action); // Ou afficher le nom si tu as une structure d'action
                // Si tu veux exécuter l'action directement pour tester :

                // attaque act = (attaque) courant->element;
                // act(equipeAdverse->membres[0]); // Par exemple, frapper l'ennemi
                
                courant = courant->suivant; // On avance sur le maillon suivant sans détruire la liste
                num_action++;
            }
            scanf("%d",&choix);
        
        default:
            printf("Choix invalide");
        }

    }
    if (equipeVivante(*equipeAdverse)){
        printf("Vous avez perdu.");
    }
    else{
        printf("Vous avez remporter ce combat.");
    }




    //  afficherObject(o);

    



    free(jPrincipal);                     // à la fin


    
    // Joueur joueur = { 
    //     .nom = "bily boy", 
    //     .niveau = 1, 
    //     .XP = 0, 
        // .Inventaire = NULL }; 

    // ajouter(&joueur.Inventaire, creerObjet(
    //     "Potion",
    //     3,
    //     SOIN,
    //     20));

    
    // Equipe allies = { .nb_membre = 2 };
    // remplirEntite(&allies.membres[0], "Issam", MAGE, 60, 30, true);
    // remplirEntite(&allies.membres[1], "Todd", GUERRIER, 100, 50, true);
    
    // Equipe ennemis = { .nb_membre = 2 };
    // remplirEntite(&ennemis.membres[0], "ADA", GUERRIER, 50, 20, false);
    // remplirEntite(&ennemis.membres[1], "OCaml", MAGE, 40, 40, false);
    
    // bool quitter = false;

    // while (!quitter && equipeVivante(&allies) && equipeVivante(&ennemis)) {
    //     Entité *allie_courant = premierVivant(&allies);
    //     Entité *cible = premierVivant(&ennemis);

    //     printf("\n%s (%d PV) contre %s (%d PV)\n",
    //            allie_courant->nom, allie_courant->pt_vie, cible->nom, cible->pt_vie);
    //     printf("1. Attaquer  2. Objet  3. Compétence  4. Fuir  5.  Quitter\n> ");

    //     int choix;
    //     if (scanf("%d", &choix) != 1) break;

    //     switch (choix) {
    //         case 1:
    //             cible->pt_vie -= 1;  // changer pour avoir le choix de l'attaque                    
    //             printf("%s inflige 15 dégâts.\n", allie_courant->nom);
    //             break;
    //         case 2:
    //             if (menuObjet(&joueur, allie_courant) != 0) {
    //             continue;   // on redemande une action sans passer au tour suivant
    //             }
    //             break;
    //         case 3:
    //             utiliserCompetence(allie_courant, cible);
    //             break;
    //         case 4:
    //             fuir(allie_courant);
    //             break;
    //         case 5:
    //             quitter = true;
    //             break;
    //         default:
    //             printf("Choix invalide.\n");
    //     }

    //     if (!quitter && equipeVivante(&ennemis)) {
    //         Entité *ennemi = premierVivant(&ennemis);
    //         allie_courant = premierVivant(&allies);
    //         if(allie_courant != NULL) {
    //             // todo : gestion attaques ennemis mais pr l'instant je suis dans le déni
    //             allie_courant->pt_vie -= 50;
    //             printf("%s attaque %s : 1 dégât.\n", ennemi->nom, allie_courant->nom);
    //         }
    //     }
    // }

    // if (!equipeVivante(&ennemis)) {
    //     printf("\nVictoire ! ദ്ദി◝ ⩊ ◜.ᐟ\n");
    // } else {
    //     printf("\nDéfaite... ｡° ૮₍°´ᯅ`°₎ა °｡\n");
    // }
    // while(joueur.Inventaire != NULL) {
    //     DataGame *suivant = joueur.Inventaire->suivant;
    //     free(joueur.Inventaire->element);
    //     free(joueur.Inventaire);
    //     joueur.Inventaire = suivant;
    // }
    // return 0;
}