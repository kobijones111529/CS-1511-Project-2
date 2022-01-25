#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

// Prompt user for a double
// Return false if input was invalid
bool promptDouble(const std::string& msg, double& doubleOut) {
    std::cout << msg;
    std::string input = "";
    std::cin >> input;
    try {
        doubleOut = stod(input);
    } catch (const std::invalid_argument&) {
        return false;
    }
    return true;
}

// Prompt user for an integer
// Return false if input was invalid
bool promptInt(const std::string& msg, int& intOut) {
    std::cout << msg;
    std::string input = "";
    std::cin >> input;
    try {
        intOut = stoi(input);
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
    const double unionDues = 10;
    const double healthInsuranceForThreeDependents = 35;

    double wage = 0;
    double hoursWorked = 0;
    int numberOfDependents = 0;

    // Prompt user for hourly wage
    if (!promptDouble("Hourly wage: ", wage)) {
        std::cerr << "Hourly wage must be a number" << std::endl;
        exit(1);
    }

    // Prompt user for hours worked
    if (!promptDouble("Hours worked: ", hoursWorked)) {
        std::cerr << "Hours worked must be a number" << std::endl;
        exit(1);
    }

    // Prompt user for number of dependents
    if (!promptInt("Number of dependents: ", numberOfDependents)) {
        std::cerr << "Number of dependents must be an integer" << std::endl;
        exit(1);
    }
    else if (numberOfDependents < 0) {
        std::cerr << "Number of dependents must be greater than or equal to 0" << std::endl;
        exit(1);
    }

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
    std::cout << "Gross pay: $" << grossPay << std::endl;
    std::cout << "Social Security tax witheld: $" << ssTaxWitheld << std::endl;
    std::cout << "Federal income tax witheld: $" << fiTaxWitheld << std::endl;
    std::cout << "State income tax witheld: $" << siTaxWitheld << std::endl;
    std::cout << "Union dues: $" << unionDues << std::endl;
    std::cout << "Health insurace witheld: $" << healthInsuranceWitheld << std::endl;
    std::cout << "Pay remaining: $" << payRemaining << std::endl;

    // Reset output formatting
    std::cout.setf(resetFlags);
    std::cout.precision(resetPrecision);
}