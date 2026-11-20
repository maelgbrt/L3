#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Element.h"
#include "Entite.h"
#include "Object.h"
#include "Joueur.h"
#include "Equipe.h"
#include "Action.h"

/* ==========================================================
 *  FONCTIONS UTILITAIRES
 * ========================================================== */

static void viderBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static bool estVivant(const Entité *e)
{
    return e != NULL && e->pt_vie > 0;
}

static int nbVivants(const Equipe *eq)
{
    int n = 0;
    for (int i = 0; i < eq->nb_membre; i++)
    {
        if (estVivant(eq->membres[i]))
            n++;
    }
    return n;
}

static void afficherEtatEquipe(const char *titre, const Equipe *eq)
{
    printf("\n%s :\n", titre);
    for (int i = 0; i < eq->nb_membre; i++)
    {
        Entité *e = eq->membres[i];
        printf("  %d - %s (PV : %d)%s\n", i + 1, e->nom, e->pt_vie,
               estVivant(e) ? "" : " [KO]");
    }
}

/* Demande au joueur de choisir un membre VIVANT de l'équipe.
 * Retourne NULL si la saisie est invalide ou si le membre est KO. */
static Entité *choisirMembre(Equipe *eq, const char *invite)
{
    printf("%s\n", invite);
    for (int i = 0; i < eq->nb_membre; i++)
    {
        if (estVivant(eq->membres[i]))
            printf("%d - %s\n", i + 1, eq->membres[i]->nom);
    }

    int choix;
    if (scanf("%d", &choix) != 1)
    {
        viderBuffer();
        printf("Saisie invalide.\n");
        return NULL;
    }
    if (choix < 1 || choix > eq->nb_membre || !estVivant(eq->membres[choix - 1]))
    {
        printf("Choix invalide ou personnage KO.\n");
        return NULL;
    }
    return eq->membres[choix - 1];
}

/* Affiche les actions d'une entité et retourne celle choisie (ou NULL). */
static ActionStruct *choisirAction(Entité *e)
{
    int i = 1;
    for (DataGame *c = e->actions; c != NULL; c = c->suivant, i++)
    {
        ActionStruct *a = (ActionStruct *)(c->element);
        if (a != NULL)
            printf("%d - %s\n", i, a->nom);
    }

    int choix;
    printf("Choisissez une action : ");
    if (scanf("%d", &choix) != 1)
    {
        viderBuffer();
        return NULL;
    }

    i = 1;
    for (DataGame *c = e->actions; c != NULL; c = c->suivant, i++)
    {
        if (i == choix)
            return (ActionStruct *)(c->element);
    }
    return NULL;
}

/* Action aléatoire d'une entité (utilisé par l'ennemi). */
static ActionStruct *actionAleatoire(Entité *e)
{
    int nb = 0;
    for (DataGame *c = e->actions; c != NULL; c = c->suivant)
        nb++;
    if (nb == 0)
        return NULL;

    int cible = rand() % nb;
    DataGame *c = e->actions;
    while (cible-- > 0)
        c = c->suivant;
    return (ActionStruct *)(c->element);
}

/* Membre vivant tiré au hasard. */
static Entité *membreVivantAleatoire(Equipe *eq)
{
    int nb = nbVivants(eq);
    if (nb == 0)
        return NULL;

    int k = rand() % nb;
    for (int i = 0; i < eq->nb_membre; i++)
    {
        if (estVivant(eq->membres[i]))
        {
            if (k == 0)
                return eq->membres[i];
            k--;
        }
    }
    return NULL;
}

/* Premier membre vivant. */
static Entité *premierVivant(Equipe *eq)
{
    for (int i = 0; i < eq->nb_membre; i++)
    {
        if (estVivant(eq->membres[i]))
            return eq->membres[i];
    }
    return NULL;
}

/* Crée un noeud de liste d'actions. */
static DataGame *noeudAction(ActionStruct *a, DataGame *suivant)
{
    DataGame *n = initialiser();
    *n = (DataGame){.element = a, .suivant = suivant};
    return n;
}

