#include <stdio.h>
#include "SudokuSolver.h"


int main()
{
	int sudoku_grid_size;
	scanf("%i", &sudoku_grid_size);
	SudokuSolver sudoku_solver(sudoku_grid_size);
	int sudoku_number_range = sudoku_solver.get_number_range(); 
	for (int y = 0; y < sudoku_number_range; y++)
	{
		for (int x = 0; x < sudoku_number_range; x++)
		{
			int n;
			scanf("%i", &n);
			sudoku_solver.set_cell(x, y, n);
		}
	}
	if (!sudoku_solver.solve())
	{
		printf("Not solvable\n");
		return 0;
	}
	sudoku_solver.print_table();
	return 0;
}