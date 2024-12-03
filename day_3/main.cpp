#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

/*
 A struct Function is a custom data type that bundles two related integers together - in this case, the two numbers from the mul() function. 
It helps organize the code by:

* Passing both numbers together as one unit
* Making the function's return values clearer
* Avoiding multiple output parameters

Instead of having separate variables or complex return types, we can work with both numbers as one logical unit.
*/

struct Function {
   int num1;
   int num2;
};


bool isValidFunction( const std::string& text, size_t pos, Function& func) {
    //checks for mul prefifx
    if (pos + 3 >= text.length() || text.substr(pos, 3) != "mul") return false;
    pos +=3;

    //checks fore opening parentheseis
    if (pos >= text.length() || text[pos] != '(') return false;
    pos ++;

    //get first number
    std::string num1;
    while (pos < text.length() && isdigit(text[pos])) {
        num1 += text[pos++];
    }

    if (num1.empty()) return false;

    //check for comma
    if (pos >= text.length() || text[pos] != ',') return false;
    pos++;

    //get second number
    std::string num2;

    while (pos < text.length() && isdigit(text[pos])) {
        num2 += text[pos++];
    }
    if (num2.empty()) return false;


    if (pos < text.length() && text[pos] == ')') {
       func.num1 = std::stoi(num1);
       func.num2 = std::stoi(num2);
       return true;
   }
   return false;
}
// do and dont flags for part 2 
bool checkDoSequence(const std::string& text, size_t pos) {
    return (pos + 4 < text.length() && text.substr(pos,4) == "do()");

}
bool checkDontSequence(const std::string& text, size_t pos) {
    return (pos + 7 < text.length() && text.substr(pos,7) == "don't()");
    
}


int main() {
    
    std::cout << "Advent of code day 3\n";
    std::ifstream file("input.txt");
    char ch;
    std::vector<char> chars; //stores characters in a list
    std::string sequence; //tracks the sequence
    int sum = 0;
    int sum_do = 0;
    bool do_flag = true;


    while (file.get(ch)) {
        chars.push_back(ch); //stores each character in a vector

    }

    //iterate through characters

        // do and dont sequence for part 2 
    for (size_t i = 0; i < chars.size(); i++) {
        if (checkDoSequence(std::string(chars.begin(), chars.end()), i)) {

            do_flag = true;
            continue;
        }
        if (checkDontSequence(std::string(chars.begin(), chars.end()), i)) {

            do_flag = false;
            continue;

        }

        Function func;
        if (isValidFunction(std::string(chars.begin(), chars.end()), i, func)) {
            sum += func.num1 * func.num2;

        }
        if (isValidFunction(std::string(chars.begin(), chars.end()), i, func)&& do_flag) {
            sum_do += func.num1 * func.num2;

        }
    }

    std::cout << " Sum of all valid function's results: " << sum << "\n";
    std::cout << " Sum of all valid function's results with the 'Do' flag: " << sum_do << "\n";
    file.close();
    return 0;


};