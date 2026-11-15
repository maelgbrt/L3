def init_double_tas():
    return [[None], [], []]
    #      racine,   g,  d


# on remonte une valeur tant qu'elle est mal placée
def verif_ordre_gauche(tab, indice):
        # tant qu'on est pas à la racine et que le père est plus grand que noeud couranr (=pas le bon ordre)
    while indice > 0 and tab[(indice-1) //2] > tab[indice]:
        # echange pere et fils
        pere = (indice-1) //2
        temp = tab[pere]
        tab[pere] = tab[indice]
        tab[indice] = temp
        indice = pere

# on remonte une valeur tant qu'elle est mal placée
def verif_ordre_droit(tab, indice):
    while indice > 0 and tab[(indice-1) //2] < tab[indice]:
        # echange pere et fils
        pere = (indice-1) //2
        temp = tab[pere]
        tab[pere] = tab[indice]
        tab[indice] = temp
        indice = pere


def main(double_tas):
    G = double_tas[1]
    D = double_tas[2]

    # --- test tas g ---
    G.append(1)
    print("G avant :", G)               # [4, 12, 7, 1]
    verif_ordre_gauche(G, len(G) - 1)
    print("G après :", G)               # attendu : [1, 4, 7, 12]
    assert G == [1, 4, 7, 12]

    # --- test tas d ---
    D.append(50)                         
    print("D avant :", D)               # [43, 26, 16, 50]
    verif_ordre_droit(D, len(D) - 1)
    print("D après :", D)               # attendu : [50, 43, 16, 26]
    assert D == [50, 43, 16, 26]

    # --- cas où rien ne bouge ---
    G2 = [1, 4, 7]
    G2.append(9)
    verif_ordre_gauche(G2, 3)
    assert G2 == [1, 4, 7, 9]


truc = [[None], [4, 12, 7], [43, 26, 16]]
main(truc)