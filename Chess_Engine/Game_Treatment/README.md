#### Path tree
```
Game_Treatment/
├── Board # creating the bitboards, and the captured pieces and the score, as well as treating how the make_move and undo_function change the different structures for a human player
│
├── Log # creating the log of the game, whats happening after each move, and the log of the bitboards of the game
│
├── Moves_Treatment # dealing with the moves of the game, the precomputed attacks, and the legality of the moves 
│
└── Settings # creating the game settings
```