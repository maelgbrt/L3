#!/usr/bin/env python3
# encoding: UTF-8     (compatibilité python2)

##################################
## INFO502: TP2
## GABORIT Maël
## BOUDJAJ Hania
## Groupe L3-info-3

import sys
import re

import datetime

#########################################
## fonction à compléter pendant le TP...
def process_line(line):
    # Permet de passer les caractères en majuscule
    #line = line.upper()
    # Question 2
    line = line.replace("<","$lt;")
    line = line.replace(">","$gt;")
    line = line.replace("&","&amp;")
    
    # Question 3
    
    return line

#########################################
## Fonction qui permet de tester si une ligne est un commentaire (commence par '%%%').
def is_comment(line):
    return line.lstrip().startswith("%%%")

# Question 4
# Vérifie via une regex si la ligne commence par "%%%" (espaces/tabs autorisés avant)
def is_comment2(line):
    return bool(re.match("^[ \t]*%%%", line))
    
# Remplace les adresses e-mail par la chaîne "EMAIL"
def replace_email(line):
    return re.sub(r"[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}","EMAIL",line)

# Convertit les URLs web (http/https) en liens HTML <a href="...">...</a>
def url(line):
    return re.sub(r"(https?://[a-zA-Z0-9._%+-/]+)", r"<a href='\1'>\1</a>", line)

# Transforme les chemins d'images entre crochets [chemin] en balises <img src='...' />
def img(line):
    return re.sub(r"\[([a-zA-Z0-9._%+-/]+)\]", r"<img src='\1' />", line)

# Fonction de rappel qui passe en majuscules tout le texte capturé par la regex
def to_upper(m):
    return m.group(0).upper()

# Passe en majuscules toute occurrence du mot "todo" et ce qui suit sur la ligne
def TODO_translate(line):
    return re.sub(r"(?i)todo.*", to_upper, line)

# Calcule la profondeur du titre selon le nombre de '=' et retourne la balise <hX>
def titre_translate(m):
    long = len(m.group(1))
    return f"<h{long}>{m.group(2)}<h{long}>"

# Détecte les titres encadrés par des '=' et les transforme en titres HTML <hX>
def titre(line):
    return re.sub(r"(^=+)(.*)(\1$)", titre_translate, line)
    
# Transforme la syntaxe **texte** en balises HTML de gras <b>texte<\b>
def detecteur_gras(line):
    return re.sub(r"(\*\*)(.*)(\1)", r"<b>\2<\\b>", line)

# Transforme la syntaxe __texte__ en balises HTML de soulignage <u>texte<\u>
def detecteur_souslignage(line):
    return re.sub(r"(__)(.*?)(\1)", r"<u>\2<\\u>", line)

# Convertit la syntaxe [texte URL] en lien HTML <a href='URL'>texte</a>
def lien(line):
    return re.sub(r"\[(.*)[ ](.*)\]" , r"<a href='\2'>\1</a>", line)

# Traite les liens complexes contenant une balise <a> imbriquée dans des crochets
def lien_better(line):
    return re.sub(r"\[(.*)[ ]<a.*>(.*)(</a>)\]", r"<a href='\2'> \1 </a>", line)

# Construit et retourne un objet datetime à partir des groupes capturés (jour, mois, année)
def is_date_valide(m):
    print("is_date_valide :\n")
    jour = m.group(1)
    mois = m.group(2)
    annee = m.group(3)
    date = datetime.datetime(annee, mois, jour)
    return date

# Détecte les dates au format JJ-MM-AAAA et appelle la fonction 'red'
def detecteur_date(line):
    print("detecteur_date :\n")
    return re.sub(r"([0-9]{,2})[-]([0-9]{,2})[-]([0-9]{,4})",red,line)

# Encadre une date dans une balise HTML <font color="red">
def red(line):
    print("red :\n")
    date = is_date_valide(line)
    return f"<font color=\"red\">{date}><//font>"

############################################################
## fonction principale, appelée depuis la ligne de commandes
def main():
    print("<!--", "-" * 70, "-->")
    
    for line in sys.stdin: 
        # suppression des symboles de fin de ligne
        line = line.strip("\n\r")

        ## suppressions des lignes "commentaires"
        ## ...
        if not is_comment2(line) :

            # traitement de la ligne
            line = process_line(line)
            line = url(line)
            line = replace_email(line)
            line = img(line)
            line = TODO_translate(line)
            line = titre(line)
            line = detecteur_gras(line)
            line = detecteur_souslignage(line)
            line = lien_better(line)
            line = detecteur_date(line)
            

        # affichage de la ligne traitée
            print(line)
    print("<!--", "-" * 70, "-->")


if __name__ == "__main__":
    main()


# Explication de l'erreur question 9
# Le code remplace la première et la dernière occurence de "__". Ainsi, il ne peut y avoir qu'une seule balise <s><\s> par ligne.

# Pour remédier au problème, on peut ajouter "?". ça permet de s'arrêter dès la première fois qu'on rencontre un deuxième "__".