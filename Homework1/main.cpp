/* @Author
Student Name: Cansu YANIK
Student ID : 150170704
Date: 26.03.2019 */

#include "Vector.h"
#include "Polynomial.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <math.h>
using namespace std;

Vector::Vector(int size=0, float *values=NULL){		/*Default Constructor*/
	this->size=size;
	this->values=values;
}

Vector::Vector(const Vector & object){				/*Copy Constructor*/
	this->size = object.getSize();
	this->values = new float[this->getSize()];
	for(int i=0; i<this->getSize(); i++){
		this->values[i] = object.getValues()[i];
	}
}
int Vector::getSize() const{
	return this->size;
}

float* Vector::getValues() const {
	return this->values;
}

Vector Vector::operator+(const Vector& object){
	int firstSize = this->getSize();
	int secondSize = object.getSize();

	if(firstSize != secondSize){				/*If vector sizes are not equal, we cannot do addition, checks it, if not equal, returns empty object*/
		cout << "The sizes of vectors are not equal!!!" << endl;
		return Vector();
	}
	float *resultvalues = new float[firstSize];
	for(int i=0; i<firstSize; i++){				/*Just does addition for each value of the vectors and saves the results to an array*/
		resultvalues[i] = this->getValues()[i] + object.getValues()[i];
	}
	return Vector(firstSize, resultvalues);		/*Creates a vector object for result*/
}

/*This function is for vector and scalar multiplication*/
Vector Vector::operator*(const int scalar){			/*Just multiplies each value with the given scalar number and return new result vector object*/
	int firstSize = this->getSize();
	float *resultvalues = new float[firstSize];

	for(int i=0; i<firstSize; i++){
		resultvalues[i] = this->getValues()[i] * scalar;
	}
	return Vector(firstSize, resultvalues);
}

/*This function is for dot product*/
float Vector::operator*(const Vector& object){
	float result=0.0;
	int firstSize = this->getSize();
	int secondSize = object.getSize();

	if(firstSize != secondSize){			/*To be able to do dot product, vector sizes must be equal*/
		cout << "The sizes of vectors are not equal!!!" << endl;
		return 0;
	}
	
	for(int i=0; i<firstSize; i++){			/*Multiplies each term and takes the summation of the results after multiplications*/
		result = result + (this->getValues()[i] * object.getValues()[i]);
	}
	return result;

}

ostream& operator<<(ostream& os, const Vector& object)
{
	int objectSize = object.getSize();
	float *tempValues = object.getValues();
	os << "(";
	for(int i=0; i<objectSize; i++){

		os << tempValues[i];		/*Prints values*/
		if(i+1 < objectSize)		/*If this value is not the last value, put a comma after prints value*/
			os << ", ";	
	}
	os << ")";
    return os;
}


///////////////////////////Polynomial//////////////////////////////////////////////////////////////////////
Polynomial::Polynomial(int degree=0, float *values=NULL){  /*Default Constructor*/
	this->degree = degree;
	this->values = values;
}

Polynomial::Polynomial(const Polynomial & object){		/*Copy Constructor*/
	this->degree = object.getDegree();
	this->values = new float[this->getDegree()+1];
	for(int i=0; i<=this->getDegree(); i++){
		this->values[i]=object.getValues()[i];
	}
}

int Polynomial::getDegree() const{
	return this->degree;
}
float* Polynomial::getValues() const{
	return this->values;
}

