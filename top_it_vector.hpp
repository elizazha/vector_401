#ifndef TOP-IT-VECTOR_HPP
#define TOP-IT-VECTOR_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector{
    ~Vector();
    Vector();
    Vector(const Vecttor&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);


    bool isEmpty() const noexcept;//дз реализоввать + тесты
    size_t getSize() const noexcept;//дз реализоввать + тесты
    size_t getCapacity() const noexcept;//дз реализоввать + тесты

    void pushback(const T& v);//дз реализоввать + тесты
    void popback();//дз реализоввать + тесты
    void insert(size_t i, const T& v);
    void erase(size_t i);

    private:
      T* data_;
      size_t size_, capacity_;
  };
}

template< class T>
void topit::Vector<T>::pushback(const T& v)
{}

template< class T >
topit::Vector< T > :: Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}

template< class T >
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}

#endif
