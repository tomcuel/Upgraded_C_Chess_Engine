# Getting all the unique openings 
sed -E 's/^(([^ ]+ ){11}[^ ]+).*/\1/' Download_Games.txt > All_Openings.txt && sort All_Openings.txt | sed '$!N; /^\(.*\)\n\1$/!P; D' > Opening_in_Games.txt 

# only 11 : limited by the file lecture capacity with the current method

# Not needed anymore : supressing the one that contain a choice (pawn choice still implemented) : ex : two knights can eat a pawn and we need to tell which knights eat the pawn
sed '/[a-h][a-h]/d' Opening_in_Games.txt > temp_file.txt && mv temp_file.txt Opening_in_Games.txt && rm -f temp_file.txt