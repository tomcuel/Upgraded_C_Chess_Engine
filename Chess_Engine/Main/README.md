## Folder containing the main functions of the game where everything is linked together

#### Path tree
```
Main/
├── Chess_Game # main function that launch the graphics part and treat the input of the user during the game, while managing the timer and the AI play 
│
├── Graphics # deals with showing all the graphics depending on the game status
│
└── Download_Log # functions that are related to download the game status in a file, and open a game depending on the file   
```


#### Limitations : 
* Opening and charging the game through the log will only make queens out of the promoted pawn
* The download_log function will erase the file "game_log.txt" and its data. To keep a game, you need to change the filename so it's not erased 
* The file to download the log isn't only the classic game log, since it would have required a lot more to extract the moves and set up the game 
* download_log + show log : don't care to look if two knights can go the same place _(referenced by Nbd2 in a real formal log)_, it's here in the move values but it would have asked me to make more calculation for something that isn't a massive deal