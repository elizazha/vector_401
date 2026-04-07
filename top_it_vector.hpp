#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include "top_it_iterators.hpp"
//ДЗ на 31.03
//Тестированипе для копирования и перемещения
// два insert два erase- строгая гарантия + сделать тесты
//строгая гарантия copy insult

//доп дз - оценивается отдельно
// итераторы для векторы
//прилумать несколько insert|erase c итераторами
//по 3 штуик + тесты


//дз(класная)
//сделать reserve, shrinkToFit, unsafePushback, pushbackRange, pushbackCount
//+ дз: исправить код, избавиться от требования тогго, чтобы тип Т конструировался по умолчанию
//
namespace topit
{
  template< class T >
  struct Vector{
    //explicit Либо только там, где initializer_list, либо на все пользовательские конструкторы 
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector(size_t size, const T& init);
    explicit Vector(std::initializer_list< T > il);

    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;
    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;

    bool isEmpty() const noexcept;//дз реализоввать + тесты 0
    size_t getSize() const noexcept;//дз реализоввать + тесты 0
    size_t getCapacity() const noexcept;//дз реализоввать + тесты 0
    void swap(Vector< T >& rhs);
    
    void pushback(const T& v);//дз реализоввать + тесты
    void popback();//дз реализоввать + тесты

    void insert(size_t i, const T& v);
    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(size_t i);
    void erase(size_t start, size_t end);

    void insert(Iter<T> it, const T& v);
    void insert(Iter<T> it, T&& v);
    template<class IT>
    void insert(Iter<T> pos, IT first, IT last);

    Iter<T> erase(Iter<T> it);
    Iter<T> erase(Iter<T> first, Iter<T> last);
    template<class Pred>
    Iter<T> erase(Iter<T> first,Iter<T> last, Pred p);
    
    Iter<T> begin() noexcept;
    Iter<T> end() noexcept;
    CIter<T> cbegin() noexcept;
    CIter<T> cend() noexcept;
    //template< class FWDIterator> //прмпмер дз
    //void insert(FWDIterator begin, FWDIterator end)
    
    T& at(size_t id);
    const T& at(size_t id) const;

    //классная работа 30.03.26
    void reserve(size_t k);//убедиться, что хватает памяти на k элементов; size_t required; size_t delta - можем передавать разное
    void shrinkToFit();//сделать так, чтобы кол-во эл-тов вектора соответствовало емкости; уменькаем капасити
    template< class IT>
    void pushbackRange(IT b, IT e);
    void pushbackCount(size_t k, const T& val);

    private:
      void unsafePushback(const T&);
      explicit Vector(size_t size); // зачем explicit?
      T* data_;
      size_t size_, capacity_;
  };
  template< class T >
  bool operator==(const Vector < T >& lhs, const Vector< T >& rhs);
}

template< class T >
topit::Vector< T >::~Vector()
{
  for (size_t i = 0; i < size_; i++)
  {
    (data_ + i) -> ~T();
  }
  ::operator delete[](data_);
}
template< class T >
topit::Vector< T > :: Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template< class T >
topit::Vector<T>::Vector(const Vector<T>& rhs): Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.size_; ++i)
  {
    new(data_ + i) T(rhs.data_[i]);
  }
  size_ = rhs.size_;
}
template< class T >
topit::Vector< T >::Vector(Vector< T>&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
  {
    rhs.data_ = nullptr;
    rhs.size_ = 0;
    rhs.capacity_ = 0;
  }
template< class T >
topit::Vector< T >::Vector(size_t size, const T& init): Vector(size)
{
  size_t i = 0;
  try
  {
    for (; i < rhs.size_; ++i)
    {
      new(data_ + i) T(rhs.data_[i]);
    }
  }
  catch(...)
  {
    for (size_t j = 0; j < i; ++j)
      (data_ + j) -> ~T();

    ::operator delete[](data_);
    throw;
  }
  size_ = rhs.size_;
}
template< class T >
topit::Vector< T >::Vector(std::initializer_list< T > il):
  Vector(il.size())
{
  size_t i = 0;
  for (const auto& v : il)
  {
    new(data_ + i++) T(v);
  }
  size_ = il.size();
}


template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector& rhs)
{
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy = rhs;//same as cpy{rhs} // как нельзя писать по-другому?
  //free data of this
  // this <- cpy
  // data this <-> cpy
  // ~cpy -> free data
  // this <- this
  swap(cpy);
  return *this;
}
template< class T>
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if( this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}
template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  //return data_[id];
  const Vector* cthis = this;
  //return cthis -> operator[](id);
  return const_cast< T& >((*cthis)[id]);
}
template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}


