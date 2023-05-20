#include "board.h"

Square::Square(){is_busy = false; checker_is_white = false; checker_is_queen = false;}

void Square::place_a_checker(bool is_white, bool is_queen) {
    is_busy = true;
    checker_is_white = is_white;
    checker_is_queen = is_queen;
}

void Square::free_a_square(){
    is_busy = false;
}