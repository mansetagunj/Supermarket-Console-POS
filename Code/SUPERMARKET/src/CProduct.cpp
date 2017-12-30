
#include <fstream>
#include <string>
#include "CProduct.h"
#include "CError.h"
#include "common_helper.h"

using namespace std;

//helper function 
//Function to check Product Name(To accept string as well as combination of string and numbers)
bool checkProdName(string x)
{
	int num = 0, alph = 0;
	if (x.length()>2)
	{
		for (int i = 0; i<x.length(); i++)
		{
			if (isalpha(x[i]))
			{
				alph++;
				continue;
			}
			else if (isdigit(x[i]))
			{
				num++;
				continue;
			}
			else
				return 0;
		}
		if ((num>0 && alph>0) || (alph>0))
			return 1;
		else return 0;
	}
	else
		return 0;

}

/*Getters & Setters for Product class*/

void Product::setProductId(unsigned long pId)
{
	if (pId>99999 && pId<1000000)
	{
		productId = pId;
	}
	else
	{
		errClass err("Invalid Product Id", -99);
		throw err;
	}
}

void Product::setProductName(string pName)
{

	if (checkProdName(pName))
	{
		productName = pName;
	}
	else
	{
		errClass err("Invalid Product Name", -98);
		throw err;
	}
}

void Product::setProductCost(double pCost)
{
	if (pCost>0)
	{
		cost = pCost;
	}
	else
	{
		errClass err("Invalid Cost", -97);
		throw err;
	}
}

void Product::setProductExpDate(string eDate)
{
	expDate = eDate;
}

void Product::setProductMfgDate(string mDate)
{
	mfgDate = mDate;
}

void Product::setProductAvailStock(unsigned aStock)
{
	if (aStock >= 0)
	{
		availStock = aStock;
	}
	else
	{
		errClass err("Invalid Stock ", -96);
		throw err;
	}

}

void Product::setProductCategory(unsigned categoryId, string categoryName)
{
	if (categoryId>99999 && categoryId<1000000)
	{
		category.setCategoryId(categoryId);
	}
	else
	{
		errClass err("Invalid Category Id ", -95);
		throw err;
	}
	if (checkName(categoryName))
	{
		category.setCategoryName(categoryName);
	}
	else
	{
		errClass err("Invalid Category Name ", -94);
		throw err;
	}
}

unsigned long Product::getProductId()
{
	return productId;
}
string Product::getProductName()
{
	return productName;
}

double Product::getProductCost()
{
	return cost;
}

string Product::getProductExpDate()
{
	return expDate;
}

string Product::getProductMfgDate()
{
	return mfgDate;
}

unsigned Product::getProductAvailStock()
{
	return availStock;
}

string Product::getProductCategoryName()
{
	return category.getCategoryName();
}

unsigned Product::getProductCategoryId()
{
	return category.getCategoryId();
}

bool Product::operator==(const Product inProd) {

	return (productId == inProd.productId);

}


ostream& operator<<(ostream &out, Product &inProd) {

	out << "\n\tProduct Id: " << inProd.productId << "\tProduct Name: " << inProd.productName << "\n\tProduct Cost: " << inProd.cost;
	out << "\tProduct Category: " << inProd.category.getCategoryName() << "\n\tProduct Available Stock: " << inProd.availStock;
	out << "\n\tMfg Date: " << inProd.mfgDate << "\tExp Date: " << inProd.expDate << endl;
	return out;
}

ofstream& operator<<(ofstream &fout, Product &inProd) {

	fout << "\n" << inProd.productId << " " << inProd.productName << " " << inProd.cost << " " << inProd.category.getCategoryId() << " " << inProd.category.getCategoryName();
	fout << " " << inProd.expDate << " " << inProd.mfgDate << " " << inProd.availStock;
	return fout;

}
ifstream& operator>>(ifstream &fin, Product &inProd) {

	string catname;
	unsigned catid;
	fin >> inProd.productId >> inProd.productName >> inProd.cost >> catid >> catname;
	fin >> inProd.expDate >> inProd.mfgDate >> inProd.availStock;
	inProd.category.setCategoryId(catid);
	inProd.category.setCategoryName(catname);
	return fin;

}