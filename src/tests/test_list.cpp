#include "tests.h"

using namespace s21;

TEST(CustomS21_List_TestListTest, ConstructorAndSize) {
  s21::list<int> list1;
  EXPECT_EQ(list1.size(), 0);

  s21::list<int> list2(5);
  EXPECT_EQ(list2.size(), 5);

  s21::list<int> list3{1, 2, 3, 4, 5};
  EXPECT_EQ(list3.size(), 5);

  s21::list<int> list4(list3);
  EXPECT_EQ(list4.size(), 5);

  s21::list<int> list5 = std::move(list4);
  EXPECT_EQ(list5.size(), 5);

  s21::list<int> list6;
  list6 = list2;
  EXPECT_EQ(list5.size(), 5);
}
TEST(S21_List_Test, PushBackAndFront) {
  s21::list<int> list;
  list.push_back(1);
  list.push_back(2);

  EXPECT_EQ(list.front(), 1);
  EXPECT_EQ(list.size(), 2);
}
TEST(S21_List_Test, PushFrontAndBack) {
  s21::list<int> list;
  list.push_front(1);
  list.push_front(2);

  EXPECT_EQ(list.back(), 1);
  EXPECT_EQ(list.front(), 2);
  EXPECT_EQ(list.size(), 2);
}
TEST(S21_List_Test, Clear) {
  s21::list<int> list{1, 2, 3, 4, 5};
  list.clear();

  EXPECT_EQ(list.size(), 0);
  EXPECT_TRUE(list.empty());
}
TEST(S21_List_Test, Erase) {
  s21::list<int> list{1, 2, 3, 4, 5};
  auto it = list.begin();
  ++it;
  ++it;
  list.erase(it);

  EXPECT_EQ(list.size(), 4);
  auto newIt1 = list.begin();
  ++newIt1;
  list.erase(newIt1);
  auto newIt = list.begin();
  EXPECT_EQ(*newIt, 1);
  ++newIt;
  EXPECT_EQ(*newIt, 4);
}
TEST(S21_List_Test, PopFrontEmptyList) {
  s21::list<int> list;
  EXPECT_EQ(list.size(), 0);
  list.pop_front();
  EXPECT_EQ(list.size(), 0);
}
TEST(S21_List_Test, PopFrontSingleElement) {
  s21::list<int> list;
  list.push_front(1);
  EXPECT_EQ(list.size(), 1);
  list.pop_front();
  EXPECT_EQ(list.size(), 0);
}
TEST(S21_List_Test, PopFrontMultipleElements) {
  s21::list<int> list;
  list.push_front(1);
  list.push_front(2);
  EXPECT_EQ(list.size(), 2);
  list.pop_front();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.front(), 1);
}

TEST(S21_List_Test, IteratorsBegin) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator our_it = our_list.begin();
  std::list<int>::iterator std_it;
  std_it = std_list.begin();
  EXPECT_EQ(*our_it, *std_it);
}

TEST(S21_List_Test, Iterators1) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator it1 = ++our_list.begin();
  std::list<int>::iterator it2 = ++std_list.begin();
  it1 = --it1;
  it2 = --it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(S21_List_Test, IteratorsEqual) {
  s21::list<int> our_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};
  s21::list<int>::iterator it1 = ++our_list.begin();
  std::list<int>::iterator it2 = ++std_list.begin();
  bool eq = 0;
  if (*it1 == *it2) eq = 1;
  it1 = --it1;
  it2 = --it2;
  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(eq, 1);
}

TEST(S21_List_Test, Swap) {
  s21::list<int> our_list1 = {1, 2, 3};
  s21::list<int> our_list2;
  our_list2.swap(our_list1);
  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2;
  std_list2.swap(std_list1);
  EXPECT_EQ(std_list2.size(), our_list2.size());
  EXPECT_EQ(our_list2.size(), 3);
}

TEST(S21_List_Test, Sort) {
  s21::list<int> our_list1 = {1, 7, 3};
  our_list1.sort();
  std::list<int> std_list1 = {1, 7, 3};
  std_list1.sort();
  auto it = our_list1.begin();
  ++it;
  auto it1 = std_list1.begin();
  ++it1;
  EXPECT_EQ(*it, *it1);
  EXPECT_EQ(*it1, 3);
}

TEST(S21_List_Test, Merge) {
  s21::list<int> our_list1 = {1, 21, 3};
  s21::list<int> our_list2 = {2, 23};
  our_list2.merge(our_list1);
  std::list<int> std_list1 = {1, 21, 3};
  std::list<int> std_list2 = {2, 23};
  std_list2.merge(std_list1);
  auto it = our_list2.begin();
  ++it;
  auto it1 = std_list2.begin();
  ++it1;
  EXPECT_EQ(*it, *it1);
  EXPECT_EQ(*it1, 2);
}

TEST(S21_List_Test, Splice) {
  s21::list<int> our_list1 = {1, 21, 3};
  s21::list<int> our_list2 = {2, 23};
  s21::list<int>::const_iterator our_const_it = our_list2.begin();
  our_list2.splice(our_const_it, our_list1);
  std::list<int> std_list1 = {1, 21, 3};
  std::list<int> std_list2 = {2, 23};
  std::list<int>::const_iterator std_const_it = std_list2.begin();
  std_list2.splice(std_const_it, std_list1);
  auto it = our_list2.begin();
  ++it;
  auto it1 = std_list2.begin();
  ++it1;
  EXPECT_EQ(*it, *it1);
  EXPECT_EQ(std_list2.size(), our_list2.size());
  EXPECT_EQ(*it, 21);
}

TEST(S21_List_Test, Insert) {
  s21::list<int> our_list1 = {1, 21, 3};
  std::list<int> std_list1 = {1, 21, 3};
  auto it_b = our_list1.begin();
  auto it_b1 = std_list1.begin();
  our_list1.insert(it_b, 5);
  std_list1.insert(it_b1, 5);
  auto it = our_list1.begin();
  auto it1 = std_list1.begin();
  EXPECT_EQ(*it, *it1);
  EXPECT_EQ(std_list1.size(), our_list1.size());
  EXPECT_EQ(*it1, 5);
}

TEST(S21_List_Test, Reverse) {
  s21::list<int> our_list1 = {1, 21, 3};
  std::list<int> std_list1 = {1, 21, 3};
  our_list1.reverse();
  std_list1.reverse();
  auto it = our_list1.begin();
  auto it1 = std_list1.begin();
  EXPECT_EQ(*it, *it1);
  EXPECT_EQ(std_list1.size(), our_list1.size());
  EXPECT_EQ(*it1, 3);
}

TEST(S21_List_Test, Unique) {
  s21::list<int> our_list1 = {1, 21, 21, 3, 3, 3, 21, 3};
  std::list<int> std_list1 = {1, 21, 21, 3, 3, 3, 21, 3};
  our_list1.unique();
  std_list1.unique();
  auto it = our_list1.begin();
  auto it1 = std_list1.begin();
  ++it;
  ++it1;
  ++it;
  ++it1;
  EXPECT_EQ(*it, *it1);
  EXPECT_EQ(std_list1.size(), our_list1.size());
  EXPECT_EQ(*it1, 3);
}

int list(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}