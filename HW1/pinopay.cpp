//
// CS31 Winter 2015
// File: HW #1 – Show Me the Money
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-1-11
// Version: 1.0
// Description: Payroll software for Pets In-N-Out
//

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
	string name;
	string idNum;
	double hours;
	double payRate;
	string taxWithheld;
	const double MIN_PAY_RATE = 9.00;

	//outputs the header using tabs to center it
	cout << "\t\t\tpinopay (v1.0) \n\t\tCopyright 2015 Pets In - N - Out\n" << endl;

	//must find a way to deal with the space by using getline()
	cout << "Employee Name (First Last): ";
	getline(cin, name);
	//If user does not enter a name, display eror message and exit
	if (name.length() == 0){
		cout << "You must enter an employee name." << endl;
		return 0;
	}

	//Read id number as a string
	cout << "Employee ID (5-digit): ";

	getline(cin, idNum);
	//If use does not enter a id num, display error message and exit
	if (idNum == "") {
		cout << "You must enter an employee ID." << endl;
		return 0;
	}
	//If length of id number is not 5, display error message and exit
	else if (idNum.length() != 5) {
		cout << "You must enter a 5-digit employee ID." << endl;
		return 0;
	}

	//If hours are less than 0, display error message and exit
	cout << "Number of Hours Worked: ";
	cin >> hours;
	if (hours < 0){
		cout << "The number of working hours must be nonnegative." << endl;
		return 0;
	}

	cout << "Pay Rate: $";
	cin >> payRate;
	//Make sure payrate is above the minimum wage and exit
	if (payRate < MIN_PAY_RATE){
		cout << "The pay rate must be at least $9." << endl;
		return 0;
	}

	cout << "Federal Income Tax Withheld (Y/N): ";
	cin >> taxWithheld;
	//If user enters input other than Y or N, display error message and exit
	if (!((taxWithheld == "Y") || (taxWithheld == "N"))){
		cout << "You must enter either Y or N." << endl;
		return 0;
	}

	//User input has been completed. Now caluclate payments.

	double roundedHours = 0;
	double timeAndHalfPayRate = 1.5*payRate;
	double grossPay = 0;
	double netPay = 0;
	const double UNION_DUES = 15.00;
	const double FED_INCOME_TAX = .15;
	const double MAX_HOURS = 40;
	const double TIME_ROUNDING = 0.5;
	//FED_TAX_THRESHOLD must be greater than UNION_DUE_THRESHOLD for code to work correctly.
	const double FED_TAX_THRESHOLD = 280.00;
	const double UNION_FEE_THRESHOLD = 150.00;

	/*Deal with rounding hours to 0.5 by determining whether the fractional hour is above or below cutoff.
	If above 0.5, then 0.5 is added to the nonfractional part of hours. Else, the fractional part is truncated.
	*/
	if ((hours - floor(hours)) >= TIME_ROUNDING){
		roundedHours = floor(hours) + TIME_ROUNDING;
	}
	else{
		roundedHours = floor(hours);
	}


	/*If user works more than 40 hours, calculate new per hour payrate which includes time and a half pay.
	If time and a half doesn't apply, timeAndHalfPayRate is assigned original inputed payrate.*/
	if (roundedHours > MAX_HOURS)
		timeAndHalfPayRate = (payRate*MAX_HOURS + timeAndHalfPayRate*(roundedHours - MAX_HOURS)) / roundedHours;
	else
		timeAndHalfPayRate = payRate;

	//Calculate gross pay. 
	grossPay = roundedHours*timeAndHalfPayRate;

	/*Determine whether to subtract Federal tax. If gross pay is above Fed tax threshold,
	it will also be above union dues threshold. Subtract both taxes (if Y) and union dues.*/
	if (grossPay > FED_TAX_THRESHOLD && taxWithheld == "Y")
		netPay = grossPay - grossPay*FED_INCOME_TAX - UNION_DUES;
	//If above union dues threshold, substract union dues.
	else if (grossPay > UNION_FEE_THRESHOLD)
		netPay = grossPay - UNION_DUES;
	//If no thresholds are met, subtract nothing.
	else
		netPay = grossPay;

	//Prints the money values to two decimal places only
	cout << name << "'s Weekly Gross Pay: $" << fixed << setprecision(2) << grossPay << endl;
	//cout.setf(ios::fixed);
	//cout.setf(ios::showpoint);

	cout << name << "'s Weekly Net Pay: $" << fixed << setprecision(2) << netPay << endl;

}