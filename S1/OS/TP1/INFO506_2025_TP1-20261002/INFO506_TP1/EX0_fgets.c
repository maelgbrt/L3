#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char buffer[100];  // zone mémoire pour stocker la ligne saisie

    printf("Entrez une phrase : ");

    // Lecture d'une ligne depuis stdin
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        printf("Vous avez saisi : %s", buffer);
    } else {
        printf("Erreur de lecture.\n");
	exit(EXIT_FAILURE) ;
    }

    return 0;
}

