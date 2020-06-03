/* @Author
* Student Name: Cansu Yanık
* Student ID : 150170704
* Date: 09.05.2019 */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>

#include "Type1.h"
#include "Type2.h"
#include "Type3.h"
#include "Stock.h"
#include "Menu.h"
#include "Table.h"
#include "Restaurant.h"
using namespace std;


Restaurant::Restaurant(){
	taxRate = 8.0;	/*Statically the tip and tax rates are defined*/
	tip = 15.0;
}
float Restaurant::getTip(float totalCost){	/*Calculates the tip*/
	return totalCost * this->tip/100.0;

}
float Restaurant::getTaxRate(float totalCost){	/*Calculates the Tax rate*/
	return totalCost * this->taxRate/100.0;

}
float Restaurant::calculateTotalCost(float totalCost){	/*Calculates the totalCost*/
	return totalCost + this->getTaxRate(totalCost) + this->getTip(totalCost);

}
Table::Table(){}
int Table::checkOrder(int tableNumber, int dishCount, string dishName, vector<Menu* >menu, Stock *stock){
	/*It is a general method for checking the existance of the orders, It will call checkStock method to control the stock and it will call the checkout system to calculate the cost*/
	bool dishExistance = false;
	int dishIndex = 0;
	int count = 0;
	int cost = 0;
	
	/*Firstly, I am trying to find the dish from the menu catalog*/
	for(unsigned int i =0; i< menu.size(); i++){
		if(dishName == menu.at(i)->getDishName()){
			dishExistance = true;
			dishIndex = i;
			break;
		}
	}
	if(dishExistance==false){	/*If we do not find the dish inside the menu, it means that we do not have this kind of dish*/
		string error = "We don't have enough ";
		error.append(dishName);
		throw error;
	}
	else{	/*Now check the stock*/
		for(int i=0; i<dishCount; i++){	/*Check the wanted number of the dish*/
			
			try{		/*Check the exitance of the order, If it is not, program will throw the error message*/
				
				/*Checks whether all type1 ingredients are existed, call the check stock function*/
				dishExistance = this->checkStock(stock->getType1(), menu.at(dishIndex)->getType1(), dishName);
				/*If we have all type1s, now we can check for type2s*/
				if(dishExistance)
					dishExistance = this->checkStock(stock->getType2(), menu.at(dishIndex)->getType2(), dishName);
					
				/*If we have all type2s, now we can check for type3s*/
				if(dishExistance)
					dishExistance = this->checkStock(stock->getType3(), menu.at(dishIndex)->getType3(), dishName);
			}
			catch(const string result){		/*If any ingredient is not exist, the error message will be thrown.*/
				cout << result << endl;
				dishExistance = false;
				break;
			}				
			count++;
		}
		/*There can be two different situations. First, the whole number of order may not be existed.*/
		/*That's why I need a count variable to know how many number of orders will be served*/
		/*Second, we may have a few of them.*/
		/*Even dishExistance is false, if the count greater than 0, it means that we can serve some amount of order*/
		
		if(dishExistance || count>0){
			cost = checkoutSystem(menu.at(dishIndex),count,stock);	
			cout << count << " " <<  dishName << " cost: " << cost << endl;
		}
	}
	return cost;
}
bool Table::checkStock(vector <Restaurant*> Type, vector <Restaurant*> Ingredient, string dishName){
	bool stockExistance = true;
	int menuIndex = 0;
	int stockIndex = 0;
	int newItemCount = 0;

	/*This methods takes the type vector(1,2 or3), and the ingredient vector with the same type*/
	/*For each item, the method finds the same item from the stock vector and gets the item count*/
	for(unsigned int j=0; j<Ingredient.size(); j++){
		for(unsigned int k=0; k<Type.size(); k++){
			if(Ingredient.at(j)->getName() == Type.at(k)->getName()){
				menuIndex = j;
				stockIndex = k;
				break;
			}
		}
		/*If given menu item count greater than the stock count, it means that we have not enough item for this dish*/
		if(Ingredient.at(menuIndex)->getItemCount() > Type.at(stockIndex)->getItemCount()){
			stockExistance = false;		
		}
		else{	/*Else, we subtract this amount from the stock count, and update the stock count*/
			newItemCount =Type.at(stockIndex)->getItemCount() - Ingredient.at(menuIndex)->getItemCount();
			Type.at(stockIndex)->setItemCount(newItemCount);
		}
	}
	if (!stockExistance){			/*if we do not have any ingredient of the order, the error message will be thrown.*/
		string error = "We don't have enough ";
		error.append(dishName);
		throw error;
	}
	return stockExistance;
}

