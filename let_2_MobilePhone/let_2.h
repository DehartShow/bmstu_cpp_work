//
// Created by dehart on 10/16/23.
//
#ifndef LET_2_MOBILEPHONE_LET_2_H_
#define LET_2_MOBILEPHONE_LET_2_H_
#include <iostream>

struct MobilePhone {
  double weight;
  bool is_broken;
  double price;
};

int main() {
  int count;
  std::cin >> count;
  const int kCount_of_phones = count;
  MobilePhone phones[kCount_of_phones];
  if (kCount_of_phones == 0) {
    std::cout << "<MobilePhone>" << std::endl << "</MobilePhone>";
    return 0;
  }
  for (int i = 0; i < kCount_of_phones; i++) {
    std::cin >> phones[i].weight >> phones[i].is_broken >> phones[i].price;
  }
  std::cout << "<MobilePhone>" << std::endl;
  for (int i = 0; i < kCount_of_phones; i++) {
    std::cout << "\tMobilePhone id=\"" << i + 1 << "\" weight=\""
              << phones[i].weight << "\" is_broken=\"" << std::boolalpha
              << phones[i].is_broken << "\" price=\"" << phones[i].price
              << "\"/>" << std::endl;
  }
  std::cout << "</MobilePhone>";
  return 0;
}

#endif  // LET_2_MOBILEPHONE_LET_2_H_
