## Exercice 2


### Question 3

```
( ab | b )*( a | ε )
```

### Question 4

```
Commence par A : 
(ab)+(a|ε)

Commence par B :
(ba)+(b|ε)


vrmt difficile
```

### Question 5

Rappelez l’algorithme r´ecursif (vu en cours) utilis´e pour tester si une
expression r´eguli`ere contient le mot vide ε
```
Soit ER := ∅ | s | ε | ER + ER | ER.ER | ER*

Si e = ∅ alors ε ∉ L(e)
Si e = s alors ε ∉ L(e)
Si e = ε alors ε ∈ L(e)
Si e = ER + ER alors (ε ∈ L(e) ssi L(e1) ∈ ε OU L(e2) ∈ ε)
Si e = ER . ER alors (ε ∈ L(e) ssi L(e1) ∈ ε ET L(e2) ∈ ε)
Si e = ER* alors ε ∈ L(e)
```

```
(a+ba*)*+b(a+(b+aba)*)*


Le calcul est de forme e1 + e2
IL faut que ε ∈ e1 ou e2


Soit e1 = (a+ba*)*
comme e1 est de la forme ER* alors ε ∈ L(e1)
Donc ε ∈ L(E)

Pour le fun :
Soit e2 =  b(a+(b+aba)*)* = s.e21
et e21 est de forme ER* alors ε ∈ L(e21)
mais ε ∉ L(s)
donc ε ∉ L(e2)




(ε + b)(aa* + bb*a)*

On décopose, on a E = e1e2
il faut donc que ε ∈ e1 et e2

e1 : 
(ε + b) = vrai

e2 : 
(aa* + bb*a)* = (ER)* donc VRAI

CLC : ε ∈ E


(ε + a)(ε + b)(ε + c)(ε + d)(e + f)

e1 :  VRAI
e2 : VRAI
e3 : VRAI
e4 : VRAI
E5 : FAUX

CLC : FAUX



(a + (b + (c + d)*)*)*

soit e1 = (c+d)* = VRAI
soit e2 = (b+e1)* = VRAI
soit e3 = (a+e2)* = VRAI
car forme ER*

CLC : VRAI
```


### Question 6

Si e = ∅ alors ∅ ∈ L(e)
Si e = ε alors ∅ ∉ L(e)
Si e = s alors ∅ ∉ L(e)
Si e = ER + ER alors (∅ ∈ L(e) ssi e1 = ∅ ET e2 = ∅)
Si e = ER * ER alors (∅ ∈ L(e) ssi e1 = ∅ ou e2 = ∅)
Si e = ER * alors ∅ ∉ L(e) (CONTIENT AU MOINS ε)


/