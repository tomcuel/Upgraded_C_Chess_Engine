

- Using Images and Sounds folder for the render and the chess sounds
- AI.c + Evaluation.c + Move_Ordering.c + Pieces_Squares_Tables.c + Pre_Computed_Data + Search.c + Transposition_Table.c : implementation of the AI part described later in this README
- Board.c : creating the bitboards, and the captured pieces and the score, as well as treating how the make_move and undo_function change the different structures for a human player
- Chess_Game.c : main function that launch the graphics part and treat the input of the user during the game, while managing the timer and the AI play 
- Constants.c : definition of the differents constants used 
- Download_log.c : functions that are related to download the game status in a file, and open a game depending on the file
- Graphics.c : show the game graphics depending on which we're in
- Log.c : creating the log of the game, whats happening after each move, and the log of the bitboards of the game
- Move_Generator.c : generating all the possible moves, the state of the game and the IA making and undoing moves function
- Settings.c : structure that represents the game settings
- Utility.c : creating all the useful functions that are used in the game but not part of the game


# AI levels

## LVL1 :
- a random AI but that will eat pieces when it can maximising the score difference between the eaten piece and the one that take it 

## LVL2 :
- the first implementation of the Alpha_Beta_Pruning method (with a depth of 2 (modifiable)) with a simple evaluation function of the position, we also order the moves depending whether they are good or not, so the best move are searched earlier and it reduces the time of the search

## LVL3 :
- a second Alpha_Beta_Pruning algorithm (with a depth of 2 (modifiable), so it doesn't take too long) but with an extended search to consider only captures after we have searched at the demanded depth, so that we don't make a shocking move, there is no depth restriction for the quiescience_search

## LVL4 :
- this third occurence of the Alpha_Beta_Pruning algorithm with the extended search for the capture moves (still in depth 2 to be reactiv) focus on an amelioration of the evaluation function that include 
- - the count of the material
- - the piece square tables that give the preferencial position of the different pieces depending on the state of the game
- - the mop_up_score to put the opponent king in a corner or to push our king forward to face the oppenent king if we're in a positiv endgame situation 
- - an evaluation of the pawn to see if they are isolated, no threatened by any opponent pawn (passed pawns)
- - an evaluation of the pawn shield structure to protect the king using precomputed data, but also looking if a file is open for a queen to threaten the king that is shielded behind pawn after a castle (there are penalty point to encourage castle to be done)

## LVL5 :
- implementation of the iterative deepening : we search at depth 1, then 2, etc until we run out of time (it's currently setup at 5sec), with the same Alpha_Beta_Pruning algorithm as in the level 4

## LVL6 :
- transpositions tables are added to the code, so when a position of the board has always been evaluated (and stored), we can get it without having to calculate it again

## LVL7 :
- we have the same thing as the level 6 but now in the Alpha_Beta_Pruning algorithm we search at different depth depending if the move is ranked highly in the move ordering or if it's an important one that needs more investigation (depth extensions)