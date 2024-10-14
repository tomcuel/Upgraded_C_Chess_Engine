CC=gcc
CGFLAGS=-Wall -Wfatal-errors -I/opt/homebrew/include/SDL2
LDFLAGS=-Iinclude -lSDL2main -lSDL2 -L/opt/homebrew/lib -lSDL2_ttf -lSDL2_image

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(OBJ)

%.o: %.c
	$(CC) $(CGFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -f *.o

realclean: clean
	rm -f *.x