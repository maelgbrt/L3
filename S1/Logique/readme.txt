GABORIT MAEL
BOUDJAJ HANIA
L3 INFO GRP3
INFO501 TP1

Question 1 :
1 - OK
2 - OK

Question 2 :
1 - La formule est satisfiable avec a, non b, non c.
2 - L'aglo ne retourne qu'une seule solution, la première.
    Pour trouver une autre solution, on lui interdit celles trouvées en ajoutant leurs inverses aux clauses.
    On a globalement l'affirmation : F sauf solution
    ce qui correspond à : F et (pas solution).
    solution = (x1 et x2 et ... xn)
    Ainsi, pas solution = (non(x1) ou non(x2) ou ... non(xn))

    On recommence jusqu'à ce que la formule ne puisse plus être satifaite.

Question 3 :
    Puisque la formule est mélangée, les clauses ne sont plus mêmes. Par conséquent, la simplification ne sera pas la même d'une formule à l'autre.
    Les clauses seront alors elles aussi différentes. De ce fait, le nombre n'est pas le même.

Question 4 :
Les clauses de l'indice 1 sont :
-x2_trefle 
-x2_pique

Les 4 clauses de l'indice 2 en FNC sont :
X_4_trefle ⟶ X_1_carreau ∨ X_2_carreau ∨ X_3_carreau
devient
-(X_4_trefle) ∨ X_1_carreau ∨ X_2_carreau ∨ X_3_carreau

X_3_trefle ⟶ X_1_carreau ∨ X_2_carreau
devient
-(X_3_trefle) ∨ X_1_carreau ∨ X_2_carreau

X_2_trefle ⟶ X_1_carreau
devient
-(X_2_trefle) ∨ X_1_carreau

¬X_1_trefle
ne change pas


Les clauses de l'indice 3 sont :

-X_1_carreau ∨ -X_2_coeur
-X_2_carreau ∨ -X_3_coeur
-X_3_carreau ∨ -X_4_coeur

-X_1_coeur ∨ -X_2_carreau
-X_2_coeur ∨ -X_3_carreau
-X_3_coeur ∨ -X_4_carreau

# il y a au plus un as de pique
-X_1_pique -X_2_pique
-X_1_pique -X_3_pique
-X_1_pique -X_4_pique
-X_2_pique -X_3_pique
-X_2_pique -X_4_pique
-X_3_pique -X_4_pique

# il y a au plus un as de X_1_carreau
-X_1_carreau -X_2_pique
-X_1_carreau -X_3_pique
-X_1_carreau -X_4_pique
-X_2_pique -X_3_pique
-X_2_pique -X_4_pique
-X_3_pique -X_4_pique

# il y a au plus un as de pique
-X_1_pique -X_2_pique
-X_1_pique -X_3_pique
-X_1_pique -X_4_pique
-X_2_pique -X_3_pique
-X_2_pique -X_4_pique
-X_3_pique -X_4_pique

# il y a au plus un as de pique
-X_1_pique -X_2_pique
-X_1_pique -X_3_pique
-X_1_pique -X_4_pique
-X_2_pique -X_3_pique
-X_2_pique -X_4_pique
-X_3_pique -X_4_pique

#Clauses qui garrantissent seulement 1 élément par place
-X_1_carreau -X_1_trefle
-X_1_carreau -X_1_pique
-X_1_carreau -X_1_coeur
-X_1_trefle -X_1_pique
-X_1_trefle -X_1_coeur
-X_1_coeur -X_1_pique

-X_2_carreau -X_2_trefle
-X_2_carreau -X_2_pique
-X_2_carreau -X_2_coeur
-X_2_trefle -X_2_pique
-X_2_trefle -X_2_coeur
-X_2_coeur -X_2_pique

-X_3_carreau -X_3_trefle
-X_3_carreau -X_3_pique
-X_3_carreau -X_3_coeur
-X_3_trefle -X_3_pique
-X_3_trefle -X_3_coeur
-X_3_coeur -X_3_pique

-X_4_carreau -X_4_trefle
-X_4_carreau -X_4_pique
-X_4_carreau -X_4_coeur
-X_4_trefle -X_4_pique
-X_4_trefle -X_4_coeur
-X_4_coeur -X_4_pique

#Clauses qui garrantissent minimum  par position
X_1_carreau X_1_coeur pique
X_1_carreau X_2_coeur
X_3_carreau X_3_coeur X_3_pique X_3_trefle 
X_4_coeur X_4_pique X_4_trefle 

Quand on teste, on a bien une unique solution.