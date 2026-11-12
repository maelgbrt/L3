print("\n------------TP1------------\n")


def permuter(tas, ind1, ind2):
    temp = tas[ind1]
    tas[ind1] = tas[ind2]
    tas[ind2] = temp


def ajouter_tas(t, x):
    """Ajoute x dans le tas t. t[0] = taille du tas.
       x est un dictionnaire : {"valeur": int, "fichier": str}"""
    t[0] += 1
    i = t[0]
    t[i] = x
    # remontée : on compare les clés "valeur"
    while i > 1 and t[i // 2]["valeur"] > t[i]["valeur"]:
        permuter(t, i, i // 2)
        i //= 2
    return t[0]


def descendre(t, i):
    """Fait descendre t[i] à sa place (min-tas)."""
    n = t[0]
    while 2 * i <= n:
        f = 2 * i
        if f + 1 <= n and t[f + 1]["valeur"] < t[f]["valeur"]:
            f += 1
        if t[i]["valeur"] <= t[f]["valeur"]:
            break
        permuter(t, i, f)
        i = f


def supprimer_racine(t):
    """Retire le minimum : le dernier élément prend la racine, taille -1."""
    n = t[0]
    t[1] = t[n]
    t[n] = 0
    t[0] -= 1
    descendre(t, 1)


def main():
    LesMonotonies = [
        "geeks.txt",
        "lechargeurdeHania.txt"
    ]

    # indice 0 = taille du tas, indice 1 = racine (minimum des minima)
    t = [0] * (len(LesMonotonies) + 1)

    # les monotonies restent sur le disque : on garde chaque fichier ouvert
    fichiers = {nom: open(nom, "r") for nom in LesMonotonies}

    # début : le 1er élément de chaque monotonie entre dans le tas
    for nom, f in fichiers.items():
        ligne = f.readline()
        if ligne.strip():
            ajouter_tas(t, {"valeur": int(ligne), "fichier": nom})

    print("Tas initialisé :", t)

    # boucle : on écrit le minimum, puis on le remplace par le suivant du même fichier
    with open("MonotonieFinale", "w") as sortie:
        while t[0] > 0:
            racine = t[1]
            sortie.write(str(racine["valeur"]) + "\n")

            ligne = fichiers[racine["fichier"]].readline()
            if ligne.strip():
                racine["valeur"] = int(ligne)
                descendre(t, 1)
            else:
                # monotonie épuisée : le tas fait -1 en taille
                supprimer_racine(t)

    # fin
    for f in fichiers.values():
        f.close()

    print("Fusion terminée : voir le fichier MonotonieFinale")


main()

print("\n------------END------------\n")