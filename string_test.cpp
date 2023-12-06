#include <gtest/gtest.h>

#include "bmstu_string/bmstu_string.h"
#include <iostream>
#include <utility>
using bmstu::basic_string;

TEST(BMSTU_Test, test1) {
  bmstu::string a("NIGGERS");
  ASSERT_EQ(a[0], 'N');
  ASSERT_EQ(a[1], 'I');
  ASSERT_EQ(a[2], 'G');
  ASSERT_EQ(a[3], 'G');
}

TEST(BMSTUTetst, EmptyCStr) {
  bmstu::string a("");
  EXPECT_STREQ(a.c_str(), "");
}

TEST(BMSTUTest, concatenation) {
  bmstu::string first_str("Hello, ");
  bmstu::string second_str("Dehart!");
  bmstu::string result = first_str + second_str;
  EXPECT_STREQ(result.c_str(), "Hello, Dehart!");
}

TEST(BMSTUtest, test2) {
  bmstu::string str_1("2389");
  ASSERT_EQ(str_1.size(), 4);
  bmstu::string str_2(" ");
  ASSERT_EQ(str_2.size(), 1);
  bmstu::string str_3(str_1);
  ASSERT_EQ(str_3.size(), str_1.size());
  bmstu::string&str_1_ref = str_1;
  ASSERT_EQ(str_1_ref.size(), str_1.size());
  bmstu::string sum_str_1_2 = str_1 + str_2;
  ASSERT_EQ(sum_str_1_2.size(), str_1.size() + str_2.size());
  bmstu::string&sum_str_1_str_2_ref = sum_str_1_2;
  bmstu::string complex_str = sum_str_1_str_2_ref + str_1_ref;
  ASSERT_EQ(complex_str.size(), str_1.size() + str_2.size() + str_1_ref.size());
  bmstu::string str_4("DOTA2");
  bmstu::string str_5 = str_4 + str_1;
  ASSERT_EQ(str_5.size(), 9);
}

TEST(BMSTUTest, test_c_str) {
  bmstu::string str_1("Ershov is the BEST!!!");
  ASSERT_STREQ(str_1.c_str(), "Ershov is the BEST!!!");
  bmstu::string str_2("");
  ASSERT_STREQ(str_2.c_str(), "");
  bmstu::string str_3("1233456*&%&%___asfdgfQEWRWQEW");
  ASSERT_STREQ(str_3.c_str(), "1233456*&%&%___asfdgfQEWRWQEW");
}

TEST(BMSTUTest, ostream) {
  bmstu::string str_1("BMSTU");
  std::stringstream os_1;
  os_1 << str_1;
  EXPECT_STREQ(os_1.str().c_str(), "BMSTU");
  EXPECT_EQ(os_1.str().size(), 5);
  bmstu::string str_2(" ");
  std::stringstream os_2;
  os_2 << str_2;
  EXPECT_STREQ(os_2.str().c_str(), " ");
  EXPECT_EQ(os_2.str().size(), 1);
  bmstu::string str_3;
  std::stringstream os_3;
  os_3 << str_3;
  EXPECT_STREQ(os_3.str().c_str(), "");
  EXPECT_EQ(os_3.str().size(), 0);
}

TEST(BMSTUTest, istream) {
  bmstu::string str1("123");
  std::stringstream os;
  os << str1;
  EXPECT_STREQ("123", os.str().c_str());
}

TEST(BMSTUTest, constructor_from_char) {
  const char* charArray = "Hello, Dehart!";
  bmstu::string str_1(charArray);
  EXPECT_EQ(str_1.size(), strlen(charArray));
  EXPECT_STREQ(str_1.c_str(), charArray);
}

TEST(BMSTUTest, copy_constructor) {
  const char* charArray = "Hello, Dehart!";
  bmstu::string str_1(charArray);
  bmstu::string copy_str(str_1);
  EXPECT_EQ(str_1.size(), copy_str.size());
  EXPECT_STREQ(str_1.c_str(), copy_str.c_str());
}

