#pragma once

#include "CTransaction.h"

class UserInterface {

public:

	UserInterface() {/*TransFact = new TransactionFactory;*/ }
	void displayUI();
	~UserInterface() {  }

private:
	Transaction *Transac;
	//TransactionFactory *TransFact;
};