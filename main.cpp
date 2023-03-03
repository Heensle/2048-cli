#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <ctime>
#include <queue>
#include <array>
#include <stdlib.h>
using namespace std;

void ruleBook(){
  char input;
  while(true){
    cout << "\033[H\033[2J\033[3J";
    cout << "''2048 is a single-player sliding tile puzzle video game written by Italian web developer Gabriele Cirulli and published on GitHub. The objective of the game is to slide numbered tiles on a grid to combine them to create a tile with the number 2048; however, one can continue to play the game after reaching the goal, creating tiles with larger numbers.''" << endl << "   Source: Wikipedia" << endl << endl << "Use 'w', 'a', 's', and 'd' inputs to slide tiles in those directions. Press enter after each character to send your input to the computer. Any other inputs will be rejected." << endl << endl << "You can use '?' to see the rules at any time." << endl << endl << "Press 'x' to continue:" << endl;
    cin >> input;
    if (input == 'x'){
      break;
    }
    cout << "\033[H\033[2J\033[3J";
  }
}

bool checkLoss (int boardValues[4][4]){
  /* loss condition is:
        no more combinable spaces
      function immediately returns false if any 0s are present 
  */
  int copyBoardValues[6][6] = {};
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 5; j++){
      copyBoardValues[i][j] = boardValues [i - 1][j - 1];
    }
  }
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 5; j++){
      if (copyBoardValues[i][j] == copyBoardValues[i - 1][j] || 
        copyBoardValues[i][j] == copyBoardValues[i][j - 1] || 
        copyBoardValues[i][j] == copyBoardValues[i + 1][j] || 
        copyBoardValues[i][j] == copyBoardValues[i][j + 1]){
        return false;
      }
    }
  }
  return true;
}

bool checkVictory(int boardValues[4][4], bool won){
  /* win condition:
      2048 is present on the board
      (function will return false in the case that the game has already been won, to avoid unremovable distracting messages)
  */
  if (won){
    return false;
  }
  bool victory = false;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (boardValues[i][j] == 2048){
        victory = true;
      }
    }
  }
  return victory;
}

void clear(queue <int>& queueToBeCleared){
  while (!queueToBeCleared.empty()){
    queueToBeCleared.pop();
  }
}

void textBackColor (int num){
  /* sets unique and background colors for all numbers up to 4 digits */
  if (num == 2){
    cout << "\u001b[7m";
  } else if (num == 4){
    cout << "\u001b[30m" << "\u001b[48;5;223m";
  } else if (num == 8){
    cout << "\u001b[48;5;214m" << "\u001b[37m";
  } else if (num == 16){
    cout << "\u001b[48;5;208m" << "\u001b[37m";
  } else if (num == 32){
    cout << "\u001b[48;5;202m" << "\u001b[37m";
  } else if (num == 64){
    cout << "\u001b[48;5;196m" << "\u001b[37m";
  } else if (num == 128){
    cout << "\u001b[48;5;229m" << "\u001b[37m";
  } else if (num == 256){
    cout << "\u001b[48;5;228m" << "\u001b[37m";
  } else if (num == 512){
    cout << "\u001b[48;5;222m" << "\u001b[37m";
  } else if (num == 1024){
    cout << "\u001b[48;5;221m" << "\u001b[37m";
  } else if (num == 2048){
    cout << "\u001b[48;5;220m" << "\u001b[37m";
  } else if (num == 4096){
    cout << "\u001b[48;5;220m" << "\u001b[37m";
  } else if (num == 8192){
    cout << "\u001b[48;5;220m" << "\u001b[37m";
  } else {
    cout << "\u001b[0m";
  }
}

void printBoard(int boardValues[4][4]){
  /* responsible for board frame output (tabletop chars) and current state of board (boardValues[x][x]) 
    "\u001b[0m" is the reset ANSI code, is outputted periodically
  */
  cout << "┌";
  for (int i = 1; i < 32; i++){
    if (i % 8 == 0){
      cout << "┬";
    } else {
      cout << "\u001b[0m" << "─";
    }
  }
  cout << "┐";
  cout << endl;
  for (int i = 0; i < 4; i++){
    cout << "│";
    for (int j = 0; j < 4; j++){
      textBackColor(boardValues[i][j]);
      cout << "       " << "\u001b[0m" << "│";
    }
    cout << endl;
    cout << "│";
    for (int j = 0; j < 4; j++){
      if (boardValues[i][j] == 0){
        cout << "       " << "│";
      } else {
      textBackColor(boardValues[i][j]);
        if (boardValues[i][j] / 10 > 100){
          cout << " " << boardValues[i][j] << "  " << "\u001b[0m" << "│";
        } else if (boardValues[i][j] / 10 > 10){
          cout << "  " << boardValues[i][j] << "  " << "\u001b[0m" << "│";
        } else if (boardValues[i][j] / 10 >= 1){
          cout << "  " << boardValues[i][j] << "   " << "\u001b[0m" << "│";
        } else{
          cout << "   " << boardValues[i][j] << "   " << "\u001b[0m" << "│";
        }
      }
      
    }
    cout << endl << "│";
    for (int j = 0; j < 4; j++){
      textBackColor(boardValues[i][j]);
      cout << "       " << "\u001b[0m" << "│";
    }
    if (i != 3){
      cout << endl << "├";
    } else {
      cout << endl << "└";
    }
    for (int j = 1; j < 32; j++){
      if (j % 8 == 0){
        if (i == 3){
          cout << "┴";
        } else {
          cout << "┼";
        }
      } else {
        cout << "─";
      }
    }
    if (i == 3){
      cout << "┘" << endl;
    } else {
      cout << "┤" << endl;
    }
  }
}

