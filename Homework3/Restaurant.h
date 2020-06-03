/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*This class is a general class for all Type classes*/

class Restaurant{
	
	float taxRate;	/*Statically the tip and tax rates are defined*/
	float tip;

public:

	Restaurant();
	virtual void addIngredients(string Name, int ItemCount, float Price)=0;	/*This method fills the types features*/
	virtual string getName()=0;				/*Gets the name of the item*/
	virtual int getItemCount() = 0;			/*Gets the item count*/
	virtual float getPrice() = 0;			/*Gets the item price*/
	virtual void setItemCount(int) = 0;		/*Updates the item count*/

	float getTaxRate(float);			/*Calculates the Tax rate*/
	float getTip(float);				/*Calculates the tip*/
	float calculateTotalCost(float);	/*Calculates the totalCost*/
};


#endif
