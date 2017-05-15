#ifndef SECTION_HPP_
#define SECTION_HPP_

#include <string>
#include <vector>

namespace ini
{
  class Section
  {
  public:
    struct Field
    {
      std::string name;
      std::string value;
    };

    explicit Section(std::string const &name = "");
    Section(Section const &) = default;
    Section(Section &&) = default;
    ~Section();

    Section &operator=(Section const &) = default;
    Section &operator=(Section &&) = default;

    std::string &      field(std::string const &name);
    std::string const &field(std::string const &name) const;

    std::string &      operator[](std::string const &name);
    std::string const &operator[](std::string const &name) const;

    void remove(std::string const &name);

    bool has(std::string const &name);

    std::string const &name() const;

    std::size_t fieldsCount() const;

    using iterator = std::vector<Field>::iterator;
    using const_iterator = std::vector<Field>::const_iterator;
    using reverse_iterator = std::vector<Field>::reverse_iterator;
    using const_reverse_iterator = std::vector<Field>::const_reverse_iterator;

    iterator               begin();
    iterator               end();
    const_iterator         begin() const;
    const_iterator         end() const;
    const_iterator         cbegin() const;
    const_iterator         cend() const;
    reverse_iterator       rbegin();
    reverse_iterator       rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

  private:
    std::string        m_name;
    std::vector<Field> m_fields;
  };

  std::ostream &operator<<(std::ostream &os, Section const &s);
}

#endif // !SECTION_HPP_
