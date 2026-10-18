# TP1 
```
GABORIT MAËL
BOUDJAJ HANIA
L3 INFORMATIQUE - GRP 3
TP1 Info502

Question 1
==========

1.1 Pour obtenir la liste des fichiers dont l'extension est .c ou .h, on utilise la commande :

$ ls *.[ch]


1.2 Pour lister tous les fichiers dont l'avant dernier caractère n'est pas le point "." : 

$ *[!.]?

Question 2
==========

2.1 Le motif shell étendu que l'on peut utiliser pour obtenir la liste de tous les fichiers sauf ceux dont l'extension est .jpg ou .jpeg est : 

$ !(*.jpg|*.jpeg)



Question 3
==========

3.1 Les lignes reconnues par l'expression régulière sont toutes celles qui comportent au moins une occurence de "aa", càd :
aa
aaaa
aaaaaa
aaa


3.2 La ligne aaa est reconnue par l'expression régulière car elle comporte une occurence de "aa".

3.3 La correction de la regex est : 

$ grep '^\(aa\)*$' test.txt



Question 4
==========

Voici la commande permettant de trouver des mots anglais qui contiennent les lettres a, b, c, d et e dans l'ordre :

$ grep ".*a.*b.*c.*d.*e.*" american-english

>> absconded


Question 5
==========

Voici une expression régulière qui liste tout les mots contenant une lettre doublée, comme "blossom" ou "zoom" :

$ grep '\(.\)\1' fichier


Question 6
==========

Voici les mots anglais contenant une même lettre 6 fois, qui n'est pas le "s" : 

$ grep -E '.*([^s])(.*\1.*){5}' american-english

>> indivisibility
indivisibility's


Question 8
==========

Voici la liste des mots anglais qui commencent et terminent par la même lettre et qui contiennent une lettre répétée au moins 5 fois : 

>> abracadabra
dispossessed
...


On les obtients grâce à la commande : 

$ grep -E '^(.).*\1$' american-english | grep -E '(.)(.*\1.*){4}' 



Question 9
==========

Pour afficher la liste des processus des navigateurs internet, on peut utilser la commande :

$ ps aux | grep -E 'firefox|chromium|safari'

Nous pouvons améliorer la commande pour ne pas afficher la ligne qui correspond au processus du grep. Pour cela, on peut utiliser l'argument -v (qui permet de sélectionner les lignes sans correspondances):

$ ps aux | grep -E 'firefox|chromium|safari' | grep -v grep



Question 10
===========
Voici la commande pour visualiser toutres les lignes contenant des caractères blancs (espaces et tabulation) juste avant le retour chariot.

Sur Sublime Text : #!/usr/bin/env python3
# encoding: UTF-8     (compatibilité python2)

##################################
## INFO502: TP2
## Gaborit Maël
## Boudjaj Hania
## INFO3 L3

import sys
import re
from datetime import datetime 

#########################################
## Fonction qui permet de tester si une ligne est un commentaire (commence par '%%%').
def is_comment(line): 
    return line.lstrip().startswith("%%%")

# Question 4
# Vérifie via une regex si la ligne commence par "%%%" (espaces/tabs autorisés avant)
def is_comment_2(line):
    return bool(re.match(r"^[ \t]*%%%", line, flags=re.S))

# Remplace les adresses e-mail par la chaîne "EMAIL"
def email(line):
    return re.sub(r"[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}", "EMAIL", line, flags=re.S)

# Convertit les URLs web (http/https) en liens HTML <a href="...">...</a>
def url(line):
    return re.sub(r"(https?://[a-zA-Z0-9._%+-/]+)", r"<a href='\1'>\1</a>", line, flags=re.S)

# Transforme les chemins d'images entre crochets [chemin] en balises <img src='...' />
def img(line):
    return re.sub(r"\[([a-zA-Z0-9._%+-/]+)\]", r"<img src='\1' />", line, flags=re.S)

# Fonction de rappel qui passe en majuscules tout le texte capturé par la regex
def uper(ch): 
    return ch.group().upper()

# Passe en majuscules toute occurrence du mot "todo" et ce qui suit sur la ligne
def TODO_translate(line):
    return re.sub(r"todo.*", uper, line, flags=re.IGNORECASE | re.S)

# Calcule la profondeur du titre selon le nombre de '=' et retourne la balise <hX>
def transfHTML(line):
    longueur = len(line.group(1))
    return f"<h{longueur}>{line.group(2)}</h{longueur}>"

# Détecte les titres encadrés par des '=' et les transforme en titres HTML <hX>
def balise_html(line):
    return re.sub(r"(^=+)(.*?)(\1$)", transfHTML, line, flags=re.S | re.M)

# Transforme la syntaxe **texte** en balises HTML de gras <b>texte<\b>
def detecteur_de_gras(line):  # question 8
    return re.sub(r"(\*\*)(.*?)\1", r"<b>\2</b>", line, flags=re.S)

# Transforme la syntaxe __texte__ en balises HTML de soulignage <u>texte<\u>
def detecteur_de_soulignagement(line): # question 8
    return re.sub(r"(__)(.*?)\1", r"<u>\2</u>", line, flags=re.S)

# Convertit la syntaxe [texte URL] en lien HTML <a href='URL'>texte</a>
def link(line): 
    return re.sub(r"\[(.*?)[ ](.*?)\]", r"<a href='\2'>\1</a>", line, flags=re.S)

# Traite les liens complexes contenant une balise <a> imbriquée dans des crochets
def link2(line):
    return re.sub(r"\[(.*?)[ ]<a.*?>(.*?)(</a>)\]", r"<a href='\2'> \1 </a>", line, flags=re.S)

# Construit et retourne un objet datetime à partir des groupes capturés (jour, mois, année)
# Si la date n'est pas valide, on l'encadre dans une balise html pour la passée en rouge
def verif_date(line):
    jour = int(line.group(1))
    mois = int(line.group(2))
    annee = int(line.group(3))
    try:
        datetime(annee, mois, jour)
        return f"<p style='color:red;'>{line.group(0)}</p>"
    except ValueError:
        return line.group(0)

# Détecte les lignes vides
def detect_ligne_vide(line):
    return bool(re.match(r"^[ \t\n]*$", line, flags=re.S))

# Détecte les dates au format JJ-MM-AAAA et appelle la fonction 'red'
def detecteur_date(line):
    return re.sub(r"([0-9]{1,2})-([0-9]{1,2})-([0-9]{4})", verif_date, line, flags=re.S)

# Transforme la syntaxe //texte// en balises HTML de soulignage <i>texte<\i>
def detecteur_italique(line):
    return re.sub(r"(//)(.*?)\1", r"<i>\2</i>", line, flags=re.S)


#########################################
## fonction à compléter pendant le TP...

def process_line(line):
    # line = line.upper() # réponse question 1
    
    line = line.replace('&', "&amp;")
    line = line.replace('<', "&lt;")  # réponse question 2.1
    line = line.replace('>', "&gt;")

    line = url(line)
    line = email(line)
    line = img(line)
    line = TODO_translate(line)
    line = balise_html(line)
    line = detecteur_de_gras(line)
    line = detecteur_de_soulignagement(line)
    # line = link(line)
    line = detecteur_date(line)
    line = link2(line)
    line = detecteur_italique(line)
            
    return line

def process_paragraphe(paragraphe):
    paragraphe_traite = process_line(paragraphe)
    print(paragraphe_traite)

############################################################
## fonction principale, appelée depuis la ligne de commandes
def main():
    print("<!--", "-" * 70, "-->")
    paragraphe = ""
    for line in sys.stdin:
        line = line.strip("\n\r")

        if not is_comment_2(line):
            if detect_ligne_vide(line):
                # paragraphe fini
                process_paragraphe(paragraphe)
                paragraphe = ""
            else:
                paragraphe = paragraphe + "\n" + line

    if paragraphe.strip():
        print("----------paragraphe------------")
        process_paragraphe(paragraphe)
        print("----------fin de paragraphe------------\n")

    print("<!--", "-" * 70, "-->")

if __name__ == "__main__":
    main()
$ [ ]$


De même pour les lignes qui commencent par une tabulation : 
$ [ ].*


Question 11
=========== 

Les lignes regex necessaires sont (search/replace) : 
$ '^ '
$ ''

Question 13
===========

Pour VSCODE
-----------

Rechercher : 
$ ^(.*),(.*)$

Remplacer : 
$ $2,$1


Pour Sublime Text : 
-------------------

Rechercher : 
$ (.*),(.*)

Remplacer :
$ \2, \1


Question 14
===========

Pour effectuer la question précédente avec sed, on peut utiliser la commande suivante : 
$ sed s/'^ '//' fichier

Le format de base de la commande sed est : $ sed s/[search]/[replace]/ fichier
Dans la commande précédente, on cherche toutes les lignes qui commencent par un espace. Puis on remplace ces espaces par "rien" (on les supprime).

Pour intervertir la colone des noms avec celle des prénoms, on utilise la commande :
$ sed -E 's/^(.*),(.*$))/\2,\1/' fichier

Le paramètre -E permet de passer en regex étendue.

Question 15
===========

En utilisant AWK, on arrive à obtenir une commande qui permet d'afficher en l'utilisation du processeur par les processus de l'utilisteur :

ps aux | LC_NUMERIC="C" awk '/'hania'/{ s+=$3 } END{print $1  "..............."  s "%"} '

```



