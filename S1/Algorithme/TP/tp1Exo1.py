print("\n------------TP1------------\n")


def permuter(tas, ind1, ind2):
    temp = tas[ind1]
    tas[ind1] = tas[ind2]
    tas[ind2] = temp


def ajouter_tas(t, x):
    """Exactement la procédure Ajouter-tas du cours"""
    print(f"  [+] AJOUT de {x['valeur']} (venant de {x['fichier']})")
    t[0] += 1
    i = t[0]
    t[i] = x
    while i > 1 and t[i // 2]["valeur"] > t[i]["valeur"]:
        print(f"      -> Remontée : {t[i]['valeur']} monte à la place de {t[i // 2]['valeur']}")
        permuter(t, i, i // 2)
        i //= 2
    print(f"      État du tas après ajout : {t}")


def retirer_min_tas(t):
    minimum = t[1]
    print(f"  [-] RETRAIT du minimum : {minimum['valeur']} (venant de {minimum['fichier']})")
    
    t[1] = t[t[0]]
    t[t[0]] = 0
    t[0] -= 1
    
    i = 1
    fini = False
    p = t[0]

    while i <= (p // 2) and not fini:
        if p == 2 * i or t[2 * i]["valeur"] < t[2 * i + 1]["valeur"]:
            j = 2 * i
        else:
            j = 2 * i + 1

        if t[i]["valeur"] > t[j]["valeur"]:
            print(f"      -> Descente : {t[i]['valeur']} descend à la place de {t[j]['valeur']}")
            permuter(t, i, j)
            i = j
        else:
            fini = True

    print(f"      État du tas après retrait : {t}")
    return minimum


def main():
    LesMonotonies = [
        "geeks.txt",
        "lechargeurdeHania.txt"
    ]

    t = [0] * (len(LesMonotonies) + 1)
    print("1. Création du tas vide :", t)
    
    fichiers = {nom: open(nom, "r") for nom in LesMonotonies}

    print("\n2. --- INITIALISATION (1ère ligne de chaque fichier) ---")
    for nom, f in fichiers.items():
        ligne = f.readline()
        if ligne.strip():
            ajouter_tas(t, {"valeur": int(ligne), "fichier": nom})

    print("\n>>> Tas initialisé prêt pour la fusion :", t)

    print("\n3. --- BOUCLE DE FUSION ---")
    tour = 1
    with open("MonotonieFinale", "w") as sortie:
        while t[0] > 0:
            print(f"\n--- Tour n°{tour} ---")
            racine = retirer_min_tas(t)
            
            sortie.write(str(racine["valeur"]) + "\n")
            print(f"  [Ecriture] {racine['valeur']} écrit dans MonotonieFinale")

            ligne = fichiers[racine["fichier"]].readline()
            if ligne.strip():
                ajouter_tas(t, {"valeur": int(ligne), "fichier": racine["fichier"]})
            else:
                print(f"  [Info] Le fichier '{racine['fichier']}' est entièrement lu !")
            
            tour += 1

    for f in fichiers.values():
        f.close()

    print("\n4. --- FIN ---")
    print("Fusion terminée : voir le fichier MonotonieFinale")


main()

print("\n------------END------------\n")