// GABORIT Maël
// BOUDJAJ Hania
// INFO506 - L3 GRP3

// ======================================
//              QUESTION 1 :
// ======================================
// FILE * est un pointeur vers un flux de donner qu'on va pouvoir modifier (lecture, écriture, lecture/écriture). 
// on utilise des buffers pour écrire et on attend l'appel système (on écrit caractère par caractère avec write())

// Un descripteur de fichier est un entier positif qui sert à identifier un flux de données ouvert. Il est passé à des fonctions. 
// Récupérer par un open. Pas efficace car car par car


// ======================================
//              QUESTION 2 :
// ======================================
// echo $? 

    // >>0
    // Quit dépile les éléments 1 par 1 et les libère de la mémoire avant de kill le procesus. Les descripteurs sont fermés.
    // Exit se content de kill le processus père.


// ======================================
//              QUESTION 3 :
// ======================================

// Quand on fait des opérations sur des fichiers (écriture, lecture,...) le répertoire de travail sert de point de repère. 
// Si on est dans le mauvais repertoire, certaines sommandes ne fonctionneront pas (ex : execution de fichier)

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>  

#define MAX_ARGS 16


// ENTREE : args    : mots de la commande (fini par NULL)
//          n       : nombre de mots
//          outfile : adresse où stocker le nom du fichier
// SORTIE : 0 si OK, -1 si erreur de syntaxe
//          *outfile = nom du fichier, ou NULL si pas de ">"
// BUT :    Chercher ">" dans args, mémoriser le fichier qui suit,
//          remplacer ">" par NULL.

int find_redirect(char **args, int n, char **outfile) {
    *outfile = NULL;

    for (int i =0; i < n && *outfile == NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            if (i + 1 >= n) {
                printf("Erreur : nom de fichier manquant.\n");
                return -1;
            }
            *outfile = args[i +1]; // fichier = l'arg après ">"
            args[i] = NULL; // on remplace ">" par un NULL
        }
    }

    if (args[0] == NULL) {
        printf("Erreur : commande manquante.");
        return -1;
    }
    return 0;
}


// ENTREE : args : mots de la commande (fini par NULL)
//          n    : nombre de mots
// SORTIE : 0 si pas de "|"
//          indice de la 2e commande si "|" trouvé
//          -1 si erreur de syntaxe
// BUT :    Chercher "|" dans args et le remplacer par NULL
//          pour séparer les deux commandes.

int find_pipe(char **args, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(args[i], "|") == 0) {
            if (i == 0 || i + 1 >= n) {
                printf("Erreur : commande manquante autour de |\n");
                return -1;
            }
            args[i] = NULL;
            return i + 1;
        }
    }
    return 0;
}


// ENTREE : outfile : nom du fichier de sortie
// SORTIE : 0 si OK, -1 si open échoue
// BUT :    Ouvrir outfile et le brancher sur la sortie standard (dup2).
//          À appeler dans le fils.

int redirect_stdout(const char *outfile) {
    int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); // O_WRONLY	ouvre en écriture seule
                                                                // O_CREAT	    crée le fichier s’il n’existe pas
                                                                // O_TRUNC	    vide le fichier s’il existe déjà
                                                                // 0644        proprio : lire et écrire. autres : lire
    if (fd == -1) {         
        perror(outfile);
        return -1;
    }
    dup2(fd, STDOUT_FILENO); // descropteur sortie standard
    close(fd);
    return 0;
}


// ENTREE : args1 : mots de la 1re commande (fini par NULL)
//          args2 : mots de la 2e commande (fini par NULL)
// SORTIE : aucune
// BUT :    Exécuter "cmd1 | cmd2" avec un pipe et deux fils,
//          puis attendre les deux.

void exec_pipe(char **args1, char **args2) {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        close(fd[0]); close(fd[1]);
        return;
    }
    if (pid1 == 0) {
        // fils 1 écrit dans le pipe
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(args1[0], args1);
        perror(args1[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        close(fd[0]); close(fd[1]);
        waitpid(pid1, NULL, 0);
        return;
    }
    if (pid2 == 0) {
        // fils 2 lit depuis le pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(args2[0], args2);
        perror(args2[0]);
        exit(EXIT_FAILURE);
    }

    // père 
    close(fd[0]);
    close(fd[1]);

    int status;
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    

    // DEBUG
    // if (WIFEXITED(status)) {
    //     printf("code de retour : %d\n", WEXITSTATUS(status));
    // }
}


// ENTREE : args : mots de la commande (fini par NULL)
//          n    : nombre de mots
// SORTIE : aucune
// BUT :    Exécuter une commande externe (pipe, redirection ">" gérés)
//          avec fork + execvp, puis attendre le fils.

void exec_cmd(char **args, int n){
    char *outfile;
    
    int p = find_pipe(args, n);
    if (p == -1)
        return;

    if (p > 0) {
        exec_pipe(args, args + p);
        return;
    }
    
    if (find_redirect(args, n, &outfile) == -1)
        return;
    
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return; // fin de fonction
    }

    if (pid == 0) {
        // fils (processus externe appelé)
        if (outfile != NULL && redirect_stdout(outfile) == -1)
            exit(EXIT_FAILURE);
        execvp(args[0], args);
        perror(args[0]); // seulement si exec échoue
        exit(EXIT_FAILURE);
    }

    // père (minishell)
    int status; //status de fin du fils
    waitpid(pid, &status, 0);
    
    // DEBUG
    // if (WIFEXITED(status)) { // macro pour vérifier si le fils s'est terminé normalement (exit ou return)
        
        // printf("Code de retour : %d\n", WEXITSTATUS(status));
    // }
}


