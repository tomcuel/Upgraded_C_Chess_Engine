## Folder containing the main functions of the game where everything is linked together

#### Path tree
```
Main/
├── Chess_Game # file that linked the graphics, the AI part and the player inputs
│
├── Graphics # deals with showing all the graphics
│
└── Download_Log # manage how to save or open a game log, to get the current game state        
```


#### limitations : 
* Opening and charging the game through the log will only make queens out of the promoted pawn
* The download_log function will erase the file "game_log.txt" and its data. To keep a game, you need to change the filename so it's not erased 
* The file to download the log isn't only the classic game log, since it would have required a lot more to extract the moves and set up the game 
* download_log + show log : don't care to look if two knights can go the same place _(referenced by Nbd2 in a real formal log)_, it's here in the move values but it would have asked me to make more calculation for something that isn't a massive deal