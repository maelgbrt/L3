###################################
# GABORIT Maël
# BOUDJAJ Hania
###################################

import random


###################################
#           QUESTION 1            #
###################################

def partie_entiere(flottant):
    return int(flottant)

def permuter(tab, ind1, ind2):
    temp = tab[ind2]
    tab[ind2] = tab[ind1]
    tab[ind1] = temp


def tri_dobosiewicz(tab, n):
    intv = n
    fini = False
    while (intv > 1 or not(fini)):
        intv = partie_entiere(intv/1.3)

        if (intv < 1):
            intv = 1

        i = 0
        fini = True

        while (i + intv < n):
            if (tab[i]>tab[i+intv]):
                permuter(tab, i, i+intv)
                fini = False
            
            i += 1
#fin

# # ---------- TESTS ----------
# if __name__ == "__main__":
#     # Test simple, lisible
#     t = [5, 2, 9, 1, 5, 6, 0, -3]
#     print("Avant :", t)
#     tri_dobosiewicz(t, len(t))
#     print("Après :", t)

#     # Cas limites
#     cas = [
#         [],                      
#         # vide
        
#         [42],                    
#         # un seul élément
        
#         [1, 2, 3, 4],            
#         # déjà trié
        
#         [4, 3, 2, 1],            
#         # ordre inverse
        
#         [7, 7, 7, 7],            
#         # doublons
#     ]
#     for c in cas:
#         copie = c[:]
#         tri_dobosiewicz(copie, len(copie))
#         assert copie == sorted(c), f"Échec sur {c} -> {copie}"
#     print("Cas limites OK")

#     # Tests aléatoires comparés à sorted()
#     for _ in range(1000):
#         n = random.randint(0, 50)
#         c = [random.randint(-100, 100) for _ in range(n)]
#         copie = c[:]
#         tri_dobosiewicz(copie, n)
#         assert copie == sorted(c), f"Échec sur {c}"
#     print("1000 tests aléatoires OK")

###################################
#           QUESTION 2            #
###################################

# Implémentaion tri à bulle

# -----------------------------------
# ----------- PSEUDO CODE -----------
# -----------------------------------

# procedure Tri-bulles(var t : tableau [1..N] de Element);
# var    
#     i, j:1..N
# debut
#     i:=1;
#     tant que i < n faire
#         pour j:=n à i +1 faire
#             si t[j] < t[j-1] alors permuter(t[j], t[j-1]) fin si;
#         fin pour
#         i:=i+1;
#     fin tant que;
# fin


def Tri_bulles(tab):
    i = 0
    n = len(tab)
    while i < n - 1:
    
        for j in range(n-1, i, -1) : # on part de la fin pour faire remonter les éléments
            if (tab[j] < tab[j-1]) :
                permuter(tab, j, j-1) # l'élément remonte
        i+=1
    return tab

t = [4, 3, 1, 2]

# TEST 
# Cas a tester :
# vide
# déjà trié
# doublons
# grande quantité
# ordre inverse

print(Tri_bulles(t))