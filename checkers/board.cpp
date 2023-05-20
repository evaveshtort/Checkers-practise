#include "board.h"

Board::Board(){
    number_of_blacks = 12;
    number_of_whites = 12;
    moving_possibility_black = true;
    moving_possibility_white = true;
    for(int i = 0; i<=6; i+=2){
        squares[i][7].place_a_checker(true, false);
        squares[i+1][6].place_a_checker(true, false);
        squares[i][5].place_a_checker(true, false);
        squares[i+1][2].place_a_checker(false, false);
        squares[i][1].place_a_checker(false, false);
        squares[i+1][0].place_a_checker(false, false);
    }
}

bool Board::possible_move(int x1, int y1, int x2, int y2){
    if(the_end() != 0) return false;
    if(x1 < 0 || x1 > 7 || x2 < 0 || x2 > 7) return false;
    if(y1 < 0 || y1 > 7 || y2 < 0 || y2 > 7) return false;
    if (squares[x2][y2].is_busy || !squares[x1][y1].is_busy) return false;

    bool moving_is_white = squares[x1][y1].checker_is_white;
    bool moving_is_queen = squares[x1][y1].checker_is_queen;

    if (abs(x2 - x1) != abs(y2 - y1)) return false;
    if (!moving_is_queen) {
        if (moving_is_white) {
            if (abs(x2 - x1) == 2 && squares[(x1 + x2) / 2][(y1 + y2) / 2].is_busy &&
                !squares[(x1 + x2) / 2][(y1 + y2) / 2].checker_is_white) return true;
            if (y2 - y1 > 0) return false;
        }
        else {
            if (abs(x2 - x1) == 2 && squares[(x1 + x2) / 2][(y1 + y2) / 2].is_busy &&
                squares[(x1 + x2) / 2][(y1 + y2) / 2].checker_is_white) return true;
            if (y2 - y1 < 0) return false;
        }
        if (abs(x2 - x1) == 1) return true;
        return false;
    }
    else{
        int i = (x2 - x1)/abs(x2 - x1), j = (y2 - y1)/abs(y2 - y1), x = x1 + i, y = y1 + j;
        while(x!=x2){
            if(squares[x][y].is_busy && squares[x][y].checker_is_white == moving_is_white) return false;
            x += i;
            y += j;
        }
    }
    return true;
}

bool Board::move_a_checker(int x1, int y1, int x2, int y2){
    if(possible_move(x1, y1, x2, y2)){
        std::cout << "possible";
        squares[x2][y2].place_a_checker(squares[x1][y1].checker_is_white, squares[x1][y1].checker_is_queen);
        squares[x1][y1].free_a_square();

        int i = (x2 - x1)/abs(x2 - x1), j = (y2 - y1)/abs(y2 - y1), x = x1 + i, y = y1 + j;
        while(x != x2){
            if(squares[x][y].is_busy){
                squares[x][y].free_a_square();
                if(squares[x2][y2].checker_is_white) number_of_blacks -= 1;
                else number_of_whites -= 1;
            }
            x += i;
            y += j;
        }
        if((squares[x2][y2].checker_is_white && y2 == 0) ||
        (!squares[x2][y2].checker_is_white && y2 == 7)) squares[x2][y2].checker_is_queen = true;

        moving_possibility_white = moving_possibility(true);
        moving_possibility_black = moving_possibility(false);

        return true;
    }
    return false;
}

bool Board::moving_possibility(bool is_white) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (squares[i][j].is_busy && squares[i][j].checker_is_white == is_white) {
                if(squares[i][j].checker_is_queen) return true;
                for(int k = 1; k < 3; k++){
                    if (possible_move(i, j, i + k, j + k) ||
                        possible_move(i, j, i - k, j - k) ||
                        possible_move(i, j, i + k, j - k) ||
                        possible_move(i, j, i - k, j + k)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


int Board::the_end(){
    if(number_of_whites == 0 or !moving_possibility_white) return 1;
    if(number_of_blacks == 0 or !moving_possibility_black) return 2;
    return 0;
}

bool Board::is_busy(int x, int y){
    return squares[x][y].is_busy;
}

bool Board::is_white(int x, int y){
    return squares[x][y].checker_is_white;
}

bool Board::is_queen(int x, int y){
    return squares[x][y].checker_is_queen;
}
