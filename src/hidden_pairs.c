#include "hidden_pairs.h"

void filter_candidates(SudokuBoard *p_board) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Cell *cell = &(p_board->data[row][col]);
            if (cell->value != 0) {
                continue;
            }
            for (int i = 0; i < cell->num_candidates; i++) {
                int candidate = cell->candidates[i];
                int row_count = 0;
                for (int c = 0; c < BOARD_SIZE; c++) {
                    if (c != col && p_board->data[row][c].value == 0) {
                        for (int j = 0; j < p_board->data[row][c].num_candidates; j++) {
                            if (p_board->data[row][c].candidates[j] == candidate) {
                                row_count++;
                                break;
                            }
                        }
                    }
                }

                int col_count = 0;
                for (int r = 0; r < BOARD_SIZE; r++) {
                    if (r != row && p_board->data[r][col].value == 0) {
                        for (int j = 0; j < p_board->data[r][col].num_candidates; j++) {
                            if (p_board->data[r][col].candidates[j] == candidate) {
                                col_count++;
                                break;
                            }
                        }
                    }
                }
                if (row_count == 0 || col_count == 0) {
                    cell->num_candidates = 1;
                    cell->candidates[0] = candidate;
                    break;
                }
            }
        }
    }
}

int hidden_pairs(SudokuBoard *p_board)
{
    int count = 0;
    for (int row = 0; row < BOARD_SIZE; row++){
        for (int i = 0; i < BOARD_SIZE - 1; i++){
            for (int j = i+1; j < BOARD_SIZE; j++){
                int pair_count = 0; 
                for (int k = 0; k < BOARD_SIZE; k++){
                    if (p_board->data[row][k].candidates[i] && p_board->data[row][k].candidates[j]){
                        pair_count++;
                    }
                }
                if (pair_count == 2){
                    count++;
                }
            }
        }
    }

    for (int col = 0; col < BOARD_SIZE; col++) {
        for (int i = 0; i < BOARD_SIZE - 1; i++) {
            for (int j = i + 1; j < BOARD_SIZE; j++) {
                int pair_count = 0;
                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (p_board->data[k][col].candidates[i] && p_board->data[k][col].candidates[j]) {
                        pair_count++;
                    }
                }
                if (pair_count == 2) {
                    count++;
                }
            }
        }
    }

    for (int block_row = 0; block_row < 3; block_row++) {
        for (int block_col = 0; block_col < 3; block_col++) {
            for (int i = 0; i < BOARD_SIZE - 1; i++) {
                for (int j = i + 1; j < BOARD_SIZE; j++) {
                    int pair_count = 0;
                    for (int row = block_row * 3; row < (block_row + 1) * 3; row++) {
                        for (int col = block_col * 3; col < (block_col + 1) * 3; col++) {
                            if (p_board->data[row][col].candidates[i] && p_board->data[row][col].candidates[j]) {
                                pair_count++;
                            }
                        }
                    }
                    if (pair_count == 2) {
                        count++;
                    }
                }
            }
        }
    }



    return count ;
}
