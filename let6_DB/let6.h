//
// Created by dehart on 11/11/23.
//
#ifndef LET6_DB_LET6_H_
#define LET6_DB_LET6_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
struct Student {
  std::string name;
  int age;
  int rating;
};
bool compare_by_rating(const Student &a, const Student &b) {
  return a.rating > b.rating;
}
bool compare_by_age(const Student &a, const Student &b) {
  return a.age > b.age;
}
bool compare_by_alphabet(const Student &a, const Student &b) {
  return a.name < b.name;
}

#endif  // LET6_DB_LET6_H_
