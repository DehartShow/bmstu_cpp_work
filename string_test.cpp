#include <gtest/gtest.h>
#include "bmstu_string/main.h"

using namespace bmstu;


TEST(BMSTU_Test, test1) {
    string a = "NIGGERS";
    ASSERT_EQ(a[0], 'N');
    ASSERT_EQ(a[1], 'I');
    ASSERT_EQ(a[2], 'G');
    ASSERT_EQ(a[3], 'G');
}

TEST(BMSTU_test, sum) {
    string str_1("iu10");
    string str_2("-16");
    string str_3 = str_1 + str_2;
    ASSERT_STREQ(str_3.c_str(), "iu10-16");
}



TEST(BMSTU_test, test2) {
    string str_1("2389");
    ASSERT_EQ(str_1.size(), 4);
    string str_2(" ");
    ASSERT_EQ(str_2.size(), 1);
    string str_3(str_1);
    ASSERT_EQ(str_3.size(), str_1.size());
    string &str_1_ref = str_1;
    ASSERT_EQ(str_1_ref.size(), str_1.size());
    string sum_str_1_2 = str_1 + str_2;
    ASSERT_EQ(sum_str_1_2.size(), str_1.size() + str_2.size());
    string &sum_str_1_str_2_ref = sum_str_1_2;
    string complex_str = sum_str_1_str_2_ref + str_1_ref;
    ASSERT_EQ(complex_str.size(), str_1.size() + str_2.size() + str_1_ref.size());
    string str_4 = "DOTA2";
    string str_5 = str_4 + str_1;
    ASSERT_EQ(str_5.size(), 9);
}

TEST(BMSTU_test, test_c_str) {
    string str_1("Ershov is the BEST!!!");
    ASSERT_STREQ(str_1.c_str(), "Ershov is the BEST!!!");
    string str_2("");
    ASSERT_STREQ(str_2.c_str(), "");
    string str_3("1233456*&%&%___asfdgfQEWRWQEW");
    ASSERT_STREQ(str_3.c_str(), "1233456*&%&%___asfdgfQEWRWQEW");
}

TEST(BMSTU_test, ostream) {
    string str_1("BMSTU");
    std::stringstream os_1;
    os_1 << str_1;
    EXPECT_STREQ(os_1.str().c_str(), "BMSTU");
    EXPECT_EQ(os_1.str().size(), 5);
    string str_2(" ");
    std::stringstream os_2;
    os_2 << str_2;
    EXPECT_STREQ(os_2.str().c_str(), " ");
    EXPECT_EQ(os_2.str().size(), 1);
    string str_3;
    std::stringstream os_3;
    os_3 << str_3;
    EXPECT_STREQ(os_3.str().c_str(), "");
    EXPECT_EQ(os_3.str().size(), 0);
}

TEST(BMSTU_test, constructor_from_char) {
    const char *charArray = "Hello, Dehart!";
    string str_1(charArray);
    EXPECT_EQ(str_1.size(), strlen(charArray));
    EXPECT_STREQ(str_1.c_str(), charArray);
}

TEST(BMSTU_test, copy_constructor) {
    const char *charArray = "Hello, Dehart!";
    string str_1(charArray);
    string copy_str(str_1);
    EXPECT_EQ(str_1.size(), copy_str.size());
    EXPECT_STREQ(str_1.c_str(), copy_str.c_str());
}

TEST(BMSTU_test, concatenation) {
    string first_str("Hello, ");
    string second_str("Dehart!");
    string result = first_str + second_str;
    EXPECT_STREQ(result.c_str(), "Hello, Dehart!");
}

