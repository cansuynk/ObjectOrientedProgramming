/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef TYPE1_H
#define TYPE1_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Restaurant.h"
using namespace std;

class Type1: public Restaurant{

	string name;	/*Type1 features*/
	int weight;
	float price;

public:

	Type1();
	void addIngredients(string Name, int ItemCount, float Price);	/*This method fills the type1 features*/
	string getName();			/*Gets the name of the type1 item*/
	int getItemCount();			/*Gets the type1 item count*/
	float getPrice();			/*Gets the type1 item price*/
	void setItemCount(int);		/*Updates the type1 item count*/
	
};


#endif
