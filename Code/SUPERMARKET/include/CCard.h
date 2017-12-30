#pragma once


#include <string>

using namespace std;

class Card		//Card class
{

public:				//Public members of Card class
	Card() {}
	Card(const string);
	void setCardNumber(unsigned long long);
	void setCardPoints(unsigned);
	unsigned long long getCardNumber();
	unsigned getCardPoints();

private:			//Private members of Card class
	unsigned long long cardNumber;
	unsigned points;
};