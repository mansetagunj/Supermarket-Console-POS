
#include <string>
#include <iostream>
#include <algorithm>
#include "CAdminTransaction.h"
#include "CError.h"
#include "common_helper.h"
#include <list>


using namespace std;

bool AdminTransaction::Login() {

	try {
		cout << "\n\tEnter the Id: ";
		unsigned id;
		cin >> id;
		admin.setAdminId(id);
		cout << "\n\tEnter the password: ";
		set_stdinEcho(false);
		string pass;
		cin >> pass;
		admin.setAdminPassword(pass);
		set_stdinEcho(true);

		list<Admin> li = getList_FromFile<Admin>(ADMIN_FILE);

		list<Admin>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++) {
			if (admin.getAdminId() == itr->getAdminId() && admin.getPassword() == itr->getPassword())
			{
				admin.setAdminName(itr->getAdminName());
				return 1;
			}
		}
		if (li.empty())
		{
			cout << "\n\tNo Admin Set. Set Admin.";
			cout << "\n\tEnter the Id: ";
			unsigned id;
			cin >> id;
			admin.setAdminId(id);
			cout << "\n\tEnter the Name: ";
			string name;
			cin >> name;
			admin.setAdminName(name);
			cout << "\n\tEnter the password: ";
			set_stdinEcho(false);
			string pass;
			cin >> pass;
			admin.setAdminPassword(pass);
			set_stdinEcho(true);

			li.push_back(admin);
			putList_InFile<Admin>(ADMIN_FILE, li);

			return 1;
		}
		else
			return 0;

			
	}
	catch (errClass inErr) {

		throw inErr;
	}

}

//this function object is used to find the employee in the admin transaction.
class searchEmployeeById {

public:
	bool operator()(Employee e1, Employee e2) {

		return e1.getEmployeeId() < e2.getEmployeeId();

	}
};

bool AdminTransaction::checkEmployee() {

	try {
		list<Employee> li = getList_FromFile<Employee>(EMPLOYEE_FILE);
		//cout<<"in check";		
		//cout<<"bin resul: "<<binary_search(li.begin(),li.end(),Emp,searchEmployeeById());
		li.sort(searchEmployeeById());
		return (binary_search(li.begin(), li.end(), Emp, searchEmployeeById()));
	}
	catch (errClass inErr) {

		throw inErr;
	}

}

//this function object is used to find the employee in the admin transaction.
class searchAdminById {

public:
	bool operator()(Admin a1, Admin a2) {

		return a1.getAdminId() < a2.getAdminId();

	}
};

bool AdminTransaction::checkAdmin(Admin inAdmin) {

	try {
		list<Admin> li = getList_FromFile<Admin>(ADMIN_FILE);
		li.sort(searchAdminById());
		return (binary_search(li.begin(), li.end(), inAdmin, searchAdminById()));
	}
	catch (errClass inErr) {

		throw inErr;
	}

}

void AdminTransaction::addAdmin(Admin inAdmin)
{
	try {
	
		list<Admin> li = getList_FromFile<Admin>(ADMIN_FILE);

		li.push_front(inAdmin);

		putList_InFile(ADMIN_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}
	
}

void AdminTransaction::removeAdmin(Admin inAdmin)
{
	try {

		list<Admin> li = getList_FromFile<Admin>(ADMIN_FILE);

		li.remove(inAdmin);

		if(!li.empty())
			putList_InFile(ADMIN_FILE, li);
		else
		{
			errClass err("Cannot delete Admin. There should be minimum of 1 admin.",-204);
			throw err;
		}
			
	}
	catch (errClass inErr) {

		inErr.display();
	}

}

void AdminTransaction::addEmployee() {

	try {


		list<Employee> li = getList_FromFile<Employee>(EMPLOYEE_FILE);

		li.push_front(Emp);

		putList_InFile(EMPLOYEE_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}
}

void AdminTransaction::removeEmployee() {

	try {
		list<Employee> li = getList_FromFile<Employee>(EMPLOYEE_FILE);

		li.remove(Emp);

		putList_InFile<Employee>(EMPLOYEE_FILE, li);
	}
	catch (errClass inErr) {

		inErr.display();
	}

}

void AdminTransaction::addProduct() {

	try {
		list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);

		li.push_back(adminProduct);

		putList_InFile<Product>(PRODUCT_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}
}

void AdminTransaction::removeProduct() {

	try {
		list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);

		li.remove(adminProduct);

		putList_InFile<Product>(PRODUCT_FILE, li);
	}
	catch (errClass inErr) {

		inErr.display();
	}

}

//this function is used in the for_each algorithm used in displayLowStockProducts() func below
//to display the low stock products.
//void displayLowStockList(Product inProd){
//
//	if(inProd.getProductAvailStock() < 6 )
//				
//		cout<<inProd;
//}


void AdminTransaction::displayLowStockProducts() {

	try {
		int count = 0;
		list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);

		cout << "\n\tLow Stock Products are below.(Products having stocks less than 6).\n";
		//for_each(li.begin(),li.end(),displayLowStockList);
		//use the below if some prob in for_each algo
		list<Product>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (itr->getProductAvailStock() < 6)
			{
				cout << *itr;
				count++;
			}
		}
		if (count == 0) {
			cout << "\n\tThere are no Low stock Products.\n"
				;
		}

	}
	catch (errClass inErr) {

		inErr.display();
	}
}

