/* @Author
Student Name: Cansu YANIK
Student ID : 150170704
Date: 22.04.2019 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Operator.h"
#include "ArithmeticOperator.h"
#include "OperatorGrid.h"
using namespace std;

/*Holds the existences of the border or conflict errors*/
bool border_error;
bool conflict_error;

/*Function definitions*/
/*Since functions are outside of the classes, they take gird, grid's row and column (row_number and column_number); sign(type here), center locations (row and column) and size of the operator as parameters*/
void plus_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size);		/*Places plus operation on the grid and checks border and conflict errors*/
void minus_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size); 	/*Places minus operation on the grid and checks border and conflict errors*/
void multiply_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size);  /*Places multiply operation on the grid and checks border and conflict errors*/
void division_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size);  /*Places division operation on the grid and checks border and conflict errors*/

Operator::Operator(int x, int y, int size){	/*Operator constructor operations*/
	this->center_x = x;
	this->center_y = y;
	this->op_size = size;
}

void Operator::reset(int new_x, int new_y, int new_size){ /*Updates operator's location and size*/
	this->set_x(new_x);
	this->set_y(new_y);
	this->set_size(new_size);
}

void Operator::set_x(int new_x){	/*Updates operator's center x*/
	this->center_x = new_x;
}

int Operator::get_x(){				/*Gets operator's center x value*/
	return this->center_x;
}

void Operator::set_y(int new_y){	/*Updates operator's center y*/
	this->center_y = new_y;
}

int Operator::get_y(){				/*Gets operator's center y value*/
	return this->center_y;
}

void Operator::set_size(int new_size){	/*Updates operator's size*/
	this->op_size = new_size;
}

int Operator::get_size(){				/*Gets operator's size*/
	return this->op_size;
}
/*ArithmeticOperator constructor operations*/
ArithmeticOperator::ArithmeticOperator(int x, int y, int size, char sign): Operator(x, y, size){
	if( sign=='+' || sign=='-' || sign=='x' || sign=='/'){	/*If sign is valid, we can save it.*/
		this->sign = sign;	
	}
	else{
		cout << "SIGN parameter is invalid!" << endl;		/*If sign is invalid, prints error message*/
	}
}

char ArithmeticOperator::get_sign(){	/*Gets operator's sign type*/
	return this->sign;
}

void ArithmeticOperator::print_operator(){	/*Prints operator's center location, size, and sign */
	cout << "ARITHMETIC_OPERATOR[" << this->get_sign() << "], CENTER_LOCATION[" << this->get_x() << "," << this->get_y()
		<<"], SIZE[" << this->get_size() << "]" << endl;
}
/*OperatorGrid constructor operations, creates grid with given rows and cols*/
OperatorGrid::OperatorGrid(int rows, int cols){
	this->grid_rows = rows;
	this->grid_cols = cols;

	this->grid=new char*[this->grid_rows]; /*Creates 2 dimensions grid array*/

	for (int i=0; i<this->grid_rows; i++){
		grid[i]=new char[grid_cols];
	}
	for (int i=0; i<this->grid_rows; i++){
		for (int j=0; j<this->grid_cols; j++){
			grid[i][j]=' ';
		}
	}

	this->num_operators = 0;	/*Initially there is no operators on the grid*/

}

/*************Helper methods*****************/
void plus_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size){
	int counter=0; /*Determines the locations of plus operator by adding or subtracting from the column or row */
	
	/*Plus operator can be placed at the bottom, top and two sides of the center so there is 4 placements states*/
	while(counter<=size){ /*Until its number reaches the size*/

		/*Placement state for the top of the center*/
		if(row-counter-1 > row_number-1 || row-counter-1 < 0 || column-1 > column_number-1 || column-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row-counter-1][column-1]!=' '){ 	/*If this place is not empty*/
			conflict_error=true;						/*There is conflict_error*/					
		}
		else{
			temp_grid[row-counter-1][column-1]=type;	/*if no error, places plus to the temp grid*/
		}
		/*Placement state for the bottom of the center*/
		if(row+counter-1 > row_number-1 || row+counter-1 < 0 || column-1 > column_number-1 || column-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row+counter-1][column-1]!=' '){ 	/*If this place is not empty*/
			conflict_error=true;					/*There is conflict_error*/						
		}
		else{
			temp_grid[row+counter-1][column-1]=type; 	/*if no error, places plus to the temp grid*/
		}
		/*Placement state for the left of the center*/
		if(row-1 > row_number-1 || row-1 < 0 || column-counter-1 > column_number-1 || column-counter-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row-1][column-counter-1]!=' '){	/*If this place is not empty*/
			conflict_error=true;						/*There is conflict_error*/
		}
		else{
			temp_grid[row-1][column-counter-1]=type;	/*if no error, places plus to the temp grid*/
		}
		/*Placement state for the right of the center*/
		if(row-1 > row_number-1 || row-1 < 0 || column+counter-1 > column_number-1 || column+counter-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row-1][column+counter-1]!=' '){
			conflict_error=true;
		}
		else{
			temp_grid[row-1][column+counter-1]=type;	/*if no error, places plus to the temp grid*/
		}
		counter++;
	}
}

