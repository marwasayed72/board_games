# board_games
#ifndef X_OGAME_H
#define X_OGAME_H

#include "BoardGame_Classes.h"

// Board class
template <typename T>
class X_Ogame_board : public Board<T> {
public:
    X_Ogame_board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

// Player class
template <typename T>
class X_Ogame_player : public Player<T> {
public:
    X_Ogame_player(string name, T symbol);
    void getmove(int& x, int& y);
};

// Random player class
template <typename T>
class X_Ogame_random_player : public RandomPlayer<T> {
public:
    X_Ogame_random_player(T symbol);
    void getmove(int& x, int& y);
};

// ----------------- Implementation ----------------------

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

// Constructor of board
template <typename T>
X_Ogame_board<T>::X_Ogame_board() {
    this->rows = this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Update board function
template <typename T>
bool X_Ogame_board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) &&(this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

// Display the board
template <typename T>
void X_Ogame_board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n------------------------------------------------";
    }
    cout << endl;
}

// Logic of the game
template <typename T>
bool X_Ogame_board<T>::is_win() {
    // Check for columns and rows
    int arr[3] = {0, 1, 2};
    for (int i = 0; i < this->rows; i++) {
        for (int n : arr) {
            if ((this->board[i][n] == this->board[i][n + 1] &&
                 this->board[i][n + 1] == this->board[i][n + 2] &&
                 this->board[i][n] != 0) ||
                (this->board[n][i] == this->board[n + 1][i] &&
                 this->board[n + 1][i] == this->board[n + 2][i] &&
                 this->board[n][i] != 0)) {
                return true;
            }
        }
    }
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            int x = i, y = j;
            while (x + 2 < 5 && y + 2 < 5) {
                if (this->board[x][y] == this->board[x + 1][y + 1] &&
                    this->board[x + 1][y + 1] == this->board[x + 2][y + 2] &&
                    this->board[x][y] != 0) {
                    return true;
                }
                x++;
                y++;
            }
        }
    }
    for (int i = 0; i <= 2; i++) {
        for (int j = 2; j < 5; j++) {
            int x = i, y = j;
            while (x + 2 < 5 && y - 2 >= 0) {
                if (this->board[x][y] == this->board[x + 1][y - 1] &&
                    this->board[x + 1][y - 1] == this->board[x + 2][y - 2] &&
                    this->board[x][y] != 0) {
                    return true;
                }
                x++; y--;
            }
        }
    }
    return false;
}

template <typename T>
bool X_Ogame_board<T>::is_draw() {
    return (this->n_moves == 24 && !is_win());
}

template <typename T>
bool X_Ogame_board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Player Constructor
template <typename T>
X_Ogame_player<T>::X_Ogame_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_Ogame_player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for Random Player
template <typename T>
X_Ogame_random_player<T>::X_Ogame_random_player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_Ogame_random_player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 4
    y = rand() % this->dimension;
}

#endif // X_OGAME_H
