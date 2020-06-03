/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef TYPE2_H
#define TYPE2_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Restaurant.h"
using namespace std;

class Type2: public Restaurant{

	string name;	/*Type2 features*/
	int number;
	float price;

public:

	Type2();
	void addIngredients(string Name, int ItemCount, float Price);	/*This method fills the type2 features*/
	string getName();			/*Gets the name of the type2 item*/
	int getItemCount();			/*Gets the type2 item count*/
	float getPrice();			/*Gets the type2 item price*/
	void setItemCount(int);		/*Updates the type2 item count*/
};


#endif
