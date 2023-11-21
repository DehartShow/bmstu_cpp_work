//
// Created by dehart on 11/21/23.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool palindrome(std::string &word) {
    for (size_t i = 0; i < (word.size() / 2 + 1); ++i) {
        if (tolower(word[i]) != tolower(word[word.size() - i - 1])) {
            return false;
        }
    }
    return true;
}

void printPalindromes(std::vector<std::string> palindromes) {
    std::cout << "{" << "\n\t \"count_palindromes\": " << palindromes.size()
              << "\n\t \"palindromes\": [";
    for (size_t i = 0; i < palindromes.size(); ++i) {
        if (i != (palindromes.size() - 1)) {
            std::cout << "\"" << palindromes[i] << "\", ";
        } else {
            std::cout << "\"" << palindromes[i] << "\"";
        }
    }
    std::cout << "]" << "\n}";
}

int main(int argc, char **argv) {
    std::vector<std::string> result;
    std::ifstream in;
    in.open(argv[1]);
    std::string line;
    if (!in) {
        std::cout << "File note open!";
        return -1;
    }
    while (std::getline(in, line)) {
        if (palindrome(line)) {
            result.push_back(line);
        }
    }
    printPalindromes(result);
}
