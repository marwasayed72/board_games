
#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"

vector<int>odd{1, 3, 5, 7, 9};
vector<int>even{2, 4, 6, 8};
int oddInd=0;
int evenInd=0;
int order=0;

template <typename T>
class X_O_Board:public Board<T> {
private:
    bool inVector(T symbol);

public:
    X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T>{
private:
    bool inVector(T symbol);
public:
    X_O_Random_Player (T symbol, string name);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;


template <typename T>
bool X_O_Board<T> :: inVector(T symbol){
    if(this -> n_moves %2 ==0){
        for(int i=0; i<odd.size(); i++){
            if(symbol == odd[i]){
                oddInd=i;
                return true;
            }
        }
        return false;
    }else{
        for(int i=0; i<even.size(); i++){
            if(symbol == even[i]){
                evenInd=i;
                return true;
            }
        }
        return false;
    }
}


// Constructor for X_O_Board
template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0) && (inVector(mark))) {
        if(this ->n_moves %2 == 0){
            odd.erase(odd.begin()+oddInd);
        }else{
            even.erase(even.begin()+evenInd);
        }
        this->n_moves++;
        order = this -> n_moves;
        this->board[x][y] = mark;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n|";
        for (int j = 0; j < this->columns; j++) {
            if(this->board[i][j]==0){
                cout << "  (" << i << "," << j << ")  |";
            }
            else if(this->board[i][j]!=0){
                cout << "    " << this->board[i][j] << "    |";
            }
        }
        cout << "\n-------------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool X_O_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2]==15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] ==15 && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0)) {
            odd={1, 3, 5, 7, 9};
            even={2, 4, 6, 8};
            oddInd=0;
            evenInd=0;
            order=0;
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2]==15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0]==15 && this->board[0][2] != 0 && this->board[2][0] != 0 && this->board[1][1] != 0)) {
        odd={1, 3, 5, 7, 9};
        even={2, 4, 6, 8};
        oddInd=0;
        evenInd=0;
        order=0;
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool X_O_Board<T>::is_draw() {
    if(this->n_moves == 9 && !is_win()){
        odd={1, 3, 5, 7, 9};
        even={2, 4, 6, 8};
        oddInd=0;
        evenInd=0;
        order=0;
    }
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    if(order%2==0){
        cout<<"First player turn";
    }else{
        cout<<"Second player turn";
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: "<<endl;
    cin >> x >> y;
    cout<<"Please, enter the symbol from: ";
    if(order %2 == 0){
        for(int i: odd){
            cout<< i << ' ';
        }
    }else{
        for(int i: even){
            cout<< i << ' ';
        }
    }
    cout<<endl;
    int s;
    cin>>s;
    this->symbol=s;
}

// Constructor for X_O_Random_Player
template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol, string name) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
bool X_O_Random_Player<T> :: inVector(T symbol){
    if(order %2 ==0){
        for(int i=0; i<odd.size(); i++){
            if(symbol == odd[i]){
                oddInd=i;
                return true;
            }
        }
        return false;
    }else{
        for(int i=0; i<even.size(); i++){
            if(symbol == even[i]){
                evenInd=i;
                return true;
            }
        }
        return false;
    }
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    do{
        this->symbol = rand() % 10;
    }
    while(this->symbol == 0 || !inVector(this ->symbol));
}







#endif //_3X3X_O_H

