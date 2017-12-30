#include "CBill.h"
#include "CError.h"
#include "common_helper.h"
#include <iostream>

using namespace std;

/*Getters & Setters for Bill class*/

Bill::Bill()
{

	unsigned long BILLNUM = 1000000000;

	ofstream OFcustIdFile;
	ifstream  IFcustIdFile;
	IFcustIdFile.open(CUSTOMERID_FILE, std::fstream::binary);
	unsigned long CustId = 0;
	unsigned long long cardNumber = 0;

	while (!IFcustIdFile.eof())
	{
		IFcustIdFile >> CustId >> cardNumber >> billNum;
	}

	IFcustIdFile.close();

	OFcustIdFile.open(CUSTOMERID_FILE, std::fstream::binary);
	if (billNum >= BILLNUM)
		OFcustIdFile << CustId << " " << cardNumber << " " << ++billNum;
	else
	{
		billNum = BILLNUM;
		OFcustIdFile << CustId << " " << cardNumber << " " << billNum;
	}

	OFcustIdFile.close();
}

void Bill::setBillNum(unsigned long billNo)
{
	billNum = billNo;

}

void Bill::setBillAmt(double billAmo)
{
	if (billAmo>0)
	{
		billAmt = billAmo;
	}
	else
	{
		errClass err("Invalid Bill Amount ", -92);
		throw err;
	}
}

void Bill::setBillDiscount(float billDisc)
{

	billDiscountAmt = billDisc;
}

void Bill::setBillDate(string billDat)
{
	billDate = billDat;
}

void Bill::setBillTime(string billTime)
{
	this->billTime = billTime;

}

string Bill::getBillTime()
{

	return billTime;
}

unsigned long Bill::getBillNum()
{
	return billNum;
}

double Bill::getBillAmt()
{
	return billAmt;
}

float Bill::getDiscount()
{
	return billDiscountAmt;
}

string Bill::getBillDate()
{
	return billDate;
}

void Bill::setBillList(list<Product> li)
{
	productList = li;
}


void Bill::printBill(Customer &inCustomer, Employee &inEmployee)
{
	system("cls"); system("COLOR F0");
	cout << "\n\n----------------------------------------------------------------------------\n";
	cout << "\n\n\t\t\t\tBILL No: " << billNum << "\n";
	cout << "\n\n\t\t\t\tSUPERMARKET\n";
	cout << "----------------------------------------------------------------------------\n";
	cout << "\n\tDate: " << billDate << "\tTime: " << billTime;
	cout << "\n\n\tEmployee Name: " << inEmployee.getEmployeeName() << "\tEmployee Id: " << inEmployee.getEmployeeId();
	cout << "\n\n\tCustomer Id: " << inCustomer.getCustId() << "\tCustomer Mobile Num: " << inCustomer.getCustPhNum();
	cout << "\n\n\tITEMS\n";
	cout << "----------------------------------------------------------------------------\n\n";
	int i = 1;
	list<Product>::iterator itr;
	cout << "\nSr.No.\tName\t\tID\t\tCategory\t\t\tCost\n";
	for (itr = productList.begin(); itr != productList.end(); itr++)
	{
		cout << "\n" << i << ".\t" << itr->getProductName() << "\t" << itr->getProductId();
		cout << "\t\t" << itr->getProductCategoryName() << "\t\t\t" << itr->getProductCost();
		i++;
	}
	cout << "\n\n----------------------------------------------------------------------------";
	cout << "\n\t\tTOTAL\t\t\t\t\t\t\t" << billAmt;
	cout << "\n\t\tDiscount\t\t\t\t\t\t" << ((billDiscountAmt / 100)*billAmt);
	cout << "\n\n\t\tGRAND TOTAL\t\t\t\t\t\t" << (billAmt - ((billDiscountAmt / 100)*billAmt));

	cout << "\n\n\t\tPLEASE VISIT AGAIN. HAVE A GOOD DAY!";
	cout << "\n\t\tFor any Queries, Contact: 7202970566\n\n";
	cout << "----------------------------------------------------------------------------\n\n";
}

void Bill::storeBill(Customer &inCustomer, Employee &inEmployee)
{

	ofstream fout;
	fout.open(BILLHISTORY_FILE, ios::app);

	fout << "\n\n----------------------------------------------------------------------------\n";
	fout << "\n\n\t\t\t\tBILL No: " << billNum << "\n";
	fout << "\n\n\t\t\t\tSUPERMARKET\n";
	fout << "----------------------------------------------------------------------------\n";
	fout << "\n\tDate: " << billDate << "\tTime: " << billTime;
	fout << "\n\n\tEmployee Name: " << inEmployee.getEmployeeName() << "\tEmployee Id: " << inEmployee.getEmployeeId();
	fout << "\n\n\tCustomer Id: " << inCustomer.getCustId() << "\tCustomer Mobile Num: " << inCustomer.getCustPhNum();
	fout << "\n\n\tITEMS\n";
	fout << "----------------------------------------------------------------------------\n\n";
	int i = 1;
	list<Product>::iterator itr;
	fout << "\nSr.No.\tName\t\tID\t\tCategory\t\t\tCost\n";
	for (itr = productList.begin(); itr != productList.end(); itr++)
	{
		fout << "\n" << i << ".\t" << itr->getProductName() << "\t" << itr->getProductId();
		fout << "\t\t" << itr->getProductCategoryName() << "\t\t\t" << itr->getProductCost();
		i++;
	}
	fout << "\n\n----------------------------------------------------------------------------";
	fout << "\n\t\tTOTAL\t\t\t\t\t\t\t" << billAmt;
	fout << "\n\t\tDiscount\t\t\t\t\t\t" << ((billDiscountAmt / 100)*billAmt);
	fout << "\n\n\t\tGRAND TOTAL\t\t\t\t\t\t" << (billAmt - ((billDiscountAmt / 100)*billAmt));

	fout << "\n\n\t\tPLEASE COME AGAIN. HAVE A GOOD DAY!";
	fout << "\n\t\tFor any Queries, Contact: 7202970566\n\n";
	fout << "----------------------------------------------------------------------------\n\n";

}
