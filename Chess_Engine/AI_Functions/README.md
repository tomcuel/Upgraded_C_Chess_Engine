## Folder containing the functions that makes the AI search and play

#### Path tree
```
AI_Functions/
├── AI # functions that are related to the AI testings to create a function that make the AI play. It also contains the principal function to make the AI play on top of all the search testing functions
│
├── Evaluation # functions that are related to the evaluation of the position, as an heuristic used in our search of tree of possibilities
│
├── Move_Generator # generating all the possible moves, the state of the game and the IA making and undoing moves function. It's also a function to get the check state of the game
│
├── Move_Ordering # ordering the moves to improve the alpha-beta pruning, by ordering the moves that are most likely to be the best moves first.
│
└── Search # the search algorithms of the level 7 AI, to find the best move to play (iterative deepening, alpha-beta pruning, quiescence search, transposition tables, opening book)
```

#### Limitations : 
* I haven't fully implemented the insufficient material rules, but in a simple and basic way
* The AI will only promote pawn to queen


## AI levels

#### LVL1 :
- a **random AI** but that will eat pieces when it can maximising the score difference between the eaten piece and the one that take it 

#### LVL2 :
- the first implementation of the **Alpha_Beta_Pruning method** (with a depth of 2 (modifiable)) with a simple evaluation function of the position, we also order the moves depending whether they are good or not, so the best move are searched earlier and it reduces the time of the search

#### LVL3 :
- a second Alpha_Beta_Pruning algorithm (with a depth of 2 (modifiable), so it doesn't take too long) but with an extended search to consider only captures after we have searched at the demanded depth, so that we don't make a shocking move, there is no depth restriction for the **quiescience_search**

#### LVL4 :
* This third occurence of the Alpha_Beta_Pruning algorithm with the extended search for the capture moves (still in depth 2 to be reactiv) focus on an amelioration of the evaluation function that include : 
    * the **count of the material**
    * the **piece square tables** that give the preferencial position of the different pieces depending on the state of the game
    * the **mop_up_score** to put the opponent king in a corner or to push our king forward to face the oppenent king if we're in a positiv endgame situation 
    * an evaluation of the pawn to see if they are isolated, no threatened by any opponent pawn (**passed pawns**)
    * an **evaluation of the pawn shield structure** to protect the king using precomputed data, but also looking if a file is open for a queen to threaten the king that is shielded behind pawn after a castle (there are penalty point to encourage castle to be done)

#### LVL5 :
* Implementation of the **iterative deepening** : we search at depth 1, then 2, etc until we run out of time (it's currently setup at 5sec), with the same Alpha_Beta_Pruning algorithm as in the level 4

#### LVL6 :
* **Transpositions tables** are added to the code, so when a position of the board has always been evaluated (and stored), we can get it without having to calculate it again

#### LVL7 :
* We have the same thing as the level 6 but now in the Alpha_Beta_Pruning algorithm we search at different depth depending if the move is ranked highly in the move ordering or if it's an important one that needs more investigation (**depth extensions**)
* The second main thing is that now it's using an **opening book** to start the game as the pro player would, following and choosing some patterns