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





void transcription_key (const char *str , char *key)

{

printf("\n");
char message[100];
int key_index = 0;
    for(int i = 0 ; i < stringLength(str);i++){
    
        if (str[i] == ' ' || str[i] == '\''){
            message[i] = ' ';
        }else{
            message[i] = key[key_index % stringLength(key)];
            key_index++;
        }
    }
    message[stringLength(str)] = '\0';
    printString(str);
    printf("\n");
    printString(message);
}







void addition_char (char a, char b)
{
    printf("\n");
    printf("%d\n", a + b); // Affichera 195

}



int position_char_sur_26(char a)
{
    return (a-65);
}




encypted_1( char * message , char * key , char vigenereTable1 ){



    // Mettre en Majuscule 
    char * maj_str1 = toUpperString();
    char * maj_key = ;

    // Transcription avec la clée
    transcription_key(maj_str1,maj_key);

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
    int val = position_char_sur_26('A');
    printf("\n la val est : %d",val);


    
    // addition_char('A','b');

    // printf('\nle charactere est : %d', test);



// // ...
// encrypt_1 ( message , key , vigenereTable1 ) ;
// printf ( » encrypt1 :␣%s\n », message ) ;
// decrypt_1 ( message , key , vigenereTable1 ) ;
// printf (« decrypt1 :␣%s\n », message ) ;
// return 0 ;
    
}
