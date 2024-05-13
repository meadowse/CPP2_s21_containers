#include <gtest/gtest.h>

#include <climits>
#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "s21_containers.h"

// S21_MAP
TEST(MapTest, MapBaseConstruct) {
  std::cout << "\n ============== TEST: S21_MAP ============== \n" << std::endl;
  s21::Map<int, int> map;
  ASSERT_EQ(map.size(), (unsigned long)0);
}

TEST(MapTest, MapListConstruct1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  ASSERT_EQ(map.size(), (unsigned long)3);
  ASSERT_EQ(map.at(2), 5);
}

TEST(MapTest, MapListConstruct2) {
  s21::Map<int, int> map({std::pair<int, int>(1, 2), std::pair<int, int>(1, 2),
                          std::pair<int, int>(1, 2)});
  ASSERT_EQ(map.size(), (unsigned long)1);
  ASSERT_EQ(map.at(1), 2);
}

TEST(MapTest, MapCopyConstruct) {
  s21::Map<int, int> map1({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                           std::pair<int, int>(3, 6)});
  s21::Map<int, int> map(map1);
  ASSERT_EQ(map.size(), (unsigned long)3);
  ASSERT_EQ(map.at(2), 5);
}

TEST(MapTest, MapMoveConstruct) {
  s21::Map<int, int> map1({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                           std::pair<int, int>(3, 6)});
  s21::Map<int, int> map(std::move(map1));
  ASSERT_EQ(map.size(), (unsigned long)3);
  ASSERT_EQ(map.at(2), 5);
  ASSERT_EQ(map1.size(), (unsigned long)0);
}

TEST(MapTest, MapEquals1) {
  s21::Map<int, int> map1({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                           std::pair<int, int>(3, 6)});
  s21::Map<int, int> map;
  map = map1;
  ASSERT_EQ(map.size(), (unsigned long)3);
  ASSERT_EQ(map.at(2), 5);
}

TEST(MapTest, MapEquals2) {
  s21::Map<int, int> map1({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                           std::pair<int, int>(3, 6)});
  s21::Map<int, int> map = std::move(map1);
  ASSERT_EQ(map.size(), (unsigned long)3);
  ASSERT_EQ(map.at(2), 5);
  ASSERT_EQ(map1.size(), (unsigned long)0);
}

TEST(MapTest, MapAt) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  ASSERT_EQ(map.at(2), 5);
}

TEST(MapTest, MapBr1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  ASSERT_EQ(map[2], 5);
}

TEST(MapTest, MapBr2) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  ASSERT_EQ(map[5], 0);
  ASSERT_EQ(map.at(5), 0);
}

TEST(MapTest, MapBegin) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  auto res = *map.begin();
  ASSERT_EQ(res.second, 4);
  ASSERT_EQ(res.first, 1);
}

TEST(MapTest, MapEmpty1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  ASSERT_EQ(map.empty(), false);
}

TEST(MapTest, MapEmpty2) {
  s21::Map<int, int> map;
  ASSERT_EQ(map.empty(), true);
}

TEST(MapTest, MapSize) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  ASSERT_EQ(map.size(), (unsigned long)3);
}

TEST(MapTest, MapClear) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  map.clear();
  ASSERT_EQ(map.size(), (unsigned long)0);
}

TEST(MapTest, MapInsert1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  auto res1 = map.insert({2, 5});
  auto res2 = map.insert({4, 5});
  auto res3 = map.insert({-2, 100});
  auto res4 = map.insert_or_assign(8, 8);
  ASSERT_EQ(res1.second, false);
  ASSERT_EQ(res2.second, true);
  ASSERT_EQ(res3.second, true);
  ASSERT_EQ(res4.second, true);
  ASSERT_EQ(map.size(), (unsigned long)6);
}

TEST(MapTest, MapInsert2) {
  s21::Map<int, int> map;
  auto res1 = map.insert({2, 5});
  ASSERT_EQ(res1.second, true);
  ASSERT_EQ(map.size(), (unsigned long)1);
}

TEST(MapTest, MapErase1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 6)});
  auto check = map.begin();
  map.erase(check);
  auto res = *map.begin();
  ASSERT_EQ(res.second, 5);
  ASSERT_EQ(map.size(), (unsigned long)2);
}

