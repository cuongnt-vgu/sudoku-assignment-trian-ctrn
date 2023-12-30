#include "naked_pairs.h"
#include <stdlib.h>

int find_naked_pair_value(Cell **p_cells, int *naked_pairs_value)
{
    int num_naked_pairs = 0; 
    for (int i = 0; i < BOARD_SIZE-1; i++)
    {
        Cell *cell1 = p_cells[i]; 
        if (cell1->num_candidates != 2)
        {
            continue;
        } 

        for (int j = i+1; j < BOARD_SIZE; j++)
        {
            Cell *cell2 = p_cells[j];
            if (cell2->num_candidates != 2)
            {
                continue;
            }
            int  a[2] = {0};
            int b[2] = {0};  
            int counter_a = 0;
            int counter_b = 0;
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (cell1->candidates[k])
                {
                    a[counter_a++] = k + 1;
                }
                if (cell2->candidates[k])
                {
                    b[counter_b++] = k + 1;
                }
            }         

            if (a[0] == b[0] && a[1] == b[1])
            {
            naked_pairs_value[num_naked_pairs * 2] = i;
            naked_pairs_value[num_naked_pairs * 2 + 1] = j;
            num_naked_pairs++;
            }
        }
    }
    return num_naked_pairs;
}

void find_naked_pair(Cell **p_cells, NakedPair *p_nakedpair, int *p_counter)
{
    int *naked_pairs_value = malloc(BOARD_SIZE * sizeof(int));

    int num_naked_pairs = find_naked_pair_value(p_cells, naked_pairs_value);
    for (int i = 0; i < num_naked_pairs; i++) {
        bool is_duplicate = false;

        for (int j = 0; j < *p_counter; j++) 
        {
            if (p_nakedpair[j].p_cell1 == p_cells[naked_pairs_value[i*2]] && p_nakedpair[j].p_cell2 == p_cells[naked_pairs_value[i*2+1]] )
            {
                is_duplicate = true;
                break;
            }
        }

        if (!is_duplicate) 
        {

            p_nakedpair[*p_counter].p_cell1 = p_cells[naked_pairs_value[i*2]];
            p_nakedpair[*p_counter].p_cell2 = p_cells[naked_pairs_value[i*2+1]];
            // p_nakedpair[*p_counter].value1 = naked_pairs_value[i*2];
            // p_nakedpair[*p_counter].value2 = naked_pairs_value[i*2+1];
            (*p_counter)++;
        }
    }
    free(naked_pairs_value);

}

int naked_pairs(SudokuBoard *p_board)
{
    NakedPair naked_pairs[BOARD_SIZE*3];
    int counter = 0; 

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pair(p_board->p_rows[i], naked_pairs, &counter);
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pair(p_board->p_cols[i], naked_pairs, &counter);
    }

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pair(p_board->p_boxes[i], naked_pairs, &counter);
    }
    return counter;

    
}