#include "tests.h"

namespace {
TEST(multiset, ConstructorDefaultSet) {
  s21::multiset<char> my_empty_set;
  std::multiset<char> orig_empty_set;
  EXPECT_TRUE(my_empty_set.empty());
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(multiset, ConstructorInitializerSet) {
  s21::multiset<int> my_set = {'x', 'b', 'z', 'y'};
  std::multiset<int> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  //   std::cout << my_set.size() << "YES" << std::endl;
  //   auto my_it = my_set.begin();
  //   auto orig_it = orig_set.begin();
  //   for (; my_it != my_set.end(); ++my_it, ++orig_it) {
  //     EXPECT_TRUE(*orig_it == *my_it);
  //   }
}

TEST(multiset, ConstructorInitializer2Set) {
  s21::multiset<char> my_set = {};
  std::multiset<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, ConstructorCopySet) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 6, 9};
  std::multiset<int> orig_set = {1, 2, 3, 4, 6, 9};
  EXPECT_EQ(my_set.size(), orig_set.size());
  s21::multiset<int> my_set_copy = my_set;
  std::multiset<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, SetIteratorsSet) {
  s21::multiset<std::string> my_set = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_set = {"This", "is", "my", "multiset"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  ++my_it;
  ++orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(multiset, ConstructorMoveSet) {
  s21::multiset<int> my_set = {1, 2, 3, 4, 5};
  std::multiset<int> orig_set = {1, 2, 3, 4, 5};
  s21::multiset<int> my_set_copy = std::move(my_set);
  std::multiset<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

//

TEST(multiset, CapacitySet) {
  s21::multiset<char> my_empty_set;
  std::multiset<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(multiset, ClearSet) {
  s21::multiset<char> my_empty_set;
  std::multiset<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(multiset, InsertSet1) {
  s21::multiset<int> my_set = {3, 4, 5, 6};
  std::multiset<int> orig_set = {3, 4, 5, 6};
  auto my_pr = my_set.insert(7);
  auto orig_pr = orig_set.insert(7);
  EXPECT_TRUE(*my_pr == *orig_pr);
  my_pr = my_set.insert(8);
  orig_pr = orig_set.insert(8);
  EXPECT_EQ(*my_pr, *orig_pr);
}

TEST(multiset, InsertSet) {
  s21::multiset<std::string> my_set = {"This", "is", "my", "multiset"};
  std::multiset<std::string> orig_set = {"This", "is", "my", "multiset"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(*my_pr == *orig_pr);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_EQ(*my_pr, *orig_pr);
}

TEST(multiset, EraseSet) {
  s21::multiset<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::multiset<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_set.size();
  my_set.erase(my_set.end());
  auto new_size = my_set.size();
  EXPECT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(multiset, SwapSet) {
  s21::multiset<int> my_set = {1};
  s21::multiset<int> my_swap_set = {3, 2, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3);
  EXPECT_EQ(my_swap_set.size(), 1);
  EXPECT_EQ(*my_set.begin(), 2);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(multiset, MergeSet) {
  s21::multiset<int> my_set = {1};
  s21::multiset<int> my_merge_set = {1, 3, 4, 5};
  my_set.merge(my_merge_set);

  std::multiset<int> orig_set = {1};
  std::multiset<int> orig_merge_set = {1, 3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(multiset, count) {
  s21::multiset<double> my_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};
  std::multiset<double> orig_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};
  auto my_count = my_set.count(2.1);
  auto orig_count = orig_set.count(2.1);
  EXPECT_EQ(my_count, orig_count);
}

TEST(multiset, FindSet) {
  s21::multiset<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(multiset, ContainsSet) {
  s21::multiset<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  std::multiset<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), 0);
  EXPECT_EQ(my_set.contains(2.1), 1);
  bool empty = my_set.empty();
  EXPECT_EQ(empty, false);
}

TEST(multiset, EqualRange) {
  s21::multiset<double> my_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};

  std::multiset<double> orig_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};

  EXPECT_EQ(*(my_set.equal_range(2.1)).first,
            *(orig_set.equal_range(2.1)).first);
  EXPECT_EQ(*(my_set.equal_range(2.1)).second,
            *(orig_set.equal_range(2.1)).second);
}

TEST(multiset, Lower_Bound) {
  s21::multiset<double> my_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};
  std::multiset<double> orig_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};
  auto my_it = my_set.lower_bound(2.4);
  auto orig_it = orig_set.lower_bound(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.lower_bound(2.1);
  orig_it = orig_set.lower_bound(2.1);
  ++orig_it;
  ++my_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(multiset, Upper_Bound) {
  s21::multiset<double> my_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};
  std::multiset<double> orig_set = {2.2, 2.1, 2.1, 2.1, 2.4, 2.5, 2.6};
  auto my_it = my_set.lower_bound(2.4);
  auto orig_it = orig_set.lower_bound(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.lower_bound(2.1);
  orig_it = orig_set.lower_bound(2.1);
  ++orig_it;
  ++my_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

}  // namespace