
[CM1.pdf](CM1.pdf)    [CM2.pdf](CM2.pdf)



__*Structure* - Définition__: 
* Type de donnée, contenant un ou plusiuer objets pouvant être de type différent, regroupés au sein d'un emême entité
* Les objetcts contenus dans la structure sont désignés pasr champs ( de la structure )

### Quiz
``` c
struc coord3D
{
	double x = 0;
	double y = 0;
	double z = 0;
}
```
**INCORRECT** : NE VAS PAS ETRE CORRECT CAR ON ATTRIBUT DIRECTEMENT VALEUR A NOS VARIABLES

``` c
struct personne 
{
	char nom[100];
	char prenom[100];
	char adresse[100];
	
	int age;
	int sexe;
}
```
**CORRECT**

#### Accès à la structure
Si on souhaite accéder au nom, on aura : ` personne.nom = ... `

#### Definition de type
**typedef** : va correspondre à un deuxièle nom -> **notion d'alias**

``` c
typedef struct  
{
	char nom[100];
	char prenom[100];
	char adresse[100];
	
	int age;
	int sexe;
} personne;
```

Permet que ça soit moins long lors de l'appel de la struct
On passe de `struct personne p1;` à `personne p1;` 
#### Structure Imbriqué
``` c
struct horloge
{
	int heure;
	int min;
	int sec;
};
```

``` c
struct date 
{
	struct horloge temps;
	int jour;
};
```

#### Structure auto référencées

``` c
typedef struct individu
{
	char nom[100]
	char prenom[100]
	struct individu *mere
}individu;
```

#### Avec Malloc, toujours un Free

Quand on libère un ptr `free(ptr)`on le remet à NULL `prt = NULL`
