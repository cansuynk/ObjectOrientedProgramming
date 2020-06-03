/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef TYPE3_H
#define TYPE3_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Restaurant.h"
using namespace std;

class Type3: public Restaurant{

	string name;	/*Type3 features*/
	int milliliter;
	float price;

public:

	Type3();
	void addIngredients(string Name, int ItemCount, float Price);	/*This method fills the type3 features*/
	string getName();			/*Gets the name of the type3 item*/
	int getItemCount();			/*Gets the type3 item count*/
	float getPrice();			/*Gets the type3 item price*/
	void setItemCount(int);		/*Updates the type3 item count*/
};


#endif
