#include "str_equals.h"
#include "test_runner.h"

void test_equal_strings(void) {
    ASSERT_TRUE(str_equals("aaab", "aaab") == true);
    ASSERT_TRUE(str_equals("", "") == true);
}

void test_different_lengths(void) {
    ASSERT_TRUE(str_equals("aaab", "aa") == false);
    ASSERT_TRUE(str_equals("a", "") == false);
}

void test_same_length_different_content(void) {
    ASSERT_TRUE(str_equals("abcd", "abce") == false);
    ASSERT_TRUE(str_equals("abc", "def") == false);
}

void run_str_equals_tests(void) {
    test_equal_strings();
    test_different_lengths();
    test_same_length_different_content();
}
