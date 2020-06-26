#include "Reversi.h"
#include <iostream>
#include <iomanip>


using namespace std;

//Desc: Prints an error message and asks the user to enter a another value id they enter a charater for options in the menu
//Pre: none
//Post: User cant enter a charater for options
void userInputValidation(int& value)

{
while ( !(cin) )
{
cout << "Invaild option, Please enter one of the menu options: " << endl;
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cin >> value;
}

}

//Desc: Calls all funtions to make the game run
//Pre: none
//Post: Game is played
int main() {
  
   
    
   Reversi rev;
    int row;
    int col;
    char game;
    int greedy = 0;
    int option=0;
    row = 0;
    col = 0;
    
   while (true) {
       
       if (rev.gameOver()) {
       
       rev.printBoard();
       
       rev.printResults();
       cout << endl;
       
       cout << "Play again? (y/n): ";
       
       
       cin >> game;
       cout << endl;
      // game = towlower(game);
       if (game == 'y') {
           rev.resetBoard();
       }
       else {
           cout << "Thank you for playing!" << endl;
           break;
       }
       }
    
       rev.displayTurn();
       rev.printBoard();
       
       do {
           
           cout << endl;
           rev.displayMenu();
           
           cin >> option;
           userInputValidation(option);
           cout << endl;
          
           
           switch (option){
               
            case 1: {
              
               cout << "State the row (0-7) and col (0-7) of the square where you want to place a disk: ";
               cin >> row >> col;
               
                
           
                
                if (rev.isMoveValid(row, col, rev.getcurrentPlayer())) {
                   
                    rev.setDisk(row, col, rev.getcurrentPlayer());
                   cout << endl;
                    rev.displayTurn();
                   rev.printBoard();
                   break;
               }
               else {
                   cout << "Invalid move, try again" << endl;
               }
           }
                   break;
                   
            case 2: {
               
               cout << "Movement Rules for Reversi 'Othello'" << endl;
               cout << "1) It creates a straight line (horizontally, vertically, or diagonally) between the newly placed disk and another of the player's disks." << endl;
               cout << "2) There must be one or more of the opponent's disks between the current player's disks. [A disk must get 'flipped'.]" << endl;
                rev.displayTurn();
           }
                   break;
                   
            case 3: {
               
               rev.getPossibleMoves(rev.getcurrentPlayer());
              
               rev.printBoard();
               
               rev.deletePossibleMoves();
                cout << endl;
                rev.displayTurn();
                
           }
                   break;
               
            case 4: {
                rev.displayTurn();
               rev.bestMove(row, col, greedy, rev.getcurrentPlayer());
               
               cout << "Your best move is: " << row << ", " << col << " and will result in a ";
               if (greedy > 0) {
                   cout << "+";
               }
               cout << greedy << " score differential" << endl;
                   break;
           }
                 
               default:
               {
                   cout <<" Invalid, try again";
                   cin >> option;
                   
               }
                   
                   
           }
           
                   
       } while (option !=4);
    
}

}