Polynomial Polynomial::operator+(const Polynomial& object){
	int i;
	int firstDegree = this->getDegree();
	int secondDegree = object.getDegree();

	/*Firstly, finds the polynomial which has highest degree, then saves the values of it directly to a new array until second polynomial's values comes*/
	/*After that, continues to save values by taking the summation of these two polynomials' values, and returns a new object with the results and the highest degree*/

	if(firstDegree > secondDegree){							/*If first polynomial has highest degree*/
		float *resultvalues = new float[firstDegree+1];

		for(i=0; i<(firstDegree - secondDegree); i++){		/*Until degrees will be equal, writes the values of the polynomial which has highest degree to the result array*/
			resultvalues[i] = this->getValues()[i];
		}
		for(int j=0; j <= secondDegree; j++, i++){			/*Now, I can take the summation of the values which have same degrees*/
			resultvalues[i] = this->getValues()[i] + object.getValues()[j];		
		}
		return Polynomial(firstDegree, resultvalues);
	}
	else if(firstDegree < secondDegree){					/*If second polynomial has highest degree, same procedure will apply for the second one*/
		float *resultvalues = new float[secondDegree+1];

		for(i=0; i<(secondDegree - firstDegree); i++){
			resultvalues[i] = object.getValues()[i];
		}
		for(int j=0; j <= firstDegree; j++, i++){
			resultvalues[i] = this->getValues()[j] + object.getValues()[i];
		}
		return Polynomial(secondDegree, resultvalues);
	}
	else{													/*If their degrees are equal, I can start to do summation.*/
		float *resultvalues = new float[secondDegree+1];

		for(int i=0; i <= secondDegree; i++){
			resultvalues[i] = this->getValues()[i] + object.getValues()[i];
		}
		return Polynomial(secondDegree, resultvalues);
	}
}

Polynomial Polynomial::operator*(const Polynomial& object){
	int firstDegree = this->getDegree();
	int secondDegree = object.getDegree();

	float *resultvalues = new float[firstDegree + secondDegree + 1]; /*Result polynomial's degree is the summation of these two polynomials' degrees*/

	for(int i=0; i<=(firstDegree + secondDegree); i++){		/*Creates a new values array, fills it with zeros.*/
		resultvalues[i]=0;
	}
	
	/*Starts with the first polynomial, for each value of the first polynomial, I traverse the second polynomial's values, multiply them and the adds the previous result for the current degree*/
	for(int i=0; i<=firstDegree; i++){
		for(int j=0; j<=secondDegree; j++){
			resultvalues[j+i] = resultvalues[j+i] + (this->getValues()[i] * object.getValues()[j]);
		}
	}

	return Polynomial(firstDegree + secondDegree, resultvalues);	/*Returns result as a new object*/
}
ostream& operator<<(ostream& os, const Polynomial& object)
{
	int objectDegree = object.getDegree();
	int valuesDegree = objectDegree;  /*I need current degree of the value thats why I save the degree in another variable.*/

	for(int i=0; i<=objectDegree; i++){

		if(object.getValues()[i] == 0){		/*If coefficient is 0, I will not print it.*/
			valuesDegree--;
			continue;
		}
		if(valuesDegree == objectDegree){			/*If this is first value(term)*/
			if(object.getValues()[i] < 0)			/*If the coefficient less than 0, I need to print minus sign*/
				os << "- ";
			if(fabs(object.getValues()[i]) != 1)	/*If value is not equal to 1*/
				os << fabs(object.getValues()[i]);	/*Prints the coefficient*/
			os << "x";								/*If the coefficient is 1, just print "x"*/
			if(valuesDegree > 1)					/*If degree is bigger than 1, print its degree*/
				os << "^" << valuesDegree;
		}
		else if(valuesDegree == 0){					/*If the term is the last term*/
			if(object.getValues()[i] < 0)			/*If the coefficient less than 0, I need to print minus sign*/
				os << " - ";
			else if(object.getValues()[i] > 0)		/*If coefficient bigger than 0*/
				os << " + ";						/*Prints "+" before the term and then prints coefficient*/
			os << fabs(object.getValues()[i]);
		}
		else{
			if(object.getValues()[i] < 0)			/*If the coefficient less than 0, I need to print minus sign*/
				os << " - ";
			else if(object.getValues()[i] > 0)		/*If term is not the first or last term, ans if it is bigger than 0, prints "+"*/
				os << " + ";
			if(fabs(object.getValues()[i]) != 1)	/*If the coefficient is not 1, prints the coefficient, if it equals to 1, do not print 1*/
				os << fabs(object.getValues()[i]);
			os << "x";
			if(valuesDegree > 1)					/*If degree is bigger than 1, prints it's degree.*/
				os << "^" << valuesDegree;
			}
		valuesDegree--;
	}

    return os;
}