SED




# TP2
```
#!/usr/bin/env python3

# encoding: UTF-8 (compatibilité python2)

  

##################################

## INFO502: TP2

## Gaborit Maël

## Boudjaj Hania

## INFO3 L3

  

import sys

import re

from datetime import datetime

  

#########################################

## Fonction qui permet de tester si une ligne est un commentaire (commence par '%%%').

def is_comment(line):

return line.lstrip().startswith("%%%")

  

# Question 4

# Vérifie via une regex si la ligne commence par "%%%" (espaces/tabs autorisés avant)

def is_comment_2(line):

return bool(re.match(r"^[ \t]*%%%", line, flags=re.S))

  

# Remplace les adresses e-mail par la chaîne "EMAIL"

def email(line):

return re.sub(r"[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}", "EMAIL", line, flags=re.S)

  

# Convertit les URLs web (http/https) en liens HTML <a href="...">...</a>

def url(line):

return re.sub(r"(https?://[a-zA-Z0-9._%+-/]+)", r"<a href='\1'>\1</a>", line, flags=re.S)

  

# Transforme les chemins d'images entre crochets [chemin] en balises <img src='...' />

def img(line):

return re.sub(r"\[([a-zA-Z0-9._%+-/]+)\]", r"<img src='\1' />", line, flags=re.S)

  

# Fonction de rappel qui passe en majuscules tout le texte capturé par la regex

def uper(ch):

return ch.group().upper()

  

# Passe en majuscules toute occurrence du mot "todo" et ce qui suit sur la ligne

def TODO_translate(line):

return re.sub(r"todo.*", uper, line, flags=re.IGNORECASE | re.S)

  

# Calcule la profondeur du titre selon le nombre de '=' et retourne la balise <hX>

def transfHTML(line):

longueur = len(line.group(1))

return f"<h{longueur}>{line.group(2)}</h{longueur}>"

  

# Détecte les titres encadrés par des '=' et les transforme en titres HTML <hX>

def balise_html(line):

return re.sub(r"(^=+)(.*?)(\1$)", transfHTML, line, flags=re.S | re.M)

  

# Transforme la syntaxe **texte** en balises HTML de gras <b>texte<\b>

def detecteur_de_gras(line): # question 8

return re.sub(r"(\*\*)(.*?)\1", r"<b>\2</b>", line, flags=re.S)

  

# Transforme la syntaxe __texte__ en balises HTML de soulignage <u>texte<\u>

def detecteur_de_soulignagement(line): # question 8

return re.sub(r"(__)(.*?)\1", r"<u>\2</u>", line, flags=re.S)

  

# Convertit la syntaxe [texte URL] en lien HTML <a href='URL'>texte</a>

def link(line):

return re.sub(r"\[(.*?)[ ](.*?)\]", r"<a href='\2'>\1</a>", line, flags=re.S)

  

# Traite les liens complexes contenant une balise <a> imbriquée dans des crochets

def link2(line):

return re.sub(r"\[(.*?)[ ]<a.*?>(.*?)(</a>)\]", r"<a href='\2'> \1 </a>", line, flags=re.S)

  

# Construit et retourne un objet datetime à partir des groupes capturés (jour, mois, année)

# Si la date n'est pas valide, on l'encadre dans une balise html pour la passée en rouge

def verif_date(line):

jour = int(line.group(1))

mois = int(line.group(2))

annee = int(line.group(3))

try:

datetime(annee, mois, jour)

return f"<p style='color:red;'>{line.group(0)}</p>"

except ValueError:

return line.group(0)

  

# Détecte les lignes vides

def detect_ligne_vide(line):

return bool(re.match(r"^[ \t\n]*$", line, flags=re.S))

  

# Détecte les dates au format JJ-MM-AAAA et appelle la fonction 'red'

def detecteur_date(line):

return re.sub(r"([0-9]{1,2})-([0-9]{1,2})-([0-9]{4})", verif_date, line, flags=re.S)

  

# Transforme la syntaxe //texte// en balises HTML de soulignage <i>texte<\i>

def detecteur_italique(line):

return re.sub(r"(//)(.*?)\1", r"<i>\2</i>", line, flags=re.S)

  
  

#########################################

## fonction à compléter pendant le TP...

  

def process_line(line):

# line = line.upper() # réponse question 1

line = line.replace('&', "&amp;")

line = line.replace('<', "&lt;") # réponse question 2.1

line = line.replace('>', "&gt;")

  

line = url(line)

line = email(line)

line = img(line)

line = TODO_translate(line)

line = balise_html(line)

line = detecteur_de_gras(line)

line = detecteur_de_soulignagement(line)

# line = link(line)

line = detecteur_date(line)

line = link2(line)

line = detecteur_italique(line)

return line

  

def process_paragraphe(paragraphe):

paragraphe_traite = process_line(paragraphe)

print(paragraphe_traite)

  

############################################################

## fonction principale, appelée depuis la ligne de commandes

def main():

print("<!--", "-" * 70, "-->")

paragraphe = ""

for line in sys.stdin:

line = line.strip("\n\r")

  

if not is_comment_2(line):

if detect_ligne_vide(line):

# paragraphe fini

process_paragraphe(paragraphe)

paragraphe = ""

else:

paragraphe = paragraphe + "\n" + line

  

if paragraphe.strip():

print("----------paragraphe------------")

process_paragraphe(paragraphe)

print("----------fin de paragraphe------------\n")

  

print("<!--", "-" * 70, "-->")

  

if __name__ == "__main__":

main()
```


