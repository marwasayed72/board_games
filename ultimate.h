
#ifndef GAMES_ULTIMATE_H
#define GAMES_ULTIMATE_H


#include "BoardGame_Classes.h"
using namespace std;


int turns=0;



template<typename T>
class ultimateBoard : public Board<T>{
private:
    char implicitBoard[3][3]= {{0, 0, 0},
                               {0, 0, 0},
                               {0, 0, 0}};
    bool checks[3][3]= {{false, false, false},
                        {false, false, false},
                        {false, false, false}};
    bool finished(bool check[3][3]);
public:
    ultimateBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


template<typename T>
class ultimatePlayer : public Player<T>{
public:
    ultimatePlayer(string name, T symbol);
    void getmove(int& x, int& y) ;
};


template<typename T>
class ultimatRandomPlayer : public RandomPlayer<T>{
public:
    ultimatRandomPlayer(T symbol, string name);
    void getmove(int& x, int& y);
};


/////////////////////////////Implemetation\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

template<typename T>
ultimateBoard<T> :: ultimateBoard(){
    this->rows = this->columns = 9;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}


template<typename T>
bool ultimateBoard<T>::finished(bool check[3][3]) {
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                if(!check[i][j]){
                    return false;
                }
            }
        }
        return true;
}


template<typename T>
void ultimateBoard<T> ::display_board() {
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
        cout << "\n-------------------------------------------------------------------------------------------";
    }
    cout << endl;
}


template<typename T>
bool ultimateBoard<T> ::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        if(x<3 && y<3){
            if(implicitBoard[0][0]!=0){
                return false;
            }
        }
        else if(2<y && y<6 && x<3){
            if(implicitBoard[0][1]!=0){
                return false;
            }
        }

        else if(5<y && y<9 && x<3){
            if(implicitBoard[0][2]!=0){
                return false;
            }
        }
        else if(y<3 && 2<x && x<6){
            if(implicitBoard[1][0]!=0){
                return false;
            }
        }
        else if(y<6 && 2<y && x<6 && x>2){
            if(implicitBoard[1][1]!=0){
                return false;
            }
        }
        else if(5<y && y<9 && x<6 && x>2){
            if(implicitBoard[1][2]!=0){
                return false;
            }
        }
        else if(x>5 && x<9 && y<3){
            if(implicitBoard[2][0]!=0){
                return false;
            }
        }
        else if(x>5 && x<9 && 2<y && y<6){
            if(implicitBoard[2][1]!=0){
                return false;
            }
        }
        else if(x>5 && x<9 && 5<y && y<9){
            if(implicitBoard[2][2]!=0){
                return false;
            }
        }
        this->n_moves++;
        turns= this->n_moves;
        this->board[x][y] = mark;
        return true;
    }
    return false;
}


template<typename T>
bool ultimateBoard<T> ::is_win() {

    for(int k=0; k<3; k++){
        for(int l=0; l<3; l++){
            implicitBoard[k][l]=0;
        }
    }
    for (int row=0; row<this->rows; row+=3) {
        for (int col = 0; col < this->columns; col += 3) {

            for (int i = 0; i < 3; i++) {
                if (this->board[i + row][col] == this->board[i + row][col + 1] &&
                     this->board[i + row][col + 1] == this->board[i + row][col + 2] &&
                     this->board[i + row][col] != 0) {
                    if (this->board[i+row][col] == 'O') {
                        implicitBoard[row / 3][col / 3] = 'O';
                    } else {
                        implicitBoard[row / 3][col / 3] = 'X';
                    }
                    checks[row / 3][col / 3]= true;
                }
                if((this->board[row][col + i] == this->board[row + 1][col + i] &&
                    this->board[row + 1][col + i] == this->board[row + 2][col + i] &&
                    this->board[row][col + i] != 0)){
                    if (this->board[row][col+i] == 'O') {
                        implicitBoard[row / 3][col / 3] = 'O';
                    } else {
                        implicitBoard[row / 3][col / 3] = 'X';
                    }
                    checks[row / 3][col / 3]= true;
                }
            }

            if ((this->board[row][col] == this->board[row + 1][col + 1] &&
                 this->board[row + 1][col + 1] == this->board[row + 2][col + 2] && this->board[row][col] != 0)) {
                if (this->board[row][col]=='O') {
                    implicitBoard[row / 3][col / 3] = 'O';
                } else {
                    implicitBoard[row / 3][col / 3] = 'X';
                }
                checks[row / 3][col / 3]= true;
            }
            if((this->board[row][col + 2] == this->board[row + 1][col + 1] &&
                this->board[row + 1][col + 1] == this->board[row + 2][col] && this->board[row][col + 2] != 0)){
                if (this->board[row][col+2]=='O') {
                    implicitBoard[row / 3][col / 3] = 'O';
                } else {
                    implicitBoard[row / 3][col / 3] = 'X';
                }
                checks[row / 3][col / 3]= true;
            }
            int filled_cells=0;
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    if(this->board[row+i][col+j] !=0){
                        filled_cells++;
                    }
                }
            }
            if(filled_cells == 9){
                checks[row / 3][col / 3]= true;
            }
        }
    }
    

    //check winner of the whole board
    for (int i = 0; i < 3; i++) {
        if ((implicitBoard[i][0] == implicitBoard[i][1] && implicitBoard[i][1] == implicitBoard[i][2] && implicitBoard[i][0] != 0) ||
            (implicitBoard[0][i] == implicitBoard[1][i] && implicitBoard[1][i] == implicitBoard[2][i]  && implicitBoard[0][i] != 0)){
            for(int k=0; k<3; k++){
                for(int l=0; l<3; l++){
                    implicitBoard[k][l]=0;
                }
            }
            turns=0;
            return true;
        }
    }

    if ((implicitBoard[0][0] == implicitBoard[1][1] && implicitBoard[1][1] == implicitBoard[2][2] && implicitBoard[0][0] != 0) ||
        (implicitBoard[0][2] == implicitBoard[1][1] && implicitBoard[1][1] == implicitBoard[2][0] && implicitBoard[0][2] != 0)) {
        for(int k=0; k<3; k++){
            for(int l=0; l<3; l++){
                implicitBoard[k][l]=0;
            }
        }
        turns=0;
        return true;
    }
    return false;
}


template<typename T>
bool ultimateBoard<T> ::is_draw() {
    if(finished(checks) && !is_win()){
        for(int k=0; k<3; k++){
            for(int l=0; l<3; l++){
                implicitBoard[k][l]=0;
            }
        }
        turns=0;
    }
    return (finished(checks) && !is_win());
}

template<typename T>
bool ultimateBoard<T> ::game_is_over() {
    return (is_win() || is_draw());
}


template<typename T>
ultimatePlayer<T> ::ultimatePlayer(string name, T symbol) : Player<T>(name, symbol){}

template<typename T>
void ultimatePlayer<T> ::getmove(int &x, int &y) {
    if(turns%2==0){
        cout<<"First player turn";
    }else{
        cout<<"Second player turn";
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: "<<endl;
    cin >> x >> y;
}


template<typename T>
ultimatRandomPlayer<T> ::ultimatRandomPlayer(T symbol, string name) : RandomPlayer<T>(symbol){
    this->dimension = 9;
    this->name = name;
    srand(static_cast<unsigned int>(time(0)));
}

template<typename T>
void ultimatRandomPlayer<T> ::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif
