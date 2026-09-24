#include <stdio.h>


// ----------------------- EXERCICE 1 -----------------------


// Une fonction qui permet d'afficher une chaîne de caractères
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
    //printf("%d\n", len);
    return len;
}

char toLowerCase(char c) {
    if (c >= 'A' && c <='Z'){
        return c + 32;
    }
    return c;
}

int stringCompare (  const char * str1  ,  const char * str2 )
{
    int i = 0;
    int size_str1 = 0;
    int size_str2 = 0;

    while (str1[i] != '\0' && str2[i] != '\0'){
        size_str1 += str1[i];
        size_str2 += str2[i];
        i++;
    }
    return size_str2 - size_str1;
    
}


const char * findFirst ( const char * str , char c) {
    const char * res = NULL;
    for(int i = 0; str[i]!='\0'; i++){
        if(c == str[i]) {
            //printf("La valeur est : %p\n", &str[i]);
            //printf("Position :%d\n", i);
            res = &str[i];
            break;
        }
    }
    return res;
}


// ---------------------- EXERCICE 2 ----------------------
char toUpperCase(char c) {
    if (c >= 'a' && c<='z'){
        return c - 32;
    }
    return c;
}

char *toUpperString(char *str) {
    int taille = stringLenght(str);
    for (int i = 0; i < taille; i++) {
        str[i] = toUpperCase(str[i]);
    }
    return str;
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

void valeur_in_tab(int x, int y, char * tab[][])
{
    printf(tab[x][y]);
}


void main(){

    // =============================
    // tests de l'exercice 1
    char *msg = "Hello World !\n";
    printf("Question 1 : printString\n");
    printString(msg);
    printf("\n");

    printf("Question 2 : stringLenght\n");    
    printf("%d",stringLenght(msg));
    printf("\n");


    printf("Question 3 : toLowerCase\n");    
    putchar(toLowerCase('M'));
    printf("\n");    
    printf("\n");

    printf("Question 4 : stringCompare\n");
    int dico = stringCompare("mael","aaaaa");
    printf("\nle number est : %d\n", dico);
    printf("\n");    

    printf("Question 5 : findFirst\n");
    printf("%p", findFirst("Hhhhellelo world", 'e'));
    printf("\n");    
    
    
    //tests de l'exercice 2
    //affichage_tab_vigenere();

    //putchar(toUpperCase('a'));
    //toUpperString(msg);
    
    

}


// carre[i][j] = 'A' + (i + j) % 26;

