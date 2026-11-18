#include "Object.h"

void afficherObject(Object *o){
    printf("Object : %s | restant : %d | Effet : %d\n", o->nm_object, o->nb_element,o->effet);
}


Object * initialiserObject(){
    Object * o = malloc(sizeof(Object));
    if(o!= NULL){
        o->type= TYPE_OBJET;
        return o;
    }
}

void ajouterObjectInInventaire(Joueur *j, Object *o) {
    if (j != NULL && o != NULL) {
        ajouter(&(j->Inventaire), o);
    }
}

void supprimerObjectInventaire(Joueur *joueur, Object *o){
    if(joueur != NULL && o != NULL){
            
    }
}
/* Affiche l'inventaire et retourne l'objet choisi (NULL si annulé ou invalide). */
Object *choisirObjet(Joueur *j)
{
    if (j == NULL || j->Inventaire == NULL)
    {
        printf("Votre inventaire est vide !\n");
        return NULL;
    }

    printf("\n====== INVENTAIRE DE %s ======\n", j->nom);

    int index = 1;
    for (DataGame *c = j->Inventaire; c != NULL; c = c->suivant, index++)
    {
        Object *obj = (Object *)(c->element);
        if (obj != NULL)
            printf("%d - %s (Quantité : %d, Valeur : %d)\n",
                   index, obj->nm_object, obj->nb_element, obj->val);
    }

    int choix;
    printf("Choisissez un objet à utiliser (0 pour annuler) : ");
    if (scanf("%d", &choix) != 1)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf("Saisie invalide.\n");
        return NULL;
    }
    if (choix == 0)
    {
        printf("Utilisation d'objet annulée.\n");
        return NULL;
    }

    index = 1;
    for (DataGame *c = j->Inventaire; c != NULL; c = c->suivant, index++)
    {
        if (index == choix)
        {
            Object *obj = (Object *)(c->element);
            if (obj != NULL && obj->nb_element > 0)
                return obj;
            break;
        }
    }

    printf("Objet invalide ou épuisé.\n");
    return NULL;
}

/* Applique l'objet sur la cible. Retourne 1 si utilisé, 0 sinon. */
int utiliserObjet(Joueur *j, Object *obj, Entité *cible)
{
    if (j == NULL || obj == NULL || cible == NULL)
        return 0;

    switch (obj->effet)
    {
    case SOIN:
        cible->pt_vie += obj->val;
        printf("✨ %s récupère %d PV grâce à %s !\n", cible->nom, obj->val, obj->nm_object);
        break;
    case ENDURANCE:
        cible->pt_endurance += obj->val;
        printf("⚡ %s récupère %d points d'endurance grâce à %s !\n", cible->nom, obj->val, obj->nm_object);
        break;
    case MALUS:
        cible->pt_vie -= obj->val;
        printf("⚠️ Aïe ! %s subit %d dégâts de %s.\n", cible->nom, obj->val, obj->nm_object);
        break;
    default:
        printf("Effet d'objet inconnu.\n");
        return 0;
    }

    obj->nb_element--;
    if (obj->nb_element <= 0)
        supprimerObjectInventaire(j, obj); // ne plus toucher à obj après

    return 1;
}