//this function object is used to find the product in the admin transaction.
class searchProductById {

public:
	bool operator()(Product p1, Product p2) {

		return p1.getProductId() < p2.getProductId();
	}
};

bool AdminTransaction::checkProduct() {

	try {
		list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);

		li.sort(searchProductById());
		return (binary_search(li.begin(), li.end(), adminProduct, searchProductById()));
	}
	catch (errClass inErr) {

		throw inErr;
	}
}

void AdminTransaction::updateStock(Product inprod, unsigned inStock) {

	try {
		list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);

		list<Product>::iterator itr;

		for (itr = li.begin(); itr != li.end(); itr++)
		{
			if (inprod.getProductId() == itr->getProductId())
				itr->setProductAvailStock(itr->getProductAvailStock() + inStock);
		}

		putList_InFile<Product>(PRODUCT_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}

}

void AdminTransaction::changePasswd(string inPass1) {

	try {

		list<Admin> li = getList_FromFile<Admin>(ADMIN_FILE);

		list<Admin>::iterator itr;
		for (itr = li.begin(); itr != li.end(); itr++) {
			if (admin.getAdminId() == itr->getAdminId() && admin.getPassword() == itr->getPassword())
			{
				itr->setAdminPassword(inPass1);
				break;
			}
		}

		putList_InFile<Admin>(ADMIN_FILE, li);

	}
	catch (errClass inErr) {

		inErr.display();
	}


}

