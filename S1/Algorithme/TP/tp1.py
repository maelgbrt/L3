print("\n------------TP1------------\n")

def afficherTableau(Tab : list):
    print(Tab)

def permuter(tas, ind1, ind2):
    temp = ind2
    tas[ind1] = ind2
    tas[temp] = ind1
    

def ajouter_tas(t, p, x):
    """Ajoute x dans le tas t (indexé à partir de 1). Retourne le nouveau nombre de nœuds."""
    p += 1
    t[p] = x
    i = p

    # on échange tant que x est "inférieur" à son père
    while i > 1 and t[i // 2] > t[i]:
        t[i], t[i // 2] = t[i // 2], t[i]
        i //= 2

    return p

# indice 0 = taille du tas, indice 1 = racine du tas (donc minimum des minima)
# le tas est en ram
# les monotonies ne sont pas en RAM
# si une monotonie s'épuise, le tas fait -1 en taille

def minima(tas : list):
    return min(tas)

def indexMinima(tas : list,val : int):
    for i in range(len(tas)):
        if tas[i] == val:
            return i
    return -1


def fichier(nameFichier : str):

    file = open(nameFichier, "r")
    lignes = file.readlines()
    if lignes:
        return lignes[0]
    file.close()





def main():

    LesMonotonies = [
        "geeks.txt",
        "lechargeurdeHania.txt"
    ]

    nbMonotonies = len(LesMonotonies)
    print(nbMonotonies)
    t = [None] * (nbMonotonies+1) 
    print(t);
    p = 0

    for x in LesMonotonies:
        print(x)
        test = fichier(x)
        print(test)

        p = ajouter_tas(t, p, fichier(x))

    # print(t[1:p+1])   # [1, 3, 8, 5]  -> min-tas

    # fichier("geeks.txt")

    # afficherTableau(LesMonotonies)

    # monotonieFinal = []


    # tas = []
    # for i in range(len(LesMonotonies)):
    #     tas.append(LesMonotonies[i][0])

    # print("\nLe tas apres ajout des minima : ")
    # afficherTableau(tas)

    # monotonieFinal = []

    # while len(LesMonotonies) > 0:
    #     valeur_min = min(tas)
    #     index_min = tas.index(valeur_min)

    #     monotonieFinal.append(valeur_min)

    #     LesMonotonies[index_min].pop(0)

    #     if len(LesMonotonies[index_min]) == 0:
    #         LesMonotonies.pop(index_min)
    #         tas.pop(index_min)
    #     else:
    #         tas[index_min] = LesMonotonies[index_min][0]

    # print("\nLa monotonie finale triée : ")
    # afficherTableau(monotonieFinal)





    # ajouterTas(tas,minima1,sizeTas)
    # ajouterTas(tas,minima2,sizeTas)

    # minTas = minima(tas)
    # index = indexMinima(tas,minTas)

    # monotonieFinal.append(minTas)
    # tas[0] = None


    # afficherTableau(monotonieFinal)
    # afficherTableau(tas)

    
    
main()

# afficherTableau(tas)
# ajouterTas(tas,5,sizeTas)
# ajouterTas(tas,2,sizeTas)
# afficherTableau(tas)

print("\n------------END------------\n")