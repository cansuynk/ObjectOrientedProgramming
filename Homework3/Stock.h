/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#ifndef STOCK_H
#define STOCK_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*This class is for restaurant stock*/

class Stock{

	vector <Restaurant*> type1Stock;	/*Restaurant stock has 3 different storages for each type*/
	vector <Restaurant*> type2Stock;
	vector <Restaurant*> type3Stock;


public:
	Stock();
	void addStockType1(Restaurant *);	/*These methods add the stock items into the corresponding vectors*/
	void addStockType2(Restaurant *);
	void addStockType3(Restaurant *);

	vector <Restaurant*> getType1();	/*For getting vectors*/
	vector <Restaurant*> getType2();
	vector <Restaurant*> getType3();
};


#endif
