#include "Reversi.h"
#include <iostream>
#include <iomanip>

Reversi::Reversi() {
   resetBoard();
}
//Desc: Searches array for squares containing color
//Pre: none
//Post: returns the number of color squares
int Reversi::count(char color) {
   int count = 0;
   for (int i = 0; i < ROWS; i++) {
       for (int j = 0; j < COLS; j++) {
           if (board[i][j] == color) {
               count++;
           }
       }
   }
   return count;
}
//Desc: Sets the square at the row and col value to color
//Pre: takes value from row, col, and color from user input
//Post: lets the current player place a disk
void Reversi::setDisk(int row, int col, char color) {
   
   board[row][col] = color;
   
   colorSwitch(row, col, color);
  
   if (currentPlayer == 'b') {
       if (MoveisValid('w')) {
           currentPlayer = 'w';
       }
   }
   else {
       if (MoveisValid('b')) {
           currentPlayer = 'b';
       }
   }
}
//Desc: Displays a new board when a piece is placed
//Pre: takes the value of row, col and color from setdisk
//Post: returns the difference between total color and opposite player
int Reversi::resultOfMove(int row, int col, char color) {
   
   char copyBoard[ROWS][COLS];
   for (int i = 0; i < ROWS; i++) {
       for (int j = 0; j < COLS; j++) {
           copyBoard[i][j] = board[i][j];
       }
   }
   
   setDisk(row, col, color);
   
   int colorNum = count(color);
   int otherNum;
   if (color == 'b') {
       otherNum = count('w');
   }
   else {
       otherNum = count('b');
   }
   
   for (int r = 0; r < ROWS; r++) {
       for (int c = 0; c < COLS; c++) {
           board[r][c] = copyBoard[r][c];
       }
   }
   
   currentPlayer = color;
   
   return (colorNum - otherNum);
}
//Desc: Displays the best move based on the row and col value for the current player based on the difference
//Pre: calling row, col ,and greedy by refereences and color from isMoveVaild
//Post: Displays best total gain cordinate for current player 
void Reversi::bestMove(int& row, int& col, int& greedy, char color){
   
   greedy = -64;
   
   for (int i = 0; i < ROWS; i++) {
       for (int j = 0; j < COLS; j++) {
           if (isMoveValid(i, j, color)) {
               
               int result = resultOfMove(i, j, color);
               
               if (greedy < result) {
                   
                   row = i;
                   col = j;
                   greedy = result;
               }
           }
       }
   }
}
//Desc: creates 8X8 array for the board
//Pre: none
//Post: displays the board for the user
void Reversi::printBoard() {
    
   
    
    cout << "  0   1   2   3   4   5   6   7" << endl;
   
   cout << "---------------------------------" << endl;
  
   for (int i = 0; i < ROWS; i++) {
       
       cout << i << "| ";
       for (int j = 0; j < COLS; j++) {
           cout << board[i][j] << " | ";
       }
       
       cout << endl;
       cout << "---------------------------------" << endl;
   }
}
//Desc: Resets board to starting board
//Pre: game must have to be reply
//Post: creates new board
void Reversi::resetBoard() {
   
   for (int i = 0; i < ROWS; i++) {
       for (int j = 0; j < COLS; j++) {
           board[i][j] = ' ';
       }
   }
   currentPlayer = 'b';
   board[ROWS / 2 - 1][COLS / 2 - 1] = 'w';
   board[ROWS / 2 - 1][COLS / 2] = 'b';
   board[ROWS / 2][COLS / 2 - 1] = 'b';
   board[ROWS / 2][COLS / 2] = 'w';
}

//Desc: Creates the menu for the user 
//Pre: none
//Post: displays the menu for the user
void Reversi::displayMenu(){
    cout << "Menu:" << endl;
    cout << "  1) Place a disk" << endl;
    cout << "  2) See movement rules" << endl;
    cout << "  3) Display possible moves" << endl;
    cout << "  4) See best move" << endl;
    cout << "Select: ";
}

