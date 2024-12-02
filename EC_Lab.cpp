/*
Author: Shayton Wright
Date: 12/1/2024
Assignment: Extra credit lab for EECS 348
Purpose: Extract a double floating point number from a string and returns the number if the input is correct.
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
using namespace std;

double extractNumeric(const std::string& str) {
    int decimals = 0; //Initialize variable to keep track of the number of decimals.
    bool isNegative = false; //Initalize variable to keep track of if the number is negative or not. Preset to false.
    double result = 0.0; //Initialize temp result variable
    double decimalPlace = 0.1; //Temp variable that will be used to handle decimal places.
    bool foundNumber = false; //Temp variable to determine if a number was found during iteration, preset to false.
    std::set<char> nums = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; //Initialize set to hold all numeric values for comparison.

    for (size_t i = 0; i < str.length(); i++) { //Iterate over the length of the input string.
        char temp = str[i]; //Initalize temp variable that is the character at the strings index i.
        if (i == 0 && (temp == '+' || temp == '-')) { //Check in the first character that i is the sign of the double.
            isNegative = (temp == '-'); //Assign boolean output of comparison between temp and '-'. If temp is '-', then we set isNegative to true to be used later.
            continue; //Continue to skip the rest of the iteration because we don't need to do any more comparisons if we already know what the value is.
        }
        if (nums.find(temp) != nums.end()) { //Check if the temp variable is in our nums set.
            foundNumber = true; //Set foundNumber to true if so.
            if (decimals == 0) { //Check to see if a decimal has been encountered yet
                result = result * 10 + (temp - '0'); //Add to the whole number side of the result.
            } 
            else {
                result += (temp - '0') * decimalPlace; //If we have already encountered a decimal, signified by decimals being >0. Add to the decimal side of the result by adding temp multiplied by our decimalPlace variable.
                decimalPlace /= 10; //Update the decimalPlace variable to be ready for the next decimal place.
            }
        }
        else if (temp == '.') { //Check if temp is a decimal.
            decimals++; //Increment decimals if we find a decimal.
            if (decimals > 1) { //If we have more than two decimals, this is an invalid input so we will return -999999.99
                return -999999.99; 
            }
        }
        else { //If character is not a sign, decimal, or number in nums. We return -999999.99
            return -999999.99;
        }
    }
    if (foundNumber) { //If foundNumber is true (required for valid input) proceed.
        if (isNegative){ //If isNegative is true, return the negative version of our result variable.
            return -result;
        }
        else{ //If isNegative is false, return the result as is.
            return result;
        }
    } else { //Return -999999.99 if foundNumber is still false after iterating over the whole string. This indicates invalid input as no numbers were given.
        return -999999.99;
    }
}

int main() { //The following main was given in the assignment instructions. (Lines 52-73)
    string input;

    while (true) {
        cout << "Enter a string (or 'END' to quit): "; 
        cin >> input; 

        if (input == "END") { 
            break; 
        }

        double number = extractNumeric(input); 

        if (number != -999999.99) { 
            cout << "Input is: " << fixed << setprecision(4) 
            << number << endl;
        } else {
            cout << "The input is invalid." << endl;
        }
    }
    return 0;
}