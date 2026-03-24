#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
//ДЗ на 31.03
//Тестированипе для копирования и перемещения
// два insert два erase- строгая гарантия + сделать тесты
//строгая гарантия copy insult

//доп дз - оценивается отдельно
// итераторы для векторы
//прилумать несколько insert|erase c итераторами\
//по 3 штуик + тесты

namespace topit
{
  template< class T >
  struct Vector{
    ~Vector();
    Vector();
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector(size_t size, const T& init);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);
    void swap(Vector< T >&);

    bool isEmpty() const noexcept;//дз реализоввать + тесты 0
    size_t getSize() const noexcept;//дз реализоввать + тесты 0
    size_t getCapacity() const noexcept;//дз реализоввать + тесты 0

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void pushback(const T& v);//дз реализоввать + тесты
    void popback();//дз реализоввать + тесты
    void insert(size_t i, const T& v);
    void erase(size_t i);

    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(Size_t start, size_t end);

    //template< class FWDIterator> //прмпмер дз
    //void insert(FWDIterator begin, FWDIterator end)

    private:
      explicit Vector(size_t size); // зачем explicit?
      T* data_;
      size_t size_, capacity_;
  };
  template< class T >
  bool operator==(const Vector < T >& lhs, const Vector< T >& rhs);
}

template< class T>
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs)
{
  if( this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  retyrn *this;
}

template< class T >
topit::Vector< T >::Vector(Vector< T>&&rhs) noexcept:
  data_(rhs.data_),
  size(rhs.sized_),
  capacity_(rhs.capacity_)
  {
    /
  }


template< class T >
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && [i] == rhs[i]); ++i);
    return isEqual;
  return res;
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init):
Vector(size)
{
  for( size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size):
data_(size ? new T[size] : nullptr),
size_(size),
 capacity_(size)
 {
  for+ try/catch
 }

template< class T >
topit::Vector<T>::Vector(const Vector<T>& rhs):
Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    try{
      data_[i] = rhs[i];
    }catch(..){
      delete[] data_;
      throw;
    }
  }
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  //return data_[id];
  const Vector< T >* cthis = this;
  //return cthis -> operator[](id);
  return const_cast< T& >((*cthis)[id]);
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
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
    return (*cthis)[id];
  }
  throw std::out_of_range("bad id");
}

template< class T >
void topit::Vector< T >::swap(Vector < T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);

}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  Vector< T > cpy = rhs;//same as cpy{rhs} // как нельзя писать по-другому?
  //free data of this
  // this <- cpy
  // data this <-> cpy
  // ~cpy -> free data
  // this <- this
  swap(cpy);
  return *this;
}

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
    throw std::out_of_range("size is zero; no data");
  }
  size_--;
}

#endif


