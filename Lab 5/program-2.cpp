//**********************************************
// Name: program-2.cpp
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
	double withdraw(double);
	void deposit(double);
	double getBalance();
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

	billAcc.withdraw(500);
	billAcc.withdraw(2500);
	cout << "---------------------" << endl;
	cout << "Balance is: " << billAcc.getBalance() << endl;
	cout << "---------------------" << endl;


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

double BankAccount :: withdraw(double toWD) {
	if (balance-toWD > 0) {
		balance -= toWD;
	}
	else {
		cout << "!!!Sorry, not enough money!!!" << endl;
		return 0;
	}
	return toWD;
}

void BankAccount :: deposit(double toDep) {
	balance += toDep;
}

double BankAccount :: getBalance() {
	return balance;
}
//**********************************************
//**********************************************