template< class T >
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_ or !data_;
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
void topit::Vector< T >::swap(topit::Vector<T> &rhs)
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);

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
      newCap = capacity_ * 2;
    }
    T* newData = static_cast<T*>(::operator new[](sizeof(T) * newCap));
    size_t i = 0;
    try
    {
      for (; i < size_; i++)
      {
        new(newData + i) T(std::move(data_[i]));
      }
      new(newData + size_) T(v);
    }
    catch(...)
    {
      for (size_t j = 0; j < i; j++)
        (newData + j)->~T();

      ::operator delete[](newData);
      throw;
    }
    for (size_t j = 0; j < size_; ++j)
    {
      (data_ + j)->~T();
    }
    ::operator delete[](data_);

    data_ = newData;
    capacity_ = newCap;
  }else
  {
    new(data_ + size_) T(v);
  }

  size_++;
}
template<class T>
void topit::Vector<T>::popback()
{
  if(size_ == 0)
  {
    throw std::out_of_range("size is zero; no data");
  }
  if (size_ > 0) {
    size_--;
  }
  (data_ + size_)->~T();
}


template< class T >
void  topit::Vector<T>::insert(size_t i, const T& v)
{
  if (i > size_)
  {
    throw std::out_of_range("index more than size");
  }
  size_t newCap = (size_ + 1 > capacity_) ? (capacity_ == 0 ? 1 : capacity_ * 2) : capacity_;
  T* newData = static_cast<T*>(::operator new[](sizeof(T) * newCap));
  size_t constructed = 0;
  try
  {
    for (; constructed < i; ++constructed)
    {
      new(newData + constructed) T(data_[constructed]);
    }
    new(newData + constructed) T(v);
    ++constructed;
    for (size_t j = i; j < size_; ++j, ++constructed)
    {
      new(newData + constructed) T(data_[j]);
    }
  }catch(...)
  {
    for (size_t k = 0; k < constructed; ++k)
      (newData + k)->~T();
    ::operator delete[](newData);
    throw;
  }
  for (size_t j = 0; j < size_; ++j)
  {
    (data_ + j)->~T();
  }
  ::operator delete[](data_);
  data_ = newData;
  size_++;
  capacity_ = newCap;
}
template< class T >
void  topit::Vector<T>::insert(size_t i, const Vector< T >& rhs, size_t start, size_t end)
{
  if (start > end || end > rhs.size_ || i > size_)
    {
        throw std::out_of_range("bad range");
    }
    size_t count = end - start;
    size_t newSize = size_ + count;
    size_t newCap = (newSize > capacity_) ? newSize : capacity_;
    T* newData = static_cast<T*>(::operator new[](sizeof(T) * newCap));
    size_t constructed = 0;
    try
    {
        for (size_t j = 0; j < i; ++j, ++constructed)
        {
            new(newData + j) T(data_[j]);
        }
        for (size_t k = start; k < end; ++k, ++constructed)
        {
            new(newData + constructed) T(rhs.data_[k]);
        }
        for (size_t j = i; j < size_; ++j, ++constructed)
        {
            new(newData + constructed) T(data_[j]);
        }
    }
    catch (...)
    {
        for (size_t j = 0; j < constructed; ++j)
        {
            (newData + j)->~T();
        }
        ::operator delete[](newData);
        throw;
    }
    for (size_t j = 0; j < size_; ++j)
    {
        (data_ + j)->~T();
    }
    ::operator delete[](data_);
    data_ = newData;
    size_ = newSize;
    capacity_ = newCap; 
}
template< class T >
void  topit::Vector<T>::erase(size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("index of delete more then size");
  }
  (data_ + i) -> ~T();
  for (size_t j = i; j < size_ - 1; j++)
  {
    new(data_ + j) T(std::move(data_[j + 1]));
    (data_ + j + 1) -> ~T();
  }
  size_--;
}
template< class T >
void  topit::Vector<T>::erase(size_t start, size_t end)
{
  if ( start > end || end > size_)
  {
    throw std::out_of_range("start mor thyan end OR end more than size");
  }
  size_t count = end - start;
  for (size_t i = start; i < end; i++)
  {
    (data_ + i) -> ~T();
  }
  for (size_t i = start; i + count < size_; i++)
  {
    new(data_ + i) T(std::move(data_[i + count]));
    (data_ + i + count) -> ~T();
  }
  size_ -= count;
}


template< class T >
void topit::Vector<T>::insert(Iter<T> it, const T& v)
{
  if (it < begin() || it > end())
  {
    throw std::out_of_range("iterator out of range");
  }
  size_t pos = it - begin();
  insert(pos, v);
}
template< class T >
void topit::Vector<T>::insert(Iter<T> it, T&& v)
{
  if (it < begin() || it > end())
  {
    throw std::out_of_range("iterator out of range");
  }
  size_t pos = it - begin();
  insert(pos, v);
}
template< class T >
template< class IT >
void topit::Vector<T>::insert(Iter<T> pos, IT first, IT last)
{
  if (pos < begin() || pos > end())
  {
    throw std::out_of_range("iterator pos out of range");
  }
  size_t index = pos - begin();
  for (IT it = first; it != last; ++it)
  {
    insert(index++, *it);
  }
}


