

#include "CTransaction.h"
#include "CAdminTransaction.h"
#include "CEmployeeTransaction.h"
#include "CCustomerTransaction.h"
#include "CError.h"


Transaction* TransactionFactory::createTransaction(string inTransactionDetails) {

	if (inTransactionDetails == "Admin")
		return new AdminTransaction;
	else if (inTransactionDetails == "Customer")
		return new CustomerTransaction;
	else if (inTransactionDetails == "Employee")
		return new EmployeeTransaction;
	else
	{
		errClass err("Invalid Transaction", 1);
		throw err;
	}

}