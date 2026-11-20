#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../DataGame.h"
#include "../Element.h" 
#include "../Action.h" 
#include "../Object.h"
#include "../Equipe.h"
#include "../Joueur.h"

int main() {

    // ####################################
    // Equipe alliée
    // ####################################

    Equipe allies = { .nb_membre = 2 };
    Entité *a1 = initialiseEntite();
    Entité *a2 = initialiseEntite();
    if (a1 == NULL || a2 == NULL) {
        return 1;
    }
    allies.membres[0] = a1;
    allies.membres[1] = a2;

    remplirEntite(a1, "Aya", MAGE, 60, 30, true);
    remplirEntite(a2, "Enzo", GUERRIER, 100, 50, true);
        

    // ####################################
    // Equipe ennemie
    // ####################################

    Equipe ennemis = { .nb_membre = 2 };
    Entité *e1 = initialiseEntite();
    Entité *e2 = initialiseEntite();
    if (e1 == NULL || e2 == NULL){
        return 1;
    }
    ennemis.membres[0] = e1;
    ennemis.membres[1] = e2;
    remplirEntite(e1, "ADA", GUERRIER, 50, 20, false);
    remplirEntite(e2, "OCaml", MAGE, 40, 40, false);

    // ###################################
    // Objets
    // ###################################

    Object *ob1 = initialiserObject();
    Object *ob2 = initialiserObject();
    Object *ob3 = NULL;
    if (ob1 == NULL || ob2 == NULL) {
        return 1;
    }
    ob1->nm_object = "Potion";
    ob1->nb_element = 3;
    ob1->effet = SOIN;
    ob1->val = 10;

    ob2->nm_object = "Poison";
    ob2->nb_element = 2;
    ob2->effet = MALUS;
    ob2->val = 15;


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


// ###################################
//              Entité
// ###################################

// -------- entiteVivante

    // Entité vivante
    int vivant = entiteVivante(a1);

    // Entité NULL
    int vivantNULL = entiteVivante(NULL);

// -------- afficherEntite

    // Afficher une Entité
    afficherEntite(a2);

    // Afficher une Entité NULL
    afficherEntite(NULL);


// ###################################
//              Action
// ###################################

// -------- initialiserAction

    // Action initialisée (nom vide, pas d'attaque)
    ActionStruct *poing = initialiserAction();
    strcpy(poing->nom, "Coup de poing");
    poing->attaque = coup_de_poing;

// -------- attaques

    // e1 : 50 PV
    poing->attaque(e1);              // -10 -> 40
    int pvApresPoing = e1->pt_vie;

    coup_de_mattraque(e1);           // -30 -> 10
    int pvApresMattraque = e1->pt_vie;

    lacrymos(e1);                    // -20 -> -10 (KO)
    int pvApresLacrymos = e1->pt_vie;

    // Entité KO
    int vivantKO = entiteVivante(e1);

// -------- defendre

    // a1 : 30 d'endurance
    defendre(a1);                    // +10 -> 40
    int enduApresDefense = a1->pt_endurance;

    // Entité NULL
    defendre(NULL);

// -------- afficherAttaque

    // Afficher une Action
    afficherAttaque(poing);
    printf("\n");


// ###################################
//              DataGame
// ###################################

// -------- ajouter

    DataGame *liste = NULL;
    ajouter(&liste, ob1);
    ajouter(&liste, ob2);

// -------- chercher

    // Element présent
    void *trouve = chercher(liste, ob1);

    // Element absent
    Object *ob4 = initialiserObject();
    ob4->nm_object = "Elixir";
    ob4->nb_element = 1;
    ob4->effet = ENDURANCE;
    ob4->val = 5;
    void *absent = chercher(liste, ob4);

    // Element NULL
    void *chercheNULL = chercher(liste, NULL);

// -------- afficher

    // Afficher un maillon
    afficher(*liste);

// -------- supprimer

    // Supprimer un élément présent
    supprimer(&liste, ob1);
    void *apresSuppr = chercher(liste, ob1);

    // Supprimer un élément absent
    supprimer(&liste, ob4);

    // Supprimer dans une liste vide
    DataGame *vide = NULL;
    supprimer(&vide, ob1);


// ###################################
//              Object
// ###################################

// -------- afficherObject

    // Afficher un Object
    afficherObject(ob2);

    // Afficher un Object NULL
    afficherObject(NULL);

// -------- initialiserObject

    // Object initialisé (0 exemplaire)
    Object *neuf = initialiserObject();
    int nbNeuf = neuf->nb_element;


// ###################################
//              Joueur
// ###################################

    Joueur joueur = { .nom = "Hania", .niveau = 1, .XP = 0, .Inventaire = NULL };

// -------- ajouterObjectInInventaire

    // Ajout normal
    ajouterObjectInInventaire(&joueur, ob1);
    ajouterObjectInInventaire(&joueur, ob2);

    // Joueur NULL, Object NULL
    ajouterObjectInInventaire(NULL, ob1);
    ajouterObjectInInventaire(&joueur, NULL);

// -------- afficherJoueur

    afficherJoueur(&joueur);

// -------- utiliserObjet

    // Soin : a1 60 PV -> 70 PV, Potion 3 -> 2
    int okSoin = utiliserObjet(&joueur, ob1, a1);
    int pvApresSoin = a1->pt_vie;
    int resteSoin = ob1->nb_element;

    // Malus : a2 100 PV -> 85 PV
    int okMalus = utiliserObjet(&joueur, ob2, a2);
    int pvApresMalus = a2->pt_vie;

    // Joueur NULL
    int refus = utiliserObjet(NULL, ob1, a1);

// -------- gagnerXP

    // Pas de niveau
    gagnerXP(&joueur, 50);
    int niveau1 = joueur.niveau;     // 1

    // Passage au niveau 2 (110 XP)
    gagnerXP(&joueur, 60);
    int niveau2 = joueur.niveau;     // 2

    // XP nulle, Joueur NULL
    gagnerXP(&joueur, 0);
    gagnerXP(NULL, 50);


// ###################################
//              Equipe
// ###################################

// -------- afficherEquipe

    afficherEquipe(&allies);

// -------- equipeVivante

    // Equipe avec des vivants
    int equipeOK = equipeVivante(allies);

    // Equipe où tout le monde est KO (e1 est KO)
    Equipe morts = { .nb_membre = 1 };
    morts.membres[0] = e1;
    int equipeKO = equipeVivante(morts);

// -------- premierEnnemie

    Entité *premier = premierEnnemie(&ennemis);   // e1

// -------- ajouterEquipe

    // Equipe pleine : 2 + 4 = 6 membres, le 5e ajout est refusé
    Entité *a3 = initialiseEntite();
    remplirEntite(a3, "Lea", MAGE, 70, 20, true);
    for (int i = 0; i < 5; i++) {
        ajouterEquipe(&allies, a3);
    }
    int nbMembres = allies.nb_membre;             // 6

// -------- fuir

    // Fuite normale
    fuir(&allies);

    // Equipe NULL
    fuir(NULL);

}