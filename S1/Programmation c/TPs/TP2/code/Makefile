CC = gcc
CFLAGS = -Wall -Wextra -g

EXEC = tp2

SRCS = tp2.c DataGame.c Element.c
OBJS = $(SRCS:.c=.o)
HEADERS = DataGame.h Element.h

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
	rm -f $(OBJS)