void menu(){
	
	cout << "Polynomial and Vector List Program!" << endl;
	cout << "Polynomials and Vectors are read from text files!" << endl << endl;

	cout << "Possible Actions:" << endl;

	cout << "1. Print Polynomial and Vector lists" << endl;
	cout << "2. Do a polynomial operation" << endl;
	cout << "3. Do a vector operation" << endl;
	cout << "4. Help: Print possible actions" << endl;
	cout << "0. Exit the program" << endl << endl;
	
}

int main(){

	ifstream vectorfile; ifstream polynomialfile;			/*For opening files*/
	int vectorAmount, vectorSize;							/*Holds number of vectors and vector's length for each vector*/
	int polynomialAmount, polynomialDegree;					/*Holds number of polynomials and polynomial's degree for each polynomial*/
	float values;											/*Holds values reading from file*/



	/**********************File operations****************************************/

	vectorfile.open( "Vector.txt" );		/*Opens file*/
	if(!vectorfile){						/*If the file cannot be opened*/
		cerr << "Cannot open vector file" << endl;
		exit(1);
	}
	polynomialfile.open( "Polynomial.txt" );		
	if(!vectorfile){								
		cerr << "Cannot open polynomial file" << endl;
		exit(1);
	}
	/*******************************vector****************************************/
	
	vectorfile >> vectorAmount;							/*Takes first line of the vector file(number of vector)*/
	Vector *vectorArray = new Vector[vectorAmount];		/*Creates a dynamic array to save all vector objects*/

	for(int i=0; i<vectorAmount; i++){					/*For each vector, reads vector size and it's values from file and saves the values to an array*/
		vectorfile >> vectorSize;
		float *valuesArray = new float[vectorSize];		

		for(int j=0; j<vectorSize; j++){				/*Reads values from file and saves them to array*/
			vectorfile >> values;
			valuesArray[j] = values;
		
		}
		Vector vectorObject(vectorSize, valuesArray);	/*Using these parameters(size and value array), create a vector object and saves it to vector object array*/
		vectorArray[i] = vectorObject;
	}

	/*******************************polynomial************************************/

	polynomialfile >> polynomialAmount;									/*Takes first line of the polynomial file(number of polynomial)*/
	Polynomial *polynomialArray = new Polynomial[polynomialAmount];		/*Creates a dynamic array to save all polynomial objects*/

	for(int i=0; i<polynomialAmount; i++){								/*For each polynomial, reads polynomial degree and it's values from file and saves the values to an array*/
		polynomialfile >> polynomialDegree;
		float *valuesArray = new float[polynomialDegree+1];

		for(int j=0; j<=polynomialDegree; j++){							/*Reads values from file and saves them to array*/
			polynomialfile >> values;
			valuesArray[j] = values;
		
		}
		Polynomial polynomialObject(polynomialDegree, valuesArray);	/*Using these parameters(degree and value array), create a polynomial object and saves it to polynomial object array*/
		polynomialArray[i] = polynomialObject;
	}
	

	vectorfile.close(); polynomialfile.close();		/*Closes files*/

	menu();						/*Calls menu for users*/
	char operation;				/*Holds operation*/
	int index1, index2;			/*Holds second index of the vector or polynomial, or a scalar for vector multiplication*/
	int choice_int=1;			
	string choice_string;		/*Firstly, I take user's choice as a string because user may enter a char or string accidentally, then I convert it to integer*/

	while(choice_int!=0){
		
		cout << endl << "Enter an option: ";
		cin >> choice_string;	
		choice_int = atoi(choice_string.c_str());	/*If user enter a string, program will exit*/

		
		/*************************************Print Vector and Polynomial Lists*****************************************/
		if(choice_int == 1){
			cout << "Vectors:" << endl;
			for(int i=0; i<vectorAmount; i++){
				cout << i+1 << ". " << vectorArray[i] << endl;			/*calls operator<<(...) for vectors*/
			}
			cout << endl << "Polynomials:" << endl;
			for(int i=0; i<polynomialAmount; i++){
				cout << i+1 << ". " << polynomialArray[i] << endl;		/*calls operator<<(...) for polynomials*/
			}
		}

		/*******************************************Polynomial Operations***********************************************/
		else if(choice_int == 2){
			cout << "Which polynomial operation would you like to do?(+:addition, *:multiplication):" << endl;
			
			cin >> index1;				/*Takes first index of polynomial*/
			cin >> operation;			/*Takes operation*/
			cin >> index2;				/*Takes second index of polynomial*/

			/*Polynomial indexes cannot be less than zero or cannot exceed the number of polynomial*/
			if( index1-1 < 0 || index2-1 < 0 || index1-1 > polynomialAmount || index2-1 > polynomialAmount ){
				cout << "Error! Invalid polynomial index" << endl << endl;
				menu();
				continue;
			}
			else{
				if(operation == '+'){		/*If the operation is addition*/
					Polynomial result = polynomialArray[index1-1] + polynomialArray[index2-1];										/*Doing operation (calls operator+(...))*/
					cout << "(" << polynomialArray[index1-1] << ") + (" << polynomialArray[index2-1] << ") = " << result << endl;	/*Prints the result to the screen(calls operator<<(...))*/
				}
				else if(operation == '*'){		
					Polynomial result = polynomialArray[index1-1] * polynomialArray[index2-1];										/*Doing operation (calls operator*(...))*/
					cout << "(" << polynomialArray[index1-1] << ") * (" << polynomialArray[index2-1] << ") = " << result << endl;	/*Prints the result to the screen(calls operator<<(...))*/
				}
				else{
					cout << "Error! Invalid polynomial operation." << endl << endl;													/*If user enter an invalid operation*/
					menu();
					continue;
				}
			}
		}

		/*******************************************Vector Operations***********************************************/		
		else if(choice_int == 3){
			cout << "Which vector operation would you like to do?(+:addition, *:scalar multiplication, .:dot product):" << endl;
									
			cin >> index1;			/*Takes first index of vector*/
			cin >> operation;		/*Takes operation*/
			cin >> index2;			/*Second index of vector or this can be a scalar number.*/
			
			if(operation == '+'){				/*If the operation is addition*/
				/*Vector indexes cannot be less than zero or cannot exceed the number of vector*/
				if( index1-1 < 0 || index2-1 < 0 || index1-1 > vectorAmount || index2-1 > vectorAmount ){
					cout << "Error! Invalid vector index" << endl << endl;
					menu();
					continue;
				}
				else{
					Vector result = vectorArray[index1-1] + vectorArray[index2-1];								    /*Doing operation (calls operator+(...))*/
					cout << vectorArray[index1-1] << " + " << vectorArray[index2-1] << " = " << result << endl;		/*Prints the result to the screen(calls operator<<(...))*/
				}
			}
			else if(operation == '*'){		/*If the operation is multiplication with scalar*/
				/*Vector index cannot be less than zero or cannot exceed the number of vector*/
				if( index1-1 < 0 || index1-1 > vectorAmount ){
					cout << "Error! Invalid vector index" << endl << endl;
					menu();
					continue;
				}
				else{
					Vector result = vectorArray[index1-1] * index2;												/*Doing operation (calls Vector operator*(...))*/
					cout << vectorArray[index1-1] << " * " << index2 << " = " << result << endl;				/*Prints the result to the screen(calls operator<<(...))*/
				}
			}
			else if(operation == '.'){		/*If the operation is dot product*/
				/*Vector indexes cannot be less than zero or cannot exceed the number of vector*/
				if( index1-1 < 0 || index2-1 < 0 || index1-1 > vectorAmount || index2-1 > vectorAmount ){
					cout << "Error! Invalid vector index" << endl << endl;
					menu();
					continue;
				}
				else{
					cout << vectorArray[index1-1] << " . " << vectorArray[index2-1]								/*Doing operation (calls float operator*(...))*/
						 << " = " << vectorArray[index1-1] * vectorArray[index2-1] << endl;						/*Prints the result to the screen(calls operator<<(...))*/
				}
			}
			else{
				cout << "Error! Invalid vector operation." << endl << endl;										/*If user enter an invalid operation*/
				menu();
				continue;
			}
		}
		else if(choice_int == 4){	/*Prints possible options for vectors and polynomials*/
			menu();	
		}
		else if(choice_int == 0) /*If 0, program will exit*/
			break;

		else{		/*Invalid option*/
			cout << endl << "Error! Invalid option. Please select a valid option given below." << endl << endl;
			menu();
		}
	}

	delete[] vectorArray;
	delete[] polynomialArray;
	return 0;
}