template<class T>
topit::Iter<T> topit::Vector<T>::erase(Iter<T> it)
{
  if (it < begin() || it >= end())
  {
    throw std::out_of_range("iterator out of range");
  }
  size_t pos = it - begin();
  erase(pos);
  return topit::Iter<T>(data_ + pos);
}
template<class T>
topit::Iter<T> topit::Vector<T>::erase(Iter<T> first, Iter<T> last)
{
  if (first < begin() || last > end() || first > last)
  {
    throw std::out_of_range("bad range");
  }
  size_t start = first - begin();
  size_t endPos = last - begin();
  erase(start, endPos);
  return topit::Iter<T>(data_ + start);
}
template<class T>
template<class Pred>
topit::Iter<T> topit::Vector<T>::erase(Iter<T> first, Iter<T> last, Pred p)
{
  if (first < begin() || last > end() || first > last)
  {
    throw std::out_of_range("bad range");
  }
  Vector<T> tmp;
  for (auto it = begin(); it != first; ++it)
  {
    tmp.pushback(*it);
  }
  for (auto it = first; it != last; ++it)
  {
    if (!p(*it))
    {
      tmp.pushback(*it);
    }
  }
  for (auto it = last; it != end(); ++it)
  {
    tmp.pushback(*it);
  }
  swap(tmp);
  return topit::Iter<T>(data_ + (first - begin()));
}


template< class T >
topit::Iter< T > topit::Vector< T >::begin() noexcept
{
  return Iter< T >(data_);
}
template< class T >
topit::Iter< T > topit::Vector< T >::end() noexcept
{
  return Iter< T >(data_ + size_);
}
template< class T >
topit::CIter< T > topit::Vector< T >::cbegin() noexcept
{
  return CIter< T >(data_);
}
template< class T >
topit::CIter< T > topit::Vector< T >::cend() noexcept
{
  return CIter< T >(data_ + size_);
}


template< class T>
T& topit::Vector< T >::at(size_t id)
{
  // if( id < getSize())
  // {
  //   return data_[id];
  // }
  // throw std::range_error("bad id");


  //return const_cast< T& >(static_cast< const topit::Vector<T>* >(this)->at(id));


  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis -> at(id));
}
template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if( id < getSize())
  {
    //return data_[id];

    //return this->operator[](id);
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}


template< class T >
void topit::Vector< T >::reserve(size_t newCap)
{
  if (newCap <= capacity_)
  {
    return;
  }
  T* newData = static_cast< T* >(::operator new[] (sizeof(T) * newCap));
  size_t i = 0;
  try {
    for (; i < size_; i++)
    {
      new(newData + i) T(std::move(data_[i]));
    }
  }catch (...)
  {
    for (; i > 0; i--) {
      (newData + i - 1) -> ~T();
    }
    ::operator delete[] (newData);
    throw;
  }
  for (i = 0; i < size_; i++)
  {
    (data_ + i) -> ~T();
  }
  ::operator delete[] (data_);
  data_ = newData;
  capacity_ = newCap;
}
template< class T >
void topit::Vector< T >::shrinkToFit()
{
  if (size_ == capacity_)
  {
    return;
  }
  T* newData = static_cast<T*>(operator new[] (sizeof(T) * size_));
  size_t i = 0;
  try
  {
    for (; i < size_; i++)
    {
      new(newData + i) T(std::move(data_[i]));
    }
  }catch(...)
  {
    for (; i > 0; i--) {
      (newData + i - 1) -> ~T();
    }
    ::operator delete[] (newData);
    throw;
  }
  for (i = 0; i < size_; i++)
  {
    (data_ + i)->~T();
  }
  ::operator delete[] (data_);
  data_ = newData;
  capacity_ = size_;
}
template< class T>
template< class IT>
void topit::Vector< T >::pushbackRange(IT b, IT e)
{
  size_t c = 0;
  for (IT it = b; it != e; ++it)
  {
    pushback(*it);
  }
  //size_t c = std::distance(b, e);
  // лучше писать pushbackRange(IT b, size_t e) потому что итераторы бывают разного достпуа и зачем нам считаь если польз может сам даьб данные
  //ч/з итераторы это долго, муторно и зря сделанная работа
  //мы не знаем какие итераторы у пользователля, поэтому более эффективно, если польз сам даст ук. на начало и размер
}
template< class T>
void topit::Vector< T >::pushbackCount(size_t k, const T& val)
{
  for( size_t i = 0; i < k; ++i)
  {
    pushback(val);
  }
  //если памяти не хватает на k
  //- делаем так, чтобы хватало k
  // добавляем в конец*
}


template< class T>
void topit::Vector< T >::unsafePushback(const T& v)
{
 assert(size_ < capacity_); // assert - проверяет. если эта штука не true, то выводит ошибку(похоже на BOOST тесты)
 new(data_ + size_) T(v);
 size_++;
}
template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? static_cast< T* >(::operator new[](sizeof(T) * size)) : nullptr),
  size_(0),
  capacity_(size)
{}


template< class T >
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs) noexcept
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && (lhs[i] == rhs[i])); ++i);
  return isEqual;
}


#endif