TEST(MapTest, MapSwap) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 7)});

  s21::Map<int, int> map1({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                           std::pair<int, int>(3, 6),
                           std::pair<int, int>(4, 7)});
  map.swap(map1);
  ASSERT_EQ(map.size(), (unsigned long)4);
  ASSERT_EQ(map1.size(), (unsigned long)3);
  ASSERT_EQ(map.at(4), 7);
  ASSERT_EQ(map1.at(3), 7);
}

TEST(MapTest, MapMerge1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 7)});

  s21::Map<int, int> map1(
      {std::pair<int, int>(10, 4), std::pair<int, int>(11, 5),
       std::pair<int, int>(12, 6), std::pair<int, int>(13, 7)});
  map.merge(map1);
  ASSERT_EQ(map.size(), (unsigned long)7);
  ASSERT_EQ(map1.size(), (unsigned long)0);
  ASSERT_EQ(map.at(13), 7);
}

TEST(MapTest, MapMerge2) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 7)});

  s21::Map<int, int> map1({std::pair<int, int>(10, 4),
                           std::pair<int, int>(2, 5), std::pair<int, int>(3, 6),
                           std::pair<int, int>(13, 7)});
  map.merge(map1);
  ASSERT_EQ(map.size(), (unsigned long)5);
  ASSERT_EQ(map1.size(), (unsigned long)2);
  ASSERT_EQ(map.at(13), 7);
  ASSERT_EQ(map1.at(2), 5);
}

TEST(MapTest, MapContains1) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 7)});
  ASSERT_EQ(map.contains(4), false);
}

TEST(MapTest, MapContains2) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 7)});
  ASSERT_EQ(map.contains(3), true);
}

TEST(MapTest, MapIter) {
  s21::Map<int, int> map({std::pair<int, int>(1, 4), std::pair<int, int>(2, 5),
                          std::pair<int, int>(3, 7)});
  int i = 0;
  int check[3] = {4, 5, 7};
  for (auto it : map) {
    ASSERT_EQ(it.second, check[i]);
    i++;
  }
}

// S21_SET
TEST(SetTest, SetBaseConstruct) {
  std::cout << "\n ============== TEST: S21_SET ============== \n" << std::endl;
  s21::Set<int> set;
  ASSERT_EQ(set.size(), (unsigned long)0);
}

TEST(SetTest, SetListConstruct1) {
  s21::Set<int> set({1, 2, 3});
  ASSERT_EQ(set.size(), (unsigned long)3);
  ASSERT_EQ(*set.find(2), 2);
}

TEST(SetTest, SetListConstruct2) {
  s21::Set<int> set({1, 1, 1});
  ASSERT_EQ(set.size(), (unsigned long)1);
  ASSERT_EQ(*set.find(1), 1);
}

TEST(SetTest, SetCopyConstruct) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1(set);
  ASSERT_EQ(set1.size(), (unsigned long)3);
  ASSERT_EQ(*set1.find(2), 2);
}

TEST(SetTest, SetMoveConstruct) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1(std::move(set));
  ASSERT_EQ(set1.size(), (unsigned long)3);
  ASSERT_EQ(*set1.find(2), 2);
  ASSERT_EQ(set.size(), (unsigned long)0);
}

TEST(SetTest, SetEquals1) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1;
  set1 = set;
  ASSERT_EQ(set1.size(), (unsigned long)3);
  ASSERT_EQ(*set1.find(2), 2);
}

TEST(SetTest, SetEquals2) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1;
  set1 = std::move(set);
  ASSERT_EQ(set1.size(), (unsigned long)3);
  ASSERT_EQ(*set1.find(2), 2);
  ASSERT_EQ(set.size(), (unsigned long)0);
}

TEST(SetTest, SetFind) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  ASSERT_EQ(*set.find(5), 5);
}

TEST(SetTest, SetEnd) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  ASSERT_EQ(*set.end(), *set.end());
}

TEST(SetTest, SetBegin) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  std::set<int> set1({1, 2, 3, 4, 5});
  ASSERT_EQ(*set.begin(), *set1.begin());
}

TEST(SetTest, SetEmpty1) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  ASSERT_EQ(set.empty(), false);
}

TEST(SetTest, SetEmpty2) {
  s21::Set<int> set;
  ASSERT_EQ(set.empty(), true);
}

