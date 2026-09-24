# TD2 - INFO505

## Exercice 1 

### Question 1
```
int i = 1;

ptr : &i

*ptr : 1
 bgf

&(*ptr) : &i

*(&ptr) : &i
```

### Question 2 
```
a = 6 , b = 5 , *ptr1 = 6, *ptr2 = 6
```
/buto

### Question 3
p -> 4 <br>
a = 0
```
print'("%d",p);
>> error il manque initialisation de p
```

### Question 4
```
fonction trio sert a rien car pas des pointeur
```

### Question 5 
```
[5,3,5]
```

### Question 6 
```
2,4,5
2
```

### Question 7
```
@nombre
```


## Exercice 2
partie 1
$$
P1(x) = 1x^2 + 2x+ 3 = [3.,2.,1.,0.] 
$$

```
void p_sum(float * R, const float * P1, const float * P2, unsigned int degree)
    {
        for (int = 0, i < degree , i++){
            R[i] = [P1] + P[2];
        }
}

```3

<br>

partie 2
```
float calculP(float *P,int x, int degree){
    int i = degree;
    float result = P[0];
    while (i>0){
        result = result + xpuissancei(x,i)*P[i];
        i--;

    }
    return result
}
```



