#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <set>
#include <ctime>
#include "dingo_array.h"

using namespace std;

void testContructors () {
  vector<int> vec = {1, 2, 3, 4};
  list<int> lst = {2, 5, 9};
  set<int> st = {3, 5, 7, 9, 11};
  int* ptr;
  ptr = (int*) malloc(4 * sizeof(int));
  for (int i = 0; i < 4; i++) ptr[i] = i;
  Array<int> a;
  Array<int> b(5);
  Array<int> c(vec);
  Array<int> d(lst);
  Array<int> e(st);
  Array<int> f({0, 7, 9, -1, 2, 4});
  Array<int> g(ptr, 4);
  // Array<int> err(-1); -> This will throw an error
  free(ptr);
}

void testStaticMethods () {
  vector<int> vec = {1, 2, 3, 4};
  list<int> lst = {2, 5, 9};
  set<int> st = {3, 5, 7, 9, 11};
  int* ptr;
  ptr = (int*) malloc(4 * sizeof(int));
  for (int i = 0; i < 4; i++) ptr[i] = i;
  Array<int> v = Array<int>::fromVector(vec);
  Array<int> w = Array<int>::fromList(lst);
  Array<int> x = Array<int>::fromSet(st);
  Array<int> y = Array<int>::fromInitList({5, 6, 7, 8});
  Array<int> z = Array<int>::fromPointer(ptr, 4);
  free(ptr);
}

