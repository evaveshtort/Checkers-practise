#ifndef CMAKESFMLPROJECT_CHECKERS_H
#define CMAKESFMLPROJECT_CHECKERS_H

#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>

class Board;

class Square{
    friend class Board;
private:
    bool is_busy;
    bool checker_is_white;
    bool checker_is_queen;
public:
    Square();
    void place_a_checker(bool, bool);
    void free_a_square();
};

class Board{
private:
    int number_of_whites;
    int number_of_blacks;
    bool moving_possibility_white;
    bool moving_possibility_black;
    Square squares[8][8];
public:
    Board();
    bool possible_move(int, int, int, int);
    bool move_a_checker(int, int, int, int);
    bool moving_possibility(bool);
    int the_end();
    bool is_busy(int, int);
    bool is_white(int, int);
    bool is_queen(int, int);
};
#endif
