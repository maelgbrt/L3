#include <stdio.h>

int printString(const char *str)
{
    if (!str) return 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        putchar(str[i]);
    }
    return 1;
}




int stringLength(const char *str)
{   
    if(!str) return 0 ;
    int i = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
    }
    return i;
}


char toLowerCase (char c){

    char minuscule = c+32;
    return minuscule;
    
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

char toUpperCase(char c) {
    if (c >= 'a' && c<='z'){
        return c - 32;
    }
    return c;
}

char *toUpperString(char *str) {
    int taille = stringLength(str);
    for (int i = 0; i < taille; i++) {
        str[i] = toUpperCase(str[i]);
    }
    return str;
}




int position_char_sur_26(char a)
{
    return (a-65);
}



void transcription_key(char *str, char *key)
{
    int str_len = stringLength(str);
    int key_len = stringLength(key);

    if (key_len == 0) return;

    str = toUpperString(str);
    // printf("%s\n", str);

    int key_index = 0;
    for (int i = 0; i < str_len; i++)
    {
        if (str[i] == ' ' || str[i] == '\'')
        {
            putchar(' '); 
        }
        else
        {

            char c = toUpperCase(key[key_index % key_len]);
            // putchar(c);
            key_index++;

            int position_x = position_char_sur_26(str[i]);
            int position_y = position_char_sur_26(c);
            // valeur_in_tab(position_x,position_y);
        }
    }
    putchar('\n');

// printf("\n");
// int key_index = 0;
//     for(int i = 0 ; i < stringLength(str);i++){
    
//         if (str[i] == ' ' || str[i] == '\''){
//             str[i] = ' ';
//         }else{
//             str[i] = (key_index % stringLength(key));
//             printf("le char est : %c",str[i]);
//             key_index++;
//         }
//     }
//     str[stringLength(str)] = '\0';
//     printString(str);
//     printf("\n");
//     printf("voila");
}







void addition_char (char a, char b)
{
    printf("\n");
    printf("%d\n", a + b); // Affichera 195

}




void encypted_1( char * message , char * key ){



    // Mettre en Majuscule 
    char * maj_str1 = toUpperString(message);
    char * maj_key= toUpperString(message);
    // char * maj_key = toUpperString("azerty");


    printString(maj_str1);
    printString(maj_key);

    // Transcription avec la clée
    // transcription_key(maj_str1,maj_key);

}






void main()
{
    printString("mael");
    printf("\n");


    int nb_lettre = stringLength("mael");
    printf("nb de lettre : %d \n " , nb_lettre);


    char minuscule = toLowerCase('M');
    printf(" la minuscule : %c", minuscule);

    int dico = stringCompare("mael","aaaaa");
    printf("\nle number est : %d", dico);







    // EXERCICE 2 

    char message [] = "L'escargot se promene avec sa maison" ;
    char * key = "perdu";
    char vigenereTable1 [26][26] ;
    transcription_key(message, key);
    // int val = position_char_sur_26('A');
    // printf("\n la val est : %d",val);

    // encypted_1(message,key);


    
    // addition_char('A','b');

    // printf('\nle charactere est : %d', test);



// // ...
// encrypt_1 ( message , key , vigenereTable1 ) ;
// printf ( » encrypt1 :␣%s\n », message ) ;
// decrypt_1 ( message , key , vigenereTable1 ) ;
// printf (« decrypt1 :␣%s\n », message ) ;
// return 0 ;
    
}
