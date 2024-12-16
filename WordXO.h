#ifndef UNTITLED23_WORDXO_H
#define UNTITLED23_WORDXO_H


#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>


using namespace std;

template <typename T>
class WordXO_Board : public Board<T> {
public:
    WordXO_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class WordXO_Player : public Player<T> {
public:
    WordXO_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class WordXO_Random_Player : public RandomPlayer<T> {
public:
    WordXO_Random_Player(T symbol);
    void getmove(int& x, int& y);
};


// Constructor for WordXO_Board
template <typename T>
WordXO_Board<T>::WordXO_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' '; // Initialize with space
        }
    }
    this->n_moves = 0;
}

// Update the board
template <typename T>
bool WordXO_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->n_moves++;
        this->board[x][y] = symbol;
        return true;
    }
    return false; // Invalid move
}

// Display the board and the pieces on it
template <typename T>
void WordXO_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Check for a winner
template <typename T>
bool WordXO_Board<T>::is_win() {
    unordered_set<string> fileContent; // Unordered set to store file content
    ifstream inputFile(R"(C:\Users\Anas Emad\Downloads\dic.txt)");

    // Reading words from the file and storing them in the unordered set
    string line;
    while (getline(inputFile, line)) {
        fileContent.insert(line); // Insert each word into the set
    }
    inputFile.close();

    // Step 1: Check rows for a winning word
    for (int i = 0; i < this->rows; i++) {
        string rowWord;
        for (int j = 0; j < this->columns; j++) {
            rowWord += this->board[i][j];
        }
        if (fileContent.count(rowWord)) {
            return true;
        }
    }

    // Step 2: Check columns for a winning word
    for (int j = 0; j < this->columns; j++) {
        string columnWord;
        for (int i = 0; i < this->rows; i++) {
            columnWord += this->board[i][j];
        }
        if (fileContent.count(columnWord)) {
            return true;
        }
    }

    // Step 3: Check diagonals for a winning word
    string diag1Word, diag2Word;
    for (int i = 0; i < this->rows; i++) {
        diag1Word += this->board[i][i];
        diag2Word += this->board[i][this->columns - i - 1];
    }

    if (fileContent.count(diag1Word)) {
        return true;
    }

    if (fileContent.count(diag2Word)) {
        return true;
    }

    return false; // No winning word found
}


// Check for a draw
template <typename T>
bool WordXO_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

// Check if the game is over
template <typename T>
bool WordXO_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for WordXO_Player
template <typename T>
WordXO_Player<T>::WordXO_Player(string name, T symbol) : Player<T>(name, symbol) {}

// Get move from player
template <typename T>
void WordXO_Player<T>::getmove(int& x, int& y) {
    cout << "\nEnter your move (x, y) separated by space : ";
    cin >> x >> y;
    cout << "Enter the input as text: ";
    cin >> this->symbol;
    this->symbol = std::toupper(this->symbol);
}


// Constructor for WordXO_Random_Player
template <typename T>
WordXO_Random_Player<T>::WordXO_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
}

template <typename T>
void WordXO_Random_Player<T>::getmove(int& x, int& y) {
    vector<char> alphabets;
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
            alphabets.push_back(letter);

    }

    srand(time(0));
    int randomIndex = rand() % alphabets.size();
    char selectedLetter = alphabets[randomIndex];
    this->symbol = selectedLetter;

    x = rand() % this->dimension;
    y = rand() % this->dimension;

    alphabets.clear();

    }


#endif // UNTITLED23_WORDXO_H














