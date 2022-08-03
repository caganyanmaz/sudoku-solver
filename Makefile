sudoku-solver:
	g++ -o sudoku-solver.out *cpp

test:
	g++ -o test.out *cpp
	cat test.txt | ./test
	rm test 