#ifndef SUDOKU_HPP
#define SUDOKU_HPP
#include <vector>
#include <fstream>

class Sudoku{
    private:
    int board[81]; //values on the sudoku board
    std::vector< std::pair<int, int> > empty; //empty (zero value) spaces
    
    public:
        Sudoku(std::ifstream& filename);
        bool solveBoard();
        bool rowValid(int space);
        bool colValid(int space);
        bool boxValid(int space);
        void printBoard();
};

#endif