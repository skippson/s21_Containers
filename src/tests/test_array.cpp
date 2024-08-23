#include "tests.h"

class TestArray {
 public:
  s21::array<int, 0> s21_array_empty;
  s21::array<int, 3> copy_array{234, 21, 11};
  s21::array<char, 0> copy_ar1;
  s21::array<double, 5> copy_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  s21::array<double, 5> copy_array2{-5.3, 1.18, -4.3, 255.34, 1.23};

  std::array<int, 0> std_array_empty;
  std::array<int, 3> orig_array{234, 21, 11};
  std::array<char, 0> orig_ar1;
  std::array<double, 5> orig_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  std::array<double, 5> orig_array2{-5.3, 1.18, -4.3, 255.34, 1.23};
};

TEST(Array, constructor_default) {
  TestArray tester;
  EXPECT_EQ(tester.s21_array_empty.size(), tester.std_array_empty.size());
  EXPECT_EQ(tester.s21_array_empty.empty(), tester.std_array_empty.empty());
}

TEST(Array, constructor_initializer) {
  TestArray tester;
  EXPECT_EQ(tester.copy_array1[1], tester.orig_array1[1]);
  EXPECT_EQ(tester.copy_array1.front(), tester.orig_array1.front());
  EXPECT_EQ(tester.copy_array1.back(), tester.orig_array1.back());
  EXPECT_EQ(tester.copy_array1.size(), tester.orig_array1.size());
  EXPECT_EQ(tester.copy_array1.empty(), tester.orig_array1.empty());
}

TEST(Array, constructor_copy_empty) {
  TestArray tester;
  s21::array<int, 0> s21_array_empty;
  s21::array<int, 0> s21_array_copy(tester.s21_array_empty);
  EXPECT_EQ(s21_array_empty.size(), s21_array_copy.size());
  EXPECT_EQ(s21_array_empty.empty(), s21_array_copy.empty());
}

TEST(Array, simple_test) {
  TestArray logger;
  for (int i{}; i < 3; i++)
    ASSERT_EQ(logger.orig_array.at(i), logger.copy_array.at(i));
  ASSERT_EQ(logger.orig_array.size(), logger.copy_array.size());
  ASSERT_EQ(logger.orig_array.max_size(), logger.copy_array.max_size());
  ASSERT_EQ(logger.orig_ar1.empty(), logger.copy_ar1.empty());
}
TEST(Array, swap_test) {
  TestArray logger;
  logger.orig_array1.swap(logger.orig_array2);
  logger.copy_array1.swap(logger.copy_array2);
  for (int i{}; i < 5; i++) {
    ASSERT_DOUBLE_EQ(logger.orig_array1[i], logger.copy_array1[i]);
    ASSERT_DOUBLE_EQ(logger.orig_array2[i], logger.copy_array2[i]);
  }
  ASSERT_EQ(logger.orig_array1.size(), logger.copy_array1.size());
  ASSERT_EQ(logger.orig_array2.max_size(), logger.copy_array2.max_size());
  ASSERT_EQ(logger.orig_array1.front(), logger.copy_array1.front());
  ASSERT_EQ(logger.orig_array2.front(), logger.copy_array2.front());
  ASSERT_EQ(logger.orig_array1.back(), logger.copy_array1.back());
  ASSERT_EQ(logger.orig_array2.back(), logger.copy_array2.back());
}

TEST(Array, copy_constructor_test) {
  std::array<int, 3> orig_array3{234, 21, 11};
  s21::array<int, 3> copy_array3{234, 21, 11};
  std::array<int, 3> orig_array4(orig_array3);
  s21::array<int, 3> copy_array4(copy_array3);
  for (int i{}; i < 3; i++) {
    ASSERT_EQ(orig_array3.at(i), copy_array3.at(i));
    ASSERT_EQ(orig_array4.at(i), copy_array4.at(i));
  }
  ASSERT_EQ(orig_array3.size(), copy_array3.size());
  ASSERT_EQ(orig_array3.max_size(), copy_array3.max_size());
  ASSERT_EQ(orig_array4.size(), copy_array4.size());
  ASSERT_EQ(orig_array4.max_size(), copy_array4.max_size());
  std::array<char, 0> orig_ar5;
  s21::array<char, 0> copy_ar5;
  std::array<char, 0> orig_ar6(orig_ar5);
  s21::array<char, 0> copy_ar6(copy_ar5);
  ASSERT_EQ(orig_ar5.empty(), copy_ar5.empty());
  ASSERT_EQ(orig_ar6.empty(), copy_ar6.empty());
}

TEST(Array, move_constructor_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2(std::move(orig_array1));
  s21::array<int, 5> copy_array2(std::move(copy_array1));
  for (size_t i = 0; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, move_operator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2{25};
  s21::array<int, 5> copy_array2{25};
  orig_array2 = std::move(orig_array1);
  copy_array2 = std::move(copy_array1);
  for (size_t i = 0; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, iterator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  int *orig_beg = orig_array1.begin();
  int *copy_beg = copy_array1.begin();
  int *orig_end = orig_array1.end();
  int *copy_end = copy_array1.end();
  while (orig_beg < orig_end && copy_beg < copy_end) {
    ASSERT_EQ(*orig_beg++, *copy_beg++);
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  s21::array<char, 0> copy_ar1;
  ASSERT_TRUE(copy_ar1.begin() == copy_ar1.end());
  s21::array<double, 3> my_arr{2.3, 4.5555, 6.1234};
  double *d = my_arr.data();
  ASSERT_DOUBLE_EQ(my_arr[0], *d);
}

TEST(Array, fill_test) {
  std::array<size_t, 10> orig_array;
  s21::array<size_t, 10> my_arr;
  orig_array.fill(555);
  my_arr.fill(555);
  for (size_t i = 0; i < orig_array.size(); i++)
    ASSERT_EQ(orig_array[i], my_arr[i]);
  ASSERT_EQ(orig_array.size(), my_arr.size());
  ;
}