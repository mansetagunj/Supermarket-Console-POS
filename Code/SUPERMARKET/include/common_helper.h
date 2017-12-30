#pragma once

#include <map>
#include <string>
#include <fstream>
#include <list>
#include "CError.h"
#include "CProduct.h"


#ifdef WIN32
#define FILE_PATH			..\\resources\\ 
#else
#define FILE_PATH			../resources/
#endif

#define FILE_EXTENSION		supermarket

#define TOSTR2(x)			#x
#define TOSTR(x)			TOSTR2(x)


#define CUSTOMER_FILE		TOSTR(FILE_PATH) "customer." TOSTR(FILE_EXTENSION)
#define EMPLOYEE_FILE		TOSTR(FILE_PATH) "employee." TOSTR(FILE_EXTENSION)
#define ADMIN_FILE			TOSTR(FILE_PATH) "admin." TOSTR(FILE_EXTENSION)
#define CART_FILE			TOSTR(FILE_PATH) "cart." TOSTR(FILE_EXTENSION)
#define BILLHISTORY_FILE	TOSTR(FILE_PATH) "billHistory." TOSTR(FILE_EXTENSION)
#define CUSTOMERID_FILE		TOSTR(FILE_PATH) "custid_card_bill_data." TOSTR(FILE_EXTENSION)
#define PRODUCT_FILE		TOSTR(FILE_PATH) "product." TOSTR(FILE_EXTENSION)


template<class T>
list<T> getList_FromFile(const char *inFileName) {

	if (!inFileName) {
		errClass err("File Cannot be Opened", 2);
		throw err;
	}

	list<T> li;
	T obj;
	ifstream file(inFileName);
	if (file.is_open())
		file.close();
	file.open(inFileName,std::fstream::binary);


	if (file.peek() == std::ifstream::traits_type::eof())
	{

		file.close();

		return li;
	}
	else
	{
		while (!file.eof())
		{
			file >> obj;
			li.push_back(obj);
		}

	}

	file.close();
	return li;

}


//All the classes should be ifstream and ofstream overloaded with a 
//comma separated and newline ended way
template<class T>
void putList_InFile(const char *inFileName, list<T> li) {

	if (!inFileName) {
		errClass err("File Cannot be Opened", 2);
		throw err;
	}

	list<T>::iterator itr;
	ofstream file(inFileName);
	if (file.is_open())
		file.close();
	file.open(inFileName, std::fstream::binary);

	for (itr = li.begin(); itr != li.end(); itr++)
		file << *itr;


	file.close();

}

multimap<unsigned long, Product> getCart_FromFile(const char *inFileName);

bool checkName(string x);

/*Function to check value for password*/
bool checkPass(string x);

istream& takePassword(istream &in, string s);

void set_stdinEcho(bool enable_echo);

const std::string getDateString();

const std::string getTimeString();