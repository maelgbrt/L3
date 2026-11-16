
Définition d'un tri stable : 
Un **tri stable** est un ==algorithme de tri qui **préserve l'ordre relatif** des éléments possédant des clés (ou des valeurs) identiques==.



```
struct case{
	int val;
	int positionInitial;
}

===============================================================================
boucle d'intervalle 

fonction boucleIntervalle(int i : in out){
	int k = i;
	while(t[k] == t[i] and k <= n){
		k += 1;
	}
	return (i, k-1);
}


