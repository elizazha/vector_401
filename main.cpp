#include <iostream>
#include <iomanip>
#include "top_it_vector.hpp"

bool testEmptyVector()
{
  //std::cout << __func__ << "\n"; // выводит рназвание исполняемой функции
  topit::Vector< int > v;
  return v.isEmpty();
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
        {"test capacity if popback's", testCapacityPopback}
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