#pragma once

#include <string>
#include <fstream>

using namespace std;

class Employee						        //Employee class
{
public:
	Employee() {}				//constructor

	void setEmployeeId(unsigned long);		//setters
	void setEmployeeName(string);
	void setPassword(string);
	unsigned long getEmployeeId();			//getters
	string getEmployeeName();
	string getEmployeePassword();
	friend ostream& operator<<(ostream&, Employee&);
	friend ofstream& operator<<(ofstream&, Employee&);
	friend ifstream& operator>>(ifstream&, Employee&);
	bool operator==(const Employee);
	//~Employee(){}
private:
	unsigned long EmployeeId;
	string EmployeeName;
	string EmployeePassword;
};