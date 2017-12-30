#pragma once

#include <string>
#include <fstream>

#include "CCategory.h"

using namespace std;


class Product			//Product Class 
{
public:					//Public data members and functions
	Product() {}
	void setProductId(unsigned long);
	void setProductName(string);
	void setProductCost(double);
	void setProductExpDate(string);
	void setProductMfgDate(string);
	void setProductAvailStock(unsigned);
	void setProductCategory(unsigned, string);
	string getProductName();
	unsigned long getProductId();
	double getProductCost();
	string getProductExpDate();
	string getProductMfgDate();
	unsigned getProductAvailStock();
	string getProductCategoryName();
	unsigned getProductCategoryId();
	bool operator==(const Product);
	friend ostream& operator<<(ostream &, Product &);
	friend ofstream& operator<<(ofstream &, Product &);
	friend ifstream& operator>>(ifstream &, Product &);


protected:				//Protected data members and functions

	unsigned long productId;
	unsigned availStock;


private:				//Private data members and functions
	string productName;
	double cost;
	string expDate;
	string mfgDate;
	Category category;

};