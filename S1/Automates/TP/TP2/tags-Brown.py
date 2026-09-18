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
def process_line(line):
    # line = line.upper() #réponse question 1
    
    
    line = line.replace('&',"&amp;")
    line = line.replace('<',"&lt;")  #réponse question 2.1
    line = line.replace('>',"&gt;")


  
    return line



def is_comment(line): 
   return line.lstrip().startswith("%%%")



def is_comment_2(line):
    return bool(re.match("^[ \t]*%%%", line))

def email(line):
    return re.sub(r"[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,}","EMAIL",line)


def url(line):
    return re.sub(r"(https?://[a-zA-Z0-9._%+-/]+)", r"<a href='\1'>\1</a>", line)

def img(line):
    return re.sub(r"\[([a-zA-Z0-9._%+-/]+)\]", r"<img src='\1' />", line)


def uper(ch): 
    return ch.group().upper()


def TODO_translate(line):
    return re.sub(r"(?i)todo.*",uper, line)

def transfHTML(line):
    longueur = len(line.group(1))
    return f"<h{longueur}>{line.group(2)}<h{longueur}>"

def balise_html(line):
    return re.sub(r"(^=+)(.*)(\1$)",transfHTML,line)


def detecteur_de_gras(line):  #question 8
    return re.sub(r"(\*\*)(.*)(\1)",r"<b>\2</b>",line)

# def debug(line):
#     print("le soulignage")

def detecteur_de_soulignagement(line): #question 8
    return re.sub(r"(__)(.*?)\1", r"<u>\2</u>", line)


def link(line): 
    return re.sub(r"\[(.*)[ ](.*)\]" , r"<a href='\2'>\1</a>",line)



def testparcequelajsuispassurdutous(line):
    return re.sub(r"\[(.*)[ ]<a.*>(.*)(</a>)\]", r"<a href='\2'> \1 </a>", line)


def verif_date(line):





def detecteur_date(line):
    return re.sub(r"([0-9]{,2})[-]([0-9]{,2})[-]([0-9]{,4})",verif_date,line)

############################################################
## fonction principale, appelée depuis la ligne de commandes
def main():
    print("<!--", "-" * 70, "-->")
    for line in sys.stdin:
        # suppression des symboles de fin de ligne
        line = line.strip("\n\r")
        
        # is_comment_2(line)
        ## suppressions des lignes "commentaires"
        ## ...
        if not is_comment_2(line) :
        # traitement de la ligne
            
            
            line = process_line(line)
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
            
            print(line)

        # affichage de la ligne traitée
    print("<!--", "-" * 70, "-->")


if __name__ == "__main__":
    main()
