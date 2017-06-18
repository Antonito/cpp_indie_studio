#include "ini_stdafx.hpp"
#include <iostream>

namespace ini
{
  Ini::Ini() : m_sections()
  {
  }

  Ini::~Ini()
  {
  }

  Section &Ini::operator[](std::string const &name)
  {
    for (Section &s : m_sections)
      {
	if (s.name() == name)
	  {
	    return (s);
	  }
      }
    m_sections.emplace_back(name);
    return (m_sections.back());
  }

  Section const &Ini::operator[](std::string const &name) const
  {
    for (Section const &s : m_sections)
      {
	if (s.name() == name)
	  {
	    return (s);
	  }
      }
    throw std::invalid_argument("No such section named '" + name + '"');
  }

  bool Ini::has(std::string const &name) const
  {
    for (Section const &s : m_sections)
      {
	if (s.name() == name)
	  {
	    return (true);
	  }
      }
    return (false);
  }

  void Ini::remove(std::string const &name)
  {
    for (std::vector<Section>::iterator it = m_sections.begin();
         it != m_sections.end(); ++it)
      {
	if (it->name() == name)
	  {
	    m_sections.erase(it);
	    return;
	  }
      }
  }

  Ini::iterator Ini::begin()
  {
    return (m_sections.begin());
  }

  Ini::iterator Ini::end()
  {
    return (m_sections.end());
  }

  Ini::const_iterator Ini::begin() const
  {
    return (m_sections.begin());
  }

  Ini::const_iterator Ini::end() const
  {
    return (m_sections.end());
  }

  Ini::const_iterator Ini::cbegin() const
  {
    return (m_sections.cbegin());
  }

  Ini::const_iterator Ini::cend() const
  {
    return (m_sections.cend());
  }

  Ini::reverse_iterator Ini::rbegin()
  {
    return (m_sections.rbegin());
  }

  Ini::reverse_iterator Ini::rend()
  {
    return (m_sections.rend());
  }

  Ini::const_reverse_iterator Ini::crbegin() const
  {
    return (m_sections.crbegin());
  }

  Ini::const_reverse_iterator Ini::crend() const
  {
    return (m_sections.crend());
  }

  Ini::const_reverse_iterator Ini::rbegin() const
  {
    return (m_sections.rbegin());
  }

  Ini::const_reverse_iterator Ini::rend() const
  {
    return (m_sections.rend());
  }

  void Ini::saveAs(std::string const &filename)
  {
    std::ofstream os(filename.c_str(), std::fstream::out);

    if (os.is_open() == false)
      {
	throw IOError("Cannot open " + filename);
      }

    bool first = true;

    if (this->has(""))
      {
	os << (*this)[""];
	first = false;
      }

    for (Section const &s : m_sections)
      {
	if (s.name() == "")
	  {
	    continue;
	  }

	if (first)
	  {
	    first = false;
	  }
	else
	  {
	    os << '\n';
	  }
	os << s;
      }
    os << std::flush;
  }

  void Ini::loadFrom(std::string const &filename)
  {
    std::ifstream fs(filename.c_str());

    if (fs.is_open() == false)
      {
	throw IOError("Cannot open " + filename);
      }

    std::string line;

    // Loop on each lines
    while (std::getline(fs, line))
      {
	std::size_t i = 0;

	// Go to the next "non space" character
	while (i < line.size() && std::isspace(line[i]))
	  {
	    ++i;
	  }
	// Check if it's a comment
	if (i == line.size() || line[i] == '#' || line[i] == ';')
	  {
	    continue;
	  }
	// Section name
	else if (line[i] == '[')
	  {
	    ++i;

	    std::size_t start = i;

	    while (i < line.size() && line[i] != ']')
	      {
		++i;
	      }

	    m_sections.emplace_back(line.substr(start, i - start));
	  }
	// Field
	else
	  {
	    std::size_t start = i;

	    while (line[i] != '=')
	      {
		if (i == line.size())
		  {
		    throw IOError("Invalid line (mising equal sign)");
		  }
		++i;
	      }

	    if (i == start)
	      {
		throw IOError("Invalid line (missing property)");
	      }

	    if (m_sections.size() == 0)
	      {
		m_sections.emplace_back("");
	      }

	    m_sections.back()[line.substr(start, i - start)] =
	        line.substr(i + 1);
	  }
      }
  }
}
