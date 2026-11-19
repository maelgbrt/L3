tableau_test = [1 , 4 , 8 , 6 , 3 , 12 ,5 , 9 ]

def tri_rapide (i,j : int, tab : list ):
    k : int
    if i < j:
        #partition(t,i,j,k)
        tri_rapide(tab,i,k-1) # tri à droite
        tri_rapide(tab,k+1,j)

def partition (tab : list , i, j, k : int):
    l : int

    # permuter(tab[i],mediant(t[i],t[j],t[i-+j] div 2))
    l = i+1
    k = j

    while l<= k :
        while tab[k] > tab[i] and l <= k :
            k = k-1

        while tab[l] <= tab[i] and l <= k :
            l = l+1

        if l < k :
            # permuter(t[l],t[k])
            l = l + 1
            k = k - 1
    # permuter(t[i],t[k])