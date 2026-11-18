#include "Joueur.h"


void afficherJoueur(Joueur * j){
    printf("============Joueur===============\n");
    printf("= Joueur : %s \n", j->nom);
    printf("= XP : %d \n", j->XP);
    printf("= Niveau : %d \n", j->niveau);
    afficherTableauMocheDeHania(j->Caracteristiques);
    afficherInventaire(j->Inventaire);
    printf("=================================\n\n");
}


Joueur *  initialiserJoueur() {
    Joueur * j = malloc(sizeof(Joueur));
    printf("Nom : \n");
    scanf("%s", j->nom);
    j->niveau = 1;
    j->XP = 100;
    j->Inventaire= NULL;

// RESPONSABILITÉ HANIA BOUDJAJ NE ME LIÉE PAS A CE CODE MEDIOCRE
    j->Caracteristiques[0] = 10; //FORCE
    j->Caracteristiques[1] = 5; //VITESSE
    j->Caracteristiques[2] = 5; //CHANCE
    j->Caracteristiques[3] = 10; //AGILITE
}


void afficherTableauMocheDeHania(int * c){
    printf("========Caracteristique==========\n");
     printf("= Force : %d\n", c[0]);
     printf("= Vitesse : %d\n", c[1]);
     printf("= Chance : %d\n", c[2]);
     printf("= Agilité : %d\n", c[3]);
}



