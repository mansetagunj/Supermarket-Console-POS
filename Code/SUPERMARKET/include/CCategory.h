#pragma once

#include <string>
#include <fstream>
using namespace std;


class Category		//Category class
{
public:				//Public members of class category
	Category() {}
	string getCategoryName();
	unsigned getCategoryId();
	void setCategoryId(unsigned);
	void setCategoryName(string);
	friend ostream& operator<<(ostream &, Category &);
	friend ofstream& operator<<(ofstream &, Category &);
	friend ifstream& operator>>(ifstream &, Category &);

private:			//Private members of class category
	unsigned catId;
	string catName;
};