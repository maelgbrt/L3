// BOUDJAJ Hania
// GABORIT Maël
// L3 INFO GRP 3

/*
====== PARTIE 3 ====== 

Explication du problème : 
4 blocs sont libérés alors qu'ils sont encore utilisés.
GC_collect ne prend en compte que la pile (qui ici contient T) et ignore le tas (T[0] à T[3]).
Il faut donc marquer les zones occupées dans le tas.
On ne peut pas parcourir le tas comme on parcourait la pile car le tas n'est pas une liste 
d'adresses contiguës avec un début et une fin clair. 
Il est divisé en plusieurs sous-parties.

Solution :
Il faut donc parcourir BLOCKS et retouver les blocs alloués par GC_malloc.
Pour ça, on vérifie pour chaque bloc alloué s'il contient des adresses pointant vers d’autres blocs.
Comme un bloc nouvellement marqué peut lui-même contenir des pointeurs vers d’autres blocs, 
on recommence le parcours tant que le nombre de blocs marqués augmente.
*/

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>

#define WORD_SIZE 4

/*
 * verbosity level
 */
int VERBOSE = 0;

/*
 * type for "raw" addresses
 * ``void*`` is not appropriate because C fordids pointer arithmetic on
 * ``void*``...
 */
typedef char *address_t;

/*
 * type of linked lists
 *
 * Note that because pointers are aligned, the field ``in_use`` could be put
 * in the least significant bit of ``start``!
 */
typedef struct cell {
    address_t start;
    size_t size;
    char in_use;
    struct cell *next;
} cell_t;

/*
 * prototypes
 */
void print_list(cell_t * list);
void insert_BLOCKS(address_t start, size_t size);

void *GC_malloc(size_t size);
void mark_BLOCK(address_t v);
void mark_region(address_t start, address_t end);
void mark_from_heap();
void mark_from_stack();

void GC_collect();

void DEBUG(int v, char *format, ...);

/*
 * GLOBAL variable containing the list of user allocated blocks
 */
cell_t *BLOCKS = NULL;

/*
 * GLOBAL variable containing the address of the start of the stack (this
 * needs to be initialized in ``main``.
 */
address_t STACK_START;

/*
 * display an ASCII representation of a linked list of blocks
 */
void print_list(cell_t * list)
{
    fprintf(stderr, "  +-------+--------------+----------+------+\n");
    fprintf(stderr, "  | index |   address    |   size   | used |\n");
    fprintf(stderr, "  +-------+--------------+----------+------+\n");
    
    cell_t *p;
    int index = 0;
    for (cell_t *p = list; p != NULL; p = p->next) {
        fprintf(stderr, "  |  %03i  |  %10p  |  %6zu  |  %d   |\n",
                        index,
                        p->start,
                        p->size,
                        p->in_use);
        index++;
    }
    
    fprintf(stderr, "  +-------+--------------+----------+------+\n");
}

/*
 * special malloc that calls system's malloc and records the corresponding
 * blocks inside global variable ``BLOCKS``
 */
void *GC_malloc(size_t size)
{
    // appeler la fonction malloc du système
    address_t *tmp = malloc(size);

    // sauvegarder les adresses du début et de fin de zone dans BLOCKS
    if (tmp != NULL) {
        insert_BLOCKS((address_t)tmp, size);
    }
    
    //print_list(BLOCKS);
    
    return tmp;
}

/*
 * mark the block containing address ``v`` as used
 */
void mark_BLOCK(address_t v)
{
    cell_t *p;
    for (p = BLOCKS; p != NULL; p = p->next) {
        // on regarde si v est dans l'interval du block (@ début - @ fin)
        if (v >= p->start && v < p->start + p->size) {
            p->in_use = 1;
        }
        // if the address ``v`` is inside the block, mark it as used
    }
}

/*
 * mark blocks from a memory region
 */
void mark_region(address_t start, address_t end)
{
    address_t p = NULL;                // pointer to memory
    address_t v = NULL;                // value at pointer p
    for (p = start; p < end; p += WORD_SIZE) {
        v = *(address_t *) p; // lit une valeur de type address_t
        mark_BLOCK(v);
    }
}

/*
 * mark blocks referenced from the stack,
 */
void mark_from_stack()
{
     // variable contenue dans l'adresse du bas de la pile
    int bottom;
    mark_region((address_t)&bottom, STACK_START);
}


// compte les blocs actuellement marqués comme utilisés
int count_marked()
{
    int n = 0;
    for (cell_t *p = BLOCKS; p != NULL; p = p->next) {
        if (p->in_use == 1) {
            n++;
        }
    }
    return n;
}

/*
 * mark blocks referenced from the heap,
 */
void mark_from_heap()
{
    int before = -1;               // valeur impossible pour entrer dans la boucle
    int after = count_marked();    // blocs marqués par la pile

    // tant qu'on découvre de nouveaux blocs, on recommence
    while (after != before) {
        before = after;

        // on regarde le contenu de chaque bloc déjà marqué
        for (cell_t *p = BLOCKS; p != NULL; p = p->next) {
            if (p->in_use == 1) {
                mark_region(p->start, p->start + p->size);
            }
        }

        after = count_marked();
    }
}

/*
 * look at the stack and heap for references to user allocated blocks, and
 * free all the blocks that were not referenced
 */