# TP 3
```
import java.util.ArrayList;

  

public class App {

public static void main(String[] args) {

  
  
  

// ==========================================

// PARTIE AUTOMATE DETERMINISTE : On a décidé de ne pas utiliser la généicité ici

// car cela ne nous semblait pas pertinent. Nous supprimerons par la suite(la partie 2 :

// automate non deterministe) des paramètres et des listes qui ne sont au final pas utile (alphabet)

// ==========================================

  
  

// ==========================================

// PARTIE 1 : Automate lettres (bbb, bab, babcb)

// ==========================================

  

// Création des 3 états (l'état "trois" est l'état acceptant)

Etat un = new Etat(false, "un", null);

Etat deux = new Etat(false, "deux", null);

Etat trois = new Etat(true, "trois", null);

// Définition des transitions entre les états

Transition trans1b2 = new Transition(un, deux, "b");

Transition trans2a2 = new Transition(deux, deux, "a");

Transition trans2b3 = new Transition(deux, trois, "b");

Transition trans3c2 = new Transition(trois, deux, "c");

Transition trans3b3 = new Transition(trois, trois, "b");

  

// Regroupement des transitions par état

ArrayList<Transition> Transition1 = new ArrayList<>();

ArrayList<Transition> Transition2 = new ArrayList<>();

ArrayList<Transition> Transition3 = new ArrayList<>();

  

Transition1.add(trans1b2);

Transition2.add(trans2a2);

Transition2.add(trans2b3);

Transition3.add(trans3c2);

Transition3.add(trans3b3);

  

// Association des listes de transitions à chaque état

un.ensembleTransitions.addAll(Transition1);

deux.ensembleTransitions.addAll(Transition2);

trois.ensembleTransitions.addAll(Transition3);

  

// Liste de tous les états de l'automate

ArrayList<Etat> ensembleEtatsQ1 = new ArrayList<>();

ensembleEtatsQ1.add(un);

ensembleEtatsQ1.add(deux);

ensembleEtatsQ1.add(trois);

  

// Alphabet accepté : a, b, c

ArrayList<String> alphabetQ1 = new ArrayList<>();

alphabetQ1.add("a");

alphabetQ1.add("b");

alphabetQ1.add("c");

  

// Instanciation de l'automate avec "un" comme état de départ

Automate Question3 = new Automate(alphabetQ1, ensembleEtatsQ1, un);

  

// Test 1 : mot "bbb" (parcours : un -> deux -> trois -> trois)

ArrayList<String> test_bbb = new ArrayList<>();

test_bbb.add("b");

test_bbb.add("b");

test_bbb.add("b");

System.out.println("Le mot bbb est reconnu : " + Question3.reconnait(test_bbb));

  

// Test 2 : mot "bab" (parcours : un -> deux -> deux -> trois)

ArrayList<String> test_bab = new ArrayList<>();

test_bab.add("b");

test_bab.add("a");

test_bab.add("b");

System.out.println("Le mot bab est reconnu : " + Question3.reconnait(test_bab));

  

// Test 3 : mot "babcb" (parcours : un -> deux -> deux -> trois -> deux -> trois)

ArrayList<String> test_babcb = new ArrayList<>();

test_babcb.add("b");

test_babcb.add("a");

test_babcb.add("b");

test_babcb.add("c");

test_babcb.add("b");

System.out.println("Le mot babcb est reconnu : " + Question3.reconnait(test_babcb));

  

// ==========================================

// PARTIE 2 : Automate Pac-Man (comportement fantôme)

// ==========================================

  

System.out.println("\n---------------Pac Man--------------");

  

// Création des 4 états du fantôme

Etat GoLabyrinthe = new Etat(false, "Parcours le labyrinthe", null);

Etat FollowPC = new Etat(false, "Poursuit Pac-Man", null);

Etat FleePC = new Etat(false, "Fuit Pac-Man", null);

Etat returnBase = new Etat(false, "Retourne à la base", null);

// Définition des actions / transitions du fantôme

Transition FindBase = new Transition(returnBase, GoLabyrinthe, "atteint la base");

Transition LosePC = new Transition(FollowPC, GoLabyrinthe, "a perdu Pac-Man");

Transition SeePC = new Transition(GoLabyrinthe, FollowPC, "a vu Pac-Man");

Transition EatbyPC = new Transition(FleePC, returnBase, "a été mangé par Pac-Man");

Transition EatGomme = new Transition(FollowPC, FleePC, "Pac-Man mange une super pac-gomme");

Transition EatGomme2 = new Transition(GoLabyrinthe, FleePC, "Pac-Man mange une super pac-gomme");

Transition ExpirePacGomme = new Transition(FleePC, GoLabyrinthe, "Super pac-gomme expire");

  

// Regroupement des transitions sortantes de chaque état

ArrayList<Transition> TransitionGoLabyrinthe = new ArrayList<>();

ArrayList<Transition> TransitionFollowPC = new ArrayList<>();

ArrayList<Transition> TransitionFleePC = new ArrayList<>();

ArrayList<Transition> TransitionReturnBase = new ArrayList<>();

  

TransitionGoLabyrinthe.add(SeePC);

TransitionGoLabyrinthe.add(EatGomme2);

TransitionFollowPC.add(LosePC);

TransitionFollowPC.add(EatGomme);

TransitionFleePC.add(ExpirePacGomme);

TransitionFleePC.add(EatbyPC);

TransitionReturnBase.add(FindBase);

  

// Association des transitions aux états correspondants

GoLabyrinthe.ensembleTransitions.addAll(TransitionGoLabyrinthe);

FollowPC.ensembleTransitions.addAll(TransitionFollowPC);

FleePC.ensembleTransitions.addAll(TransitionFleePC);

returnBase.ensembleTransitions.addAll(TransitionReturnBase);

  

// Alphabet des événements possibles dans le jeu

ArrayList<String> alphabet = new ArrayList<>();

alphabet.add("atteint la base");

alphabet.add("Pac-Man mange une super pac-gomme");

alphabet.add("a vu Pac-Man");

alphabet.add("a perdu Pac-Man");

alphabet.add("a été mangé par Pac-Man");

alphabet.add("Super pac-gomme expire");

  

// Liste de tous les états du jeu

ArrayList<Etat> ensembleEtats = new ArrayList<>();

ensembleEtats.add(GoLabyrinthe);

ensembleEtats.add(FollowPC);

ensembleEtats.add(FleePC);

ensembleEtats.add(returnBase);

  

// Création de l'automate avec GoLabyrinthe comme état initial

Automate AutomatePC = new Automate(alphabet, ensembleEtats, GoLabyrinthe);

  

// ==========================================

// TESTS DE L'AUTOMATE PAC-MAN

// ==========================================

  

// Scénario 1 : Le fantôme voit Pac-Man puis le perd

System.out.println("\n--- SCÉNARIO 1 : Chasse puis perte de vue ---");

ArrayList<String> test1 = new ArrayList<>();

test1.add("a vu Pac-Man");

test1.add("a perdu Pac-Man");

System.out.println("Séquence valide : " + AutomatePC.reconnait(test1));

  

```

