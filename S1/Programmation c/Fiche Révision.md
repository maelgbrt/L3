# FICHE DE RÉVISION : INFO 505 (CM1 & CM2)

---

## 1. Chaîne de compilation & Fichiers

Un projet C sépare l'interface (`.h`) de l'implémentation (`.c`)[cite: 1].

### Les 4 étapes
1. **Préprocesseur** : traite les `#` (`#include`, `#define`, `#ifndef`)[cite: 1]. Ne compile rien, fait du copier-coller et du remplacement textuel[cite: 1].
2. **Compilateur (`gcc -c`)** : traduit le C en langage machine et produit un fichier objet (`.o`)[cite: 1].
3. **Assembleur** : génère les instructions binaires[cite: 1].
4. **Linker / Éditeur de liens (`gcc`)** : assemble les fichiers `.o` et les bibliothèques pour créer l'exécutable final[cite: 1].

### Commandes GCC essentielles
* `gcc -c file.c` : compile en `file.o` sans faire l'édition de liens[cite: 1].
* `gcc main.o fct.o -o prog` : lie les `.o` pour créer l'exécutable `prog`[cite: 1].
* `-Wall -Wextra` : active tous les avertissements importants[cite: 1].
* `-g` : ajoute les symboles pour le débogueur (`gdb`)[cite: 1].
* `-I<dir>` : chemin des fichiers d'en-tête (`.h`)[cite: 1].
* `-L<dir>` et `-l<nom>` : chemin et nom de la bibliothèque à lier[cite: 1].

### Bibliothèques
* **Statique (`.a`)** : créée avec `ar -crs libnom.a f1.o f2.o`[cite: 1]. Son code est dupliqué directement dans l'exécutable[cite: 1].
* **Dynamique (`.so`)** : compilée avec `-fPIC` puis liée avec `gcc -shared -o libnom.so ...`[cite: 1]. Une seule copie chargée en mémoire RAM, partagée par les programmes[cite: 1].

---

## 2. Organisation de la mémoire

Chaque programme en mémoire est découpé en 4 segments principaux :

| Zone | Ce qu'elle stocke | Durée de vie | Remarques |
| :--- | :--- | :--- | :--- |
| **Segment de code** | Instructions machine du programme | Tout le programme[cite: 1] | **Lecture seule** (protégé)[cite: 1] |
| **Segment de données** | Variables globales et variables `static`[cite: 1, 2] | Tout le programme[cite: 1, 2] | Alloué dès le démarrage |
| **Pile (*Stack*)** | Variables locales et arguments de fonctions[cite: 1, 2] | Durée de la fonction[cite: 1] | Automatique (LIFO), rapide[cite: 1, 2] |
| **Tas (*Heap*)** | Mémoire dynamique (`malloc`/`free`)[cite: 1, 2] | Manuelle (du malloc au free)[cite: 1] | Géré par le développeur[cite: 1, 2] |

---

## 3. Portée et Modificateurs

* **Portée locale** : déclarée dans un bloc `{ ... }`, accessible uniquement dans ce bloc[cite: 1].
* **Portée globale** : déclarée hors des fonctions, accessible partout[cite: 1, 2].
* **`const`** : variable en lecture seule, impossible à modifier après assignation[cite: 1].
* **`static`** :
  * *Dans une fonction* : la variable ne meurt pas à la fin de la fonction, elle garde sa valeur pour l'appel suivant (stockée en segment de données)[cite: 1, 2].
  * *Hors fonction (globale)* : rend la variable ou la fonction privée au fichier `.c` en cours[cite: 1].
* **`extern`** : prévient que la variable globale est définie et allouée dans un autre fichier `.c` du projet[cite: 1].

---

## 4. Pointeurs et Adressage

Un pointeur est une variable qui contient l'**adresse mémoire** d'une autre variable.

### Les deux opérateurs clés
* **`&` (Adresse de)** : donne l'adresse mémoire où se trouve la variable.
* **`*` (Déréférencement / Contenu à l'adresse)** : accède à la valeur située à l'adresse pointée.

```c
int a = 10;
int *p = &a; // p contient l'adresse de a

printf("%d\n", *p); // Affiche 10 (lit à l'adresse p)
*p = 25;            // Modifie la case pointée : a devient 25 !