###################################
# GABORIT Maël
# BOUDJAJ Hania
###################################


###################################
#           QUESTION 1            #
###################################

def init_double_tas():
    """
    Fonction qui permet d'initialiser un double tas.
    """
    return [[None], [], []]
    #      racine,   g,  d


###################################
#           QUESTION 2            #
###################################


# on remonte une valeur tant qu'elle est mal placée
def verif_ordre_gauche(tab, indice):
    """
    Fonction qui permet de vérifier l'ordre des éléments dans le sous-arbre gauche.
    Entrée : 
        - tab : un tableau, le sous-arbre gauche
        - indice : l'indice du noeud courant
    """
    # tant qu'on est pas à la racine et que le père est plus grand que noeud courant (=pas le bon ordre)
    while indice > 0 and tab[(indice-1) //2] > tab[indice]:
        # echange pere et fils
        pere = (indice-1) //2
        temp = tab[pere]
        tab[pere] = tab[indice]
        tab[indice] = temp
        indice = pere

# on remonte une valeur tant qu'elle est mal placée
def verif_ordre_droit(tab, indice):
    """
    Fonction qui permet de vérifier l'ordre des éléments dans le sous-arbre droit.
    Entrée : 
        - tab : un tableau, le sous-arbre droit
        - indice : l'indice du noeud courant
    """
    while indice > 0 and tab[(indice-1) //2] < tab[indice]:
        # echange pere et fils
        pere = (indice-1) //2
        temp = tab[pere]
        tab[pere] = tab[indice]
        tab[indice] = temp
        indice = pere


def inser_gauche(g, d, val):
    """
    Fonction qui permet d'insérer un élément dans le sous-arbre gauche
    Entrée : 
        - g : un tableau, le sous-arbre gauche
        - d : un tableau, le sous-arbre droite
        - indice : l'indice du noeud courant
    """
    g.append(val)
    indice = len(g) - 1
    
    if indice == 0: # nouveau niveau dans g
        return
    
    pere = (indice-1) //2
    # quand m n'existe pas    
    if val > d[pere]: # valeur trop grande (un elt de g ne doit pas depasser son correspondant dans d)
        g[indice] = d[pere] # on inverse les elts de g et d
        d[pere] = val
        verif_ordre_droit(d, pere)
    else :
        verif_ordre_gauche(g, indice)


def inser_droite(g, d, val):
    """
    Fonction qui permet d'insérer un élément dans le sous-arbre droit.
    Entrée : 
        - g : un tableau, le sous-arbre gauche
        - d : un tableau, le sous-arbre droite
        - indice : l'indice du noeud courant
    """
    d.append(val)
    indice = len(d) - 1
    
    if val < g[indice]: # si d[i] existe, g[i] existe forcement donc pas besoin de pere
        d[indice] = g[indice]
        g[indice] = val
        verif_ordre_gauche(g, indice)
    else :
        verif_ordre_droit(d, indice)

def nb_niveaux(nb_elts_g):
    """
    Fonction qui compte le nombre de niveaux du sous-arbre gauche.
    Entrée :
        - nb_elts_g : le nombre d'éléments du sous arbre g.
    Sortie : 
        - h : le nombre de niveaux
    """
    # un arbre complet a h niveaux et 2^h - 1 elts
    h = 0
    while 2 ** h - 1 < nb_elts_g:
        h += 1
    return h

def ajouter(double_tas, val):
    """
    Fonction qui permet d'insérer un élément à la fin du double tas.
    Entrée : 
        - double_tas : un double_tas
        - val : la valeur qu'on veut insérer
    Sortie :
        - le double tas avec un nouvel élément à la bonne position
    """
    g, d = double_tas[1], double_tas[2]
    taille_g = len(g)
    h = nb_niveaux(taille_g) 
    
    dernier_niveau_incomplet = taille_g < 2 ** h -1
    if dernier_niveau_incomplet or len(d) >= taille_g:
        inser_gauche(g, d, val)
    else:
        inser_droite(g, d, val)
    return double_tas


def est_double_tas(double_tas):
    """
    Une fonction qui vérifie les 5 conditions présisées dans le sujet.
    Si elle sont toutes satisfaites, on a bien un double_tas.
    Entrée :
        - double_tas : le double_tas
    Sortie : 
        - un booléen qui indique si les conditions sont vérifiées.
    """
    g, d = double_tas[1], double_tas[2]

    # b et c
    for i in range(1, len(g)):
        if g[(i - 1)//2] > g[i]:
            return False
    for i in range(1, len(d)):
        if d[(i - 1)//2] < d[i]:
            return False

    # d
    haut_g, haut_d = nb_niveaux(len(g)), nb_niveaux(len(d))
    if haut_d != haut_g and haut_d != haut_g -1:
        return False
    
    # e
    for i in range(len(g)):
        if i < len(d):
            if g[i] > d[i]:
                return False
        elif i > 0 and g[i] > d[(i - 1)// 2]:
            return False
    return True
    

###################################
#           AFFICHAGE 9            #
###################################


def afficher_tas(tab, titre):
    
    print(f"  {titre} : {tab}")
    i, niveau = 0, 0
    while i < len(tab):
        n = 2 ** niveau
        print(f"      niveau {niveau} : {tab[i:i+n]}")
        i += n
        niveau += 1


def afficher(g, d, titre=""): #pour les sous-arbres
    
    print(f"--- {titre} ---")
    print("  racine : (vide)")
    print(f"  {'niveau':<7}| {'G':<22}| D")
    i, niveau = 0, 0
    while i < len(g) or i < len(d):
        n = 2 ** niveau
        print(f"  {niveau:<7}| {str(g[i:i+n]):<22}| {d[i:i+n]}")
        i += n
        niveau += 1
    print()

def main():
    # --- 1. verif_ordre_gauche / droit ---
    print("=== 1. verif_ordre ===")
    G = [4, 12, 7]
    G.append(1)
    afficher_tas(G, "G avant")
    verif_ordre_gauche(G, len(G) - 1)
    afficher_tas(G, "G après")
    assert G == [1, 4, 7, 12]

    D = [43, 26, 16]
    D.append(50)
    afficher_tas(D, "D avant")
    verif_ordre_droit(D, len(D) - 1)
    afficher_tas(D, "D après")
    assert D == [50, 43, 16, 26]

    G2 = [1, 4, 7, 9]                          # rien ne doit bouger
    verif_ordre_gauche(G2, 3)
    assert G2 == [1, 4, 7, 9]
    print("1. OK\n")

    # --- 2. nb_niveaux ---
    attendu = {0: 0, 1: 1, 2: 2, 3: 2, 4: 3, 7: 3, 8: 4}
    for nb, h in attendu.items():
        assert nb_niveaux(nb) == h, (nb, nb_niveaux(nb), h)
    print("=== 2. nb_niveaux : OK ===\n")

    # --- 3. inser_gauche ---
    print("=== 3. inser_gauche ===")
    g, d = [2, 5, 7], [10, 9, 8]
    afficher(g, d, "avant : insertion de 12 dans G (échange attendu)")
    inser_gauche(g, d, 12)
    afficher(g, d, "après")
    assert g == [2, 5, 7, 9] and d == [12, 10, 8]

    g, d = [2, 5, 7], [10, 9, 8]
    afficher(g, d, "avant : insertion de 1 dans G (pas d'échange)")
    inser_gauche(g, d, 1)
    afficher(g, d, "après")
    assert g == [1, 2, 7, 5] and d == [10, 9, 8]
    print("3. OK\n")

    # --- 4. inser_droite ---
    print("=== 4. inser_droite ===")
    g, d = [2, 5, 7], [10, 9]
    afficher(g, d, "avant : insertion de 8 dans D (pas d'échange)")
    inser_droite(g, d, 8)
    afficher(g, d, "après")
    assert g == [2, 5, 7] and d == [10, 9, 8]

    g, d = [2, 5, 7], [10, 9]
    afficher(g, d, "avant : insertion de 1 dans D (échange attendu)")
    inser_droite(g, d, 1)
    afficher(g, d, "après")
    assert g == [1, 5, 2] and d == [10, 9, 7]
    print("4. OK\n")

    # --- 5. ajouter, insertion par insertion ---
    print("=== 5. ajouter ===")
    dd = init_double_tas()
    afficher(dd[1], dd[2], "départ")
    for val in [5, 3, 8]:
        ajouter(dd, val)
        afficher(dd[1], dd[2], f"après ajouter({val})")
        assert est_double_tas(dd)
    print("5. OK\n")

    # --- 6. est_double_tas sur des structures invalides ---
    print("=== 6. est_double_tas ===")
    invalides = {
        "(e) pas ok": [[None], [5], [3]],
        "(b) pas  ok": [[None], [3, 1], [9]],
        "(c) pas ok": [[None], [1], [3, 9]],
    }
    for nom, dd_invalide in invalides.items():
        afficher(dd_invalide[1], dd_invalide[2], f"structure invalide, {nom}")
        assert not est_double_tas(dd_invalide)
    print("6. OK\n")

    # --- 7. exemple pas à pas : étapes écrites en dur, puis vrai ajouter() ---
    print("=== 7. exemple pas à pas ===")
    dd = init_double_tas()
    afficher(dd[1], dd[2], "départ")

    # ---------------------------------------------------------------
    print("##### Insertion 1 : ajouter(10) #####")
    print("|G| = 0, |D| = 0 -> on insère dans G")
    print("10 est ajouté à la fin de G, à l'indice 0 (nouveau niveau)")
    print("Il n'y a rien à comparer avec D ni rien à remonter")
    ajouter(dd, 10)
    assert dd[1] == [10] and dd[2] == []
    afficher(dd[1], dd[2], "après ajouter(10)")

    # ---------------------------------------------------------------
    print("##### Insertion 2 : ajouter(5) #####")
    print("|G| = 1 (niveau plein), |D| = 0 -> on insère dans D")
    print("5 est ajouté à la fin de D, à l'indice 0")
    afficher([10], [5], "2.1 état juste après l'ajout (invalide : g[0] > d[0])")
    print("5 < g[0] = 10 : la propriété g[i] <= d[i] pas respectée -> échange entre G et D")
    print("5 va dans G, 10 va dans D, puis verif_ordre_gauche (indice 0 : rien à remonter)")
    ajouter(dd, 5)
    assert dd[1] == [5] and dd[2] == [10]
    afficher(dd[1], dd[2], "après ajouter(5)")

    # ---------------------------------------------------------------
    print("##### Insertion 3 : ajouter(7) #####")
    print("|G| = 1, |D| = 1 -> on insère dans G")
    print("7 est ajouté à la fin de G, à l'indice 1 (père : indice 0)")
    print("7 <= d[0] = 10 : pas d'échange avec D")
    print("verif_ordre_gauche : père g[0] = 5 <= 7, rien à remonter")
    ajouter(dd, 7)
    assert dd[1] == [5, 7] and dd[2] == [10]
    afficher(dd[1], dd[2], "après ajouter(7)")

    # ---------------------------------------------------------------
    print("##### Insertion 4 : ajouter(20) #####")
    print("|G| = 2, dernier niveau de G incomplet -> on insère dans G")
    print("20 est ajouté à la fin de G, à l'indice 2 (père : indice 0)")
    afficher([5, 7, 20], [10], "4.1 état juste après l'ajout (invalide : g[2] > d[0])")
    print("20 > d[0] = 10 : un élément de G dépasse son correspondant dans D -> échange entre G et D")
    print("20 va dans D, 10 va dans G, puis verif_ordre_droit (indice 0 : rien à remonter)")
    ajouter(dd, 20)
    assert dd[1] == [5, 7, 10] and dd[2] == [20]
    afficher(dd[1], dd[2], "après ajouter(20)")

    # ---------------------------------------------------------------
    print("##### Insertion 5 : ajouter(3) #####")
    print("|G| = 3 (2 niveaux pleins), |D| = 1 -> on insère dans D")
    print("3 est ajouté à la fin de D, à l'indice 1")
    afficher([5, 7, 10], [20, 3], "5.1 état juste après l'ajout (invalide : g[1] > d[1])")
    print("3 < g[1] = 7 : échange entre G et D")
    afficher([5, 3, 10], [20, 7], "5.2 après l'échange G/D (G n'est plus un min-tas : 5 > 3)")
    print("verif_ordre_gauche : père g[0] = 5 > 3 -> on échange 3 et 5 dans G")
    print("3 est à la racine de G, la remontée s'arrête")
    ajouter(dd, 3)
    assert dd[1] == [3, 5, 10] and dd[2] == [20, 7]
    afficher(dd[1], dd[2], "après ajouter(3)")

    # ---------------------------------------------------------------
    print("##### Insertion 6 : ajouter(15) #####")
    print("|G| = 3, |D| = 2 -> on insère dans D")
    print("15 est ajouté à la fin de D, à l'indice 2")
    print("15 >= g[2] = 10 : pas d'échange avec G")
    print("verif_ordre_droit : père d[0] = 20 >= 15, rien à remonter")
    ajouter(dd, 15)
    assert dd[1] == [3, 5, 10] and dd[2] == [20, 7, 15]
    afficher(dd[1], dd[2], "après ajouter(15)")

    # ---------------------------------------------------------------
    print("##### Insertion 7 : ajouter(1) #####")
    print("|G| = 3, |D| = 3 -> on insère dans G (G gagne un niveau)")
    print("1 est ajouté à la fin de G, à l'indice 3 (père : indice 1)")
    afficher([3, 5, 10, 1], [20, 7, 15], "7.1 état juste après l'ajout (G n'est plus un min-tas)")
    print("1 <= d[1] = 7 : pas d'échange avec D, on remonte dans G")
    print("verif_ordre_gauche : père g[1] = 5 > 1 -> on échange 1 et 5")
    afficher([3, 1, 10, 5], [20, 7, 15], "7.2 après le premier échange")
    print("père g[0] = 3 > 1 -> on échange 1 et 3")
    print("1 est à la racine de G, la remontée s'arrête")
    ajouter(dd, 1)
    assert dd[1] == [1, 3, 10, 5] and dd[2] == [20, 7, 15]
    afficher(dd[1], dd[2], "après ajouter(1)")

    # ---------------------------------------------------------------
    print("##### Insertion 8 : ajouter(30) #####")
    print("|G| = 4, dernier niveau de G incomplet -> on insère dans G")
    print("30 est ajouté à la fin de G, à l'indice 4 (père : indice 1)")
    afficher([1, 3, 10, 5, 30], [20, 7, 15], "8.1 état juste après l'ajout (invalide : g[4] > d[1])")
    print("30 > d[1] = 7 : échange entre G et D")
    afficher([1, 3, 10, 5, 7], [20, 30, 15], "8.2 après l'échange G/D (D n'est plus un max-tas : 20 < 30)")
    print("verif_ordre_droit : père d[0] = 20 < 30 -> on échange 30 et 20 dans D")
    print("30 est à la racine de D, la remontée s'arrête")
    ajouter(dd, 30)
    assert dd[1] == [1, 3, 10, 5, 7] and dd[2] == [30, 20, 15]
    afficher(dd[1], dd[2], "après ajouter(30)")

    assert est_double_tas(dd), dd
    print("7. OK\n")
    print("Tous les tests passent")


main()