/* Tire un butin aléatoire après une victoire. */
static void butinAleatoire(Joueur *j)
{
    if (rand() % 100 >= 60)             // 60 % de chance d'avoir un objet
    {
        printf("Aucun objet trouve cette fois.\n");
        return;
    }

    Object *o = initialiserObject();
    int tirage = rand() % 100;
    
    // 55 % : potion
    if (tirage < 55)                    
    {
        *o = (Object){
            .effet = SOIN,
            .nb_element = 1 + rand() % 2,
            .nm_object = "Potion de Soin",
            .val = 15};
    }
    // 25 % : grande potion
    else if (tirage < 80)               
    {
        *o = (Object){
            .effet = SOIN,
            .nb_element = 1,
            .nm_object = "Grande Potion de Soin",
            .val = 40};
    }
    else                                
    // 20 % : élixir d'endurance
    {
        *o = (Object){
            .effet = ENDURANCE,
            .nb_element = 1,
            .nm_object = "Elixir d'Endurance",
            .val = 5};
    }

    printf("BUTIN : vous obtenez %d x %s !\n", o->nb_element, o->nm_object);
    ajouterObjectInInventaire(j, o);
}

typedef enum { TOUR_FAIT, TOUR_FUITE, TOUR_QUITTER } ResultatTour;

/* Fait jouer UN allié : on redemande tant que l'action n'est pas valide
 * (une saisie invalide ou annulée ne consomme pas le tour). */