TEST(SetTest, SetSize) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  ASSERT_EQ(set.size(), (unsigned long)5);
}

TEST(SetTest, SetMaxSize) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  std::set<int> set1({1, 2, 3, 4, 5});
  ASSERT_EQ(set.size(), set1.size());
}

TEST(SetTest, SetClear) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  set.clear();
  ASSERT_EQ(set.size(), (unsigned long)0);
}

TEST(SetTest, SetInsert1) {
  s21::Set<int> set({1, 2, 3, 4, 5});
  auto res1 = set.insert(1);
  auto res2 = set.insert(-10);
  auto res3 = set.insert(1000);
  auto res4 = set.insert(6);
  ASSERT_EQ(res1.second, false);
  ASSERT_EQ(res2.second, true);
  ASSERT_EQ(res3.second, true);
  ASSERT_EQ(res4.second, true);
  ASSERT_EQ(set.size(), (unsigned long)8);
}

TEST(SetTest, SetInsert2) {
  s21::Set<int> set;
  auto res1 = set.insert(1);
  ASSERT_EQ(res1.second, true);
  ASSERT_EQ(set.size(), (unsigned long)1);
}

TEST(SetTest, SetErase1) {
  s21::Set<int> set({1, 2, 3});
  auto check = set.begin();
  set.erase(check);
  auto res = *set.begin();
  ASSERT_EQ(res, 2);
  ASSERT_EQ(set.size(), (unsigned long)2);
}

TEST(SetTest, SetSwap) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1({4, 5, 6, 7});
  set.swap(set1);
  ASSERT_EQ(set.size(), (unsigned long)4);
  ASSERT_EQ(set1.size(), (unsigned long)3);
  ASSERT_EQ(*set.find(4), 4);
  ASSERT_EQ(*set1.find(3), 3);
}

TEST(SetTest, SetMerge1) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1({4, 2, 3, 7});
  set.merge(set1);
  ASSERT_EQ(set.size(), (unsigned long)5);
  ASSERT_EQ(set1.size(), (unsigned long)2);
  ASSERT_EQ(*set.find(7), 7);
}

TEST(SetTest, SetMerge2) {
  s21::Set<int> set({1, 2, 3});
  s21::Set<int> set1({-12, 12, -13, 13});
  set.merge(set1);
  ASSERT_EQ(set.size(), (unsigned long)7);
  ASSERT_EQ(set1.size(), (unsigned long)0);
  ASSERT_EQ(*set.find(13), 13);
}

TEST(SetTest, SetContains1) {
  s21::Set<int> set({1, 2, 3});
  ASSERT_EQ(set.contains(4), false);
}

TEST(SetTest, SetContains2) {
  s21::Set<int> set({1, 2, 3});
  ASSERT_EQ(set.contains(3), true);
}

TEST(SetTest, SetIter) {
  s21::Set<int> set({1, 2, 3});
  int i = 0;
  int check[3] = {1, 2, 3};
  for (auto it : set) {
    ASSERT_EQ(it, check[i]);
    i++;
  }
}

// S21_VECTOR
TEST(VectorTest, VecBaseConstruct) {
  std::cout << "\n ============== TEST: S21_VECTOR ============== \n"
            << std::endl;
  s21::Vector<int> Vec;
  ASSERT_EQ(Vec.size(), (unsigned long)0);
}

TEST(VectorTest, VecLSizeConstruct1) {
  s21::Vector<int> Vec(5);
  ASSERT_EQ(Vec.capacity(), (unsigned long)5);
}

TEST(VectorTest, VecLSizeConstruct2) {
  s21::Vector<int> Vec(0);
  ASSERT_EQ(Vec.size(), (unsigned long)0);
}

TEST(VectorTest, VecListConstruct) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec.size(), (unsigned long)5);
  ASSERT_EQ(Vec[2], 3);
}

TEST(VectorTest, VecVecConstruct1) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1(Vec);
  ASSERT_EQ(Vec1.size(), (unsigned long)5);
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, VecVecConstruct2) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1(std::move(Vec));
  ASSERT_EQ(Vec1.size(), (unsigned long)5);
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, EqualsOp1) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1;
  Vec1 = Vec;
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, EqualsOp2) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  s21::Vector<int> Vec1;
  Vec1 = std::move(Vec);
  ASSERT_EQ(Vec1[2], 3);
}

