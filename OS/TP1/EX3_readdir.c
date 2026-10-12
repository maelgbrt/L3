#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<string.h>
#include<sys/stat.h>

/* Compte le nombre de fichier dans le repertoire courant */
int main(void){
	DIR *dir = NULL ; 
	struct dirent* ent = NULL;
	int nbr = 0;

	//ouvrir un repertoire 
	dir = opendir(".") ; 
   
       	//parcourir les entrée 	
	while ((ent = readdir(dir)) != NULL)
    	{
        	if(strcmp(ent->d_name, ".") != 0 
            		&& strcmp(ent->d_name, "..") != 0
			&& ent->d_type == DT_REG )
        		
			nbr++; 
    	}

	printf("Le repertoire contient %d fichiers réguiliers\n", nbr );
	return (0) ; 
}
