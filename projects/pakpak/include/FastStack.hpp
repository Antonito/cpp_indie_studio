#ifndef FASTSTACK_HPP_
#define FASTSTACK_HPP_

#include <vector>

namespace core
{
  template <typename T>
  class FastStack
  {
  public:
    FastStack() : m_data()
    {
    }

    FastStack(FastStack const &other) : m_data(other.m_data)
    {
    }

    FastStack(FastStack &&other) : m_data(std::move(other.m_data))
    {
    }

    ~FastStack()
    {
    }

    FastStack &operator=(FastStack const &other)
    {
      if (this == &other)
	return (*this);
      m_data = other.m_data;
      return (*this);
    }

    FastStack &operator=(FastStack &&other)
    {
      if (this == &other)
	return (*this);
      m_data = std::move(other.m_data);
      return (*this);
    }

    void clear()
    {
      m_data.clear();
    }

    std::size_t size() const
    {
      return (m_data.size());
    }

    void push(T const &e)
    {
      m_data.push_back(e);
    }

    void push(T &&e)
    {
      m_data.push_back(std::move(e));
    }

    void pop()
    {
      m_data.pop_back();
    }

    T &top()
    {
      return (m_data.back());
    }

    T const &top() const
    {
      return (m_data.back());
    }

    bool empty() const
    {
      return (m_data.size() == 0);
    }

    T &operator[](std::size_t i)
    {
      return (m_data[i]);
    }

    T const &operator[](std::size_t i) const
    {
      return (m_data[i]);
    }

  private:
    std::vector<T> m_data;
  };
}

#endif // !FASTSTACK_HPP_