void AdminTransaction::displayMenu() {

	char choice;
	unsigned long id;
	system("COLOR 1F");
	do {
		system("cls");
		cout << "\n\t\t\tTEAM 1 SUPERMARKET\n";
		cout << "\n\t" << __DATE__;
		cout << "\n\t\t\tWELCOME " << admin.getAdminName() << ".\n";
		cout << "\n\t\t\tEnter the choice to enter into                     \n\n";
		cout << "\t\t\tEmployee Related Options\n\n";
		cout << "\t\t\t  1.Add Employee\n";
		cout << "\t\t\t  2.Remove Employee\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tAdmin Related Options\n\n";
		cout << "\t\t\t  3.Add Admin\n";
		cout << "\t\t\t  4.Remove Admin\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tProduct Related Options\n\n";
		cout << "\t\t\t  5.Add Product\n";
		cout << "\t\t\t  6.Remove Product\n";
		cout << "\t\t\t  7.Update Stocks\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tPersonal Details Change\n\n";
		cout << "\t\t\t  8.Change your Password\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\tOffers Related Options\n\n";
		cout << "\t\t\t  9. Remove Offers Left to do\n"; //todo
		cout << "\t\t\t  A. Add/Update Offers Left to do\n"; //todo
		cout << "------------------------------------------------------------------\n";
		cout << "\t\t\t  B.LOGOUT\n";
		cout << "------------------------------------------------------------------\n";
		cout << "\n\t\tEnter your choice----> ";
		cin >> choice;


		switch (choice) {

			//case 1 takes emp id, checks in the file if it already exists. if it does it displays 
			//error msg and if the id is unique it accepts the other details and stores the employee
		case '1':
			try {
				cout << "\n\tEnter the Employee id: ";
				cin >> id;
				Emp.setEmployeeId(id);

				if (!checkEmployee())
				{
					cout << "\n\tEnter the Employee Name: ";
					string name;
					cin >> name;
					Emp.setEmployeeName(name);
					cout << "\n\tEnter the Employee Password: ";
					set_stdinEcho(false);
					string pass;
					cin >> pass;
					Emp.setPassword(pass);
					set_stdinEcho(true);
					//this will execute only if the employee id entered does nt exists
					// and the details for the employee entered are correct
					addEmployee();
				}
				else
				{
					cout << "\n\tEntered Id already Exists.";

				}

			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;

			//this takes the emp id and checks if it is there in file or not. 
			//if it is not there is shows error msg and if its there the employee will be removed.
		case '2':
			try {
				cout << "\n\tEnter the Employee id: ";
				unsigned id;
				cin >> id;
				Emp.setEmployeeId(id);

				if (checkEmployee())
					removeEmployee();
				else
				{
					cout << "\n\tEntered Id doesnot Exist. Employee cannot be removed";
				}
			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;


		case '3':
			try {
				cout << "\n\tEnter the Admin id: ";
				cin >> id;
				Admin admin;
				admin.setAdminId(id);

				if (!checkAdmin(admin))
				{
					cout << "\n\tEnter the Admin Name: ";
					string name;
					cin >> name;
					admin.setAdminName(name);
					cout << "\n\tEnter the Admin Password: ";
					set_stdinEcho(false);
					string pass;
					cin >> pass;
					admin.setAdminPassword(pass);
					set_stdinEcho(true);
					//this will execute only if the employee id entered does nt exists
					// and the details for the employee entered are correct
					addAdmin(admin);
				}
				else
				{
					cout << "\n\tEntered Id already Exists.";
				}

			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;

		case '4':
			try {
				cout << "\n\tEnter the Admin id: ";
				cin >> id;
				Admin admin;
				admin.setAdminId(id);

				if (checkAdmin(admin))
				{
					removeAdmin(admin);
				}
				else
				{
					cout << "\n\tEntered Id doesnot Exists. Admin cannot be removed";
				}

			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;


			//case 1 takes product id, checks in the file if it already exists. if it does it displays 
			//error msg and if the id is unique it accepts the other details and stores the product
		case '5':
			try {

				cout << "\n\tEnter the Product id: ";
				unsigned long id;
				cin >> id;
				adminProduct.setProductId(id);

				if (!checkProduct())
				{
					cout << "\n\tEnter the Product Name: ";
					string name;
					cin >> name;
					adminProduct.setProductName(name);

					cout << "\n\tEnter the Product Cost : ";
					unsigned long cost;
					cin >> cost;
					adminProduct.setProductCost(cost);

					cout << "\n\tEnter the Product Exp Date : ";
					string expdate;
					cin >> expdate;
					adminProduct.setProductExpDate(expdate);

					cout << "\n\tEnter the Product Mfg Date : ";
					string mfgdate;
					cin >> mfgdate;
					adminProduct.setProductMfgDate(mfgdate);

					cout << "\n\tEnter the Product Available Stock : ";
					unsigned stock;
					cin >> stock;
					adminProduct.setProductAvailStock(stock);

					cout << "\n\tEnter the Product Category Name : ";
					string catName;
					cin >> catName;
					for_each(catName.begin(), catName.end(), [](char &a) {a = toupper(a); });
					cout << "\n\tEnter the Product Category Id : ";
					unsigned catId;
					cin >> catId;
					adminProduct.setProductCategory(catId, (catName));

					addProduct();
				}
				else
				{
					cout << "\n\tProduct Already Exists. Enter Unique Id";
					break;
				}
			}
			catch (errClass inErr) {
				inErr.display();
			}

			break;

			//this takes the product id and checks if it is there in file or not. 
			//if it is not there is shows error msg and if its there the product will be removed. 
		case '6':
			try {

				cout << "\n\tEnter the Product id: ";
				unsigned long id;
				cin >> id;
				adminProduct.setProductId(id);

				if (checkProduct())
				{
					removeProduct();
				}
				else
				{
					cout << "\n\tProduct Does not Exists. Cannot Remove.";
					break;
				}
			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;

			//this case displays the products having stock less than 5
			//the admin enters the product id from the displayed product list.
			//then the admin enters the stock to be increased and then the stock increases. 
		case '7':
			try {

				displayLowStockProducts();

				cout << "\n\tEnter the Product id: ";
				unsigned long id;
				cin >> id;
				adminProduct.setProductId(id);
				if (checkProduct())
				{
					cout << "\n\tEnter the number of items to increase: ";
					unsigned stockcount;
					cin >> stockcount;
					if (stockcount>0)
						updateStock(adminProduct, stockcount);
					else
					{
						cout << "\n\tStock should be greater than ZERO.";
						break;
					}
				}
				else
				{
					cout << "\n\tProduct Does not Exists. Cannot Remove.";
					break;
				}

			}
			catch (errClass inErr) {
				inErr.display();
			}
			break;

			//TO change the password of the admin.
			//Admin enters the the password to be changed to two times and the password
			//should be alphanumeric. 
		case '8':
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
					cout << "\n\t->Passwords Entered Does not match each other.<-\n";
			}
			catch (errClass inErr) {
				inErr.display();
			}

			break;
			//to exit
		case '9':
		case 'a':
		case 'A':
		case 'b':
		case 'B': choice = '0';

			break;

		default:
			cout << "\n\tInvalid Choice";
			break;

		}

		if (choice != '0')
		{
			cin.clear();
			cin.sync();
			cout << "\n\n\tDo you want to continue as Admin?\n\tPress 1 to continue. 0. Exit----> ";
			cin >> choice;
			cout << "\n\n";
		}

	} while (choice != '0');
	system("COLOR F0");
}