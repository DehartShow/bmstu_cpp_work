#include "let6.h"

int main(int argc, char **argv) {
  std::fstream file(argv[1], std::ios::binary | std::ios::in);
  if (!file) {
    std::cout << "Ошибка открытия файла" << std::endl;
    return 1;
  }
  u_int32_t count_students;
  file.read(reinterpret_cast<char *>(&count_students), sizeof(count_students));

  std::vector<Student> students;
  students.resize(count_students);

  std::string user_command;
  user_command = argv[2];

  for (size_t i = 0; i < count_students, file.peek() != EOF; ++i) {
    Student student;
    std::getline(file, student.name, '\0');
    file.read(reinterpret_cast<char *>(&student.age), sizeof(int));
    file.read(reinterpret_cast<char *>(&student.rating), sizeof(int));
    students[i] = std::move(student);
  }

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