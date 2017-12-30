
#include "CEmployeeTransaction.h"
#include "CError.h"
#include "CBill.h"
#include "common_helper.h"

#include <iostream>

using namespace std;

bool EmployeeTransaction::Login() {

	try {
		unsigned id;
		cout << "\n\tEnter the Id: ";
		cin >> id;
		employee.setEmployeeId(id);
		string passwd;
		cout << "\n\tEnter the password: ";
		set_stdinEcho(false);
		cin >> passwd;
		employee.setPassword(passwd);
		set_stdinEcho(true);

		int count = 1;

		list<Employee> li = getList_FromFile<Employee>(EMPLOYEE_FILE);

		list<Employee>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++) {
			if (employee.getEmployeeId() == itr->getEmployeeId() && employee.getEmployeePassword() == itr->getEmployeePassword())
			{
				employee.setEmployeeName(itr->getEmployeeName());
				return true;
			}
			else
				count = 0;
		}
		if (count == 0 || li.empty())
			return false;
	}
	catch (errClass inErr) {

		throw inErr;
	}

}

/*Function to modify the details(Name) of the employee*/
void EmployeeTransaction::changeName(string inName) {

	try {

		list<Employee> li = getList_FromFile<Employee>(EMPLOYEE_FILE);

		list<Employee>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++) {
			if (employee.getEmployeeId() == itr->getEmployeeId())
			{
				itr->setEmployeeName(inName);
				break;
			}
		}

		putList_InFile<Employee>(EMPLOYEE_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}


}


/*Function to modify the details(Password) of the employee*/
void EmployeeTransaction::changePasswd(string inPass1) {

	try {

		list<Employee> li = getList_FromFile<Employee>(EMPLOYEE_FILE);

		list<Employee>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++) {
			if (employee.getEmployeeId() == itr->getEmployeeId() && employee.getEmployeePassword() == itr->getEmployeePassword())
			{
				itr->setPassword(inPass1);
				break;
			}
		}

		putList_InFile<Employee>(EMPLOYEE_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}


}


bool EmployeeTransaction::billing() {

	multimap<unsigned long, Product> mapfrom;
	list<Product> li;
	list<Customer> liC;
	list<Customer>::iterator itrC;

	//getting the cart details along with the customer id  from the Cart.txt into a multimap
	mapfrom = getCart_FromFile(CART_FILE);
	unsigned long tempcustid = 0;
	double tempamt = 0;

	multimap<unsigned long, Product>::iterator itr;

	if (!mapfrom.empty())
	{
		for (itr = mapfrom.begin(); itr != mapfrom.end(); itr++) {

			if (tempcustid != itr->first)
			{
				cout << "\n\tCust id: " << itr->first << endl;
				tempcustid = itr->first;
			}
		}

		cout << "\n\tEnter the customer id to display its Cart: ";
		cin >> tempcustid;
		customer.setCustId(tempcustid);
		cout << endl << endl;
		cout << "\n\tCart for Customer Id: " << tempcustid << endl;
		for (itr = mapfrom.begin(); itr != mapfrom.end(); itr++)
		{
			if (itr->first == tempcustid)
			{
				cout << "\n\t" << itr->second << endl;
				li.push_back(itr->second);
				tempamt += itr->second.getProductCost();

			}
		}
		cout << "\n\tCart Total: " << tempamt;

		//setting the product list in the private data member of the object bill in the employe transaction
		bill.setBillList(li);
		bill.setBillAmt(tempamt);

		//setting up customer for the current bill procedure
		liC = getList_FromFile<Customer>(CUSTOMER_FILE);

		for (itrC = liC.begin(); itrC != liC.end(); itrC++)
		{
			if (itrC->getCustId() == tempcustid)
			{
				customer.setCardNumber(itrC->getCardNumber());
				customer.setCardPoints(itrC->getCardPoints());
				customer.setCustPhNum(itrC->getCustPhNum());
			}
		}

		return true;

	}
	else
	{
		return false;
	}


}

//setting up the bill discount from the current card points
void EmployeeTransaction::addDiscount() {


	if (customer.getCardPoints() > 99)
	{
		bill.setBillDiscount(10.0);
		customer.setCardPoints(0);
	}
	else
		bill.setBillDiscount(0);
}

