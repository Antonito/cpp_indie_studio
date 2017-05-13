#ifndef INI_HPP_
#define INI_HPP_

#include <vector>
#include "Section.hpp"

namespace ini
{
  class Ini
  {
  public:
    Ini();
    Ini(Ini const &) = default;
    Ini(Ini &&) = default;
    ~Ini();

    Ini &operator=(Ini const &) = default;
    Ini &operator=(Ini &&) = default;

    Section &      operator[](std::string const &name);
    Section const &operator[](std::string const &name) const;

    bool has(std::string const &name) const;

    void remove(std::string const &name);

    using iterator = std::vector<Section>::iterator;
    using const_iterator = std::vector<Section>::const_iterator;
    using reverse_iterator = std::vector<Section>::reverse_iterator;
    using const_reverse_iterator =
        std::vector<Section>::const_reverse_iterator;

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

    void saveAs(std::string const &filename);
    void loadFrom(std::string const &filename);

  private:
    std::vector<Section> m_sections;
  };
}

#endif // !INI_HPP_
