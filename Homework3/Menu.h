/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*This class is for each menu item.*/

class Menu{

	string dishName;	/*Holds the dish name*/
	
	/*These vector keeps the menu item's ingredient*/
	vector <Restaurant*> type1Ingredients;	/*I use 3 separate vectors for each type*/
	vector <Restaurant*> type2Ingredients;
	vector <Restaurant*> type3Ingredients;

public:

	Menu(string);
	void addType1(Restaurant *);		/*These methods add the ingredients into the corresponding vectors*/
	void addType2(Restaurant *);
	void addType3(Restaurant *);

	string getDishName();				/*For getting dish name*/
	vector <Restaurant*> getType1();	/*For getting vectors*/
	vector <Restaurant*> getType2();
	vector <Restaurant*> getType3();
};


#endif
