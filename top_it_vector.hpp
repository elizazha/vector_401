#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector{
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept;//дз реализоввать + тесты 0
    size_t getSize() const noexcept;//дз реализоввать + тесты 0
    size_t getCapacity() const noexcept;//дз реализоввать + тесты 0

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

template< class T >
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
void topit::Vector<T>::pushback(const T& v)
{
  if(size_ == capacity_)
  {
    size_t newCap;
    if(capacity_ == 0)
    {
      newCap = 1;
    }else
    {
      newCap = capacity_ + 1;
    }
    T* newData = new T[newCap];
    for(size_t i = 0; i < size_; i++)
    {
      newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCap;
  }

  data_[size_] = v;
  size_++;
}

template<class T>
void topit::Vector<T>::popback()
{
  if(size_ == 0)
  {
    throw std::out_of_range("size is zero; no data")
  }
  size_--;
}

#endif
