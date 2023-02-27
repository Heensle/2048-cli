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

bool checkLoss (int boardValues[4][4]){
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
  } else {
    cout << "\u001b[0m";
  }
}

void printBoard(int boardValues[4][4]){
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
  return 'x';
}

queue <int> combine (queue <int> uncombined){
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

  addRand (boardValues);
  addRand (boardValues);

  while (true){
    
    if (changed){
      addRand (boardValues);
    }
    
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++){
        prevValues[i][j] = boardValues[i][j];
      }
    }
    
    changed = false;
    
    while (true){
      
      if (checkVictory(boardValues, won)){
        status = "Winner";
      }
      
      printHeader(moves, status);
      printBoard(boardValues);
      
      if (checkVictory(boardValues, won)){
        cout << endl << endl << "            " << "YOU WIN!" << endl;
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
      
      cout << "\033[H\033[2J\033[3J";
      cout << "Not a valid input. Try again." << endl;
      
    }
    
    boardShift(boardValues, move);
    cout << "\033[H\033[2J\033[3J";
    
    for (int i = 0; i < 4; i++){
      for (int j = 0; j < 4; j++){
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