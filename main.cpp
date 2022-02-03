#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

// Prompt user for a double
// Return false if input was invalid
bool promptDouble(std::string msg, double& doubleOut, std::string& inputOut) {
    std::cout << msg;
    std::cin >> inputOut;
    try {
        doubleOut = stod(inputOut);
    } catch (const std::invalid_argument&) {
        return false;
    }
    return true;
}

// Prompt user for an integer
// Return false if input was invalid
bool promptInt(std::string msg, int& intOut, std::string& inputOut) {
    std::cout << msg;
    std::cin >> inputOut;
    try {
        intOut = stoi(inputOut);
    } catch (const std::invalid_argument&) {
        return false;
    }
    return true;
}

int main() {
    const double overtimeWageModifier = 1.5;
    const double ssTax = 0.06;
    const double fiTax = 0.14;
    const double siTax = 0.05;
    const double unionDues = 10.0;
    const double healthInsuranceForThreeDependents = 35.0;

    std::cout << std::endl << "Enter 'q' at any time to quit" << std::endl << std::endl;

    bool running = true;
    while (running) {
        double wage = 0.0;
        double hoursWorked = 0.0;
        int numberOfDependents = 0;

        std::string inputStr;
        bool valid = false;

        // Prompt user for hourly wage
        do {
            valid = promptDouble("Hourly wage: $", wage, inputStr);
            if (inputStr == "q" || inputStr == "Q") {
                exit(0);
            }
            else if (!valid) {
                std::cerr << "Error: Hourly wage must be a number" << std::endl;
            }
            else if (wage < 0) {
                std::cerr << "Error: Hourly wage cannot be negative" << std::endl;
                valid = false;
            }
        } while (!valid);

        // Prompt user for hours worked
        do {
            valid = promptDouble("Hours worked: ", hoursWorked, inputStr);
            if (inputStr == "q" || inputStr == "Q") {
                exit(0);
            }
            else if (!valid) {
                std::cerr << "Error: Hours worked must be a number: " << std::endl;
            }
            else if (hoursWorked < 0) {
                std::cerr << "Error: Hours worked cannot be negative" << std::endl;
                valid = false;
            }
            else if (hoursWorked > 24 * 7) {
                std::cerr << "Error: Cannot have worked more hours than are in a week" << std::endl;
                valid = false;
            }
        } while (!valid);

        // Prompt user for number of dependents
        do {
            valid = promptInt("Number of dependents: ", numberOfDependents, inputStr);
            if (inputStr == "q" || inputStr == "Q") {
                exit(0);
            }
            else if (!valid) {
                std::cerr << "Error: Number of independents must be a number" << std::endl;
            }
            else if (numberOfDependents < 0) {
                std::cerr << "Error: Number of dependents cannot be negative" << std::endl;
                valid = false;
            }
        } while (!valid);

        // Calculate taxes
        double baseHours = std::min(hoursWorked, 40.0);
        double overtimeHours = std::max(hoursWorked - 40, 0.0);
        double grossPay = baseHours * wage + overtimeHours * wage * overtimeWageModifier;
        double ssTaxWitheld = grossPay * ssTax;
        double fiTaxWitheld = grossPay * fiTax;
        double siTaxWitheld = grossPay * siTax;
        double healthInsuranceWitheld = numberOfDependents >= 3 ? healthInsuranceForThreeDependents : 0;
        double payRemaining = grossPay - ssTaxWitheld - fiTaxWitheld - siTaxWitheld - unionDues - healthInsuranceWitheld;

        // Set output formatting
        std::ios::fmtflags resetFlags = std::cout.setf(std::ios::fixed, std::ios::floatfield);
        std::streamsize resetPrecision = std::cout.precision(2);

        // Print data
        std::cout << std::endl;
        std::cout << "Gross pay: $" << grossPay << std::endl;
        std::cout << "Social Security tax witheld: $" << ssTaxWitheld << std::endl;
        std::cout << "Federal income tax witheld: $" << fiTaxWitheld << std::endl;
        std::cout << "State income tax witheld: $" << siTaxWitheld << std::endl;
        std::cout << "Union dues: $" << unionDues << std::endl;
        std::cout << "Health insurace witheld: $" << healthInsuranceWitheld << std::endl;
        std::cout << "Pay remaining: " << (payRemaining < 0 ? "-$" : "$") << std::abs(payRemaining) << std::endl;

        // Reset output formatting
        std::cout.setf(resetFlags);
        std::cout.precision(resetPrecision);

        std::string goAgain;
        std::cout << std::endl << "Would you like to enter more data? (y/n): ";
        std::cin >> goAgain;
        if (!(goAgain == "y" || goAgain == "Y")) {
            running = false;
        }
    }
}