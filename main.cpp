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

bool checkVictory(int boardValues[4][4]){
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
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 4; j++){
      textBackColor(boardValues[i][j]);
      cout << "       " << "\u001b[0m" << "|";
    }
    cout << endl;
    for (int j = 0; j < 4; j++){
      if (boardValues[i][j] == 0){
        cout << setw(8) << "|";
      } else {
      textBackColor(boardValues[i][j]);
        if (boardValues[i][j] / 10 > 100){
          cout << " " << boardValues[i][j] << "  " << "\u001b[0m" << "|";
        } else if (boardValues[i][j] / 10 > 10){
          cout << "  " << boardValues[i][j] << "  " << "\u001b[0m" << "|";
        } else if (boardValues[i][j] / 10 >= 1){
          cout << "  " << boardValues[i][j] << "   " << "\u001b[0m" << "|";
        } else{
          cout << "   " << boardValues[i][j] << "   " << "\u001b[0m" << "|";
        }
      }
    }
    cout << endl;
    for (int j = 0; j < 4; j++){
      textBackColor(boardValues[i][j]);
      cout << "       " << "\u001b[0m" << "|";
    }
    cout << endl;
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
  cout << "\u001b[48;5;17m" << "    " << "Moves: " << moves << "    " << "Status: " << status << endl << endl << endl;
}


int main() {

  int moves = 0;
  string status = "Loser";

  srand ((unsigned) time(NULL));

  int boardValues[4][4] = {};
  char move;

  addRand (boardValues);

  while (true){
    addRand (boardValues);
    while (true){

      if (checkVictory(boardValues)){
      status = "Winner";
    }
      printHeader(moves, status);
      printBoard(boardValues);
      if (checkVictory(boardValues)){
        cout << endl << endl << "            " << "YOU WIN!" << endl;
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
    moves++;
  }

  return 0;
}