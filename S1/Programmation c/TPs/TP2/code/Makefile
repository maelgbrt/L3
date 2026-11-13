CC = gcc
CFLAGS = -Wall -Wextra -g

EXEC = tp2
LIB = libgame.a

LIBSRCS = DataGame.c Element.c Action.c
SRCS = tp2.c $(LIBSRCS)
OBJS = $(SRCS:.c=.o)
LIBOBJS = $(LIBSRCS:.c=.o)
HEADERS = DataGame.h Element.h Action.h

all: $(EXEC)

# Édition de liens 
# .o en executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

# Compilation des objets : si un .c ou un .h change, on recompile
# .c ou .h en -> .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(LIB)