TEST(VectorTest, VecAt) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec.at(2), 3);
}

TEST(VectorTest, VecBr) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  int check = Vec[2];
  ASSERT_EQ(check, 3);
}

TEST(VectorTest, VecData) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(*Vec.data(), 1);
}

TEST(VectorTest, VecFront) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec1.front(), Vec.front());
}

TEST(VectorTest, VecBack) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec1.back(), Vec.back());
}

TEST(VectorTest, VecBegin) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(*Vec.begin(), 1);
}

TEST(VectorTest, VecEnd) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(*Vec.end(), *Vec.end());
}

TEST(VectorTest, VecSize) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  std::vector<int> Vec1({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec1.size(), Vec.size());
}

TEST(VectorTest, VecEmpty1) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  ASSERT_EQ(Vec.empty(), false);
}

TEST(VectorTest, VecEmpty2) {
  s21::Vector<int> Vec;
  ASSERT_EQ(Vec.empty(), true);
}

TEST(VectorTest, VecReserve) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  Vec.reserve(8);
  ASSERT_EQ(Vec.size(), (unsigned long)5);
}

TEST(VectorTest, VecCapacity1) {
  s21::Vector<int> Vec(1);
  ASSERT_EQ(Vec.capacity(), (unsigned long)1);
}

TEST(VectorTest, VecSwap) {
  s21::Vector<int> Vec({1, 1, 1, 1, 1});
  s21::Vector<int> Vec1({2, 2, 2, 2, 2});
  Vec1.swap(Vec);
  ASSERT_EQ(Vec1[1], 1);
  ASSERT_EQ(Vec[2], 2);
}

TEST(VectorTest, VecPrint) { s21::Vector<int> Vec({1, 1, 1, 1, 1}); }

TEST(VectorTest, VecClear) {
  s21::Vector<int> Vec({1, 1, 1, 1, 1});
  Vec.clear();
  ASSERT_EQ(Vec.size(), (unsigned long)0);
}

TEST(VectorTest, VecShrink_to_fit) {
  s21::Vector<int> Vec({1, 1, 1, 1, 1});
  Vec.shrink_to_fit();
}

TEST(VectorTest, VecInsert) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  auto res1 = Vec.insert(Vec.begin(), 1);
  ASSERT_EQ(*res1, 1);
  auto res2 = Vec.insert(Vec.begin(), -11);
  ASSERT_EQ(*res2, -11);
  auto res3 = Vec.insert(Vec.end(), 1000);
  ASSERT_EQ(*res3, 1000);
  auto res4 = Vec.insert(Vec.end(), 6);
  ASSERT_EQ(*res4, 6);
  ASSERT_EQ(Vec.size(), (unsigned long)9);
}

TEST(VectorTest, VecErase) {
  s21::Vector<int> Vec({1, 2, 3, 4, 5});
  Vec.erase(Vec.begin());
  ASSERT_EQ(Vec[0], 2);
  ASSERT_EQ(Vec.size(), (unsigned long)4);
}

// S21_LIST
TEST(tests_of_list, push_back) {
  s21::List<int> Mylist_1 = {1};
  Mylist_1.push_back(2);
  Mylist_1.push_back(3);
  Mylist_1.push_back(4);
  Mylist_1.push_back(5);
  Mylist_1.push_back(6);
  Mylist_1.push_back(7);

  for (auto it : Mylist_1) {
    std::cout << it << " " << std::ends;
  }

  auto Mylist_2 = Mylist_1;
  auto it_2 = Mylist_2.begin();
  for (auto it = Mylist_1.begin(); it != Mylist_1.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }

  s21::List<int> Mylist_4;
  Mylist_4 = Mylist_1;

  auto it = Mylist_1.begin();
  auto it_4 = Mylist_4.begin();
  for (size_t i = 1; i <= Mylist_1.size(); i++) {
    EXPECT_EQ(*it_4, *it);
    ++it;
    ++it_4;
  }

  it = Mylist_1.begin();
  for (size_t i = 1; i <= Mylist_1.size(); i++) {
    EXPECT_EQ(i, (unsigned long)*it);
    ++it;
  }
}