void minus_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size){
	int counter=0; /*Determines the locations of minus sign operator by adding or subtracting from the column*/
	/*Minus sign operator can be placed at the two sides of the center so there is 2 placements states*/
	
	while(counter<=size){ /*Until its number reaches the size*/

		/*Placement state for the left of the center*/
		if(row-1 > row_number-1 || row-1 < 0 || column-counter-1 > column_number-1 || column-counter-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row-1][column-counter-1]!=' '){	/*If this place is not empty*/
			conflict_error=true;						/*There is conflict_error*/
		}
		else{
			temp_grid[row-1][column-counter-1]=type;	/*if no error, places minus sign to the temp grid*/
		}
		/*Placement state for the right of the center*/
		if(row-1 > row_number-1 || row-1 < 0 || column+counter-1 > column_number-1 || column+counter-1 < 0){
			border_error=true;
		}
		else if(grid[row-1][column+counter-1]!=' '){
			conflict_error=true;
		}
		else{
			temp_grid[row-1][column+counter-1]=type;
		}
		counter++;
	}
}

void multiply_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size){
	int counter=0;	/*Determines the locations of multiply sign operator by adding or subtracting from the column and row */
	/*Multiply sign operator can be placed at cross directions of the center so there is 4 placements states*/

	while(counter<=size){

		/*Placement state for the top-left of the center*/
		if(row-counter-1 > row_number-1 || row-counter-1 < 0 || column-counter-1 > column_number-1 || column-counter-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row-counter-1][column-counter-1]!=' '){	/*If this place is not empty*/
			conflict_error=true;								/*There is conflict_error*/
		}
		else{
			temp_grid[row-counter-1][column-counter-1]=type;	/*if no error, places multiply sign to the temp grid*/
		}
		/*Placement state for the bottom-left of the center*/
		if(row+counter-1 > row_number-1 || row+counter-1 < 0 || column-counter-1 > column_number-1 || column-counter-1 < 0){
			border_error=true;
		}
		else if(grid[row+counter-1][column-counter-1]!=' '){
			conflict_error=true;
		}
		else{
			temp_grid[row+counter-1][column-counter-1]=type;
		}
		/*Placement state for the top-right of the center*/
		if(row-counter-1 > row_number-1 || row-counter-1 < 0 || column+counter-1 > column_number-1 || column+counter-1 < 0){
			border_error=true;
		}
		else if(grid[row-counter-1][column+counter-1]!=' '){
			conflict_error=true;
		}
		else{
			temp_grid[row-counter-1][column+counter-1]=type;
		}
		/*Placement state for the bottom-right of the center*/
		if(row+counter-1 > row_number-1 || row+counter-1 < 0 || column+counter-1 > column_number-1 || column+counter-1 < 0){
			border_error=true;
		}
		else if(grid[row+counter-1][column+counter-1]!=' '){
			conflict_error=true;
		}
		else{
			temp_grid[row+counter-1][column+counter-1]=type;
		}
		counter++;
	}
}