```
import java.util.ArrayList;

// Représente un automate fini déterministe
public class Automate {
    // Composants de l'automate
    ArrayList<String> alphabet = new ArrayList<>();       // Ensemble des symboles valides (l'alphabet)
    ArrayList<Etat> EnsembleEtats = new ArrayList<>();    // Ensemble de tous les états de l'automate
    Etat etatInitial;                                      // État de départ pour la lecture d'un mot
    
    // Constructeur : initialise l'automate avec son alphabet, ses états et son état initial
    public Automate(ArrayList<String> alphabet, ArrayList<Etat> EnsembleEtats, Etat etatInitial) {
        this.alphabet = alphabet;
        this.EnsembleEtats = EnsembleEtats;
        this.etatInitial = etatInitial;
    }

    // Vérifie si une séquence de symboles (un mot) est acceptée par l'automate
    public boolean reconnait(ArrayList<String> Tab_mot) {

        // On commence la lecture à l'état initial
        Etat etat_courant = etatInitial;
        
        // Parcourt chaque symbole du mot un par un
        for (int i = 0; i < Tab_mot.size(); i++) {
            String c = Tab_mot.get(i);

            // Recherche la transition sortante pour le symbole 'c'
            etat_courant = etat_courant.findTransition(c);
            
            // Si aucune transition n'existe pour ce symbole, le mot est rejeté
            if (etat_courant == null) {
                return false;
            }
        }
        
        // À la fin du mot, on vérifie si l'état d'arrivée est un état final (acceptant)
        return etat_courant.getEstEtatFinal();
    }

    // --- Getters et Setters ---

    public ArrayList<String> getAlphabet() {
        return alphabet;
    }

    public ArrayList<Etat> getEnsembleEtats() {
        return EnsembleEtats;
    }

    public Etat getEtatInitial() {
        return etatInitial;
    }

    public void setAlphabet(ArrayList<String> alphabet) {
        this.alphabet = alphabet;
    }

    public void setEnsembleEtats(ArrayList<Etat> ensembleEtats) {
        EnsembleEtats = ensembleEtats;
    }

    public void setEtatInitial(Etat etatInitial) {
        this.etatInitial = etatInitial;
    }
}
```

