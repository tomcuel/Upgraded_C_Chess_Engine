CC=gcc
CGFLAGS=-Wall -Wfatal-errors -I/opt/homebrew/include/SDL2
LDFLAGS=-Iinclude -lSDL2main -lSDL2 -L/opt/homebrew/lib -lSDL2_ttf -lSDL2_image

all : Chess_Game.x

Chess_Game.x : Chess_Game.o ../AI_Functions/AI.o ../Game_Treatment/Board.o Download_Log.o ../AI_Functions/Evaluation.o Graphics.o ../Game_Treatment/Log.o ../AI_Functions/Move_Generator.o ../AI_Functions/Move_Ordering.o ../Game_Treatment/Moves_Treatment.o ../AI_Data/Openings.o ../AI_Data/Pieces_Squares_Tables.o ../AI_Data/Pre_Computed_Data.o ../AI_Functions/Search.o ../Game_Treatment/Settings.o ../AI_Data/Transposition_Table.o ../Useful/Utility.o
	$(CC) $(CGFLAGS) -o $@ $^ $(LDFLAGS)

%.o : %.c 
	$(CC) $(CGFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -f *.o

realclean: clean
	rm -f *.x