TEST(BMSTUTest, move_constructor) {
  bmstu::string str_1("Hello, Dehart!");
  bmstu::string copy_str(std::move(str_1));
  EXPECT_EQ(str_1.size(), 0);
  EXPECT_EQ(copy_str.size(), 14);
  EXPECT_STREQ(copy_str.c_str(), "Hello, Dehart!");
}

TEST(StringTest, DefaultConstructor) {
  bmstu::string str;
  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, DefaultConstructorW) {
  bmstu::wstring str;
  ASSERT_STREQ(str.c_str(), L"");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorW) {
  bmstu::wstring str{};
  ASSERT_STREQ(str.c_str(), L"");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructor) {
  bmstu::wstring str{};
  ASSERT_STREQ(str.c_str(), L"");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorNonEmpty) {
  bmstu::wstring str{L'С', L'Л', L'О', L'В', L'О'};
  ASSERT_STREQ(str.c_str(), L"СЛОВО");
  ASSERT_EQ(str.size(), 5);
}

TEST(StringTest, ConstructorSizeW) {
  bmstu::wstring str(10);
  ASSERT_STREQ(str.c_str(), L"          ");
  ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSize) {
  bmstu::string str(10);
  ASSERT_STREQ(str.c_str(), "          ");
  ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSizeOne) {
  bmstu::wstring str(1);
  ASSERT_STREQ(str.c_str(), L" ");
  ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, FromCStr) {
  bmstu::string str("str\n");
  ASSERT_STREQ(str.c_str(), "str\n");
  ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStr) {
  bmstu::wstring str(L"おはよう");
  ASSERT_STREQ(str.c_str(), L"おはよう");
  ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStrSymbol) {
  bmstu::wstring str(L"おはよう");
  ASSERT_STREQ(str.c_str(), L"おはよう");
  wchar_t c = L'お';
  ASSERT_EQ(str[0], c);
}

TEST(StringTest, USymbolsW) {
  bmstu::wstring str(L"お");
  ASSERT_STREQ(str.c_str(), L"お");
  wchar_t c = L'お';
  ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, USymbol) {
  bmstu::string str("\xe3\x81\x8a\x00");
  ASSERT_STREQ(str.c_str(), "お");
  ASSERT_EQ(str.size(), 3);
}


TEST(StringTest, USymbols) {
  bmstu::string str("おはよう");
  ASSERT_STREQ(str.c_str(), "おはよう");
  ASSERT_EQ(str.size() + 1, sizeof("おはよう"));
}

TEST(StringTest, Empty) {
  bmstu::string empty;
  ASSERT_EQ(empty.size(), 0);
  ASSERT_STREQ(empty.c_str(), "");
}

TEST(StringTest, EmptyW) {
  bmstu::wstring empty;
  ASSERT_EQ(empty.size(), 0);
  ASSERT_STREQ(empty.c_str(), L"");
}

TEST(StringTest, CopyAssignW) {
  bmstu::wstring empty(L"Non Empty строка");
  bmstu::wstring nonempty = empty;
  ASSERT_STREQ(nonempty.c_str(), L"Non Empty строка");
  ASSERT_EQ(nonempty.size(), 16);
}

TEST(StringTest, CopyConstructor) {
  bmstu::string empty("Non Empty строка");
  bmstu::string nonempty = empty;
  ASSERT_STREQ(nonempty.c_str(), "Non Empty строка");
  ASSERT_EQ(nonempty.size(), sizeof("Non Empty строка") - 1);
}

TEST(StringTest, CopyAssignConstructor) {
  bmstu::string* str = new bmstu::string("str");
  bmstu::string* nonempty = new bmstu::string;
  *nonempty = *str;
  ASSERT_STREQ(nonempty->c_str(), "str");
  ASSERT_EQ(nonempty->size(), sizeof("str") - 1);
  delete str;
  delete nonempty;
}

