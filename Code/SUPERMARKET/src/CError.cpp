
#include "CError.h"
#include <iostream>

using namespace std;

//ERROR CLASS
void errClass::display()
{
	cout << "\n\tError: " << errmsg << " Error Code: " << errcode << endl;
}