# TP4

``` /**************************************************************/
/******** NE PAS MODIFIER LES  PREMIERES LIGNES  **************/
/**************************************************************/
import fr.usmb.l3info.tp4.TP4Scanner;

parser code {:
    TP4Scanner s;
    public Parser(TP4Scanner s){this.s=s; }
:}

/* define how to connect to the scanner! */
scan with {: return s.next_token(); :};

/**************************************************************/
/******** NE PAS MODIFIER LES LIGNES PREMIERES LIGNES**********/
/**************************************************************/


/************ A PARTIR D'ICI, A MODIFIER ***********/
/* Déclaration des symboles terminaux. */
terminal            LPAREN, RPAREN, ZERO, ONE, CONCAT;
terminal Character    LETTRE;        

/* Déclaration des symboles non terminaux. */
non terminal String    expr;

/* Precedences */


/* The grammar rules */
expr      ::=  ZERO								{: RESULT = "0";			:}
       		 | LPAREN expr:e RPAREN	         	{: RESULT = "(" + e + ")";  :}
       		 | LETTRE:s	                 		{: RESULT = s + "";      	:}
       		 ;
       
             
```


```
package fr.usmb.l3info.tp4;

  

import fr.usmb.l3info.tp4.parser.sym;

import java_cup.runtime.*;

  

public class TP4Scanner {

/* single lookahead character */

private int cnt= 0;

private final String s;

/* we use a SymbolFactory to generate Symbols */

private final SymbolFactory sf = new ComplexSymbolFactory();

  
  

public TP4Scanner(String string) {

this.s = string;

}

  

/* recognize and return the next complete token */

public Symbol next_token()

{

if (cnt < s.length()) {

Character next_char = s.charAt(cnt);

cnt++;

switch (next_char) {

case '0':

return sf.newSymbol("ZERO", sym.ZERO);

//case '1': return sf.newSymbol("ONE", sym.ONE);

case 'a': case 'b': case 'c': case 'd': case 'e':

return sf.newSymbol("LETTRE",sym.LETTRE, next_char);

case '(': return sf.newSymbol("LPAREN",sym.LPAREN);

case ')': return sf.newSymbol("RPAREN",sym.RPAREN);

}

}

return sf.newSymbol("EOF",sym.EOF);

}

}; 
```


```
package fr.usmb.l3info.tp4;

  
  

import fr.usmb.l3info.tp4.parser.*;

import java_cup.runtime.Symbol;

  

public class Main {

public static void main(String[] argv) throws Exception{

exemple();

question1();

}

  
  

private static void exemple() throws Exception {

System.out.println("****************** Exemple **************");

Parser p = new Parser(new TP4Scanner("(a)"));

Symbol s = p.parse();

String chaine = (String) s.value;

System.out.println(chaine);

}

  

private static void question1() {

System.out.println("****************** Question 1 **************");

}

}

```
