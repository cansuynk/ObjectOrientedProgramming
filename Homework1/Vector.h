/* @Author
Student Name: Cansu YANIK
Student ID : 150170704
Date: 26.03.2019 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
using namespace std;

class Vector{

private:
	int size;
	float* values;

public:

	Vector(int,float*);					/*Default Constructor*/
	Vector(const Vector &);				/*Copy Constructor*/
	int getSize() const;				/*Gets size of the vector*/
	float* getValues() const;			/*Gets the values of vector*/
	Vector operator+(const Vector &);	/*Addition operation*/
	Vector operator*(const int);		/*Dot product operation*/
	float operator*(const Vector &);	/*Multiplication with a scalar*/
	friend ostream& operator<<(ostream& os, const Vector &);	/*For printing the results*/

};



#endif