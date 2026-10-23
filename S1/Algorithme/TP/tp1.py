print("\n------------TP1------------\n")

monotonie1 = [1,2,10,42,60]
monotonie2 = [3,10,11,48,63,71]
tas = []
sizeTas = 0;


def main() : 
    print("Minima Monotonie 1 : "  , monotonie1[0])
    print("Minima Monotonie 2 : " , monotonie2[0])

def afficherTableau(Tab : list):
    print(Tab)

def ajouterTas(tas : list,val : int,nbElement : int ):
    if (nbElement<=2):
        tas.append(val)
        nbElement = nbElement +1


def minima(tas : list):
    return min(tas)

main()

afficherTableau(tas)
ajouterTas(tas,5,sizeTas)
ajouterTas(tas,2,sizeTas)
afficherTableau(tas)

print("\n------------END------------\n")