void testMethodShow () {
  Array<int> a({1, 2, 3, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.show(true): ";
  a.show(true);
  cout<<"a.show(false, false): ";
  a.show(false, false);
  cout<<"a.show(true, true, true, true): ";
  a.show(true, true, true, true);
  Array<int> b;
  cout<<"b.show(): ";
  b.show();
}

void testMethodSize () {
  Array<int> a({1, 2, 3, 4});
  cout<<"a.size() = "<<a.size()<<endl;
  Array<int> b;
  cout<<"b.size() = "<<b.size()<<endl;
}

void testSubscriptOperators () {
  Array<int> a({1, 2, 3, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a[0] = "<<a[0]<<endl;
  cout<<"a[-1] = "<<a[-1]<<endl;
  cout<<"a[{0, 1, -1}] = ";
  a[{0, 1, -1}].show();
  // cout<<"a[7] = "<<a[7]<<endl; -> This will throw an error
  cout<<"a[2] = 5 -> ";
  a[2] = 5;
  a.show();
}

void testMethodAppend () {
  Array<int> a({1, 2, 3, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.append(5): ";
  a.append(5);
  a.show();
  cout<<"a.append({6, 7, 8}): ";
  a.append({6, 7, 8});
  a.show();
  Array<int> b({0, -1, -7});
  cout<<"b.show(): ";
  b.show();
  cout<<"a.append(b): ";
  a.append(b);
  a.show();
}

void testMethodInsert () {
  Array<int> a({1, 2, 3, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.insert(5, 1): ";
  a.insert(5, 1);
  a.show();
  cout<<"a.insert({-2, -1, 0}, 0): ";
  a.insert({-2, -1, 0}, 0);
  a.show();
  Array<int> b({0, -1, -7});
  cout<<"b.show(): ";
  b.show();
  cout<<"a.insert(b, -3): ";
  a.insert(b, -3);
  a.show();
  // a.insert(1, 100); -> This will throw an error
}

void testMethodErase () {
  Array<int> a({1, 2, 3, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.erase(0, 2): ";
  a.erase(0, 2);
  a.show();
  cout<<"a.erase(-1): ";
  a.erase(-1);
  a.show();
}

void testMethodFill () {
  Array<int> a(10);
  cout<<"a.show(): ";
  a.show();
  cout<<"a.fill(1): ";
  a.fill(1);
  a.show();
  cout<<"a.fill(2, 1, 3): ";
  a.fill(2, 1, 3);
  a.show();
  cout<<"a.fill({1, 2, 3}): ";
  a.fill({1, 2, 3});
  a.show();
  cout<<"a.fill({1, 2, 3}, \'s\'): ";
  a.fill({1, 2, 3}, 's');
  a.show();
}

void testMethodReverse () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.reverse(): ";
  a.reverse();
  a.show();
  cout<<"a.reverse(2, 4): ";
  a.reverse(2, 4);
  a.show();
}

void testMethodResize () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.resize(4): ";
  a.resize(4);
  a.show();
  cout<<"a.resize(6): ";
  a.resize(6);
  a.show();
}

void testMethodCount () {
  Array<int> a({1, 2, 3, 4, 1, 2, 3, 2, 3});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.count(3) = "<<a.count(3)<<endl;
  cout<<"a.count(3, 4) = "<<a.count(3, 4)<<endl;
  cout<<"a.count(0) = "<<a.count(0)<<endl;
  cout<<"a.count({1, 2, 3}) = "<<a.count({1, 2, 3})<<endl;
}

void testMethodFind () {
  Array<int> a({1, 2, 3, 4, 1, 2, 3, 2, 3});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.find(3) = "<<a.find(3)<<endl;
  cout<<"a.find(3, 4) = "<<a.find(3, 4)<<endl;
  cout<<"a.find(0) = "<<a.find(0)<<endl;
  cout<<"a.find({1, 2, 3}) = "<<a.find({1, 2, 3})<<endl;
}

void testMethodFindAll () {
  Array<int> a({1, 2, 3, 4, 1, 2, 3, 2, 3});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.findAll(3) = ";
  a.findAll(3).show();
  cout<<"a.findAll(3, 4) = ";
  a.findAll(3, 4).show();
  cout<<"a.findAll(0) = ";
  a.findAll(0).show();
  cout<<"a.findAll({1, 2, 3}) = ";
  a.findAll({1, 2, 3}).show();
}

void testMethodShift () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.shift(1): ";
  a.shift(1);
  a.show();
  cout<<"a.shift(-2): ";
  a.shift(-2);
  a.show();
  cout<<"a.shift(7): ";
  a.shift(7);
  a.show();
  cout<<"a.shift(1, 2, 4): ";
  a.shift(1, 2, 4);
  a.show();
  cout<<"a.shift(-1, 2, -2): ";
  a.shift(-1, 2, -2);
  a.show();
}

void testMethodContains () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.contains(1) = "<<a.contains(1)<<endl;
  cout<<"a.contains(1, 2, 4) = "<<a.contains(1, 2, 4)<<endl;
  cout<<"a.contains(0) = "<<a.contains(0)<<endl;
  cout<<"a.contains({3, 4, 5}) = "<<a.contains({3, 4, 5})<<endl;
}

void testMethodReplace () {
  Array<int> a({1, 2, 3, 4, 3, 2, 1});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.replace(1, 2): ";
  a.replace(1, 2);
  a.show();
  cout<<"a.replace(2, 7, -2): ";
  a.replace(2, 7, -2);
  a.show();
}

void testMethodSlice () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.slice(2) = ";
  a.slice(2).show();
  cout<<"a.slice(1, -2) = ";
  a.slice(1, -2).show();
  cout<<"a.slice() = ";
  a.slice().show();
}

void testMethodClear () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.clear(): ";
  a.clear();
  a.show();
}

void testMethodUnique () {
  Array<int> a({1, 2, 3, 2, 1, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.unique(): ";
  a.unique().show();
}

void testMethodSort () {
  Array<int> a({1, 2, 3, 2, 1, 4});
  cout<<"a = ";
  a.show();
  cout<<"a.sort(): ";
  a.sort();
  a.show();
  cout<<"a.sort(false): ";
  a.sort(false);
  a.show();
  cout<<"a.sort(true, 1, -2): ";
  a.sort(true, 1, -2);
  a.show();
  cout<<"a.toSorted() = ";
  a.toSorted().show();
  cout<<"a = ";
  a.show();
}

void testMethodForEach () {
  Array<int> a({1, 2, 3, 2, 1, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.forEach([] (int elem) { cout<<\"(\"<<elem<<\"),\"; }) -> ";
  a.forEach([] (int elem) { cout<<"("<<elem<<"),"; });
  cout<<endl<<"a.forEach([] (int elem, int idx) { cout<<\"(\"<<idx<<\": \"<<elem<<\"),\"; }) -> ";
  a.forEach([] (int elem, int idx) { cout<<"("<<idx<<": "<<elem<<"),"; });
}

void testMethodFilter () {
  Array<int> a({1, 2, 3, 2, 1, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.filter([] (int elem) { return elem > 2; }): ";
  a.filter([] (int elem) { return elem > 2; }).show();
  cout<<"a.filter([] (int elem, int index) { return elem > 1 && index < 4; }): ";
  a.filter([] (int elem, int index) { return elem > 1 && index < 4; }).show();
  cout<<"a.filter([] (int elem, int index, Array<int> array) { return elem > array.mean(); }): ";
  a.filter([] (int elem, int index, const Array<int> &array) { return elem > array.mean(); }).show();
}

void testMethodMap () {
  Array<int> a({1, 2, 3, 4, 0, 5});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.map<int>([] (int elem) { return elem * 2; }): ";
  a.map<int>([] (int elem) { return elem * 2; }).show();
  cout<<"a.map<int>([] (int elem, int idx) { return elem * idx; }): ";
  a.map<int>([] (int elem, int idx) { return elem * idx; }).show();
  cout<<"a.map<double>([] (int elem, int idx, const Array<int> &array) { return elem - array.mean(); }): ";
  a.map<double>([] (int elem, int idx, const Array<int> &array) { return elem - array.mean(); }).show();
}

void testMethodsMinMax () {
  Array<int> a({1, 2, 3, 4, 5, 6});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.min() = "<<a.min()<<endl;
  cout<<"a.max() = "<<a.max()<<endl;
  cout<<"a.min(2) = "<<a.min(2)<<endl;
  cout<<"a.max(2, -2) = "<<a.max(2, -2)<<endl;
}

void testMethodsArgminArgmax () {
  Array<int> a({1, 2, 3, 1, 3, 2, 3});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.argmin() = ";
  a.argmin().show();
  cout<<"a.argmax() = ";
  a.argmax().show();
  cout<<"a.argmin(1) = ";
  a.argmin(1).show();
  cout<<"a.argmax(0, -3) = ";
  a.argmax(0, -3).show();
}

void testMethodsSumProduct () {
  Array<int> a({1, 2, 3, 4, 5});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.sum() = "<<a.sum()<<endl;
  cout<<"a.sum(2) = "<<a.sum(2)<<endl;
  cout<<"a.product() = "<<a.product()<<endl;
  cout<<"a.product(1, -2) = "<<a.product(1, -2)<<endl;
}

void testMethodsMeans () {
  Array<int> a({1, 2, 3, 4, 5});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.mean() = "<<a.mean()<<endl;
  cout<<"a.mean(2) = "<<a.mean(2)<<endl;
  cout<<"a.meanG() = "<<a.meanG()<<endl;
  cout<<"a.meanG(1, -2) = "<<a.meanG(1, -2)<<endl;
  cout<<"a.meanH() = "<<a.meanH()<<endl;
  cout<<"a.meanH(0, -3) = "<<a.meanH(0, -3)<<endl;
  cout<<"a.weightedMean({5, 4, 3, 2, 1}) = "<<a.weightedMean({5, 4, 3, 2, 1})<<endl;
  cout<<"a.weightedMean({1, 2, 3, 4}, 1) = "<<a.weightedMean({1, 2, 3, 4}, 1)<<endl;
}

void testMethodsVarStdev () {
  Array<int> a({1, 2, 3, 4, 5});
  cout<<"a.show(): ";
  a.show();
  cout<<"a.variance() = "<<a.variance()<<endl;
  cout<<"a.variance(2) = "<<a.variance(2)<<endl;
  cout<<"a.stdev() = "<<a.stdev()<<endl;
  cout<<"a.stdev(1, -2) = "<<a.stdev(1, -2)<<endl;
}

void testOperatorsArithmetic () {
  Array<int> a({1, 2, 3, 4, 5});
  Array<int> b({2, 1, 2, 1, 3, 4});
  cout<<"a.show(): ";
  a.show();
  cout<<"b.show(): ";
  b.show();
  cout<<"a + 2 = ";
  (a + 2).show();
  cout<<"a - 2 = ";
  (a - 2).show();
  cout<<"a * 2 = ";
  (a * 2).show();
  cout<<"a / 2 = ";
  (a / 2).show();
  cout<<"a.astype<float>() / 2 = ";
  (a.astype<float>() / 2).show();
  cout<<"a % 2 = ";
  (a % 2).show();
  cout<<"a + b = ";
  (a + b).show();
  cout<<"a - b = ";
  (a - b).show();
  cout<<"a * b = ";
  (a * b).show();
  cout<<"a / b = ";
  (a / b).show();
  cout<<"a.astype<float>() / b.astype<float>() = ";
  (a.astype<float>() / b.astype<float>()).show();
  cout<<"a % b = ";
  (a % b).show();
  cout<<"a += 2: ";
  a += 2;
  a.show();
  cout<<"a -= 2: ";
  a -= 2;
  a.show();
  cout<<"a *= 2: ";
  a *= 2;
  a.show();
  cout<<"a /= 2: ";
  a /= 2;
  a.show();
  cout<<"a %= 4: ";
  a %= 4;
  a.show();
  cout<<"a.show(): ";
  a.show();
  cout<<"b.show(): ";
  b.show();
  cout<<"a += b: ";
  a += b;
  a.show();
  cout<<"a -= b: ";
  a -= b;
  a.show();
  cout<<"a *= b: ";
  a *= b;
  a.show();
  cout<<"a /= b: ";
  a /= b;
  a.show();
  cout<<"a %= b: ";
  a %= b;
  a.show();
}

void testOperatorsComparison () {
  Array<int> a({1, 2, 3, 4, 5});
  Array<int> b({2, 1, 2, 1, 3, 4});
  cout<<"a = ";
  a.show();
  cout<<"(a == 2) = ";
  (a == 2).show();
  cout<<"(a != 2) = ";
  (a != 2).show();
  cout<<"(a >= 2) = ";
  (a >= 2).show();
  cout<<"(a > 2) = ";
  (a > 2).show();
  cout<<"(a <= 2) = ";
  (a <= 2).show();
  cout<<"(a < 2) = ";
  (a < 2).show();
  cout<<"b = ";
  b.show();
  cout<<"(a == b) = ";
  (a == b).show();
  cout<<"(a != b) = ";
  (a != b).show();
  cout<<"(a >= b) = ";
  (a >= b).show();
  cout<<"(a > b) = ";
  (a > b).show();
  cout<<"(a <= b) = ";
  (a <= b).show();
  cout<<"(a < b) = ";
  (a < b).show();
}

void testOperatorsBoolean () {
  Array<bool> a({1, 0, 1, 1, 0});
  Array<bool> b({0, 0, 0, 1, 1, 1});
  cout<<"a = ";
  a.show();
  cout<<"b = ";
  b.show();
  cout<<"!a = ";
  (!a).show();
  cout<<"a | b = ";
  (a | b).show();
  cout<<"a & b = ";
  (a & b).show();
  cout<<"a ^ b = ";
  (a ^ b).show();
  cout<<"a | 1 = ";
  (a | 1).show();
  cout<<"a & 0 = ";
  (a & 0).show();
  cout<<"a ^ 1 = ";
  (a ^ 1).show();
  cout<<"a |= b: ";
  a |= b;
  a.show();
  cout<<"a &= b: ";
  a &= b;
  a.show();
  cout<<"a ^= b: ";
  a ^= b;
  a.show();
}

int main () {
  cout<<"Running all tests..."<<endl;
  clock_t begin = clock();
  testContructors();
  testStaticMethods();
  testMethodShow();
  testMethodSize();
  testSubscriptOperators();
  testMethodAppend();
  testMethodInsert();
  testMethodErase();
  testMethodFill();
  testMethodReverse();
  testMethodResize();
  testMethodCount();
  testMethodFind();
  testMethodFindAll();
  testMethodShift();
  testMethodContains();
  testMethodReplace();
  testMethodSlice();
  testMethodClear();
  testMethodUnique();
  testMethodSort();
  testMethodForEach();
  testMethodFilter();
  testMethodMap();
  testMethodsMinMax();
  testMethodsArgminArgmax();
  testMethodsSumProduct();
  testMethodsMeans();
  testMethodsVarStdev();
  testOperatorsArithmetic();
  testOperatorsComparison();
  testOperatorsBoolean();
  clock_t end = clock();
  double elapsed = double(end - begin) / CLOCKS_PER_SEC;
  cout<<"Testing complete in "<<elapsed<<"s."<<endl;
 
  // END //
  cin.ignore();
  cin.get();
  return 0;
}