TEST(tests_of_List, push_front) {
  s21::List<int> MyList_1 = {0};
  MyList_1.push_front(1);
  MyList_1.push_front(2);
  MyList_1.push_front(3);
  int i = 4;
  EXPECT_EQ((unsigned long)i, MyList_1.size());
}
TEST(tests_of_List, pop_back) {
  s21::List<int> MyList_1;
  MyList_1.push_front(1);
  MyList_1.push_front(2);
  MyList_1.push_front(3);
  MyList_1.pop_back();
  auto it = MyList_1.begin();
  int i = 3;
  size_t size = 0;
  while (size < MyList_1.size()) {
    ASSERT_EQ(i, *it);
    i--;
    ++it;
    size++;
  }
}

TEST(tests_of_List, pop_front) {
  s21::List<int> MyList_1 = {0};
  MyList_1.push_front(1);
  MyList_1.push_front(2);
  MyList_1.push_front(3);
  int i = 4;
  EXPECT_EQ((unsigned long)i, MyList_1.size());
}

TEST(tests_of_List, front) {
  s21::List<int> MyList_1 = {1, 2, 3};
  int a = MyList_1.front();
  ASSERT_EQ(1, a);
}

TEST(tests_of_List, back) {
  s21::List<int> MyList_1 = {1, 2, 3};
  int a = MyList_1.back();
  ASSERT_EQ(3, a);
}

TEST(tests_of_List, empty) {
  s21::List<int> MyList_1 = {1, 2, 3};
  int a = MyList_1.empty();
  ASSERT_EQ(0, a);
}
TEST(tests_of_List, size) {
  s21::List<int> MyList_1 = {1, 2, 3, 4};
  size_t a = MyList_1.size();
  ASSERT_EQ((unsigned long)4, a);
}

TEST(tests_of_List, unique) {
  s21::List<int> MyList_2 = {2, 1, 1, 2, 3, 4};
  std::list<int> stdList = {2, 1, 1, 2, 3, 4};
  MyList_2.unique();
  stdList.unique();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); itStd++) {
    EXPECT_EQ(*it, *itStd);
    it++;
  }
}
TEST(tests_of_List, unique_2) {
  s21::List<int> MyList_2 = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4};
  std::list<int> stdList = {1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 4};
  MyList_2.unique();
  stdList.unique();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, unique_3) {
  s21::List<int> MyList_2 = {1, 2, 3, 4, 1};
  std::list<int> stdList = {1, 2, 3, 4, 1};
  MyList_2.unique();
  stdList.unique();
  auto it = MyList_2.begin();
  for (auto itStd = stdList.begin(); itStd != stdList.end(); ++itStd) {
    EXPECT_EQ(*it, *itStd);
    ++it;
  }
}

TEST(tests_of_List, merge) {
  s21::List<int> MyList_1 = {1, 5, 7, 8, 12};
  s21::List<int> MyList_2 = {2, 3, 4, 7, 9};
  s21::List<int> result = {1, 2, 3, 4, 5, 7, 7, 8, 9, 12};
  MyList_1.merge(MyList_2);

  auto it = MyList_1.begin();
  for (auto it_res = result.begin(); it_res != result.end(); ++it_res) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
  EXPECT_EQ(MyList_1.size(), result.size());
}

