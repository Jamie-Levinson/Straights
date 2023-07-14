# Straights
Straights is an interactive text based card game, written for a school project in C++ using object oriented design principles.

This is a 4-player game, where each player (either human or computer) takes turns entering commands to interact with the game board.

## Rules:
 The objective is to get the fewest number of points among the players. 
 The game ends when one player accumulates 80 points or more, and the player with the lowest score is declared the winner. 
 If the lowest score is a tie, then all players with that score win.

 Straights uses a standard 52-card deck, without the jokers. Each player is dealt 13 cards at the beginning of each round. 
 In this game, the Ace is considered to be the lowest card in each suit (rank of 1), while the King is the highest (rank of 13).

 On a player's turn, they can play a card (only certain plays are legal). If they don't have any legal plays,
 they must choose a card to discard. Once all cards are played or discarded, a player's score is calculated as the sum of their discard pile.

 Additionally, a player could choose to ragequit, allowing the computer to take their spot.

