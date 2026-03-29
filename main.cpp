#include <iostream>
#include <iomanip>
#include "top_it_vector.hpp"

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav = v;
  return v ==yav;
}
bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushback(1);
  topit::Vector< int > yav = v;
  try{
    return yav.getSize() == v.getSize() && yav.at(0) == v.at(0);
  }catch(...){
    return false;
  }
}

bool testEmptyVector()
{
  //std::cout << __func__ << "\n"; // выводит рназвание исполняемой функции
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testElementsAccess(){
  topit::Vector< int > v;
  v.pushback(1);
  try{
    int& val = v.at(0);
    return val == 1;
  }catch(...){
    return false;
  }
}

bool testElementsOutOfBoundAccess(){
  topit::Vector< int > v;
  try{
    int& val = v.at(0);
    return false;
  }catch(const std::out_of_range&){
    return true;
  }catch(...){
    return false;
  }
}

bool testElementsConstAccess(){
  topit::Vector< int > v;
  v.pushback(1);
  const topit::Vector< int >& rv = v;
  try{
    const int& val = rv.at(0);
    return val == 1;
  }catch(...){
    return false;
  }
}

bool testElementsOutOfBoundConstAccess(){
  const topit::Vector< int > v; // так можно только в out, потому что он изначально пцстой, нас это устраивает
  try{
    v.at(0);
    return false;
  }catch(const std::out_of_range&){
    return true;
  }catch(...){
    return false;
  }
}

bool testSize()
{
  topit::Vector< int > v;
  return v.getSize() == 0;
}

bool testSize2() {
    topit::Vector<int> v;
    v.pushback(1);
    v.pushback(2);
    v.popback();
    v.pushback(3);
    return v.getSize() == 2;
}

bool testPushback()
{
  topit::Vector< int > v;
  v.pushback(5);
  return v.getSize() == 1 && !v.isEmpty() && v.getCapacity() >= 1;;
}

bool testMultiplePushback()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; i++)
  {
    v.pushback(i);
  }
  return v.getSize() == 5;
}

bool testPopback()
{
  topit::Vector< int > v;
  v.pushback(10);
  v.popback();
  return v.getSize() == 0 && v.isEmpty();
}

bool testPopbackEmpty()
{
  topit::Vector< int > v;
  try
  {
    v.popback();
  }catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return true;
  }
  return false;
}

bool testCapacityMultiple()
{
  topit::Vector< int > v;
  v.pushback(1);
  bool q1 = v.getCapacity() == 1;
  v.pushback(2);
  bool q2 = v.getCapacity() == 2;
  v.pushback(3);
  bool q3 = v.getCapacity() == 3;
  return q1 && q2 && q3;
}

bool testCapacityPopback()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; i++)
  {
    v.pushback(i);
  }
  size_t firstCap = v.getCapacity();
  v.popback();
  v.popback();
  return v.getCapacity() == firstCap;

}

bool testEraseOne()
{
  topit::Vector< int > v;
  v.pushback(1);
  v.pushback(2);
  v.pushback(3);
  v.erase(1);
  return (v.getSize() == 2 && (v[0] == 1 && v[1] == 3));
}

bool testEraseStart()
{
  topit::Vector< int > v;
  v.pushback(1);
  v.pushback(2);
  v.erase(0);
  return (v.getSize() == 1 && v[0] == 2);
}

bool testEraseFromTo()
{
  topit::Vector< int > v;
  v.pushback(1);
  v.pushback(2);
  v.pushback(3);
  v.pushback(4);
  v.erase(1, 3);
  return (v.getSize() == 2 && (v[0] == 1 && v[1] == 4));

}

bool testInsertSingle()
{
  topit::Vector< int > v;
  v.pushback(1);
  v.pushback(3);
  v.insert(1, 2);
  return(v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3);
}

bool testInsertStart()
{
  topit::Vector< int > v;
  v.pushback(2);
  v.pushback(3);
  v.insert(0, 1);
  return (v[0] == 1 && v[1] == 2);

}

bool testInsertFromTo()
{
  topit::Vector< int > v;
  v.pushback(1);
  v.pushback(4);
  topit::Vector< int > rhs;
  rhs.pushback(2);
  rhs.pushback(3);
  v.insert(1, rhs, 0, 2);
  return (v.getSize() == 4 && v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4);
}


int main()
{
  using test_t = std::pair< const char*, bool(*)() >;
  test_t tests[] = {
        {"Empty vector", testEmptyVector},
        {"Test size of empty vector", testSize},
        {"Test size of non empty vector", testSize2},
        {"test single pushback", testPushback},
        {"test multiple pushback's", testMultiplePushback},
        {"test single popback after pushback",testPopback },
        {"test if try to popback empty list", testPopbackEmpty},
        {"test changes of capacity", testCapacityMultiple},
        {"test capacity if popback's", testCapacityPopback},
        {"test inbound acsses", testElementsAccess},
        {"test out of bound access", testElementsOutOfBoundAccess}, 
        {"test inbound const acsses", testElementsConstAccess},
        {"test out of bound const access", testElementsOutOfBoundConstAccess},
        {"test copy for empty vector", testCopyConstructorForEmpty},
        {"test copy for non empty vector", testCopyConstructorForNonEmpty},
        {"test single erase", testEraseOne},
        {"test erase begining", testEraseStart},
        {"test erase range", testEraseFromTo},
        {"test insert single", testInsertSingle},
        {"test insert begining", testInsertStart},
        {"test insert range", testInsertFromTo}
    };
  // bool(*tests[])() = {//массик указателей ничего не принимающий восвращающий логическое
  //   testEmptyVector
  // };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for(size_t i = 0; i <count; i++)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }
  std::cout << "Result: " << pass << "\n";
  //подсчет пройденных.не пройденных тестов
  //выводить только не прошедшие тесты
  return 0;
}