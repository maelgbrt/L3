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
        .nom = "Toad",
        .classe = MAGE,
        .pt_endurance = 12,
        .pt_vie = 80,
        .actions = noeudAction(coup_de_poingStruct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAllie, e1);

    Entité *e3 = initialiseEntite();
    *e3 = (Entité){
        .allie = true,
        .nom = "Luigi",
        .classe = GUERRIER,
        .pt_endurance = 10,
        .pt_vie = 100,
        .actions = noeudAction(coup_de_poingStruct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAllie, e3);

    Entité *e4 = initialiseEntite();
    *e4 = (Entité){
        .allie = true,
        .nom = "Peach",
        .classe = MAGE,
        .pt_endurance = 8,
        .pt_vie = 60,
        .actions = noeudAction(coup_de_poingStruct, NULL)};
    ajouterEquipe(equipeAllie, e4);

    printf("DEBUG: Nombre de membres dans l'equipe = %d\n", equipeAllie->nb_membre);
    afficherEquipe(equipeAllie);

    // ÉQUIPE ADVERSE
    printf("ANNONCE : Vous rencontrez des adversaires\n");
    Equipe *equipeAdverse = initialierEquipe();

    Entité *e2 = initialiseEntite();
    *e2 = (Entité){
        .allie = false,
        .nom = "Gerald",
        .classe = GUERRIER,
        .pt_endurance = 1,
        .pt_vie = 157,
        .actions = noeudAction(coup_ennemi_struct, NULL)};
    ajouterEquipe(equipeAdverse, e2);

    Entité *e5 = initialiseEntite();
    *e5 = (Entité){
        .allie = false,
        .nom = "Brutus",
        .classe = GUERRIER,
        .pt_endurance = 1,
        .pt_vie = 90,
        .actions = noeudAction(coup_ennemi_struct,
                               noeudAction(coup_de_mattraqueStruct, NULL))};
    ajouterEquipe(equipeAdverse, e5);

    printf("\n=================================\n");
    printf("\n=             COMBAT            =\n");
    printf("\n=================================\n");
    printf("Un combat commence.\n");

    // BOUCLE PRINCIPALE DE COMBAT
    while (nbVivants(equipeAllie) > 0 && nbVivants(equipeAdverse) > 0)
    {
        afficherEtatEquipe("Ennemis", equipeAdverse);
        afficherEtatEquipe("Votre equipe", equipeAllie);

        int choix;
        printf("\n====== A VOUS DE JOUER ======\n");
        printf("1 - Attaquer\n");
        printf("2 - Utiliser un objet\n");
        printf("3 - Attaque Speciale\n");
        printf("4 - Fuir\n");
        printf("5 - Quitter le jeu\n");
        printf("Que voulez vous faire ? \n");

        if (scanf("%d", &choix) != 1)
        {
            viderBuffer();
            choix = 0; // -> "Choix invalide"
        }

        switch (choix)
        {
        case 1: { // --- ATTAQUER ---
            printf("Vous avez decide d'attaquer. \n");

            Entité *attaquant = choisirMembre(equipeAllie, "Choisissez votre attaquant :");
            if (attaquant == NULL)
                break;

            ActionStruct *actionChoisie = choisirAction(attaquant);
            if (actionChoisie == NULL || actionChoisie->attaque == NULL)
            {
                printf("Choix d'action invalide.\n");
                break;
            }

            Entité *cible = choisirMembre(equipeAdverse, "Choisissez votre cible :");
            if (cible == NULL)
                break;

            printf("%s utilise : %s sur %s\n", attaquant->nom, actionChoisie->nom, cible->nom);
            actionChoisie->attaque(cible);

            if (!estVivant(cible))
                printf("%s est KO !\n", cible->nom);
            break;
        }

        case 2: { // --- UTILISER UN OBJET ---
             printf("Vous avez choisi d'utiliser un objet.\n");

    Object *objet = choisirObjet(jPrincipal);
    if (objet == NULL)
        continue; // annulé ou invalide : le joueur rejoue

    printf("Objet choisi : %s\n", objet->nm_object);
    Entité *cibleAllie = choisirMembre(equipeAllie, "Sur quel membre utiliser l'objet ?");
    if (cibleAllie == NULL)
        continue; // l'objet n'est pas consommé

    utiliserObjet(jPrincipal, objet, cibleAllie);
    break;
        }

        case 3: { // --- ATTAQUE SPECIALE ---

            printf("pas dispo");
            // printf("Vous avez choisi une attaque speciale.\n");
            // Entité *allieCourant = choisirMembre(equipeAllie, "Qui lance l'attaque speciale ?");
            // Entité *cibleEnnemie = premierVivant(equipeAdverse);

            // if (allieCourant != NULL && cibleEnnemie != NULL)
            // {
            //     if (allieCourant->aura > 50)
            //     {
            //         printf("%s declenche une attaque speciale sur %s !\n",
            //                allieCourant->nom, cibleEnnemie->nom);
            //     }
            //     else
            //     {
            //         printf("Vous n'avez pas assez d'aura !\n");
            //     }
            // }
            // else
            // {
            //     printf("Impossible d'effectuer l'attaque speciale.\n");
            // }
            // break;
        }

        case 4: { // --- FUIR ---
            printf("Vous tentez de fuir le combat...\n");
            fuir(equipeAllie);
            printf("Vous avez pris la fuite !\n");
            break;
        }

        case 5: { // --- QUITTER LE JEU ---
            printf("Fermeture du jeu...\n");
            free(jPrincipal);
            free(equipeAllie);
            free(equipeAdverse);
            return 0;
        }

        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }

        // ==========================================
        // TOUR DES ENNEMIS 
        // ==========================================
        if (nbVivants(equipeAdverse) > 0 && nbVivants(equipeAllie) > 0)
        {
            printf("\n--- Tour des ennemis ---\n");

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
    }

    // Fin du combat
    if (nbVivants(equipeAllie) == 0)
        printf("\nVous avez perdu.\n");
    else
        printf("\nVous avez remporte ce combat.\n");

    free(jPrincipal);
    free(equipeAllie);
    free(equipeAdverse);

    return 0;
}