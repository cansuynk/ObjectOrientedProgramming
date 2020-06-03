#ifndef ARITHMETICOPERATOR_H
#define ARITHMETICOPERATOR_H

#include <iostream>
#include "Operator.h"
using namespace std;

class ArithmeticOperator: public Operator{
	char sign;

public:
	ArithmeticOperator(int x, int y, int size, char sign);

	char get_sign();

	//Prints out operator's center location, size, and sign character
	void print_operator();
};

#endif