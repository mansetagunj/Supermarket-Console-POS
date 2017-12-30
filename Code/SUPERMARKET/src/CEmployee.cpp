
#include <fstream>
#include <string>
#include "CEmployee.h"
#include "CError.h"
#include "common_helper.h"
#include <algorithm>

//EMPLOYEE CLASS

void Employee::setEmployeeId(unsigned long EmpId)		//setters for Employee
{


	if ((EmpId>9999) && (EmpId<100000))
	{
		EmployeeId = EmpId;
	}
	else
	{
		errClass err("InValid Employee Id", -99);
		throw err;
	}
}

void Employee::setEmployeeName(string EmpName)
{
	if (checkName(EmpName))
	{
		EmployeeName = EmpName;
	}
	else
	{
		errClass err("InValid Employee Name", -99);
		throw err;
	}
}

void Employee::setPassword(string EmpPwd)
{

	if (checkPass(EmpPwd))
	{
		EmployeePassword = EmpPwd;
	}
	else
	{
		errClass err("Invalid Employee Password", -99);
		throw err;
	}

}

unsigned long Employee::getEmployeeId()					//getters for Employee
{
	return EmployeeId;
}

string Employee::getEmployeeName()
{
	return EmployeeName;
}

string Employee::getEmployeePassword()
{
	return EmployeePassword;
}

bool Employee::operator==(const Employee emp) {

	return (EmployeeId == emp.EmployeeId);

}

ostream& operator<<(ostream& out1, Employee &emp)
{
	out1 << "\nEmployee ID :" << emp.EmployeeId;
	out1 << "\nEmployee Name :" << emp.EmployeeName;
	out1 << "\nEmployee Password :" << emp.EmployeePassword;
	return out1;
}

//File Handling for Employee

//writting to the file

ofstream& operator<<(ofstream &fout, Employee &OfEmp)
{
	//string gibberishPass;
	for_each(OfEmp.EmployeePassword.begin(), OfEmp.EmployeePassword.end(), [](char &a){ a = a - 25; });
	fout << "\n" << OfEmp.EmployeeId << " " << OfEmp.EmployeeName << " " << OfEmp.EmployeePassword;
	return fout;
}


//Reading from the file

ifstream& operator>>(ifstream &fin, Employee &IfEmp)
{
	fin >> IfEmp.EmployeeId >> IfEmp.EmployeeName >> IfEmp.EmployeePassword;
	//string gibberishPass;
	for_each(IfEmp.EmployeePassword.begin(), IfEmp.EmployeePassword.end(), [](char &a) { a = a + 25; });
	return fin;
}