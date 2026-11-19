###################################
# GABORIT Maël
# BOUDJAJ Hania
###################################


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
    i = 0
    fini = False
    while (intv > 1 or not(fini)):
        intv = partie_entiere(intc/1.3)

        if (intv < 1):
            intv = 1

        i = 1
        fini = True

        while (i + intv <= n):
            if (t[i]>t[i+intv]):
                permuter(i, i+intv)
                fini = False
            
            i += 1
#fin

###################################
#           QUESTION 2            #
###################################

# Implémentaion tri à bulle