#ifndef FASTLIST_HPP_
#define FASTLIST_HPP_

namespace core
{
  template <typename T>
  class FastList
  {
  public:
    FastList() : m_data()
    {
    }

    FastList(FastList const &other) : m_data(other.m_data)
    {
    }

    FastList(FastList &&other) : m_data(std::move(other.m_data))
    {
    }

    ~FastList()
    {
    }

    FastList &operator=(FastList const &other)
    {
      if (this == &other)
	return (*this);
      m_data = other.m_data;
      return (*this);
    }

    FastList &operator=(FastList &&other)
    {
      if (this == &other)
	return (*this);
      m_data = std::move(other.m_data);
      return (*this);
    }

    T &operator[](std::size_t i)
    {
      return (m_data[i]);
    }

    T const &operator[](std::size_t i) const
    {
      return (m_data[i]);
    }

    std::size_t size() const
    {
      return (m_data.size());
    }

    void push_back(T const &e)
    {
      m_data.push_back(e);
    }

    void push_back(T &&e)
    {
      m_data.push_back(std::move(e));
    }

    void push_front(T const &e)
    {
      m_data.insert(m_data.begin(), e);
    }

    void push_front(T &&e)
    {
      m_data.insert(m_data.begin(), std::move(e));
    }

    T &front()
    {
      return (m_data.front());
    }

    T const &front() const
    {
      return (m_data.front());
    }

    T &back()
    {
      return (m_data.back());
    }

    T const &back() const
    {
      return (m_data.back());
    }

    void clear()
    {
      m_data.clear();
    }

    bool empty()
    {
      return (m_data.empty());
    }

    void pop_front()
    {
      m_data.erase(m_data.begin());
    }

    void pop_back()
    {
      m_data.pop_back();
    }

    void erase(std::size_t n)
    {
      m_data.erase(m_data.begin() + n);
    }

    void erase(std::size_t n, std::size_t m)
    {
      m_data.erase(m_data.begin() + n, m_data.begin() + m);
    }

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator =
        typename std::vector<T>::const_reverse_iterator;

    iterator begin()
    {
      return (m_data.begin());
    }

    reverse_iterator rbegin()
    {
      return (m_data.rbegin());
    }

    const_iterator cbegin() const
    {
      return (m_data.cbegin());
    }

    const_reverse_iterator crbegin() const
    {
      return (m_data.crbegin());
    }

  private:
    std::vector<T> m_data;
  };
}

#endif // !FASTLIST_HPP_
