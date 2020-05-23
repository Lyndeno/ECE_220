//**********************************************
// Name: program-1.cpp
//**********************************************

#include <iostream>
#include <string.h>
using namespace std;

#define MAX_NAME_LEN 40

class BankAccount {
private:
	char name[MAX_NAME_LEN];
	int  account_number;
	double balance;
public:
	BankAccount ();
	BankAccount (char *);
	BankAccount (char *, int, double);
	void printSummary();
};


int main(void) {
	char nCindy[] = "Cindy";
	char nBill[] = "Bill";

	BankAccount daveAcc;
	BankAccount cindyAcc(nCindy);
	BankAccount billAcc(nBill, 123456, 2000);

	daveAcc.printSummary();
	cindyAcc.printSummary();
	billAcc.printSummary();

	return 0;
}

//**********************************************
// class BankAccount: methods
//**********************************************
BankAccount :: BankAccount () {
	name[0] = 0;
	account_number = 0;
	balance = 0.0;
}

BankAccount :: BankAccount (char *n) {
	strcpy(name, n);
	account_number = 0;
	balance = 0.0;
}

BankAccount :: BankAccount (char *n, int a_no, double bal) {
	strcpy(name, n);
	account_number = a_no;
	balance = bal;
}

void BankAccount :: printSummary() {
	cout << "---------------------" << endl;
	cout << "Name: " << name << endl;
	cout << "Account Number: " << account_number << endl;
	cout << "Balance: " << balance << endl;
	cout << "---------------------" << endl;
}

//**********************************************
//**********************************************

