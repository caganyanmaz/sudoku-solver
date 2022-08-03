#ifndef _SUDOKU_SOLVER_H_
#define _SUDOKU_SOLVER_H_

#include <vector>
#include <utility>
#include "Bitmap.h"

class SudokuSolver
{
	int grid_length;
	int number_range;
	std::vector<int> sudoku_cells;
	mutable bool started_checking_row = false; // FOR DEBUG PURPOSES, DELETE LATER 
public:
	SudokuSolver(int grid_length);
	
	void init_cells();
	
	bool solve(int last_cell_index=0);

	void set_cell(int x, int y, int number);
	int get_cell(int x, int y)const;

	int get_number_range()const;
	int get_cell_count()const;

	void print_table()const;
	void print_row(int y)const;
private:
	int find_first_empty_cell_after(int index)const;
	
	Bitmap get_possible_numbers_for(int index)const;
	
	bool is_cell_out_of_range(int index)const;
	bool is_number_available_for_cell(int number, int cell_index)const;
	
	bool is_cells_row_containing(int number, int cell_index)const;
	bool is_cells_column_containing(int number, int cell_index)const;
	bool is_cells_grid_containing(int number, int cell_index)const;

	int get_row_of(int cell_index)const;
	int get_column_of(int cell_index)const;
	std::pair<int, int> get_grid_starting_position_of(int cell_index)const;

	bool is_row_containing(int number, int y)const;
	bool is_column_containing(int number, int x)const;
	bool is_grid_containing(int number, const std::pair<int, int> &grid_starting_position)const;
};


#endif