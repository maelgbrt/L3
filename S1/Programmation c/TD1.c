// Exercice 1 : Echauffement...


// Compilation : gcc TD1.c -o TD1
// Lancer : ./TD1
#include <stdio.h>
#define NB_ELEMENT 4

void calcul_cash(int somme, int *p10, int *p5, int *p2, int *p1){
    int sommeTab[NB_ELEMENT];
    int val[NB_ELEMENT] = {10,5,2,1};

    for (int i = 0; i < NB_ELEMENT; i++){
        sommeTab[i] = somme / val[i];
        somme = somme % val[i];
        printf("Valeur pour %d est %d\n",val[i],sommeTab[i]);
    }
}



// ------------------------------------------------------------//

// EXERCICE 2


void swap(int *case1, int *case2){
    int tmp;
    tmp = *case1;
    *case1= *case2;
    *case2 = tmp;
}

void scheduling(){
    #define NB_ELEMENTS 5
    int tasks[NB_ELEMENTS] = {1,2,3,4,5};
    int p[NB_ELEMENTS] = {32,13,26,7,29};
    int d[NB_ELEMENTS] = {83,37,29,70,69};
    int res;
    int resultat[NB_ELEMENTS];


    for (int i = 0; i < NB_ELEMENTS; i++){
        resultat[i] = d[i] - p[i];
        printf("La val est %d \n",resultat[i]);
    }

   for (int i = 0; i < NB_ELEMENTS - 1; i++){
        for (int j = 0; j < NB_ELEMENTS - 1 - i; j++){
            if (resultat[j] > resultat[j+1]){
                swap(&resultat[j], &resultat[j+1]);
                swap(&tasks[j], &tasks[j+1]);
                swap(&p[j], &p[j+1]);
                swap(&d[j], &d[j+1]);
            }
        }
    }

    printf("\n--- Ordre des tâches après tri (marge croissante) ---\n");
    for (int i = 0; i < NB_ELEMENTS; i++){
        printf("Position %d -> Tâche %d (Marge: %d)\n", i + 1, tasks[i], resultat[i]);
    }
}






void main () {
    printf("Hello World\n\n");
    int p10,p5,p2,p1,somme;
    printf("Saisissez une Somme ?\n");
    scanf("%d",&somme);
   
   
    // p10 = somme / 10;
    // somme = somme % 10;
    // p5 = somme / 5;
    // somme = somme % 5;
    // p2 = somme / 2;
    // somme = somme % 2;
    // p1 = somme / 1;
    // somme = somme % 1;
    // printf("Nb 10 : %d , Nb 5 : %d , Nb 2 : %d, Nb 1 : %d",p10, p5, p2,p1);


    calcul_cash(somme,&p10,&p5,&p2,&p1);


    scheduling();

}