// ENTREE : cmdline : ligne saisie (modifiable)
//          cmdargs : tableau à remplir (taille MAX_ARGS)
// SORTIE : nombre de mots (max MAX_ARGS - 1), cmdargs[n] = NULL
// BUT :    Découper la ligne en mots avec strtok.

int get_cmd_args ( char * cmdline , char ** cmdargs ){
    
    char *element; // là où on stock le strtok
   
    int n = 0;

    element=strtok(cmdline, " \t\n");  // On sépare tous les mots de la ligne (séparateur = espace ou retour ligne ou tabuation)  
    
    while (element != NULL && n < MAX_ARGS - 1) { // on parcours sur element pour ajouter les mots au tableau cmdargs mais on laisse la denière case libre
            cmdargs[n++] = element;
            element = strtok(NULL, " \t\n"); // On enlève le mot de element (condiition d'arrêt : element = NULL)
        }
    cmdargs[n] = NULL; // le dernier elt doit être NULL pour la foncton execvp (partie 3)
	return (n);
}


// ENTREE : aucune
// SORTIE : 0
// BUT :    Boucle REPL : lire une ligne, la découper, exécuter
//          une commande interne (exit, pwd, ls, lsl, cd) ou externe.

int main(void) {
    char cmdline[] = "";   /* tableau modifiable */
    char *tab[MAX_ARGS];
    char cmd[100];

    int n = get_cmd_args(cmdline, tab);
    
    for (int i = 0; i < n; i++) {
        puts(tab[i]);
    }

    // Boucle d’interpretation des commandes REPL
    while (1) {
        /* READ */
        // 1 - Recuperation de la ligne de commande
        printf(">>> ");
        fgets(cmd, sizeof(cmd), stdin); // stdin = flux entree

        // 2 - Recuperarion des elements de la commande
        int n = get_cmd_args (cmd, tab) ;
        
        /* EVAL */
        // 3 - Traitement de la commande

        // COMMANDES INTERNES -------------------------------
        if (strcmp(tab[0], "exit") == 0) {
            exit(EXIT_SUCCESS);
        }
        
        else if (strcmp(tab[0], "pwd") == 0) {
            getcwd(cmd, sizeof(cmd));
            printf("%s\n", cmd);
        }

        else if (strcmp(tab[0], "ls") == 0) {
            DIR *dir = opendir(".");
            struct dirent *entry;
            
            while((entry = readdir(dir)) != NULL) {
                printf("%s\n", (*entry).d_name);
            }
            closedir(dir);
        }
        
        else if (strcmp(tab[0], "lsl") == 0) {
            DIR *dir = opendir(".");
            if (dir == NULL) {
                perror("opendir");
            } else {
                struct dirent *entry;

                while((entry = readdir(dir)) != NULL) {
                    struct stat st;
                if (stat(entry->d_name, &st) == -1) {
                    perror(entry->d_name);
                } else {

                // gestion droits
                    printf("%s\n",(*entry).d_name); 
                    // ? 'r' : '-' = opérateur ternaire. Résultat est non nul, on prend 'r/w/x', sinon '-'.
                    printf("%c", (st.st_mode & S_IRUSR) ? 'r' : '-'); // lecture proprio
                    printf("%c", (st.st_mode & S_IWUSR) ? 'w' : '-'); // écriture proprio
                    printf("%c", (st.st_mode & S_IXUSR) ? 'x' : '-'); // exécuion proprio
                    printf("%c", (st.st_mode & S_IRGRP) ? 'r' : '-'); // lecture groupe
                    printf("%c", (st.st_mode & S_IWGRP) ? 'w' : '-'); // écriture groupe
                    printf("%c", (st.st_mode & S_IXGRP) ? 'x' : '-'); // exécution groupe
                    printf("%c", (st.st_mode & S_IROTH) ? 'r' : '-'); // lecture autres
                    printf("%c", (st.st_mode & S_IWOTH) ? 'w' : '-'); // écriture autres
                    printf("%c", (st.st_mode & S_IXOTH) ? 'x' : '-'); // exécution autres

                    printf(" %8ld %6ld %10lu %s\n",
                    (long)st.st_size,
                    (long)st.st_blocks,
                    (unsigned long)st.st_ino,
                    (*entry).d_name);
                    }      
                }
            }
        }

        else if (strcmp(tab[0], "cd") == 0) {
            const char *dest;

            if (n > 1) {
                dest = tab[1];
            } 
            else {
                dest = getenv("HOME");
            }
            

            if (dest == NULL) {
                printf("cd: HOME non défini\n");
            } 
            else if (chdir(dest)== -1){
                perror("cd");
            }
        }
        // FIN COMMANNDES INTERNES --------------------------
        
        // COMMANDES EXTERNES
        else {
                exec_cmd(tab, n);
        }
    } /* LOOP */

    return 0;
}

// NOTES 

// char * getenv( const char * varName );

// Cette fonction est utilisée pour récupérer le contenu d'une variable d'environnement. 
// Les variables d'environnement sont définies par le système d'exploitation utilisé 
// et permmettent d'obtenir des informations sur l'environnement dans lequel 
// s'exécute le processus (le programme) en cours. 