TEST(tests_of_List, splice) {
  s21::List<int> MyList_1 = {1, 4, 5, 6};
  s21::List<int> MyList_2 = {2, 3};
  auto it_1 = MyList_1.cbegin();
  ++it_1;
  MyList_1.splice(it_1, MyList_2);
  auto it = MyList_1.begin();
  std::list<int> result = {1, 2, 3, 4, 5, 6};

  for (auto it_res = result.begin(); it_res != result.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }

  std::list<int> result_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::List<int> MyList3 = {7, 8, 9};
  MyList_1.splice(MyList_1.cend(), MyList3);
  it = MyList_1.begin();
  for (auto it_res = result_2.begin(); it_res != result_2.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }

  std::list<int> result_3 = {-3, -2, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::List<int> MyList4 = {-3, -2, -1};
  MyList_1.splice(MyList_1.cbegin(), MyList4);
  it = MyList_1.begin();
  for (auto it_res = result_3.begin(); it_res != result_3.end(); it_res++) {
    EXPECT_EQ(*it, *it_res);
    ++it;
  }
}

TEST(tests_of_List, insert) {
  s21::List<int> MyList_1 = {1, 2, 3, 4, 5};
  std::list<int> stdList = {1, 2, 3, 4, 5};
  auto it_1 = MyList_1.begin();
  auto it_std = stdList.begin();

  auto it_2 = MyList_1.insert(it_1, 0);
  auto it_std_2 = stdList.insert(it_std, 0);

  ASSERT_EQ(*it_std_2, *it_2);

  it_1 += 3;
  for (size_t i = 0; i < 3; i++) {
    it_std++;
  }

  it_2 = MyList_1.insert(it_1, 6);
  it_std_2 = stdList.insert(it_std, 6);
  ASSERT_EQ(*it_std_2, *it_2);

  it_1 = MyList_1.end();
  it_std = stdList.end();
  it_2 = MyList_1.insert(it_1, 7);
  it_std_2 = stdList.insert(it_std, 7);
  ASSERT_EQ(*it_std_2, *it_2);
}

// S21_QUEUEU
TEST(tests_of_queue, push_1) {
  s21::Queue<int> Myqueue_1;
  Myqueue_1.push(1);
  Myqueue_1.push(2);
  Myqueue_1.push(3);

  int i = 1;
  size_t size = 0;
  while (size < Myqueue_1.size()) {
    ASSERT_EQ(i, Myqueue_1.front());
    i++;
    size++;
    Myqueue_1.pop();
  }
}

TEST(tests_of_queue, pop_1) {
  s21::Queue<int> Myqueue_1;
  Myqueue_1.push(1);
  Myqueue_1.push(2);
  Myqueue_1.push(3);

  Myqueue_1.pop();
  Myqueue_1.pop();
  Myqueue_1.pop();

  bool empty_queue = Myqueue_1.empty();
  ASSERT_EQ(1, empty_queue);
}

TEST(tests_of_queue, back) {
  s21::Queue<int> Myqueue_1;
  Myqueue_1.push(1);
  Myqueue_1.push(2);
  Myqueue_1.push(3);
  auto it = Myqueue_1.back();
  ASSERT_EQ(3, it);
}

TEST(tests_of_queue, size_1) {
  s21::Queue<int> Myqueue_1;
  Myqueue_1.push(1);
  Myqueue_1.push(2);
  Myqueue_1.push(3);
  auto it = Myqueue_1.size();
  ASSERT_EQ((unsigned long)3, it);
}
TEST(tests_of_queue, size_2) {
  s21::Queue<int> Myqueue_1;
  Myqueue_1.push(1);
  auto it = Myqueue_1.size();
  ASSERT_EQ((unsigned long)1, it);
}

TEST(tests_of_queue, equal) {
  s21::Queue<int> Myqueue_1;
  Myqueue_1.push(1);
  Myqueue_1.push(2);
  Myqueue_1.push(3);
  int i = 1;
  size_t size = 0;
  while (size < Myqueue_1.size()) {
    ASSERT_EQ(i, Myqueue_1.front());
    i++;
    size++;
    Myqueue_1.pop();
  }
}

// S21_STACK
TEST(tests_of_stack, push_1) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);

  int i = 3;
  size_t size = 0;
  while (size < Mystack_1.size()) {
    ASSERT_EQ(i, Mystack_1.top());
    i--;
    size++;
    Mystack_1.pop();
  }
}

TEST(tests_of_stack, pop_1) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);

  Mystack_1.pop();
  Mystack_1.pop();
  Mystack_1.pop();

  bool empty_stack = Mystack_1.empty();
  ASSERT_EQ(1, empty_stack);
}

TEST(tests_of_stack, top) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);
  auto it = Mystack_1.top();
  ASSERT_EQ(3, it);
}

TEST(tests_of_stack, size_1) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);
  auto it = Mystack_1.size();
  ASSERT_EQ((unsigned long)3, it);
}

TEST(tests_of_stack, size_2) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  auto it = Mystack_1.size();
  ASSERT_EQ((unsigned long)1, it);
}

TEST(tests_of_stack, equal) {
  s21::Stack<int> Mystack_1;
  Mystack_1.push(1);
  Mystack_1.push(2);
  Mystack_1.push(3);
  int i = 3;
  size_t size = 0;
  while (size < Mystack_1.size()) {
    ASSERT_EQ(i, Mystack_1.top());
    i--;
    size++;
    Mystack_1.pop();
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