static ResultatTour tourAllie(Entité *allie, Joueur *jPrincipal,
                              Equipe *equipeAllie, Equipe *equipeAdverse)
{
    while (1)
    {
        afficherEtatEquipe("Ennemis", equipeAdverse);
        afficherEtatEquipe("Votre equipe", equipeAllie);

        printf("\n====== Tour de %s (PV : %d) ======\n", allie->nom, allie->pt_vie);
        printf("1 - Attaquer\n");
        printf("2 - Utiliser un objet\n");
        printf("3 - Fuir\n");
        printf("4 - Quitter le jeu\n");
        printf("Que voulez-vous faire ? \n");

        int choix;
        if (scanf("%d", &choix) != 1)
        {
            viderBuffer();
            printf("Saisie invalide.\n");
            continue;
        }

        switch (choix)
        {
        case 1: { // --- ATTAQUER ---
            ActionStruct *action = choisirAction(allie);
            if (action == NULL || action->attaque == NULL)
            {
                printf("Choix d'action invalide.\n");
                continue;
            }

            Entité *cible = choisirMembre(equipeAdverse, "Choisissez votre cible :");
            if (cible == NULL)
                continue;

            printf("%s utilise : %s sur %s\n", allie->nom, action->nom, cible->nom);
            action->attaque(cible);
            if (!estVivant(cible))
                printf("%s est KO !\n", cible->nom);
            return TOUR_FAIT;
        }

        case 2: { // --- UTILISER UN OBJET ---
            Object *objet = choisirObjet(jPrincipal);
            if (objet == NULL)
                continue;

            printf("Objet choisi : %s\n", objet->nm_object);
            Entité *cibleAllie = choisirMembre(equipeAllie, "Sur quel membre utiliser l'objet ?");
            if (cibleAllie == NULL)
                continue; // l'objet n'est pas consommé

            utiliserObjet(jPrincipal, objet, cibleAllie);
            return TOUR_FAIT;
        }

        case 3: // --- FUIR ---
            printf("Vous tentez de fuir le combat...\n");
            fuir(equipeAllie);
            printf("Vous avez pris la fuite !\n");
            return TOUR_FUITE;

        case 4:
            return TOUR_QUITTER;

        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}

/* Phase ennemie : chaque ennemi vivant attaque une cible aléatoire. */
static void tourEnnemis(Equipe *equipeAdverse, Equipe *equipeAllie)
{
    printf("\n######## TOUR DES ENNEMIS ########\n");

    for (int i = 0; i < equipeAdverse->nb_membre; i++)
    {
        Entité *ennemi = equipeAdverse->membres[i];
        if (!estVivant(ennemi))
            continue;
        if (nbVivants(equipeAllie) == 0)
            break;

        Entité *cible = membreVivantAleatoire(equipeAllie);
        ActionStruct *action = actionAleatoire(ennemi);

        if (action != NULL && action->attaque != NULL)
        {
            printf("%s (Ennemi) utilise : %s contre %s !\n",
                   ennemi->nom, action->nom, cible->nom);
            action->attaque(cible);
            if (!estVivant(cible))
                printf("%s est KO !\n", cible->nom);
        }
        else
        {
            printf("%s n'a aucune action disponible !\n", ennemi->nom);
        }
    }
}

static Equipe *creerEquipeAdverse(ActionStruct *griffe, ActionStruct *mattraque)
{
    static char *noms[] = {"Chenille", "Brutus", "Gobelin", "Orc", "Troll"};
    int nbNoms = sizeof noms / sizeof noms[0];

    Equipe *eq = initialierEquipe();
    int nb = 1 + rand() % 3; // 1 à 3 ennemis

    for (int i = 0; i < nb; i++)
    {
        DataGame *liste;
        if (rand() % 2)
            liste = noeudAction(griffe, noeudAction(mattraque, NULL));
        else
            liste = noeudAction(griffe, NULL);

        Entité *e = initialiseEntite();
        *e = (Entité){
            .allie = false,
            .nom = noms[rand() % nbNoms],
            .classe = GUERRIER,
            .pt_endurance = 1,
            .pt_vie = 80 + rand() % 90,
            .actions = liste,
        };
        ajouterEquipe(eq, e);   
    }
    return eq;                 
}

static void libererEquipeAdverse(Equipe *eq)
{
    for (int i = 0; i < eq->nb_membre; i++)
    {
        Entité *e = eq->membres[i];
        DataGame *c = e->actions;
        while (c != NULL)
        {
            DataGame *suiv = c->suivant;
            free(c);
            c = suiv;
        }
        free(e);
    }
    free(eq);
}

/* ==========================================================
 *  MAIN
 * ========================================================== */

int main()
{
    srand(time(NULL));

    Joueur *jPrincipal = initialiserJoueur();
    afficherJoueur(jPrincipal);

    // OBJET
    printf("ANNONCE : vous avez obtenu une potion\n");
    Object *o = initialiserObject();
    *o = (Object){
        .effet = SOIN,
        .nb_element = 1,
        .nm_object = "Potion de Soin",
        .val = 15};
    afficherObject(o);

    ajouterObjectInInventaire(jPrincipal, o);


    // ACTIONS (partagées, mais chaque entité a ses propres noeuds de liste)
    ActionStruct *coup_de_poingStruct = initialiserAction();
    *coup_de_poingStruct = (ActionStruct){
        .attaque = coup_de_poing,
        .nom = "Coup de Poing (10 degats)"};

    ActionStruct *coup_de_mattraqueStruct = initialiserAction();
    *coup_de_mattraqueStruct = (ActionStruct){
        .attaque = coup_de_mattraque,
        .nom = "Coup de Mattraque (30 degats)"};

    ActionStruct *coup_ennemi_struct = initialiserAction();
    *coup_ennemi_struct = (ActionStruct){
        .attaque = coup_de_poing,
        .nom = "Coup de Griffe"};

    // ÉQUIPE ALLIÉE
    printf("ANNONCE : Des membres ont rejoint votre equipe\n");
    Equipe *equipeAllie = initialierEquipe();

    Entité *e1 = initialiseEntite();
    *e1 = (Entité){
        .allie = true,
        .nom = "Python",
        .classe = MAGE,
        .pt_endurance = 12,
        .pt_vie = 80,
        .actions = noeudAction(coup_de_poingStruct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAllie, e1);

    Entité *e3 = initialiseEntite();
    *e3 = (Entité){
        .allie = true,
        .nom = "Ocaml",
        .classe = GUERRIER,
        .pt_endurance = 10,
        .pt_vie = 100,
        .actions = noeudAction(coup_de_poingStruct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAllie, e3);

    Entité *e4 = initialiseEntite();
    *e4 = (Entité){
        .allie = true,
        .nom = "C++",
        .classe = MAGE,
        .pt_endurance = 8,
        .pt_vie = 60,
        .actions = noeudAction(coup_de_poingStruct, NULL)};
    ajouterEquipe(equipeAllie, e4);

        Entité *e5 = initialiseEntite();
    *e5 = (Entité){
        .allie = true,
        .nom = "Kotlin",
        .classe = MAGE,
        .pt_endurance = 9,
        .pt_vie = 70,
        .actions = noeudAction(coup_de_poingStruct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAllie, e5);

    Entité *e6 = initialiseEntite();
    *e6 = (Entité){
        .allie = true,
        .nom = "Java",
        .classe = GUERRIER,
        .pt_endurance = 11,
        .pt_vie = 90,
        .actions = noeudAction(coup_de_poingStruct, NULL)};
    ajouterEquipe(equipeAllie, e6);

    Entité *e7 = initialiseEntite();
    *e7 = (Entité){
        .allie = true,
        .nom = "PHP",
        .classe = GUERRIER,
        .pt_endurance = 14,
        .pt_vie = 120,
        .actions = noeudAction(coup_de_poingStruct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAllie, e7);

    //printf("DEBUG: Nombre de membres dans l'equipe = %d\n", equipeAllie->nb_membre);
    afficherEquipe(equipeAllie);

    // ÉQUIPE ADVERSE
    Equipe *equipeAdverse = creerEquipeAdverse(coup_ennemi_struct, coup_de_mattraqueStruct);


    printf("\n=================================\n");
    printf("\n=             COMBAT            =\n");
    printf("\n=================================\n");
    printf("Un combat commence.\n");

    // BOUCLE PRINCIPALE DE COMBAT (tour par tour)

    int numCombat = 1;
bool quitter = false;
bool fuite;

do
{
    fuite = false;
    bool victoire = false;
    printf("\n=== COMBAT n°%d ===\n", numCombat);

    while (nbVivants(equipeAllie) > 0 && nbVivants(equipeAdverse) > 0)
    {
        printf("\n######## TOUR DES ALLIES ########\n");

        for (int i = 0; i < equipeAllie->nb_membre; i++)
        {
            Entité *allie = equipeAllie->membres[i];
            if (!estVivant(allie)) continue;
            if (nbVivants(equipeAdverse) == 0) break;

            ResultatTour r = tourAllie(allie, jPrincipal, equipeAllie, equipeAdverse);
            if (r == TOUR_QUITTER) { quitter = true; break; }
            if (r == TOUR_FUITE)   { fuite = true;   break; }
        }

        if (quitter || fuite)
            break;

        if (nbVivants(equipeAdverse) > 0 && nbVivants(equipeAllie) > 0)
            tourEnnemis(equipeAdverse, equipeAllie);
    }

    if (!quitter && !fuite && nbVivants(equipeAllie) > 0)
        {
            printf("\nVous avez remporte ce combat !\n");
            gagnerXP(jPrincipal, 50);
            butinAleatoire(jPrincipal);
            victoire = true;
        }

        if (fuite || victoire)
        {
            printf("\nDe nouveaux ennemis apparaissent !\n");
            libererEquipeAdverse(equipeAdverse);
            equipeAdverse = creerEquipeAdverse(coup_ennemi_struct, coup_de_mattraqueStruct);
            numCombat++;
        }
    } while (!quitter && nbVivants(equipeAllie) > 0);

    // Fin de partie
    if (quitter)
        printf("Fermeture du jeu...\n");
    else
        printf("\nVous avez perdu.\n");

    libererEquipeAdverse(equipeAdverse);
    free(equipeAllie);
    free(jPrincipal);
    return 0;
}