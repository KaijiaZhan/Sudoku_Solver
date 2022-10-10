#pragma once
#include <string>
#include <tuple>
#include <vector>
class SudokuGame {
 private:
 std::vector<std::vector<int>> arr;
 
 public:
  SudokuGame() = default;
  SudokuGame(std::string filename);
  const std::vector<std::vector<int>>& grid() const;
  void print() const;
  int size() const;
  int value(int row, int column) const;
  void value(int row, int column, int newValue);
  
};

class SudokuPlayer {
 private: 
 //std::vector<std::vector<int>> arr;
 //declare the bool methods
 bool Empty(int &row, int &column, SudokuGame & game)const;
 bool Present_Row(int row, int num, SudokuGame & game)const;
 bool Present_Column(int column, int num, SudokuGame & game)const;
 bool Present_Box(int box_row, int box_column, int num, SudokuGame & game)const;
 public:
  SudokuPlayer() = default;
  bool solve(SudokuGame& game) const;
};