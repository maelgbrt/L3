#!/usr/bin/env python3
# encoding: UTF-8     (compatibilité python2)

##################################
## INFO502: TP2
## Boudjaj Hania, Gaborit Maël info3 L3

import sys
import re
from datetime import datetime 

#########################################
## fonction à compléter pendant le TP...

def is_comment(line): 
    return line.lstrip().startswith("%%%")

def is_comment_2(line):
    return bool(re.match(r"^[ \t]*%%%", line, flags=re.S))

def email(line):
    return re.sub(r"[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}", "EMAIL", line, flags=re.S)

def url(line):
    return re.sub(r"(https?://[a-zA-Z0-9._%+-/]+)", r"<a href='\1'>\1</a>", line, flags=re.S)

def img(line):
    return re.sub(r"\[([a-zA-Z0-9._%+-/]+)\]", r"<img src='\1' />", line, flags=re.S)

def uper(ch): 
    return ch.group().upper()

def TODO_translate(line):
    return re.sub(r"todo.*", uper, line, flags=re.IGNORECASE | re.S)

def transfHTML(line):
    longueur = len(line.group(1))
    return f"<h{longueur}>{line.group(2)}</h{longueur}>"

def balise_html(line):
    return re.sub(r"(^=+)(.*?)(\1$)", transfHTML, line, flags=re.S | re.M)

def detecteur_de_gras(line):  # question 8
    return re.sub(r"(\*\*)(.*?)\1", r"<b>\2</b>", line, flags=re.S)

def detecteur_de_soulignagement(line): # question 8
    return re.sub(r"(__)(.*?)\1", r"<u>\2</u>", line, flags=re.S)

def link(line): 
    return re.sub(r"\[(.*?)[ ](.*?)\]", r"<a href='\2'>\1</a>", line, flags=re.S)

def testparcequelajsuispassurdutous(line):
    return re.sub(r"\[(.*?)[ ]<a.*?>(.*?)(</a>)\]", r"<a href='\2'> \1 </a>", line, flags=re.S)

def verif_date(line):
    jour = int(line.group(1))
    mois = int(line.group(2))
    annee = int(line.group(3))
    try:
        datetime(annee, mois, jour)
        return f"<p style='color:red;'>{line.group(0)}</p>"
    except ValueError:
        return line.group(0)

def detect_ligne_vide(line):
    return bool(re.match(r"^[ \t\n]*$", line, flags=re.S))

def detecteur_date(line):
    return re.sub(r"([0-9]{1,2})-([0-9]{1,2})-([0-9]{4})", verif_date, line, flags=re.S)

def detecteur_italique(line):
    return re.sub(r"(//)(.*?)\1", r"<i>\2</i>", line, flags=re.S)



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
    line = testparcequelajsuispassurdutous(line)
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