//setting the card points on the total bill amount
void EmployeeTransaction::addPointsToCard() {


	if (bill.getBillAmt() > 1000)
	{
		customer.setCardPoints(customer.getCardPoints() + 10);
	}

}

//generate the bill and print on the screen after setting the Bill date and number
void EmployeeTransaction::generateBill() {

	bill.setBillDate(getDateString());
	bill.setBillTime(getTimeString());
	bill.printBill(customer, employee);
	bill.storeBill(customer, employee);
}


void EmployeeTransaction::updateCart_File() {

	multimap<unsigned long, Product> mapC = getCart_FromFile(CART_FILE);
	multimap<unsigned long, Product>::iterator itr;

	ofstream fileout;
	fileout.open(CART_FILE);
	for (itr = mapC.begin(); itr != mapC.end(); itr++) {

		if (itr->first != customer.getCustId())
		{
			fileout << itr->second << " " << itr->first;
		}

	}
	fileout.close();

}

void EmployeeTransaction::updateCardPoints_File() {

	list<Customer> li = getList_FromFile<Customer>(CUSTOMER_FILE);

	list<Customer>::iterator itr;

	/*for(itr=li.begin();itr!=li.end();itr++)
	{
	cout<<*itr;
	}*/

	for (itr = li.begin(); itr != li.end(); itr++)
	{
		if (customer.getCustId() == itr->getCustId())
		{
			itr->setCardPoints(customer.getCardPoints());
		}

	}

	putList_InFile(CUSTOMER_FILE, li);
}



/*Menu for the Employee Transaction*/
void EmployeeTransaction::displayMenu()
{
	char choice;
	system("COLOR 3F");

	do {
		system("cls");
		cout << "\n\t\t\tTEAM 1 SUPERMARKET\n";
		cout << "\n\t" << getDateString();
		cout << "\n\t\t\tWELCOME " << employee.getEmployeeName() << "\n";
		cout << "\n\t\t\tEnter the choice to enter into\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tSelf Service Options Modify Details\n\n";
		cout << "\t\t\t 1.Change your Name\n";
		cout << "\t\t\t 2.Change your Password\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\n\t\t\tBilling Related Options\n\n";
		cout << "\t\t\t 3.Billing\n";
		cout << "------------------------------------------------------------------\n\n";
		cout << "\t\t\t 4.LOGOUT\n";
		cout << "\n------------------------------------------------------------------\n";
		cout << "\n\tEnter your choice----> ";
		cin >> choice;

		switch (choice) {

			//case 1 modifies the employee Name which is done by employee only. 
		case '1':
			try {
				cout << "\n\tEnter the name to be updated ";
				string nam;
				cin >> nam;
				changeName(nam);
			}
			catch (errClass inErr) {
				inErr.display();
			}

			break;

			/*This is used to change the password of the Employee.*/
		case '2':
			try {
				cout << "\n\tEnter the new Password: ";
				string pass1;
				cin >> pass1;
				cout << "\n\tConfirm Password: ";
				string pass2;
				cin >> pass2;
				if (pass1 == pass2)
					changePasswd(pass1);
				else
					cout << "\n\tPasswords Entered Does not match each other.";
			}
			catch (errClass inErr) {
				inErr.display();
			}

			break;

			//Get Cart Details and display.
		case '3':
			try {
				cout << "\n\tThe Customer Id having pending orders. \n";
				if (billing())
				{
					cout << "\n\n\tDo you want to Generate the Bill?\n\t1.YES. Any Other key for no. ---> ";
					char chbill;
					cin >> chbill;
					if (chbill == '1')
					{
						addDiscount();
						addPointsToCard();
						generateBill();
						updateCart_File();
						updateCardPoints_File();
					}
				}
				else
					cout << "\n\tSorry!There are no Customers With Pending order.\n";

			}
			catch (errClass inErr) {
				inErr.display();
			}

			break;

		case '4': choice = '0';
			break;

		default:
			cout << "\n\tInvalid Choice";
			break;

		}

		if (choice != '0')
		{
			cin.clear();
			cin.sync();
			cout << "\n\n\tDo you want to continue as Employee?\n\tPress 1 to continue. 0. EXIT ----> ";
			cin >> choice;
		}
	} while (choice != '0' && choice == '1');
	//system("COLOR F0");
}