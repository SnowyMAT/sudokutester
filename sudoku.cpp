#include <iostream>
#include <fstream>
#include <vector>
#include "sudoku.hpp"

//Open a text file representing an unsolved sudoku
//board and prints out the completed board if possible
//Note that the text file must have 81 numbers (0-9)
//with 0 to represent empty spaces

int main(int argc, char* argv[]){
    std::ifstream tbr;
    tbr.open(argv[1]);
    if(tbr.fail()){
        std::cerr << "Failed to open file." << std::endl;
        exit(1);
    }
    Sudoku test(tbr);
    tbr.close();
    std::cout << "Unsolved: " << std::endl;
    test.printBoard();
    bool result = test.solveBoard();
    if(result){
        std::cout << "Solved: " << std::endl;
        test.printBoard();
    }
    else{
        std::cout << "Board cannot be solved." << std::endl;
    }
    return 0;
}

Sudoku::Sudoku(std::ifstream& filename){
    int temp;
    int count = 0;
    while(filename >> temp){
        if(temp < 0 || temp > 9){
            break;
        }
        board[count] = temp;
        if(temp == 0){
            empty.push_back({count, 0});
        }
        count++;
    }
    if(count != 81){
        std::cerr << "Invalid board." << std::endl;
    }
}

bool Sudoku::solveBoard(){
    //i iterates over vector
    //j iterates possible sudoku values for a space
    for(int i = 0; i < empty.size(); i++){
        for(int j = empty[i].second + 1; j <= 10; j++){
            if(j == 10){
                board[empty[i].first] = 0;
                empty[i].second = 0;
                i--;
                empty[i].second = board[empty[i].first];
                i--;
                break;
            }
            board[empty[i].first] = j;
            if(boxValid(empty[i].first) && rowValid(empty[i].first) && colValid(empty[i].first)){
                break;
            }
        }
        if(i < -1){
            return false;
        }
    }
    return true;
}

bool Sudoku::rowValid(int space){
    int row = space / 9;
    for(int i = 0; i <= 8; i++){
        if(i == space % 9){
            i++;
        }
        if(i > 8){
            break;
        }
        if(board[i + row * 9] == board[space]){
            return false;
        }
    }
    return true;
}

bool Sudoku::colValid(int space){
    int col = space % 9;
    int row = space / 9;
    for(int i = 0; i <= 8; i++){
        if(i == row){
            i++;
        }
        if(i > 8){
            break;
        }
        if(board[col + i * 9] == board[space]){
            return false;
        }
    }
    return true;
}

bool Sudoku::boxValid(int space){
    int col = space % 9;
    int row = space / 9;
    int colSec = col / 3;
    int rowSec = row / 3;
    int index = rowSec * 27 + colSec * 3;
    for(int i = 0; i <= 2; i++){
        for(int j = 0; j <= 2; j++){
            if(index + i * 9 + j == space){
                j++;
            }
            if(j > 2){
                break;
            }
            if(board[index + i * 9 + j] == board[space]){
                return false;
            }
        }
    }
    return true;
}

void Sudoku::printBoard(){
    int count = 0;
    for(int i = 0; i < 81; i++){
        std::cout << board[i] << " ";
        count++;
        if(count == 9){
            std::cout << std::endl;
            count = 0;
        }
    }
}