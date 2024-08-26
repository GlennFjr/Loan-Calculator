// Assignment 2: Loan Calculator
// Objective: Create a loan calculator that produces an amortization schedule given loan amount, apr, and number of months to pay it off.  In addition, the program should
//  include a variety of functions and display the total interest paid, total payment, and the monthly payment amount.
// 
// Glenn Fortunato
// COP3014
// Professor Taebi
// Florida Atlantic University
// 9/23/2023

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;


// Checks if there are any non-digits in the user input, and returns false if there are.
bool int_verification(string test) {
    for (int i = 0; i < test.length(); i++) {
        if (isdigit(test[i]) == false) {
            cout << "failed";
            return false;
        }
    }
    return true;
    
}


// Prompts user to input 3 values used for calculating
void initial_inputs(double& principal, double& apr, int& n_months)
{
    // String only used for checking characters in user input
    string testStr;

    while (true) {
        cout << "\nEnter Loan Amount: $";
        cin >> testStr;
        if (int_verification(testStr)) {
            principal = stod(testStr);
            break;
        }
        else {
            cout << "\nOnly positive integers are accepted, try again.";
        }
    }

    while (true) {
        cout << "\nEnter Annual Percent Rate: %";
        cin >> testStr;
        if (int_verification(testStr)) {
            apr = stod(testStr);
            break;
        }
        else {
            cout << "\nOnly positive integers are accepted, try again.";
        }

    }

    while (true) {
        cout << "\nEnter Number of Months: #";
        cin >> testStr;
        if (int_verification(testStr)) {
            n_months = stoi(testStr);
            break;
        }
        else {
            cout << "\nOnly positive integers are accepted, try again.";
        }
    }
}


// Converts annual interest rate to monthly
// rate = ((1 + APR/100)^1/12) - 1
double monthly_interest(double rate)
{
    
    const double base = (1 + (rate / 100));
    const double exp = 1.0 / 12.0;

    double result = pow(base, exp) - 1;

    return result;
}


// Calculates the monthly payments
// M = P((r(1+r)^n)/((1+r)^n -1)
double monthly_payments(double principal,double r,double n_months) 
{
    double m = principal * ((r * pow(1 + r, n_months)) / (pow(1 + r, n_months) - 1));

    return m;
}


// Calculates the monthly interest and principal balance
void monthly_tracker(double& principal, double& r, double& monthly_payment, int& n_months, double& interest, double& totalInterest)
{
    double balance = principal;
    int i = 1;
    while (i <= n_months)
    {
        double interest = balance * r;
        totalInterest += interest;

        principal = monthly_payment - interest;
        balance = balance - principal;
        i++;
    }
}


// Currently only calculates totalPayments
void total_tracker(double& totalPayment, double& totalInterest, double& monthly_payment, int& n_months, double& interest) {

    totalPayment = n_months * monthly_payment;

    // The total interest is calculated in the monthly_tracker function at the start of the while loop
}


// Prints out the table
void table_display(int& n_months, double& r, double balance, double interest, double principal, double monthly_payment) {

    // Table allignment
    int tableWidth = 24;
    int year = 1;
    string ifiller = "  ";
    
    // Table Header
    cout << endl << "Months             " << "Starting Balance          " << "Interest              " << "Principal         " << "Ending Balance";

    // For loop iterates over each month and calculates each value, then neatly prints it out as a table
    for (int i = 1; i <= n_months; i++) {

        double startBalance = balance;

        interest = balance * r;
        principal = monthly_payment - interest;
        balance = balance - principal;

        if (i > 9) {
            ifiller = " ";
        }
        else if (i > 99) {
            ifiller = "";
        }

        // Output for table
        cout << endl << i << ifiller << setw(tableWidth) << fixed << setprecision(2) << right << startBalance << setw(tableWidth) << right << interest << setw(tableWidth) << right << principal << setw(tableWidth) << right << balance;

        if (i % 12 == 0)
        {
            cout << endl << setw(50) << "Year #" << year << " End";
            year++;
        }
    }
}


// Neatly summarizes total calculations and the monthly payment amount
void payment_summary(double& monthly_payment, double& totalPayment, double& totalInterest) {
    cout << "\n\n============================\n       Payment Summary\n============================\n";
    cout << endl << "Monthly Payments: $" << monthly_payment ;
    cout << endl << "Total Payments: $" << totalPayment;
    cout << endl << "Total Interest: $" << totalInterest;
}


// Menu to continuously use the calculator or quit at any time
void menu() {
    while (true) {
        string input = "";
        cout << "\n\n           Loan Calculator\n\n" << " Select an Option:";
        cout << "\n1. Calculate" << "\n2. Quit\n";
        cin >> input;
        if (input == "1") {
            break;
        }
        else if (input == "2") {
            exit(0);
        }
        else {
            cout << "\nOops, that wasn't one of the options. Try Again";
        }
    }
}


// Main function, variables are initialized and majority of functions are called here
int main()
{
    while (true) {
        menu();

        // Initializing variables
        double principal, apr = 0;
        int n_months = 0;
        double monthly_payment, interest = 0;
        double totalPayment, totalInterest = 0;

        // Prompts user for values and records initial principal as the balance
        initial_inputs(principal, apr, n_months);
        double balance = principal;

        // Calculates monthly interest rate from annual percentage rate
        double r = monthly_interest(apr);

        // Calculates monthly payments
        monthly_payment = monthly_payments(principal, r, n_months);

        // Tracks monthly and total values
        monthly_tracker(principal, r, monthly_payment, n_months, interest, totalInterest);
        total_tracker(totalPayment, totalInterest, monthly_payment, n_months, interest);
        
        // Output functions to display results
        table_display(n_months, r, balance, interest, principal, monthly_payment);
        payment_summary(monthly_payment, totalPayment, totalInterest);


    }
}
