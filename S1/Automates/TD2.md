# TD 2 Expression Régulière et Dérivation

## Exercice 1 

```
Soit S = {a,b}
1. ((a+ b)(a + b))*
2. b*(ab*ab*)* 
3. (b*(ab*ab*)*) + (a*(ba*ba*)*)

4. (paire,paire)(impaire,paire)(paire,impaire)(impaire,impaire)
    q0            q1            q2              q3
 on a : aa ou bb
 ab = (impaire,impaire) -> q3
 ba = q3

 comme on est plus ds q0 on peut naviguer sans chager situation avec doublette

 retour a Q0   inverse du voyage

 ((ab + ba) (aa + bb)^ (ab + ba) + aa + bb)*
```


## Exercice 2 
```


R = a*(aab + bb*a + bb)*

R/a :
a* ∈ ∅
donc on pose
R1.R2 = R1/a.R2 + R2/a

R1 = a*
R2 = (aab + bb*a + bb)*

E = a*/a . (aab + bb*a + bb)* + (aab + bb*a +bb)*/a


R1 : 
a*/a = a/a . a* = ε . a* = a*
R1.R2  = a*.(aab+bb*a+bb)*

R2/a : 
(aab + bb*a+bb)*/a

(aab + bb*a+bb)/a . (aab + bb*a+bb)*

(aab + bb*a+bb)/a : 

aab/a = ab

bb*a/a = ∅

bb/a = ∅

donc = ab

R2\a = ab.(abb+bb*a+bb)*

a*.(aab+bb*a+bb)* + ab.(abb+bb*a+bb)*

E = (a*+ab)((aab+bb*a+bb)*)




Pour R/b



E = a*/B . (aab + bb*a + bb)* + (aab + bb*a +bb)*/b

R1/b : a*/b = ∅

donc R1.R2 = ∅


et R2/b = 

(aab + bb*a +bb)/b.(aab + bb*a +bb)*

(aab + bb*a +bb)/b : 
aab/b = ∅
bb*a/b = b*a
bb/b = b

donc (aab + bb*a +bb)/b = b*a + b

R2/b =  b*a.(aab + bb*a +bb)*


E = (b*a + b).(aab + bb*a +bb)*



R/ab

(R/a)/b 

R/a = (a*+ab)((aab+bb*a+bb)*)

(R/a)/b =  ((a*+ab)(aab+bb*a+bb)*)/b

on definit b1 = (a*+ab)

on definit b2 = (aab+bb*a+bb)*

on a b1.b2 donc verifions b1


-------------------a1-------------------
b1 = (a*+ab)/b
b1 = a*/b +ab/b
b1 = ∅ + ∅ = ∅

comme b1 = ∅ on doit donc poser

E = b1/b.b2 + b2/b
-------------------a2-------------------
b2 = (aab+bb*a+bb)*
b2 = (aab+bb*a+bb)/b.(aab+bb*a+bb)*
b2 = {
    aab/b = ∅
    bb*a/b = b*a
    bb/b = b

    (aab+bb*a+bb)/b = b*a + b
}

b2/b =  (b*a + b).(aab+bb*a+bb)*


ON pose donc 

b1/b = ∅
b2 = (aab+bb*a+bb)*
b2/b = (b*a + b).(aab+bb*a+bb)*

donc 

E =  (b*a + b).(aab+bb*a+bb)*









- R = (aaa)*

R/a

Soit: 
(aaa) / a . (aaa)*
aaa / a = aa

donc on pose aa.(aaa)*

R/b
Soit :
(aaa) / b = ∅
∅.(aaa)*
 = ∅



```