int Table::checkoutSystem(Menu* menuItem, int count, Stock * stock){
	/*This method calculates the cost of the dish by adding all ingredients one by one*/
	float cost = 0.0;
	string item, item2;
	/*Dish can be have all three types ingredients, Therefore, I will search them separately*/
	for(unsigned int j=0; j<menuItem->getType1().size(); j++){
		for(unsigned int k=0; k<stock->getType1().size(); k++){	/*When the order and the stock ingredients matches, I will calculate the cost*/
			if(menuItem->getType1().at(j)->getName() == stock->getType1().at(k)->getName()){
				cost = cost + stock->getType1().at(k)->getPrice() * menuItem->getType1().at(j)->getItemCount();
				break;
			}
		}
	}
	/*Same procedure is applied*/
	for(unsigned int j=0; j<menuItem->getType2().size(); j++){
		for(unsigned int k=0; k<stock->getType2().size(); k++){
			if(menuItem->getType2().at(j)->getName() == stock->getType2().at(k)->getName()){
				cost = cost + stock->getType2().at(k)->getPrice() * menuItem->getType2().at(j)->getItemCount();
				break;
			}
		}
	}
	/*Since sometimes I suffer from Carriage Return (\r) character, I check the items normally and also check them by the erasing this last character.*/
	for(unsigned int j=0; j<menuItem->getType3().size(); j++){
		item = menuItem->getType3().at(j)->getName();		
		for(unsigned int k=0; k<stock->getType3().size(); k++){
			item = menuItem->getType3().at(j)->getName();
			item2 = stock->getType3().at(k)->getName();
			if(item == item2 || item.erase(item.size()-1,1) == item2){
				cost = cost + stock->getType3().at(k)->getPrice() * menuItem->getType3().at(j)->getItemCount();
				break;
			}
		}
	}
	return cost * count; /*Multiply cost with the wanted amount of dish*/
}
void Table::takeOrders(int tableNumber, string dishName, int dishCount){
	/*This method pushes the orders into the corresponding table vectors*/
	if(tableNumber == 1){
		Table1.push_back(std::make_pair(dishName,dishCount));
	}
	if(tableNumber == 2){
		Table2.push_back(std::make_pair(dishName,dishCount));
	}
	if(tableNumber == 3){
		Table3.push_back(std::make_pair(dishName,dishCount));
	}
	if(tableNumber == 4){
		Table4.push_back(std::make_pair(dishName,dishCount));
	}
	if(tableNumber == 5){
		Table5.push_back(std::make_pair(dishName,dishCount));
	}
}

Type1::Type1(){}
Type2::Type2(){}
Type3::Type3(){}

void Type1::addIngredients(string Name, int ItemCount, float Price){
	/*This method fills the Type1's features*/
	this->name = Name;
	this->weight = ItemCount;
	this->price = Price;
}
string Type1::getName(){	/*Gets the name of the type1 item*/
	return this->name;
}
int Type1::getItemCount(){	/*Gets the type1 item count*/
	return this->weight;
}
float Type1::getPrice(){	/*Gets the type1 item price*/
	return this->price;
}
void Type1::setItemCount(int newItemCount){		/*Updates the type1 item count*/
	this->weight = newItemCount;
}

void Type2::addIngredients(string Name, int ItemCount, float Price){
	/*This method fills the Type2's features*/
	this->name = Name;
	this->number = ItemCount;
	this->price = Price;
}
string Type2::getName(){	/*Gets the name of the type2 item*/
	return this->name;
}
int Type2::getItemCount(){	/*Gets the type2 item count*/
	return this->number;
}
float Type2::getPrice(){ 	/*Gets the type2 item price*/
	return this->price;
}
void Type2::setItemCount(int newItemCount){ /*Updates the type2 item count*/
	this->number = newItemCount;
}

