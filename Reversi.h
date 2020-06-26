#pragma once
#include <iostream>

using namespace std;

class Reversi {
private:
   const static int ROWS = 8;
   const static int COLS = 8;
   char board[ROWS][COLS];

public:
   Reversi();
   int count(char color);
   void setDisk(int row, int col, char color);
   int resultOfMove(int row, int col, char color);
   void bestMove(int& row, int& col, int& fliped, char color);
   void printBoard();
   void resetBoard();
   void displayMenu();
   void displayTurn();
   void colorSwitch(int row, int col, char color);
   bool isMoveValid(int row, int col, char color);
   char getcurrentPlayer();
   char currentPlayer;
   bool MoveisValid(char color);
   void getPossibleMoves(char color);
   void deletePossibleMoves();
   bool gameOver();
   void printResults();

};

