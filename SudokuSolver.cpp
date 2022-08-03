#include "SudokuSolver.h"
#include <stdio.h>

SudokuSolver::SudokuSolver(int grid_length)
{
    this->grid_length = grid_length;
    this->number_range = grid_length * grid_length;
    init_cells();
}

void SudokuSolver::init_cells()
{
    this->sudoku_cells = std::move(std::vector<int>(this->number_range * this->number_range, 0));
}

bool SudokuSolver::solve(int last_cell_index)
{
    int current_cell_index = find_first_empty_cell_after(last_cell_index);
    if (is_cell_out_of_range(current_cell_index))
    {
        return true; // It means the sudoku is completed without problems
    }
    Bitmap possible_numbers = get_possible_numbers_for(current_cell_index);
    for (int i = 0; i < number_range; i++)
    {
        if (possible_numbers.get_value(i))
        {
            this->sudoku_cells[current_cell_index] = i + 1;
            if (solve(current_cell_index))
                return true;
        }
    }
    this->sudoku_cells[current_cell_index] = 0;
    return false;
}

int SudokuSolver::find_first_empty_cell_after(int index)const
{
    int i;
    for (i = 0; i < sudoku_cells.size(); i++)
    {
        if (sudoku_cells[i] == 0)
            break;
    }
    return i;
}

bool SudokuSolver::is_cell_out_of_range(int index)const
{
    return index < 0 || index >= sudoku_cells.size();
}

Bitmap SudokuSolver::get_possible_numbers_for(int index)const
{
    Bitmap bitmap(number_range);
    for (int i = 0; i < number_range; i++)
        bitmap.set_value(i, is_number_available_for_cell(i + 1, index));
    return bitmap;
}

bool SudokuSolver::is_number_available_for_cell(int number, int cell_index)const
{
    return !(
        is_cells_row_containing(number, cell_index) || 
        is_cells_column_containing(number, cell_index) || 
        is_cells_grid_containing(number, cell_index)
    );
}

bool SudokuSolver::is_cells_row_containing(int number, int cell_index)const
{
    int y = get_row_of(cell_index);
    return is_row_containing(number, y);
}

bool SudokuSolver::is_cells_column_containing(int number, int cell_index)const
{
    int x = get_column_of(cell_index);
    return is_column_containing(number, x);
}

bool SudokuSolver::is_cells_grid_containing(int number, int cell_index)const
{
    std::pair<int, int> grid_starting_position = get_grid_starting_position_of(cell_index);
    return is_grid_containing(number, grid_starting_position);
}

bool SudokuSolver::is_row_containing(int number, int y)const
{
    for (int x = 0; x < number_range; x++)
    {
        if (get_cell(x, y) == number)
            return true;
    }
    return false;
}

bool SudokuSolver::is_column_containing(int number, int x)const
{
    for (int y = 0; y < number_range; y++)
    {
        if (get_cell(x, y) == number)
            return true;
    }
    return false;
}

bool SudokuSolver::is_grid_containing(int number, const std::pair<int, int> &grid_starting_position)const
{
    int y_limit = grid_starting_position.second + grid_length;
    int x_limit = grid_starting_position.first + grid_length;
    for (int y = grid_starting_position.second; y < y_limit; y++)
    {
        for (int x = grid_starting_position.first; x < x_limit; x++)
        {
            if (get_cell(x, y) == number)
                return true;
        }
    }
    return false;
}

void SudokuSolver::set_cell(int x, int y, int number)
{
    sudoku_cells[y * number_range + x] = number;
}

int SudokuSolver::get_cell(int x, int y)const
{
    return this->sudoku_cells[y * number_range + x];
}

int SudokuSolver::get_row_of(int cell_index)const
{
    return cell_index / number_range;
}

int SudokuSolver::get_column_of(int cell_index)const
{
    return cell_index % number_range;
}

std::pair<int, int> SudokuSolver::get_grid_starting_position_of(int cell_index)const
{
    int x = get_column_of(cell_index) / grid_length;
    int y = get_row_of(cell_index) / grid_length;
    return std::pair<int, int> (x * grid_length, y * grid_length);
}

int SudokuSolver::get_cell_count()const
{
    return sudoku_cells.size();
}

int SudokuSolver::get_number_range()const
{
    return number_range;
}

void SudokuSolver::print_table() const
{
	for (int y = 0; y < number_range; y++)
	{
		if (y % grid_length == 0 && y != 0)
			printf("\n");
        print_row(y);
	}
}

void SudokuSolver::print_row(int y)const
{
    for (int x = 0; x < number_range; x++)
    {
        if (x % grid_length == 0 && x != 0)
            printf("  ");
        printf("%i ", get_cell(x, y));
    }
	printf("\n");
}