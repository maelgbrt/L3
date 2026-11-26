tableau_test = [1 , 4 , 8 , 6 , 3 , 12 ,5 , 9 ]

def permuter(tab: list, a: int, b: int) -> None:
    tab[a], tab[b] = tab[b], tab[a]

def mediant(tab: list, a: int, b: int, c: int) -> int:
    """Renvoie l'INDICE (parmi a, b, c) de la valeur médiane."""
    x, y, z = tab[a], tab[b], tab[c]
    if x <= y <= z or z <= y <= x:
        return b
    if y <= x <= z or z <= x <= y:
        return a
    return c


def partition(tab: list, i: int, j: int) -> int:
   

    permuter(tab, i, mediant(tab, i, j, (i + j) // 2))
    l = i + 1
    k = j

    while l <= k:
        while l <= k and tab[k] > tab[i]:
            k -= 1
        while l <= k and tab[l] <= tab[i]:
            l += 1
        if l < k:
            permuter(tab, l, k)
            l += 1
            k -= 1

    permuter(tab, i, k)   # le pivot va à sa place définitive
    return k


def tri_rapide(tab: list, i: int, j: int) -> None:
    if i < j:
        k = partition(tab, i, j)
        tri_rapide(tab, i, k - 1)   # partie gauche
        tri_rapide(tab, k + 1, j)   # partie droite

tri_rapide(tableau_test, 0, len(tableau_test) - 1)
print(tableau_test)





# Tri par tas
def TriParTas(tab: list):
  # Note : tab[0] est une case factice (None) pour commencer les indices à 1
    n = len(tab) - 1
    p = 0
    while p < n:
        p = AjouterTas(tab, p, tab[p + 1])
    while p > 1:
        p, minimum = Retirer_min_tas(tab, p)
        tab[p + 1] = minimum




def Retirer_min_tas(t: list, p: int) -> tuple[int, int]:
  # On récupère le minimum courant
  minimum = t[1]
  t[1] = t[p]
  p = p - 1
  i = 1
  fini = False

  while (i <= (p // 2)) and not fini:
    if (p == 2 * i) or (t[2 * i] < t[2 * i + 1]):
      j = 2 * i
    else:
      j = 2 * i + 1

    # t[j] est le plus petit des 2 fils s'ils existent ou le fils unique le cas échéant
    if t[i] > t[j]:
      permuter(t, i, j)
      i = j
    else:
      fini = True

  return p, minimum



def AjouterTas(tab: list, p: int, x: int) -> int:
  p = p + 1
  tab[p] = x
  i = p
  while i > 1 and tab[i // 2] > tab[i]:
    permuter(tab, i, i // 2)
    i = i // 2
  return p

# # Exemple d'utilisation :
mon_tas = [None, 15, 10, 20,7,9,10,7,89,12]
# p = 3  # nombre de nœuds actuels

# # On récupère le nouveau p retourné par la fonction
# p = AjouterTas(mon_tas, p, 5)

# print(mon_tas)  # Résultat attendu : [0, 5, 10, 20, 15] (le 5 est remonté à la racine)
# print(
#     "Nouveau p :", p,
#     "nouveau tab" , mon_tas
# )  # Résultat attendu : 4 (le nombre de nœuds est bien passé à 4)
    
TriParTas(mon_tas)
print("mon tas : " , mon_tas)
def tri_insertion(tab:list,i:int):
   k : int
   x : int

   if i > 1 :
      tri_insertion(tab,i-1)
      k = i -1
      x = tab[i]

      while k > i and tab[k] > x :
         tab[k+1] = tab[k]
    


