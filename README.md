# CHESS-GAME-USING-C
Used C programming to code.
I tried to split the code into modules so, I thought about how to do this.
I decided to build many functions for every piece a function to check it move it’s available or not and a function for moving the piece of the move is legal and function to kill another piece if it is found in the place the first piece is going, a function to display all pieces to the user and update it every move 
The Code support undoes and redoes till the first play.
I used struct to achieve this struct save move and I have created an array of it so every move is saved In the array and stored if there is a kill in that play so if when undo bring the last piece in the kill array and return it in the game

