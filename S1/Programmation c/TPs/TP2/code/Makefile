CC = gcc
CFLAGS = -Wall -Wextra -g

EXEC = tp2
LIB = libgame.a

TESTDIR = tests
TEST_SRC = $(TESTDIR)/test_jeu.c
TEST_EXEC = $(TESTDIR)/test_jeu

LIBSRCS = DataGame.c Element.c Action.c Object.c Joueur.c Inventaire.c Equipe.c Entite.c
SRCS = tp2.c $(LIBSRCS)
OBJS = $(SRCS:.c=.o)
LIBOBJS = $(LIBSRCS:.c=.o)
HEADERS = DataGame.h Element.h Action.h Object.h Joueur.h Inventaire.h Equipe.h Entite.h

all: $(EXEC)

# Création librairie statique
$(LIB): $(LIBOBJS)
	ar rcs $@ $^


# Édition de liens 
# .o en executable
$(EXEC): tp2.o $(LIB)
	$(CC) tp2.o -L. -lgame -o $(EXEC)


# Compilation des objets : si un .c ou un .h change, on recompile
# .c ou .h en -> .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


# Compilation des tests
$(TEST_EXEC): $(TEST_SRC) $(LIB) $(HEADERS)
	$(CC) $(CFLAGS) $(TEST_SRC) -L. -lgame -o $(TEST_EXEC)

test: $(TEST_EXEC)
	./$(TEST_EXEC)


clean:
	rm -f $(OBJS) $(LIB)
