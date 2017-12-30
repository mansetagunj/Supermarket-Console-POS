

#include <fstream>
#include <string>
#include "CCategory.h"

using namespace std;

/********************************************************************************************/
/*Getters & Setters for Category class*/
void Category::setCategoryId(unsigned cId)
{
	catId = cId;
}
void Category::setCategoryName(string cName)
{
	catName = cName;
}
string Category::getCategoryName()
{
	return catName;
}

unsigned Category::getCategoryId()
{
	return catId;
}

ostream& operator<<(ostream &out, Category &inCat) {

	out << "Category Id: " << inCat.catId << " Name: " << inCat.catName;
	return out;
}

ofstream& operator<<(ofstream &fout, Category &inCat) {

	fout << "\n" << inCat.catId << " " << inCat.catName;
	return fout;

}
ifstream& operator>>(ifstream &fin, Category &inCat) {

	fin >> inCat.catId >> inCat.catName;
	return fin;

}
