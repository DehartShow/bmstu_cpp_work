//
// Created by dehart on 10/16/23.
//

#ifndef BMSTU_STRING_MAIN_H_
#define BMSTU_STRING_MAIN_H_

#include <iostream>

namespace bmstu {
    class string {
    private:
        /// приватные хелперы
        static size_t strlen_(const char *str) {
            size_t counter = 0;
            while (str[counter] != '\0')
                counter++;
            return counter;
        }

        void clean_() {
            if (!ptr_)
                return;

            size_ = 0;
            delete[] ptr_;
        }

        /// Поля класса
        char *ptr_ = nullptr;
        int size_;

    public:
        /// Конструктор по умолчанию
        string() {
            ptr_ = new char[1];
            ptr_[0] = '\0';
            size_ = 0;
        }

        /// Конструктор с параметром "cи строкой"
        string(const char *c_str) {
            size_ = strlen_(c_str);
            ptr_ = new char[size_ + 1];

            for (int i = 0; i < size_; ++i)
                ptr_[i] = c_str[i];

            ptr_[size_] = '\0';
        }

        /// Копирующий конструктор
        string(const string &other) {
            size_ = other.size_;
            ptr_ = new char[size_ + 1];

            for (int i = 0; i < size_; ++i)
                ptr_[i] = other.ptr_[i];

            ptr_[size_] = '\0';
        }

        /// Конструктор перемещения
        string(string &&dying) noexcept {
            size_ = dying.size_;
            ptr_ = new char[size_ + 1];

            for (int i = 0; i < size_; i++)
                ptr_[i] = dying[i];

            ptr_[size_] = '\0';

            dying.clean_();
        }

        /// Деструктор
        ~string() { clean_(); }

        // Output string data
        void print() { std::cout << ptr_ << std::endl; }

        /// Геттер на си-строку
        const char *c_str() const { return ptr_; }

        /// Геттер на размер
        size_t size() const { return size_; }

        /// Оператор копирующего присваивания
        string &operator=(const string &other) {
            size_ = other.size_;
            ptr_ = new char[size_ + 1];

            for (int i = 0; i < size_; ++i)
                ptr_[i] = other.ptr_[i];

            ptr_[size_] = '\0';
        }

        /// Оператор перемещающего присваивания
        string &operator=(string &&other) noexcept {
            size_ = other.size_;
            ptr_ = new char[size_ + 1];

            for (int i = 0; i < size_; i++)
                ptr_[i] = other[i];

            ptr_[size_] = '\0';

            other.clean_();

            return *this;
        }

        /// Оператор присваивания си строки
        string &operator=(const char *c_str) {
            size_ = strlen_(c_str);
            ptr_ = new char[size_ + 1];

            for (int i = 0; i < size_; i++)
                ptr_[i] = c_str[i];

            ptr_[size_] = '\0';
        }

        /* Все все понимают */
        friend string operator+(const string &left, const string &right) {
            int new_size_ = left.size_ + right.size_;
            char *new_array_ = new char[new_size_ + 1];

            for (int i = 0; i < left.size_; i++)
                new_array_[i] = left.ptr_[i];

            for (int i = 0; i < right.size_; i++)
                new_array_[left.size_ + i] = right.ptr_[i];

            new_array_[new_size_] = '\0';

            string out = new_array_;
            delete[] new_array_;

            return out;
        }

        friend std::ostream &operator<<(std::ostream &os, const string &obj) {
            os << obj.c_str();
            return os;
        }

        friend std::istream &operator>>(std::istream &is, string &obj) {
            int i = 0;
            char *input_str = new char[i];

            do {
                char sup = 0;
                is >> sup;
                input_str[i] = sup;
                if (sup == 0) {
                    break;
                }
                i++;
            } while (true);

            obj = input_str;
            delete[] input_str;

            return is;
        }

        string &operator+=(const string &other) {
            *this = (*this + other);
            return *this;
        }

        string &operator+=(char symbol) {
            int newsize_ = size_ + sizeof(symbol);

            char *out = new char[newsize_ + 1];
            for (int i = 0; i < size_; i++)
                out[i] = ptr_[i];

            out[newsize_ - 1] = symbol;
            out[newsize_] = '\0';

            *this = string(out);
            delete[] out;

            return *this;
        }

        char &operator[](size_t index) {
            return index > size_ ? ptr_[0] : ptr_[index];
        }
    };
}  // namespace bmstu



#endif  // BMSTU_STRING_MAIN_H_
