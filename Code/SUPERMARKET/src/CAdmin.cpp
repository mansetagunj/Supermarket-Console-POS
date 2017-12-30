

#include <string>
#include <fstream>
#include "CError.h"
#include "CAdmin.h"
#include "common_helper.h"

//ADMIN CLASS

unsigned Admin::getAdminId()
{
	return adminId;
}

string Admin::getAdminName()
{
	return adminName;
}

string Admin::getPassword()
{
	return password;
}

void Admin::setAdminName(string inName)
{
	adminName = inName;
}

ostream& operator<<(ostream &out, Admin &inAdmin) {

	out << "Id: " << inAdmin.adminId << " Name: " << inAdmin.adminName << endl;
	return out;

}

ofstream& operator<<(ofstream &fout, Admin &inAdmin) {

	//string gibberishPass;
	for each (char a in inAdmin.password)
	{
		a = a - 25;
	}
	fout << "\n" << inAdmin.adminId << " " << inAdmin.adminName << " " << inAdmin.password;
	return fout;
}

ifstream& operator>>(ifstream &fin, Admin &inAdmin) {

	//string gibberishPass;
	fin >> inAdmin.adminId >> inAdmin.adminName >> inAdmin.password;
	for each (char a in inAdmin.password)
	{
		a = a + 25;
	}
	return fin;

}

bool Admin::operator==(const Admin inAdmin)
{

	return adminId == inAdmin.adminId;
}

void Admin::setAdminPassword(string inPass) {

	if (checkPass(inPass))
	{
		password = inPass;
	}
	else
	{
		errClass err("Password Incorrect. Password Requirements: >6 chars(alphanumeric)", -88);
		throw err;
	}
}

void Admin::setAdminId(unsigned inId) {

	if (inId>999 && inId<10000) {
		adminId = inId;
	}
	else
	{
		errClass err("Admin ID Incorrect.", -89);
		throw err;
	}

}