void Type3::addIngredients(string Name, int ItemCount, float Price){
	/*This method fills the Type3's features*/
	this->name = Name;
	this->milliliter = ItemCount;
	this->price = Price;
}
string Type3::getName(){	/*Gets the name of the type3 item*/
	return this->name;
}
int Type3::getItemCount(){	/*Gets the type3 item count*/
	return this->milliliter;
}
float Type3::getPrice(){	/*Gets the type3 item price*/
	return this->price;
}
void Type3::setItemCount(int newItemCount){ /*Updates the type3 item count*/
	this->milliliter = newItemCount;
}
Stock::Stock(){

}
void Stock::addStockType1(Restaurant *type1){
	/*Pushes type1 item into the corresponding vector*/
	this->type1Stock.push_back(type1);
}
void Stock::addStockType2(Restaurant *type2){
	/*Pushes type2 item into the corresponding vector*/
	this->type2Stock.push_back(type2);
}
void Stock::addStockType3(Restaurant *type3){
	/*Pushes type3 item into the corresponding vector*/
	this->type3Stock.push_back(type3);
}

vector <Restaurant*> Stock::getType1(){	/*Gets the type1 stock vector*/
	return this->type1Stock;
}
vector <Restaurant*> Stock::getType2(){	/*Gets the type2 stock vector*/
	return this->type2Stock;
}
vector <Restaurant*> Stock::getType3(){	/*Gets the type3 stock vector*/
	return this->type3Stock;
}

