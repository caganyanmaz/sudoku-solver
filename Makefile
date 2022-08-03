sudoku-solver:
	g++ -o sudoku-solver *cpp

test:
	g++ -o test *cpp
	cat test.txt | ./test
	rm test 