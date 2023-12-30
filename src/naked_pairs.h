#pragma once

#include "sudoku.h"

typedef struct NakedPair_impl
{
    Cell *p_cell1 ;
    Cell *p_cell2 ;
    int value1 ; 
    int value2 ;

} NakedPair; 

int find_naked_pair_value(Cell **p_cells, int *naked_pairs_value);

void find_naked_pair(Cell **p_cells, NakedPair *p_nakedpair, int *p_counter);

int naked_pairs(SudokuBoard *p_board);