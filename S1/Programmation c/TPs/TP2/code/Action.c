#include "Action.h"


// LES ATTAQUES

void coup_de_poing(Entité * e){
    e->pt_vie - 10;
}

void lacrymos(Entité * e){
    e->pt_vie - 20;   
}

void coup_de_mattraque(Entité * e){
    e->pt_vie - 30;
}

void poubelle_en_feu(Entité * e){
    int val = rand()%10;
    if(val < 5){
        e->pt_vie - 40;
    }
}


// FUIR
void fuir(Entité * e){
    printf("Vous avez fuis c pas bien");
    e->aura - 100;
}

// DEFENDRE
void defendre (Entité * e){
    e->pt_endurance + 10;
}



void competence(Entité *e1, Entité *e2){
    if (e1->classe == 0 ){ // Mage
        printf("Vous avez utilisé l'attque suprapuissante de l'autra incroyable");
    }else if (e1->classe == 1) //Guerrier
    {
        printf("Vous avez utilisé le coup d'épee supra mega puissant");
    }else{ //Voleur de Cirano
        printf("gOGO POWER RANGERS");
    }
    e1->aura += 10;
    e2->pt_vie = 0;
}



void utiliserObject(){
    o->nb_element -= 1 ;
    printf("Vous avez utilisé %s",o->nm_object);
    //faut que l'on finisse cetrte focntion
    
} 