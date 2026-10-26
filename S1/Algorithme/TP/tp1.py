print("\n------------TP1------------\n")

def afficherTableau(Tab : list):
    print(Tab)

def ajouterTas(tas : list,val : int,nbElement : int ):
    if (nbElement<=2):
        tas.append(val)
        nbElement = nbElement +1

def minima(tas : list):
    return min(tas)

def indexMinima(tas : list,val : int):
    for i in range(len(tas)):
        if tas[i] == val:
            return i
    return -1


def fichier(nameFichier : str):
    monotonieTest = []
    file = open(nameFichier, "r")
    for line in file:
        monotonieTest.append(int(line.strip()))
    file.close()
    return monotonieTest



def main():


    LesMonotonies = [
        fichier("geeks.txt"),
        fichier("lechargeurdeHania.txt")
    ]

    afficherTableau(LesMonotonies)

    monotonieFinal = []


    tas = []
    for i in range(len(LesMonotonies)):
        tas.append(LesMonotonies[i][0])

    print("\nLe tas apres ajout des minima : ")
    afficherTableau(tas)

    monotonieFinal = []

    while len(LesMonotonies) > 0:
        valeur_min = min(tas)
        index_min = tas.index(valeur_min)

        monotonieFinal.append(valeur_min)

        LesMonotonies[index_min].pop(0)

        if len(LesMonotonies[index_min]) == 0:
            LesMonotonies.pop(index_min)
            tas.pop(index_min)
        else:
            tas[index_min] = LesMonotonies[index_min][0]

    print("\nLa monotonie finale triée : ")
    afficherTableau(monotonieFinal)





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