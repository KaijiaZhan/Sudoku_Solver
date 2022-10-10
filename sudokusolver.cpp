#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "main.h"
#define N 9
#include <vector>
SudokuGame::SudokuGame(std::string filename){

    //reading the file contents and putting into a single string;
    std::ifstream ifs(filename);
    std::string array(std::istreambuf_iterator<char>(ifs), {});
    ifs.close();
    
    //split file contents into lines;
    int num_lines = std::count(array.begin(), array.end(), '\n') + 1;
    std::vector<std::string> lines(num_lines);
    std::istringstream iss(array);
    std::generate(lines.begin(), lines.end(), [&iss](){
        std::string str;
        std::getline(iss, str, '\n');
        return str;
    });
    
    //read csv as a vector or rows and columns;
    std::vector<std::vector<std::string>> arr_str;
    std::transform(lines.begin(), lines.end(), std::back_inserter(arr_str), [](const std::string& line){
        int num_columns = std::count (line.begin(), line.end(), ',') +1;
        std::vector<std::string> columns(num_columns);
        std::istringstream iss(line);
        std::generate(columns.begin(), columns.end(), [&iss](){
            std::string str;
            std::getline(iss,str,',');
            return str;
        });
        return columns;
    });
    std::transform(lines.begin(), lines.end(), std::back_inserter(arr), [](const std::string & line){
        int num_columns = std::count(line.begin(), line.end(), ',') + 1;
        std::vector<int> columns(num_columns);
        std::istringstream iss(line);
        std::generate(columns.begin(), columns.end(), [&iss](){
            std::string str;
            std::getline(iss,str, ',');
            return std::stoi(str);
        });
        return columns;
    });

}
const std::vector<std::vector<int>> & SudokuGame::grid()const{
    return arr;
}
void SudokuGame::print() const{
    for (int row = 0; row < 9; row++){
        for (int column = 0; column< 9; column++){
            if (column==3 || column ==6){
               std::cout << " | ";   
            }
            std::cout << arr[row][column]; 
        }
        if (row==2 || row==5){
            std::cout <<std::endl;
                for (int border = 0; border <= 14; border++){
                    std::cout << "-";
                }}
        std::cout << std::endl;
        
    }
}
int SudokuGame::size()const{
    int size;
    size = arr.size();
    return size;
}
int SudokuGame::value(int row, int column)const{
    return arr[row%9][column%9];
}
void SudokuGame::value(int row, int column, int num){
    arr[row%9][column%9] = num;
}

bool SudokuPlayer::Empty(int &row, int &column, SudokuGame & game)const{ //function to find empty spots in the sudoku grid
    for (row = 0; row < 9; row ++){
        for (column = 0; column < 9; column++){
            if (game.value(row, column)== 0){
                return true;
            }
        }
    }
    return false;
}
bool SudokuPlayer::Present_Row(int row, int num, SudokuGame & game)const{
    for (int column = 0; column < 9; column++){ //using column as our looping variable, we choose one row, and go through all of the column numbers in it
        if (game.value(row,column)==num){
            return true;
        }
    }
    return false;
}
bool SudokuPlayer::Present_Column(int column, int num, SudokuGame & game)const{
    for (int row = 0; row < 9; row++){ //using row as our looping variable, we choose one column, and go through all of the row numbers in it
        if (game.value(row,column)==num){
            return true;
        }
    }
    return false;
}
bool SudokuPlayer::Present_Box(int box_row, int box_column, int num, SudokuGame & game)const{//need to revise this function since it is confusing
    int r_int = 3 * (box_row/3);
    int c_int = 3 * (box_column/3);
    for (int row = 0; row < 3; row ++){
        for (int column = 0; column < 3; column++){
            if (game.value (r_int+row, c_int+column)==num){
                return true;
            }
        }
    }
    return false;
}
bool SudokuPlayer::solve(SudokuGame & game) const{//need to revise this function
    int row;
    int column;
    int num;
    if (!Empty(row, column, game)){ //means that a valid solution is found
        return true;
    }
    else{
        for ( num = 0; num <9; num++){
            if (!Present_Row(row, num+1, game) && !Present_Column(column, num+1, game) && !Present_Box(row, column, num+1,game)){
                game.value(row, column, num+1);
                if (solve(game)){
                    return true;
                }
                game.value(row, column, 0);
            }
            
        }
    }
    return false;
}

int main() {
  SudokuGame game("sudoku_game_1.csv");
  std::cout << "Puzzle" << std::endl;
  game.print();

  SudokuPlayer player;
  bool solved = player.solve(game);
  if (solved) {
      std::cout << "Solution found!" << std::endl;
      game.print();
  } else {
      std::cout << "No solution found." << std::endl;
  }
  return 0;
}