char playerInput (){
  char move;
  cin >> move;
  if (move == 'w' || move == 'a' || move == 's' || move == 'd'){
    return move;
  }
  if (move == '?'){
    ruleBook();
    return '?';
  }
  return 'x';
}

queue <int> combine (queue <int> uncombined){
  /* combines queue values according to 2048 standard of equivalent combination
  */
  queue <int> combined;
  while (uncombined.size() > 1){
    int comparison = uncombined.front();
    uncombined.pop();
    if (uncombined.front() == comparison){
      combined.push(comparison + uncombined.front());
      uncombined.pop();
    } else {
      combined.push(comparison);
    }
  }
  
  if (uncombined.size() == 1){
    combined.push(uncombined.front());
    uncombined.pop();
  }
  
  return combined;
}

void boardShift (int (&boardValues)[4][4], char move){
  /* feeds queues to combined() in direction indicated by input */
  queue <int> uncombined;
  if (move == 'w'){
    for (int i = 0; i < 4; i++){
      clear(uncombined);
      for (int j = 0; j < 4; j++){
        if (boardValues[j][i] != 0){
          uncombined.push(boardValues[j][i]);
        }
      }
      queue <int> combined = combine(uncombined);
      for (int j = 0; j < 4; j++){
        if (combined.size() > 0){
          boardValues[j][i] = combined.front();
          combined.pop();
        } else {
          boardValues[j][i] = 0;
        }
      }
    }
  } else if (move == 'a'){
    for (int i = 0; i < 4; i++){
      clear(uncombined);
      for (int j = 0; j < 4; j++){
        if (boardValues[i][j] != 0){
          uncombined.push(boardValues[i][j]);
        }
      }
      queue <int> combined = combine(uncombined);
      for (int j = 0; j < 4; j++){
        if (combined.size() > 0){
          boardValues[i][j] = combined.front();
          combined.pop();
        } else {
          boardValues[i][j] = 0;
        }
      }
    }
  } else if (move == 's'){
    for (int i = 3; i >= 0; i--){
      clear(uncombined);
      for (int j = 3; j >= 0; j--){
        if (boardValues[j][i] != 0){
          uncombined.push(boardValues[j][i]);
        }
      }
      queue <int> combined = combine(uncombined);
      for (int j = 3; j >= 0; j--){
        if (combined.size() > 0){
          boardValues[j][i] = combined.front();
          combined.pop();
        } else {
          boardValues[j][i] = 0;
        }
      }
    }
  } else if (move == 'd'){
    for (int i = 0; i < 4; i++){
      clear(uncombined);
      for (int j = 3; j >= 0; j--){
        if (boardValues[i][j] != 0){
          uncombined.push(boardValues[i][j]);
        }
      }
      queue <int> combined = combine(uncombined);
      for (int j = 3; j >= 0; j--){
        if (combined.size() > 0){
          boardValues[i][j] = combined.front();
          combined.pop();
        } else {
          boardValues[i][j] = 0;
        }
      }
    }
  } 
}  

void addRand (int (&boardValues)[4][4]){
  /* generates 2 / 4 in random empty space */
  int numAdd;
  if (rand() % 10 + 1 > 1){
    numAdd = 2;
  } else {
    numAdd = 4;
  }
  vector <int> emptyI;
  vector <int> emptyJ;
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      if (boardValues[i][j] == 0){
        emptyI.push_back(i);
        emptyJ.push_back(j);
      }
    }
  }
  int randNum = rand() % emptyI.size();
  boardValues[emptyI.at(randNum)][emptyJ.at(randNum)] = numAdd;
}

void printHeader (int moves, string status){
  cout << "\u001b[48;5;17m" << "    " << "Moves: " << moves << "    " << "Status: " << status << "   " << endl << endl << endl;
}

int main() {

  srand ((unsigned) time(NULL));
  
  bool won = false;
  bool changed = false;
  int moves = 0;
  string status = "Loser";
  char move;

  int boardValues[4][4] = {};
  int prevValues[4][4];

  /* initial values to begin game */
  addRand (boardValues);
  addRand (boardValues);

  cout << "Press '?' for rules." << endl << endl;

  while (true){
    
    if (changed){
      /* no numbers will be added if no valid move was made */
      addRand (boardValues);
    }
    
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++){
        /* values stored for comparison */
        prevValues[i][j] = boardValues[i][j];
      }
    }
    
    changed = false;
    
    while (true){
      /* loop entered for invalid input barrier */
      
      if (checkVictory(boardValues, won)){
        status = "Winner";
      }
      
      printHeader(moves, status);
      printBoard(boardValues);
      
      if (checkVictory(boardValues, won)){
        cout << endl << endl << "            " << "YOU WIN!" << endl;
        /* prevents message from spamming terminal */
        won = true;
      }
      
      if (checkLoss(boardValues)){
        cout << endl << endl << "            " << "YOU LOSE" << endl;
        return 0;
      }
      
      move = playerInput();
      
      if (move == 'a' || move == 's' || move == 'd' || move == 'w'){
        break;
      }
    
      /* clear screen ANSI code */
      cout << "\033[H\033[2J\033[3J";
      if (move == 'x'){
        cout << "Not a valid input. Try again." << endl;
      }
    }
    
    boardShift(boardValues, move);
    cout << "\033[H\033[2J\033[3J";
    
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++){
        /* comparison for valid move indentification */
        if (prevValues[i][j] != boardValues[i][j]){
          changed = true;
        }
      }
    }
    
    if (changed){
      moves++;
    }
    
  }

  return 0;
}