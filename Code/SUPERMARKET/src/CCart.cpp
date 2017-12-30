

#include <iostream>
#include "CCart.h"
#include "common_helper.h"

using namespace std;

//CART

void Cart::setCustid(unsigned cusId)
{
	custId = cusId;
}

void Cart::addToCart(Product &inProd) {

	list<Product> li = getList_FromFile<Product>(PRODUCT_FILE);
	list<Product>::iterator itr;
	for (itr = li.begin(); itr != li.end(); itr++) {

		if (inProd.getProductId() == itr->getProductId()) {

			//cout<<*itr;
			cartList.push_back(*itr);
		}
	}


}

void Cart::displayCart() {

	list<Product>::iterator itr;
	int i = 1;
	cout << "\n\n*******************  CART     **************** \n\n";
	cout << "\n\t\tCUSTOMER ID: " << custId << "\n";

	if (cartList.empty())
	{
		cout << "\n\tSorry. Cannot Display your Cart is Empty!\n\n";
		cout << "\n**********************************************\n";
	}
	else
	{
		for (itr = cartList.begin(); itr != cartList.end(); itr++) {

			cout << "\nItem " << i << ": " << *itr << "\n";
			i++;
		}
		cout << "\n**********************************************\n";
	}

}


bool byCategoryName(Product p1, Product p2) {
	return (p1.getProductCategoryName() < p2.getProductCategoryName());
}



void Cart::sortBy_ProdCategory_displayCart() {

	cartList.sort(byCategoryName);
	displayCart();

}


bool byCost(Product p1, Product p2) {

	return p1.getProductCost() < p2.getProductCost();
}


void Cart::sortBy_ProdCost_displayCart() {

	cartList.sort(byCost);
	displayCart();

}


bool byName(Product p1, Product p2) {

	return p1.getProductName() < p2.getProductName();
}


void Cart::sortBy_ProdName_displayCart() {

	cartList.sort(byName);
	displayCart();
}

list<Product> Cart::getCart() {

	return cartList;
}

unsigned Cart::getCustid() {

	return custId;
}


ofstream& operator<<(ofstream &fout, Cart &inCart) {

	list<Product>::iterator itr;
	for (itr = inCart.cartList.begin(); itr != inCart.cartList.end(); itr++)
	{
		fout << *itr << " " << inCart.custId;
	}
	return fout;
}

ostream& operator<<(ostream &out, Cart &inCart) {

	list<Product>::iterator itr;
	for (itr = inCart.cartList.begin(); itr != inCart.cartList.end(); itr++)
	{
		out << *itr << " " << inCart.custId;
	}
	return out;
}
ifstream& operator>>(ifstream &fin, Cart &inCart) {

	Product prod;
	fin >> prod >> inCart.custId;
	inCart.cartList.push_back(prod);
	return fin;
}

void Cart::clearCartList() {

	cartList.clear();
}

void Cart::enterCartToFile() {


	if (!(cartList.empty()))
	{

		list<Product>::iterator itr;

		ofstream fileout;
		fileout.open(CART_FILE, ios::app);

		for (itr = cartList.begin(); itr != cartList.end(); itr++)
		{
			fileout << *itr << " " << custId;

		}

	}
	else
		cout << "\n\tCannot Place order. Your Cart is Empty!\n";

}