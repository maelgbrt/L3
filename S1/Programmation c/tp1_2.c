#include <stdio.h>

int printString( const char *str) {
    while(*str != '\0'){
        putchar(*str);
        str++;
    }
    return 0;
}

int stringLenght( const char *str) {
    int len = 0;
    while(*str != '\0'){
        str++;
        len++;
    }
    printf("%d\n", len);
    return len;
}

char toLowerCase(char c) {
    if (c >= 'A' && c<='Z'){
        return c + 32;
    }
    return c;
}


// int stringCompare ( const char * str1 , const char * str2 ){
//     int res = 0;
//     if (stringLenght(*str1) == stringLenght(*str2)) {
        
//     }
// }

// ---------------------- EXERCICE 2 ----------------------
char toUpperCase(char c) {
    if (c >= 'a' && c<='z'){
        return c - 32;
    }
    return c;
}

char toUpperString(const char *str) {
    int taille = stringLenght(str);
    for (int i = 0; i < taille; i++) {
        printf("%c",toUpperCase(str[i]));
    }
    return *str;
}


void affichage_tab_vigenere(){
    char tab[26][26];
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 26; j++){
            tab[i][j] = 'A' + (i + j) % 26;
            printf("| %c ", tab[i][j]);
        }
    printf("\n---------------------------------------------------------------------------------------------------------\n");
    }
    printf("tab[a] = %c", *tab['A'-65]);
}

void main(){

    // =============================
    // tests 
    char *msg = "Hello World !\n";
    // printString(msg);
    // stringLenght(msg);
    // putchar(toLowerCase('M'));

    //affichage_tab_vigenere();
    //putchar(toUpperCase('a'));

    toUpperString(msg);
}


// carre[i][j] = 'A' + (i + j) % 26;

