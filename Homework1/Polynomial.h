/* @Author
Student Name: Cansu YANIK
Student ID : 150170704
Date: 26.03.2019 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
using namespace std;

class Polynomial{

private:
	int degree;
	float *values;

public:

	Polynomial(int,float*);						/*Default Constructor*/
	Polynomial(const Polynomial &);				/*Copy Constructor*/
	int getDegree() const;						/*Gets degree of the polynomial*/
	float* getValues() const;					/*Gets the values of polynomial*/
	Polynomial operator+(const Polynomial &);	/*Addition operation*/
	Polynomial operator*(const Polynomial &);	/*Multiplication operation*/
	friend ostream& operator<<(ostream& os, const Polynomial &);	/*For printing the results*/
};



#endif