TEST(StringTest, MoveAssignConstructor) {
  bmstu::string str = "str";
  bmstu::string str2 = "other";
  str2 = std::move(str);
  ASSERT_STREQ(str2.c_str(), "str");
  ASSERT_EQ(str2.size(), sizeof("str") - 1);

  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructor2) {
  bmstu::string str = "str";
  bmstu::string str2 = "other";
  str2 = std::move(str);
  ASSERT_STREQ(str2.c_str(), "str");
  ASSERT_EQ(str2.size(), sizeof("str") - 1);

  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, CopyAssignConstructor2) {
  bmstu::string str = "str";
  bmstu::string str2(bmstu::string("other"));
  str2 = std::move(str);
  ASSERT_STREQ(str2.c_str(), "str");
  ASSERT_EQ(str2.size(), sizeof("str") - 1);

  ASSERT_STREQ(str.c_str(), "");
  ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructorW) {
  bmstu::wstring str2(std::move(bmstu::wstring(L"other")));
  ASSERT_STREQ(str2.c_str(), L"other");
  ASSERT_EQ(str2.size(), (sizeof(L"other") / sizeof(wchar_t)) - 1);
}

TEST(StringTest, CStrCopyAssign) {
  const char* str = "Simple Str";
  bmstu::string b_str;
  b_str = str;
  ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, CStrCopyAssignW) {
  const wchar_t* str = L"Простая строка";
  bmstu::wstring b_str;
  b_str = str;
  ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, AssignCStr) {
  bmstu::wstring str = L"123456789";
  ASSERT_STREQ(str.c_str(), L"123456789");
}

TEST(StringTest, ConcatOpW) {
  bmstu::wstring a_str(L"right");
  bmstu::wstring b_str(L"_left");
  auto c_str = a_str + b_str;
  ASSERT_STREQ(c_str.c_str(), L"right_left");
}

TEST(StringTest, ConcatOp) {
  bmstu::string a_str("right");
  bmstu::string b_str("_left");
  auto c_str = a_str + b_str;
  ASSERT_STREQ(c_str.c_str(), "right_left");
}

TEST(StringTest, OStream) {
  bmstu::string a_str("String value");
  std::stringstream ss;
  ss << a_str;
  ASSERT_STREQ(ss.str().c_str(), "String value");
}

TEST(StringTest, OStreamW) {
  bmstu::wstring a_str(L"String значение");
  std::wstringstream ss;
  ss << a_str;
  ASSERT_STREQ(ss.str().c_str(), L"String значение");
}

TEST(StringTest, IStream) {
  std::stringstream ss;
  ss.str("Value of\nstring");
  bmstu::string a_str;
  std::string a;
  ss >> a_str;
  ASSERT_STREQ(a_str.c_str(), "Value of\nstring");
}

TEST(StringTest, IStreamW) {
  std::wstringstream ss;
  ss.str(L"Value of\nстрока");
  bmstu::wstring a_str;
  ss >> a_str;
  ASSERT_STREQ(a_str.c_str(), L"Value of\nстрока");
}

TEST(StringTest, IStreamWNewLine) {
  std::wstringstream ss;
  ss.str(L"Value of\nstring");
  bmstu::wstring a_str;
  ss >> a_str;
  ASSERT_STREQ(ss.str().c_str(), L"Value of\nstring");
}

TEST(StringTest, ConcatSymbol) {
  bmstu::wstring a_str;
  a_str += L'S';
  ASSERT_STREQ(a_str.c_str(), L"S");
  a_str += L'т';
  ASSERT_STREQ(a_str.c_str(), L"Sт");
  a_str += L'р';
  ASSERT_STREQ(a_str.c_str(), L"Sтр");
  ASSERT_EQ(a_str.size(), 3);
}

TEST(StringTest, Item) {
  bmstu::wstring a_str(L"СТРОКААГ");
  ASSERT_EQ(a_str[0], L'С');
  ASSERT_EQ(a_str[1], L'Т');
  ASSERT_EQ(a_str[a_str.size() - 1], L'Г');
}