CC = gcc
CFLAGS = -Wall -Wextra -g

EXEC = tp2
LIB = libgame.a

LIBSRCS = DataGame.c Element.c
SRCS = tp2.c $(LIBSRCS)
OBJS = $(SRCS:.c=.o)
LIBOBJS = $(LIBSRCS:.c=.o)
HEADERS = DataGame.h Element.h

all: $(EXEC)

# Création librairie statique
$(LIB): $(LIBOBJS)
	ar rcs $@ $^

# Édition de liens
$(EXEC): tp2.o $(LIB)
	$(CC) tp2.o -L. -lgame -o $(EXEC)
# $(CC) $(OBJS) -o $(EXEC)

# Compilation des objets : si un .c ou un .h change, on recompile
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)