Menu::Menu(string dishName){ 	/*Initializes the dish name*/
	this->dishName = dishName;
}
void Menu::addType1(Restaurant *type1){ /*Pushes the type1 ingredient into corresponding menu vector*/
	this->type1Ingredients.push_back(type1);
}
void Menu::addType2(Restaurant *type2){	/*Pushes the type2 ingredient into corresponding menu vector*/
	this->type2Ingredients.push_back(type2);
}
void Menu::addType3(Restaurant *type3){	/*Pushes the type3 ingredient into corresponding menu vector*/
	this->type3Ingredients.push_back(type3);
}
string Menu::getDishName(){	/*Gets the dish name*/
	return this->dishName;
}
vector <Restaurant*> Menu::getType1(){	/*Gets the type1 menu vector*/
	return this->type1Ingredients;
}
vector <Restaurant*> Menu::getType2(){	/*Gets the type2 menu vector*/
	return this->type2Ingredients;
}
vector <Restaurant*> Menu::getType3(){	/*Gets the type3 menu vector*/
	return this->type3Ingredients;
}
int Table::getCount(int tableNumber){	/*Gets the count of the orders of the given table number*/
	if(tableNumber==1)
		return this->Table3.at(Table3.size()-1).second;
	if(tableNumber==2)
		return this->Table3.at(Table3.size()-1).second;
	if(tableNumber==3)
		return this->Table3.at(Table3.size()-1).second;
	if(tableNumber==4)
		return this->Table4.at(Table4.size()-1).second;
	if(tableNumber==5)
		return this->Table5.at(Table5.size()-1).second;
	return 0;
};
int main(){
	
	ifstream stock_file;		/*File variables*/
	ifstream menu_file;
	ifstream order_file;

	/***********************Stock File Reading Process****************************/
	
	Restaurant *myRestaurant;				/*Creates general class for types objects*/
	Stock *restaurantStock = new Stock();	/*Create a stock object*/

	stock_file.open( "stock.txt" );			/*Opens file*/
	if(!stock_file){						/*If the file cannot be opened*/
		cerr << "Cannot open stock file" << endl;
		exit(1);
	}
	
	string name;		/*Holds the item names*/
	int type;			/*Holds the item's type*/
	int itemCount;		/*Holds the total amount of items in the stock*/
	float price;		/*Holds the item's price*/
	string line;		/*For reading items line by line*/
	string item;		/*For holding the extracted items */
	
	getline(stock_file, line);		/*Get the title*/
	while ( getline(stock_file, line) )	{	/*Reads until file ends*/
		
		istringstream iss(line);		/*Take string until tab comes (It is item name)*/
		getline(iss, name, '\t');

		getline(iss, item, '\t');		/*Second item will be the type*/
		type = atoi(item.c_str());		/*Convert it to integer*/

		getline(iss, item, '\t');		/*Third item will be item count*/
		itemCount = atoi(item.c_str()); /*Convert it to integer*/

		getline(iss, item, '\t');		/*And the last item will be price of this item*/
		price = atof(item.c_str());		/*Convert it to integer*/

		
		/*Depends on the item types, creates an item object. Fill the stock object with this item object(item's name, count and price)*/
		if (type == 1){					
			myRestaurant = new Type1();
			myRestaurant->addIngredients(name, itemCount, price);
			restaurantStock->addStockType1(myRestaurant);
		}
		if (type == 2){
			myRestaurant = new Type2();
			myRestaurant->addIngredients(name, itemCount, price);
			restaurantStock->addStockType2(myRestaurant);
		}
		if (type == 3){
			myRestaurant = new Type3();
			myRestaurant->addIngredients(name, itemCount, price);
			restaurantStock->addStockType3(myRestaurant);	
		}
	}
	/***********************Menu File Reading Process****************************/
	
	menu_file.open( "menu.txt" );		/*Opens file*/
	if(!menu_file){						/*If the file cannot be opened*/
		cerr << "Cannot open menu file" << endl;
		exit(1);
	}
	
	vector <Menu *> myMenu;		/*This is our Menu catalog, I will save the menu items into this vector*/
	Restaurant *ingredientType;	/*Class for ingredients, at the end of the loop, it will be pushed into the Menu vector*/
	string ingredient;			/*Holds ingredients of the dish*/
	int number;					/*Holds the amounts of the ingredients*/
	item="";					/*These variables for separating the ingredients*/
	string item2;			
	type=2;						/*I gave 2 as a default value to the type for ingredient's types*/

	getline(menu_file, line);					/*Gets the title*/
	while ( getline(menu_file, line) )	{		/*Reads line by line*/
		
		
		for(size_t i = 0; i<line.length(); ++i){	/*To be able to separate ingredients bu using comma, firstly I erase the space after the comma, add * and ;*/
			if(line[i] == ','){						/*It look something like this:  massala chicken	  250 gram chicken*;,3 onion*;,...*/
				line.erase(++i, 1);					/*I will explain my method below.*/
				line.insert(i-1, "*");	
				line.insert(i++, ";");		
			}
		}
		istringstream iss(line);
		getline(iss, name, '\t');			/*Extract the string until tab comes, this is dishname*/

		Menu *menuItem = new Menu(name);	/*We can create a new menu item, now we need to fill it with its ingredients*/
		
		while ( getline(iss, ingredient, ',') ){	/*Reads until line end comes*/
			
			istringstream iss2(ingredient);		/*By using space, I can take the amount of ingredients*/
			getline(iss2, item, ' ');
				
			number = atoi(item.c_str());		/*Converts it to integer*/
		
			getline(iss2, item, ';');			/*Now, I take the rest of the strings between the number and the ";" character. Example:  "gram chicken*" */
			item2 = item;						/*And I save this string because it may not have gram or ml like "onion" */
			
			istringstream iss3(item);			/*Read the string until space comes. Example: "gram" */
			getline(iss3, item, ' ');
			istringstream iss4(item);			

			if(item == "gram" || item ==  "ml"){	/*If we have gram or ml, we will skip these but we can use them to determine the type of the ingredient*/
				if(item == "gram")
					type = 1;
				else
					type = 3;						/*(After extracting the gram or ml we have ingredient and the * character like "chicken*" )*/
				getline(iss3, item, '*');			/*Now I can read the ingredient. Example: "chicken" */
			}										
			else{									/*If this item is not gram or ml, it means that its type is 2*/
				type = 2;							/*I can read the ingredient. Example: "onion" */
				getline(iss4, item, '*');
				item=item2.erase(item2.length()-1,1);				
			}
				
			if (item == "N/" || item == "N/A"){		/*If the item is "N/A", I decided to also save the dishname as its ingredient*/
				item = name;
				number = 1;
				type = 2;
			}
			/*After extracting the ingredients, depends oh their types, I create type objects with their names and amounts*/
			/*Then add these ingredient type objects to types storages of their own menuItem objects*/
			if(type == 1){	
				ingredientType = new Type1();
				ingredientType->addIngredients(item, number, 0);
				menuItem->addType1(ingredientType);
			}
			if(type == 2){
				ingredientType = new Type2();
				ingredientType->addIngredients(item, number, 0);
				menuItem->addType2(ingredientType);
			}
			if(type == 3){
				ingredientType = new Type3();
				ingredientType->addIngredients(item, number, 0);
				menuItem->addType3(ingredientType);
			}
		}
		myMenu.push_back(menuItem);		/*After filling the dish and its ingredients, now I can push this dish into the menu catalog*/
	}
	
	/***********************Order File Reading Process****************************/
	
	order_file.open( "order.txt" );			/*Opens file*/
	if(!order_file){							/*If the file cannot be opened*/
		cerr << "Cannot open order file" << endl;
		exit(1);
	}
	
	Table *Tables = new Table(); 	/*Creates a Table object*/
	int menuItemCount;				/*Holds the wanted menu item count*/
	int cost = 0;					/*Holds the menu item cost*/
	float totalCost;				/*Holds the total table cost*/
	
	/*Since I was forced to read the order file line by line, I decided to read this file sometimes word by word, sometimes char by char*/
	
	while (order_file >> line && !order_file.eof()){	/*Read until file ends*/
		
		/*Takes first word (Table number)*/
		
		totalCost = 0;
		cout << line << " ordered:"<<endl;		/*Prints the Table*/
		name = line;
						
		order_file >> number;				/*Takes the number of order*/
		
		for (int i=0; i<number; i++){
			item = "";
			order_file >> menuItemCount;	/*Takes the number of menu item*/
			line = order_file.get();
			line = order_file.get();
			while (line!="\n" && !order_file.eof()){	/*get the chars until end of line or file comes and save it to item*/
				item = item + line;
				line = order_file.get();
			}
			
			/*While reading from this file, depends on the file format, last line can be read in a different type. After a long search, I found that*/
			/* there is a control character called Carriage Return (\r). Since sometimes I suffer from this character, I check existance of this in order to */
			/* get rid of it. If the item has this character, I will erase this last character.*/
			 
			if(item[item.size()-1] == '\n' || item[item.size()-1] == EOF || item[item.size()-1] == '\r'){
				item.erase(item.size()-1,1);
			}
		
			try{	/*Check the exitance of the order, If it is not, program will throw the error message*/
				
				if(name == "Table1")
					cost = Tables->checkOrder(1, menuItemCount, item, myMenu, restaurantStock);
				if(name == "Table2")
					cost = Tables->checkOrder(2, menuItemCount, item, myMenu, restaurantStock);
				if(name == "Table3")
					cost = Tables->checkOrder(3, menuItemCount, item, myMenu, restaurantStock);
				if(name == "Table4")
					cost = Tables->checkOrder(4, menuItemCount, item, myMenu, restaurantStock);
				if(name == "Table5")
					cost = Tables->checkOrder(5, menuItemCount, item, myMenu, restaurantStock);
					
				totalCost = totalCost + cost;	
			}
			catch(const string result){		/*If the order is not exist in the menu*/
				cout << result << endl;
			}		
		}
		cout << "Tip is " << myRestaurant->getTip(totalCost) << endl;	/*After getting the cost, I can calculate tip and the total cost and prints them.*/
		cout << "Total cost: " << myRestaurant->calculateTotalCost(totalCost) << " TL" << endl;
		cout << "**************************" << endl;
	}		
	
	/*Updates stock file (Writes new stocks to the file)*/
	ofstream stock_file2;
	stock_file2.open ( "stock.txt" );

	stock_file2 << "Name" << "\t" << "Type" << "\t" << "ItemCount" << "\t" << "Price" << endl;
	for (unsigned int i = 0; i < restaurantStock->getType1().size(); i++){
		stock_file2 << restaurantStock->getType1().at(i)->getName() << "\t" << "1" << "\t"
					<<  restaurantStock->getType1().at(i)->getItemCount() << "\t" <<  restaurantStock->getType1().at(i)->getPrice() << endl;
	}
	for (unsigned int i = 0; i < restaurantStock->getType2().size(); i++){
		stock_file2 << restaurantStock->getType2().at(i)->getName() << "\t" << "2" << "\t"
			<< restaurantStock->getType2().at(i)->getItemCount() << "\t" << restaurantStock->getType2().at(i)->getPrice() << endl;
	}
	for (unsigned int i=0; i<restaurantStock->getType3().size(); i++){
		stock_file2 << restaurantStock->getType3().at(i)->getName() << "\t" << "3" << "\t"
			<< restaurantStock->getType3().at(i)->getItemCount() << "\t" << restaurantStock->getType3().at(i)->getPrice() << endl;
	}
	
	/*Closes the files*/
	stock_file2.close();	
	stock_file.close();
	menu_file.close();

	return 0;
}
