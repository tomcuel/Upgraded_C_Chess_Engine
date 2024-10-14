## Folder containing the main functions of the game where everything is linked together


#### Path tree
```
AI_Data/
├── Openings # the generation and management of the opening book
│
├── Pieces_Square_Tables # creating all the piece square tables that are used in the game, to give the preferencial positions of the different pieces (also depending on the game phase)
│
├── Pre_Computed_Data # creating all the pre-computed data that are used in the game, without having to recompute them each time
│
├── Transposition_Tables # creating the transposition table of the game, to store the different positions and their values to avoid recomputing them
│
└── Opening_Book files # the files used for the opening book, it included all the download games, the opening it created and file to convert the formal log into move_values
```


#### Getting all the openings 
* Getting the unique openings (ex : 6 completes moves = 12 moves) : `sed -E 's/^(([^ ]+ ){11}[^ ]+).*/\1/' Download_Games.txt > All_Openings.txt && sort All_Openings.txt | sed '$!N; /^\(.*\)\n\1$/!P; D' > Opening_in_Games.txt`
* Not needed anymore : supressing the one that contain a choice _(ex Nbxd2, two knights can eat a pawn and we need to tell which knights eat the pawn)_ : `sed '/[a-h][a-h]/d' Opening_in_Games.txt > temp_file.txt && mv temp_file.txt Opening_in_Games.txt && rm -f temp_file.txt`, but now I've been able to changed my opening book loading to consider those moves


#### Limitations : 
* The opening book will only make queens out of the promoted pawn
* Book opening with 12 openings deep (18 already tested), problems loading the file and calculating the value of moves restricted me, I should have tried to change everything to be able to search further without aberration (still possible to play like that but sometimes it will crash or do anything which can be frustrating, this is due to the method of reading the file probably deserves to be reviewed).
* Launching the game will crash the memory, occasionally opening files since the openning book was added, otherwise it won't crash normally during the game.
