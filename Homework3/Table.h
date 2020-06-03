/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef	TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*This class is for tables and their orders*/

class Table{
	vector<pair<string, int> >Table1;	/*We have 5 table in this restaurant, and these vectors have two parameters as a string(dish) and a int (desired amount of dish)*/
	vector<pair<string, int> >Table2;
	vector<pair<string, int> >Table3;
	vector<pair<string, int> >Table4;
	vector<pair<string, int> >Table5;

public:

	Table();
	void takeOrders(int, string, int);	/*Pushes the orders into the corresponding table vectors*/
	
	/*It is a general method for checking the existance of the orders, It will call checkStock method to control the stock and it will call the checkout system to calculate the cost*/
	int checkOrder(int, int, string, vector<Menu*>, Stock *);	
	
	bool checkStock(vector <Restaurant*>, vector <Restaurant*>, string);	/*It checks the stock*/
	int checkoutSystem(Menu *, int, Stock*);	/*It calculates the dish cost*/
	int getCount(int);		/*Gets stock number of the item*/
};


#endif