void GC_collect()
{
    // unmark all blocks
    cell_t *p;
    for (p = BLOCKS; p != NULL; p = p->next) {
        p->in_use = 0;
    }

    // mark blocks referenced from stack
    mark_from_stack();

    // mark blocks referenced from heap
    mark_from_heap();

    // free all unused blocks
    cell_t *tmp;
    p = BLOCKS;
    cell_t *prev = NULL;
    while (p != NULL) {
        if (p->in_use == 0) {
            free(p->start);
            if (prev == NULL) {        // first element
                BLOCKS = p->next;
                // NOTE: do not set prev, it should remain NULL
            } else {
                prev->next = p->next;
            }
            tmp = p->next;
            free(p);
            p = tmp;
        } else {
            prev = p;
            p = p->next;
        }
    }
}

int test_1_1() 
{
    BLOCKS = NULL;

    printf("Liste vide :\n");
    print_list(BLOCKS);

    // insertion de blocs dans BLOCKS

    insert_BLOCKS((address_t)0x1000, 2048);
    insert_BLOCKS((address_t)0x500,  256);   
    insert_BLOCKS((address_t)0x3000, 1024);     
    insert_BLOCKS((address_t)0x800,  512);   
    

    printf("=== Test 1 ========================\n");
    printf("Plusieurs blocs non utilisés :\n");
    print_list(BLOCKS);
    
    printf("=== Test 2 ========================\n");
    printf("Plusieurs blocs dont 2 utilisés :\n");
   
    BLOCKS->in_use = 1;              // 0x500  : utilisé
    BLOCKS->next->next->in_use = 1;  // 0x1000 : utilisé
    
    print_list(BLOCKS);

    // On libère la liste
    while (BLOCKS != NULL) {
        cell_t *tmp = BLOCKS;
        BLOCKS = BLOCKS->next;
        free(tmp);
    }

    printf("=== Test 3 ========================\n");
    printf("BLOCKS après libération :\n");

    print_list(BLOCKS);

    return 0;
}

int test_gc(void)
{
    printf("== test_gc ==\n");

    // allocations
    int *a = GC_malloc(100);
    int *b = GC_malloc(200);
    int *c = GC_malloc(300);
    int *d = GC_malloc(400);

    // on écrase certains pointeurs ( b et d deviennent inaccessibles)
    b = NULL;
    d = NULL;

    // liste avant le ramasse-miettes : 4 blocs
    fprintf(stderr, "Avant GC_collect :\n");
    print_list(BLOCKS);

    // collecte
    GC_collect();

    // liste après : 2 blocs (a et c)
    fprintf(stderr, "Après GC_collect :\n");
    print_list(BLOCKS);

    printf("a=%p c=%p\n", (void *)a, (void *)c);
    return 0;
}

void partie_3()
{
    int size = 4;
    
    int **T = GC_malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        T[i] = GC_malloc(size * sizeof(int));
    }

    fprintf(stderr, "Avant GC_collect (T + 4 lignes = 5 blocs) :\n");
    print_list(BLOCKS);

    GC_collect();

    fprintf(stderr, "Après GC_collect (gestion du tas prise en compte):\n");
    print_list(BLOCKS);

    printf("T=%p\n", (void *)T);
    for (int i = 0; i < size; i++) {
        printf("T[%d]=%p\n", i, (void *)T[i]);
    }
    printf("\nOn a bien 5 blocs marqués (T dans la pile et T[0] à T[3] dans le tas.)\n");
}

/***************************************************************************
 ***   ``main`` function   *************************************************
 ***************************************************************************/
int main(int argc, char **argv)
{
    int start; // adresse du haut de la pile
    STACK_START = (address_t) &start;
    // get first command line argument for verbosity
    if (argc > 1) {
        VERBOSE = atoi(argv[1]);
        printf("VERBOSE = %i\n", VERBOSE);
    }
    // tests
    printf("\n============================\n========= PARTIE 1 =========\n============================\n");
    int test11 = test_1_1();
    
    printf("\n============================\n========= PARTIE 2 =========\n============================\n");
    test_gc();

    printf("\n============================\n========= PARTIE 3 =========\n============================\n");
    partie_3();
    return 0;
}
/***************************************************************************
 ***************************************************************************
 ***   DO NOT MODIFY FOLLOWING FUNCTIONS   *********************************
 ***************************************************************************
 ***************************************************************************/

/*
 * display debug messages:
 * ``DEBUG`` takes a first argument giving the verbosity level at which the
 * message is displayed
 * the remaining arguments are interpreted as for the standard ``printf``
 * function...
 *
 * Note: the global variable ``VERBOSE`` is initialized in ``main`` as the
 * value of the first argument ``argv[1]``.
 */
void DEBUG(int v, char *format, ...)
{
    va_list args;
    if (v <= VERBOSE) {
        va_start(args, format);
        vfprintf(stderr, format, args);
        va_end(args);
    }
}

/*
 * insert a new cell into the global variable ``BLOCKS``
 */
void insert_BLOCKS(address_t start, size_t size)
{
    cell_t *c = malloc(sizeof(cell_t));
    c->start = start;
    c->size = size;
    c->next = NULL;
    c->in_use = 0;

    if (BLOCKS == NULL) {
        // initialize BLOCKS list if necessary
        BLOCKS = c;
    } else if (c->start < BLOCKS->start) {
        // insert in first position
        c->next = BLOCKS;
        BLOCKS = c;
    } else {
        // otherwise, look for position just before the new cell
        cell_t *p;
        for (p = BLOCKS; p->next != NULL; p = p->next) {
            if (p->next->start > c->start) {
                break;
            }
        }
        c->next = p->next;
        p->next = c;
    }
}
