## Question 3 

```
procedure recopier (t1 : tableau, i1 : entier;t2  :tableau , i2) is
    debut
        si t1[i1] != _|_ ( la fin de l'arbre ) alors
        t2[i2]:=t1[i1];
        recopier(t1,2*i1,t2,2*i2)
        recopier(t1,2*i1+1,t2,2*i2+1)
        fin si;
    fin recopier;
```

```
procedure rotation-droite(t1 : tableau ; var t2 : tableau);
    debut
        t2[1] := t1[2],
        t2[3]:=t1[1];
        recopier(t1,4,t2,2);
        recopier(t1,5,t2,6);
        recopier(t2,3,t2,7);

    fin rotation-droite;
```








