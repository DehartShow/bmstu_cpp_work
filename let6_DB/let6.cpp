//
// Created by dehart on 11/11/23.
//
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

int main() {
  std::string command;
  std::fstream file(
      "/home/dehart/BMSTU/cmake-example-repo/let6_DB/students.bin",
      std::ios::binary | std::ios::in);
  if (!file) {
    std::cout << "Ошибка открытия файла" << std::endl;
    return 1;
  }
  u_int32_t count_students;
  file.read((char *)&count_students, sizeof(count_students));

  std::vector<Student> students;
  students.resize(count_students);

  for (size_t i = 0; i < count_students, file.peek() != EOF; ++i) {
    Student student;
    std::getline(file, student.name, '\0');
    file.read((char *)&student.age, sizeof(int));
    file.read((char *)&student.rating, sizeof(int));
    students[i] = std::move(student);
  }

  std::string user_command;
  std::cout << "Введите команду:";
  std::cin >> user_command;

  if (user_command == "-a") {
    std::sort(students.begin(), students.end(), compare_by_age);
    std::vector<Student>::iterator beg = students.begin();
    std::vector<Student>::iterator top = students.begin() + 15;
    for (auto it = beg; beg != top; ++beg) {
      std::cout << beg->name << std::endl;
    }
  } else if (user_command == "-o") {
    std::sort(students.begin(), students.end(), compare_by_age);
    std::sort(students.begin(), students.end(), compare_by_alphabet);
    std::vector<Student>::iterator beg = students.begin();
    std::vector<Student>::iterator top = students.begin() + 15;
    for (auto it = beg; beg != top; ++beg) {
      std::cout << beg->name << std::endl;
    }
  } else if (user_command == "-g") {
    std::sort(students.begin(), students.end(), compare_by_rating);
    std::vector<Student>::iterator beg = students.begin();
    std::vector<Student>::iterator top = students.begin() + 15;
    for (auto it = beg; beg != top; ++beg) {
      std::cout << beg->name << std::endl;
    }
  } else if (user_command == "-r") {
    std::sort(students.begin(), students.end(), compare_by_rating);
    std::sort(students.begin(), students.end(), compare_by_alphabet);
    std::vector<Student>::iterator beg = students.begin();
    std::vector<Student>::iterator top = students.begin() + 15;
    for (auto it = beg; beg != top; ++beg) {
      std::cout << beg->name << std::endl;
    }
  } else {
    std::cout << "Введена неверная команда" << std::endl;
  }
}