//Desc: displays the current players turn
//Pre: none
//Post: displays current player
void Reversi::displayTurn() {
   
   if (currentPlayer == 'b') {
       cout << "Player 1: Black" << endl;
   }
   else {
       cout << "Player 2: White" << endl;
   }
}
//Desc: Takes no parameters
//Pre: none
//Post: returns the current player
char Reversi::getcurrentPlayer() {
   return currentPlayer;
}
//Desc: switches color for the next player
//Pre: takes user input for row, col, and color is set to value
//Post: sets the color the next player
void Reversi::colorSwitch(int row, int col, char color) {
   
     bool Flip = false;
     
     for (int i = row - 1; i >= 0; i--) {
         if ((color == 'b' && board[i][col] == 'w') || (color == 'w' && board[i][col] == 'b')){
             Flip = true;
         }
         else if (Flip && board[i][col] == color) {
             
             for (int r = row - 1; r >= 0; r--) {
                 if (board[r][col] == color) {
                     break;
                 }
                 else {
                     board[r][col] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
     
     for (int i = row + 1; i < ROWS; i++) {
         if ((color == 'b' && board[i][col] == 'w') || (color == 'w' && board[i][col] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[i][col] == color) {
             
             for (int r = row + 1; r < ROWS; r++) {
                 if (board[r][col] == color) {
                     break;
                 }
                 else {
                     board[r][col] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
  
     for (int i = col - 1; i >= 0; i--) {
         if ((color == 'b' && board[row][i] == 'w') || (color == 'w' && board[row][i] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[row][i] == color) {
             
             for (int c = col - 1; c >= 0; c--) {
                 if (board[row][c] == color) {
                     break;
                 }
                 else {
                     board[row][c] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
          for (int i = col + 1; i < COLS; i++) {
         if ((color == 'b' && board[row][i] == 'w') || (color == 'w' && board[row][i] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[row][i] == color) {
             
             for (int c = col + 1; c < COLS; c++) {
                 if (board[row][c] == color) {
                     break;
                 }
                 else {
                     board[row][c] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
     
    for (int i = row - 1, j = col - 1; static_cast<void>(i >= 0), j >= 0; i--, j--) {
         if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[i][j] == color) {
             
             for (int r = row - 1, c = col - 1; static_cast<void>(r >= 0), c >= 0; r--, c--) {
                 if (board[r][c] == color) {
                     break;
                 }
                 else {
                     board[r][c] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
     
    for (int i = row - 1, j = col + 1; static_cast<void>(i >= 0), j < COLS; i--, j++) {
         if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[i][j] == color) {
             
             for (int r = row - 1, c = col + 1; static_cast<void>(r >= 0), c < COLS; r--, c++) {
                 if (board[r][c] == color) {
                     break;
                 }
                 else {
                     board[r][c] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
     
    for (int i = row + 1, j = col - 1; static_cast<void>(i < ROWS), j >= 0; i++, j--) {
         if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[i][j] == color) {
            
             for (int r = row + 1, c = col - 1; static_cast<void>(r < ROWS), c >= 0; r++, c--) {
                 if (board[r][c] == color) {
                     break;
                 }
                 else {
                     board[r][c] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
     
    for (int i = row + 1, j = col + 1; static_cast<void>(i < ROWS), j < COLS; i++, j++) {
         if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
             Flip = true;
         }
         else if (Flip && board[i][j] == color) {
            
             for (int r = row + 1, c = col + 1; static_cast<void>(r < ROWS), c < COLS; r++, c++) {
                 if (board[r][c] == color) {
                     break;
                 }
                 else {
                     board[r][c] = color;
                 }
             }
             Flip = false;
             break;
         }
         else {
             Flip = false;
             break;
         }
     }
  }
//Desc: Checks move is valid for verical, horizonal,and diagonal
//Pre: takes in row, col, and color values from the user
//Post: returns true or false value for every direction
bool Reversi::isMoveValid(int row, int col, char color) {
  
   if (board[row][col] != ' ') {
       return false;
   }
   bool Flip = false;
   
       for (int i = row-1; i >= 0; i--) {
           if ((color == 'b' && board[i][col] == 'w') || (color == 'w' && board[i][col] == 'b')) {
               Flip = true;
           }
           else {
               
               if (Flip && ((color == 'b' && board[i][col] == 'b') || (color == 'w' && board[i][col] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
      
       for (int i = row + 1; i < ROWS; i++) {
           if ((color == 'b' && board[i][col] == 'w') || (color == 'w' && board[i][col] == 'b')) {
               Flip = true;
           }
           else {
               
               if (Flip && ((color == 'b' && board[i][col] == 'b') || (color == 'w' && board[i][col] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
  
   
       for (int i = col - 1; i >= 0; i--) {
           if ((color == 'b' && board[row][i] == 'w') || (color == 'w' && board[row][i] == 'b')) {
               Flip = true;
           }
           else {
               
               if (Flip && ((color == 'b' && board[row][i] == 'b') || (color == 'w' && board[row][i] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
       
       for (int i = col + 1; i < COLS; i++) {
           if ((color == 'b' && board[row][i] == 'w') || (color == 'w' && board[row][i] == 'b')) {
               Flip = true;
           }
           else {
               
               if (Flip && ((color == 'b' && board[row][i] == 'b') || (color == 'w' && board[row][i] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
  
    for (int i = row - 1, j = col - 1; static_cast<void>(i >= 0), j >= 0; i--,j--) {
           if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
               Flip = true;
           }
           else {
              
               if (Flip && ((color == 'b' && board[i][j] == 'b') || (color == 'w' && board[i][j] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
      
    for (int i = row - 1, j = col + 1; static_cast<void>(i >= 0), j < COLS; i--, j++) {
           if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
               Flip = true;
           }
           else {
              
               if (Flip && ((color == 'b' && board[i][j] == 'b') || (color == 'w' && board[i][j] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
      
    for (int i = row + 1, j = col - 1; static_cast<void>(i < ROWS), j >= 0; i++, j--) {
           if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
               Flip = true;
           }
           else {
               
               if (Flip && ((color == 'b' && board[i][j] == 'b') || (color == 'w' && board[i][j] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
      
    for (int i = row + 1, j = col + 1; static_cast<void>(i < ROWS), j < COLS; i++, j++) {
           if ((color == 'b' && board[i][j] == 'w') || (color == 'w' && board[i][j] == 'b')) {
               Flip = true;
           }
           else {
               
               if (Flip && ((color == 'b' && board[i][j] == 'b') || (color == 'w' && board[i][j] == 'w'))) {
                       return true;
                   }
               else {
                   Flip = false;
                   break;
               }
           }
       }
   return false;
}

//Desc: Checks if move is valid based off the isMoveValid function by searching the board by rows and cols
//Pre: takes in color form isMoveValid function
//Post: returns a true or false value
bool Reversi::MoveisValid(char color) {
   for (int r = 0; r < ROWS; r++) {
       for (int c = 0; c < COLS; c++) {
           if (isMoveValid(r, c, color)) {
               return true;
           }
       }
   }
   return false;
}
//Desc: Puts on x on a possible moves
//Pre: Gets color from the isMoveValid function
//Post: Places a x at the row and col position
void Reversi::getPossibleMoves(char color) {
  
   for (int r = 0; r < ROWS; r++) {
       for (int c = 0; c < COLS; c++) {
           if (isMoveValid(r, c, color)) {
               board[r][c] = 'x';
           }
       }
   }
}
//Desc: searches 2D array for an x at the r and c value if it doesnt gives r and c a blank space
//Pre: none
//Post: moves are deleted
void Reversi::deletePossibleMoves() {
   for (int r = 0; r < ROWS; r++) {
       for (int c = 0; c < COLS; c++) {
           if (board[r][c] == 'x') {
               board[r][c] = ' ';
           }
       }
   }
}
 
//Desc: ends game when no moves can be played
//Pre:none
//Post: game ends
bool Reversi::gameOver() {
   
   return !(MoveisValid(currentPlayer));
}
//Desc: displays the winner
//Pre: games is over
//Post: displays a certain message if black wins,white wins, or its a tie
void Reversi::printResults() {
  
   int white = count('w');
   int black = count('b');
   if (white < black) {
       
        //cout << "Congrats! Player 2: White has won the game! (" << white << " - " << black << ")" << endl;
        cout << "Congrats! Player 1: Black has won the game! ( " << black << " - " << white << ")" << endl;
   }
   else if (white > black) {
       cout << "Congrats! Player 2: White has won the game! (" << white << " - " << black << ")" << endl;
      // cout << "Congrats! Player 1: Black has won the game! ( " << black << " - " << white << ")" << endl;
   }
   else {
       cout << "The Game is a Tie! " << white << " - " << black << endl;
   }
}


