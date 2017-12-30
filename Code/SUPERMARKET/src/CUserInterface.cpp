

#include <iostream>
#include "CUserInterface.h"
#include "CError.h"
#include "CTransaction.h"
#include "common_helper.h"

using namespace std;

void UserInterface::displayUI() {

	char choice;

	do {
		system("cls");
		system("Color F0");
		cout << "\n\t\t\tTEAM 1 SUPERMARKET\n";
		cout << "\n\t" << getDateString();
		cout << "\n\n\t************   Select the transaction ******\n";
		cout << "\n\t**             1.Admin                    **" << endl;
		cout << "\t**             2.Customer                 **" << endl;
		cout << "\t**             3.Employee                 **" << endl;
		cout << "\t**             4.EXIT                     **" << endl;
		cout << "\n\t********************************************\n";
		cout << "\n\tEnter your choice-----> ";
		cin >> choice;
		cout << "\n\n";


		switch (choice) {

		case '1': try {
			Transac = TransactionFactory::createTransaction("Admin");
			if (Transac->Login())
				Transac->displayMenu();
			else
				cout << "\n\tInvalid Id or Password";
		}
				  catch (errClass inErr) {
					  inErr.display();
				  }
				  break;

		case '2':  try {
			Transac = TransactionFactory::createTransaction("Customer");
			if (Transac->Login())
				Transac->displayMenu();

		}
				   catch (errClass inErr) {
					   inErr.display();
				   }
				   break;

		case '3': try {
			Transac = TransactionFactory::createTransaction("Employee");
			if (Transac->Login())
				Transac->displayMenu();
			else
				cout << "\n\tInvalid Id or Password.";
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
			cout << "\n\n\n\tDo you want another Transaction?\n\tPress 1 to continue. 0. EXIT----> ";
			cin >> choice;
		}
		system("cls");

	} while (choice != '0' && choice == '1');

}