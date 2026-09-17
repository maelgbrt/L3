#!/usr/bin/env python3
# encoding: UTF-8     (compatibilité python2)

##################################
## INFO502: TP2
## Boudjaj Hania, Gaborit Maël info3 L3

import sys
import re


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
    return re.sub(r"todo.*",uper, line)



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
            print(line)

        # affichage de la ligne traitée
    print("<!--", "-" * 70, "-->")


if __name__ == "__main__":
    main()
