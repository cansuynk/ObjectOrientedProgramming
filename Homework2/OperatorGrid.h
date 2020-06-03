#ifndef OPERATORGRID_H
#define OPERATORGRID_H

#include <iostream>
#include "ArithmeticOperator.h"
using namespace std;

#define MAX_OPERATOR_SIZE 50		/*I defined it to be able to test my code.*/

class OperatorGrid{
	int grid_rows;
	int grid_cols;
	char **grid;

	int num_operators;
	ArithmeticOperator *operators[MAX_OPERATOR_SIZE];

public:
	OperatorGrid(int rows, int cols);
	~OperatorGrid();
	
	bool place_operator (ArithmeticOperator *);
	bool move_operator (int x, int y, char direction, int move_by);
	void print_operators();
};

#endif