void division_opr(char** grid, int row_number, int column_number, char **temp_grid, char type, int row, int column, int size){
	int counter=0; /*Determines the locations of division sign operator by adding or subtracting from the column and row */
	/*Division sign operator can be placed at 2 cross directions of the center so there is 2 placements states*/

	while(counter<=size){

		/*Placement state for the bottom-left of the center*/
		if(row+counter-1 > row_number-1 || row+counter-1 < 0 || column-counter-1 > column_number-1 || column-counter-1 < 0){ /*Checks borders*/
			border_error=true;
		}
		else if(grid[row+counter-1][column-counter-1]!=' '){	/*If this place is not empty*/
			conflict_error=true;								/*There is conflict_error*/
		}
		else{
			temp_grid[row+counter-1][column-counter-1]=type;	/*if no error, places division sign to the temp grid*/
		}
		/*Placement state for the top-right of the center*/
		if(row-counter-1 > row_number-1 || row-counter-1 < 0 || column+counter-1 > column_number-1 || column+counter-1 < 0){
			border_error=true;
		}
		else if(grid[row-counter-1][column+counter-1]!=' '){
			conflict_error=true;
		}
		else{
			temp_grid[row-counter-1][column+counter-1]=type;
		}
		counter++;
	}
}

bool OperatorGrid::place_operator(ArithmeticOperator * new_operator){

	bool success = false;								/*This value will be returned. It shows whether operator places successfully or not, initially it is false*/
	border_error = false;  conflict_error = false;		/*Initially there is no error*/	
	int row_number = this->grid_rows;					/*Saves grid's row and column numbers in different variables*/
	int column_number = this->grid_cols;

	char **temp_grid = new char*[row_number];	/*I need temp grid in order not to affect to grid*/
	for (int i=0; i<row_number; i++){			/*Created temp grid*/
		temp_grid[i] = new char[column_number];
	}

	for (int i=0; i<row_number; i++){	/*To make empty temp grid*/
		for (int j=0; j<column_number; j++){
			temp_grid[i][j]=' ';
		}
	}

	char type = new_operator->get_sign();	/*Saves the incoming operator's features(sign, center location and size)*/
	int row = new_operator->get_x();
	int column = new_operator->get_y();	
	int size = new_operator->get_size();


	if(type=='+'){ 		/*If operation is plus, calls the plus function for the placement*/
		plus_opr(this->grid, row_number, column_number, temp_grid, type, row, column, size);
	}
	else if(type=='-'){	/*If operation is minus, calls the minus function for the placement*/
		minus_opr(this->grid, row_number, column_number, temp_grid, type, row, column, size);
	}
	else if(type=='x'){	/*If operation is multiply, calls the multiply function for the placement*/
		multiply_opr(this->grid, row_number, column_number, temp_grid, type, row, column, size);
	}
	else if(type=='/'){	/*If operation is division, calls the division function for the placement*/
		division_opr(this->grid, row_number, column_number, temp_grid, type, row, column, size);
	}
	else{
		success = false;
		return success;
	}

	/*If border or conflict error occurs in the operations functions*/
	if(border_error){  
		cout << "BORDER ERROR: Operator " << type << " with size " << size << " can not be placed on ("
			<< row << "," << column << ")." << endl;
		success = false;
	}
	if(conflict_error){
		cout << "CONFLICT ERROR: Operator " << type << " with size " << size << " can not be placed on ("
			<< row << "," << column << ")." << endl;
		success = false;
	}

	if (!border_error && !conflict_error){ /*If there is no error*/
		if(this->num_operators != MAX_OPERATOR_SIZE){	/*And If the operators array is not full, we can place the operator on the grid.*/
			operators[this->num_operators] = new ArithmeticOperator(row, column, size, type);	/*Saves the operator into array*/	
			for (int i=0; i<row_number; i++){ 
				for (int j=0; j<column_number; j++){
					if (temp_grid[i][j]!=' '){
						grid[i][j]=temp_grid[i][j]; /*Places to grid*/

					}
				}
			}
			this->num_operators++;
			success = true;
			cout << "SUCCESS: Operator " << type << " with size " << size << " is placed on (" << row << "," << column << ")." << endl;
		}
		else{	/*If the operators array is full*/
			success = false;		
		}
	}
	for(int i = 0; i < row_number; ++i) {		/*Gives back allocated spaces to the memory*/
		delete[] temp_grid[i];   
	}
	delete[] temp_grid;
	return success;
}
bool OperatorGrid::move_operator(int x, int y, char direction, int move_by){

	bool success = false;		/*This value will be returned. It shows whether operator places successfully or not, initially it is false*/
	int index = 0;				/*It holds index of the necassary operation*/

	border_error = false; conflict_error = false;		/*Initially there is no error*/

	int row_number = this->grid_rows;					/*Saves grid's row and column numbers in different variables*/
	int column_number = this->grid_cols;


	char **temp_grid = new char*[row_number];			/*I need two temp grids in order not to affect to grid*/
	char **temp_grid2 = new char*[row_number];
	for (int i=0; i<row_number; i++){					/*Cretaes temp grids*/
		temp_grid[i] = new char[column_number];
		temp_grid2[i] = new char[column_number];
	}


	if(this->grid[x-1][y-1]!=' '){	/*If there is a sign at given location, do the desired mov*/

		for(int a=0; a < this->num_operators; a++){		/*Until finds the correct operator, which is wanted to be moved, it checks every operator in the operators array.*/
			int counter = 0;
			for (int i=0; i<row_number; i++){ 			/*To make empty temp grids*/
				for (int j=0; j<column_number; j++){
					temp_grid[i][j]=' ';
					temp_grid2[i][j]=' ';
				}
			}
			/*To be able to do an easy mov operation, I places every operator into an empty temp grid.*/
			if(operators[a]->get_sign()=='+'){ 		/*If operation is plus, places this operator directly into an empty temp grid (This temp grid is only for this operator, so I dont need to check any error)*/
				while(counter<=operators[a]->get_size()){ /*Until its number reaches the size*/
					temp_grid[operators[a]->get_x()-counter-1][operators[a]->get_y()-1]=operators[a]->get_sign();	
					temp_grid[operators[a]->get_x()+counter-1][operators[a]->get_y()-1]=operators[a]->get_sign(); 	
					temp_grid[operators[a]->get_x()-1][operators[a]->get_y()-counter-1]=operators[a]->get_sign();	
					temp_grid[operators[a]->get_x()-1][operators[a]->get_y()+counter-1]=operators[a]->get_sign();	
					counter++;
				}
			}
			else if(operators[a]->get_sign()=='-'){	/*If operation is minus, places this operator directly into an empty temp grid (This temp grid is only for this operator, so I dont need to check any error)*/
				while(counter<=operators[a]->get_size()){ /*Until its number reaches the size*/
					temp_grid[operators[a]->get_x()-1][operators[a]->get_y()-counter-1]=operators[a]->get_sign();
					temp_grid[operators[a]->get_x()-1][operators[a]->get_y()+counter-1]=operators[a]->get_sign();
					counter++;
				}		
			}
			else if(operators[a]->get_sign()=='x'){	/*If operation is multiply sign, places this operator directly into an empty temp grid (This temp grid is only for this operator, so I dont need to check any error)*/
				while(counter<=operators[a]->get_size()){
					temp_grid[operators[a]->get_x()-counter-1][operators[a]->get_y()-counter-1]=operators[a]->get_sign();	
					temp_grid[operators[a]->get_x()+counter-1][operators[a]->get_y()-counter-1]=operators[a]->get_sign();
					temp_grid[operators[a]->get_x()-counter-1][operators[a]->get_y()+counter-1]=operators[a]->get_sign();
					temp_grid[operators[a]->get_x()+counter-1][operators[a]->get_y()+counter-1]=operators[a]->get_sign();
					counter++;
				}		
			}
			else if(operators[a]->get_sign()=='/'){	/*If operation is dividing sign, places this operator directly into an empty temp grid (This temp grid is only for this operator, so I dont need to check any error)*/
				while(counter<=operators[a]->get_size()){					
					temp_grid[operators[a]->get_x()+counter-1][operators[a]->get_y()-counter-1]=operators[a]->get_sign();	
					temp_grid[operators[a]->get_x()-counter-1][operators[a]->get_y()+counter-1]=operators[a]->get_sign();
					counter++;
				}
			}
			if (temp_grid[x-1][y-1]==this->grid[x-1][y-1]){	/*If both grids have the same sign in given location, It means that we found the correct operator which is going to be moved*/
				index=a;									/*Saves the index and stop the searching*/
				break;
			}
		}		
		for (int i=0; i<row_number; i++){  /*Removes the places of the operation from the grid in order to move*/
			for (int j=0; j<column_number; j++){
				if (temp_grid[i][j]==this->grid[i][j]){
					this->grid[i][j]=' ';
				}
			}
		}
		/*Here are the mov operations. x and y variables hold the new locations*/
		if(direction == 'R'){ 
			x = operators[index]->get_x();
			y = operators[index]->get_y()+move_by;
		}
		else if(direction == 'L'){
			x = operators[index]->get_x();
			y = operators[index]->get_y()-move_by;
		}
		else if(direction == 'U'){
			x = operators[index]->get_x()-move_by;
			y = operators[index]->get_y();
		}
		else if(direction == 'D'){
			x = operators[index]->get_x()+move_by;
			y = operators[index]->get_y();
		}
		else{		/*If invalid char is given, returns false.*/
			success = false;
			return success;
		}
		
		/*Calls the placement function in terms of the type of operation with the new row or column*/
		if(operators[index]->get_sign()=='+'){
			plus_opr(this->grid, row_number, column_number, temp_grid2, operators[index]->get_sign(), x, y, operators[index]->get_size());
		}
		else if(operators[index]->get_sign()=='-'){
			minus_opr(this->grid, row_number, column_number, temp_grid2, operators[index]->get_sign(), x, y, operators[index]->get_size());
		}
		else if(operators[index]->get_sign()=='x'){
			multiply_opr(this->grid, row_number, column_number, temp_grid2, operators[index]->get_sign(), x, y, operators[index]->get_size());
		}
		else if(operators[index]->get_sign()=='/'){
			division_opr(this->grid, row_number, column_number, temp_grid2, operators[index]->get_sign(), x, y, operators[index]->get_size());
		}

		/*If there is border or conflict error with the new location*/
		if(border_error){ 
			cout << "BORDER ERROR: " << operators[index]->get_sign() << " can not be moved from (" << operators[index]->get_x() << "," << operators[index]->get_y() << ") to (" 
				<< x << "," << y << ")."<< endl;
			success = false;
			
		}
		if(conflict_error){
			cout << "CONFLICT ERROR: " << operators[index]->get_sign() << " can not be moved from (" << operators[index]->get_x() << "," << operators[index]->get_y() << ") to (" 
				<< x << "," << y << ")."<< endl;
			success = false;
		}

		if (!border_error && !conflict_error){ /*If there is no border or conflict error*/
			cout << "SUCCESS: " << operators[index]->get_sign() << " moved from ("  << operators[index]->get_x() << "," << operators[index]->get_y() << ") to (" 
				<< x << "," << y << ")."<< endl;

			operators[index]->set_x(x);				/*Updates the row or column of the operation*/
			operators[index]->set_y(y);

			success = true;

			for (int i=0; i<row_number; i++){ /*And puts the operation's places to the grid*/
				for (int j=0; j<column_number; j++){
					if (temp_grid2[i][j]!=' '){
						grid[i][j]=temp_grid2[i][j];

					}
				}
			}
		}
		else{
			for (int i=0; i<row_number; i++){ /*And puts the operation's places to the grid*/
				for (int j=0; j<column_number; j++){
					if (temp_grid[i][j]!=' '){
						grid[i][j]=temp_grid[i][j];

					}
				}
			}		
		}
		index=0;
	}
	
	for(int i = 0; i < row_number; ++i) {	/*Gives back allocated spaces to memory*/
		delete[] temp_grid[i]; 
		delete[] temp_grid2[i]; 
	}
    
	delete[] temp_grid;
	delete[] temp_grid2;
	return success;
}

void OperatorGrid::print_operators(){  /*Prints all operator's center locations, sizes, and sign characters */
	for(int i=0; i<this->num_operators; i++){
		this->operators[i]->print_operator();
	}
}

OperatorGrid::~OperatorGrid(){		/*Destructor: gives all allocated spaces to the memory and prints these actions*/

	for(int i = 0; i < this->grid_rows; ++i) {
		delete[] grid[i];  
	}
	delete[] grid;

	cout << "DESTRUCTOR: GIVE BACK[" << this->grid_rows <<","<<  this->grid_cols << "] chars." << endl;	

	for(int i = 0; i < this->num_operators; ++i) {
		delete[] this->operators[i];  
	}
	cout << "DESTRUCTOR: GIVE BACK[" << this->num_operators <<"] Operators."<< endl;

}