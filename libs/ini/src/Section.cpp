#include "ini_stdafx.hpp"
#include "..\include\Section.hpp"

namespace ini
{
  Section::Section(std::string const &name) : m_name(name), m_fields()
  {
  }

  Section::~Section()
  {
  }

  std::string &Section::field(std::string const &name)
  {
    for (Field &f : m_fields)
      {
	if (f.name == name)
	  {
	    return (f.value);
	  }
      }
    m_fields.push_back({name, ""});
    return (m_fields.back().value);
  }

  std::string const &Section::field(std::string const &name) const
  {
    for (Field const &f : m_fields)
      {
	if (f.name == name)
	  {
	    return (f.value);
	  }
      }
    return ("");
  }

  std::string &Section::operator[](std::string const &name)
  {
    return (this->field(name));
  }

  std::string const &Section::operator[](std::string const &name) const
  {
    return (this->field(name));
  }

  void Section::remove(std::string const &name)
  {
    for (std::vector<Field>::iterator it = m_fields.begin();
         it != m_fields.end(); ++it)
      {
	if (it->name == name)
	  {
	    m_fields.erase(it);
	    return;
	  }
      }
  }

  bool Section::has(std::string const &name)
  {
    for (Field const &f : m_fields)
      {
	if (f.name == name)
	  {
	    return (true);
	  }
      }
    return (false);
  }

  std::string const &Section::name() const
  {
    return (m_name);
  }

  std::size_t Section::fieldsCount() const
  {
    return (m_fields.size());
  }

  Section::iterator Section::begin()
  {
    return (m_fields.begin());
  }

  Section::iterator Section::end()
  {
    return (m_fields.end());
  }

  Section::const_iterator Section::begin() const
  {
    return (m_fields.begin());
  }

  Section::const_iterator Section::end() const
  {
    return (m_fields.end());
  }

  Section::const_iterator Section::cbegin() const
  {
    return (m_fields.cbegin());
  }

  Section::const_iterator Section::cend() const
  {
    return (m_fields.cend());
  }

  Section::reverse_iterator Section::rbegin()
  {
    return (m_fields.rbegin());
  }

  Section::reverse_iterator Section::rend()
  {
    return (m_fields.rend());
  }

  Section::const_reverse_iterator Section::rbegin() const
  {
    return (m_fields.rbegin());
  }

  Section::const_reverse_iterator Section::rend() const
  {
    return (m_fields.rend());
  }

  Section::const_reverse_iterator Section::crbegin() const
  {
    return (m_fields.crbegin());
  }

  Section::const_reverse_iterator Section::crend() const
  {
    return (m_fields.crend());
  }

  std::ostream &operator<<(std::ostream &os, Section const &s)
  {
    std::string const &name = s.name();

    if (name.size() > 0)
      {
	os << '[' << s.name() << ']' << '\n';
      }

    for (Section::Field const &f : s)
      {
	os << f.name << '=' << f.value << '\n';
      }

    return (os);
  }
}