#pragma once

#include <string>
using namespace std;


//Error class
class errClass {

public:
	errClass() {}
	errClass(string inerrmsg, int inerrcode) :errmsg(inerrmsg), errcode(inerrcode) {}
	void display();

private:
	string errmsg;
	int errcode;

};