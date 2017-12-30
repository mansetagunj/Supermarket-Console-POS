#pragma once

#include <string>
#include <fstream>

class Admin {

public:
	Admin() {}
	Admin(unsigned inAdminId, string inAdminName, string inAdminPasswd) : adminId(inAdminId), adminName(inAdminName), password(inAdminPasswd) {}
	unsigned getAdminId();
	string getAdminName();
	string getPassword();
	void setAdminName(string inName);
	void setAdminId(unsigned);
	void setAdminPassword(string);
	friend ostream& operator<<(ostream&, Admin&);
	friend ofstream& operator<<(ofstream&, Admin&);
	friend ifstream& operator>>(ifstream&, Admin&);
	bool operator==(const Admin);

private:
	unsigned adminId;
	string adminName;
	string password;
};