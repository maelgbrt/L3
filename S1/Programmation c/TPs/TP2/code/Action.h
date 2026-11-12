#include "Element.h"

typedef void (*attaque)(Entité * e);

typedef void (*competence)(Entité *e);

void coup_de_poing(Entité * e);

void lacrymos(Entité * e);

void coup_de_mattraque(Entité * e);

void poubelle_en_feu(Entité * e);

void defendre (Entité * e);

void fuir (Entité * e);

void utiliserCompetence (Entité * e1,Entité *e2);

DataGame **chercherObjet(DataGame **tete, const char *nom_objet);

void utiliserObject(Joueur *j, const char *nom, Entité *cible);


