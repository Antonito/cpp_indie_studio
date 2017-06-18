#include <chrono>
#include "Token.hpp"
#include "Logger.hpp"

constexpr std::chrono::minutes Token::validityInMinuts;

Token::Token() : m_token(""), m_crypto(), m_genDate()
{
}

Token::~Token()
{
}

Token::Token(Token const &other)
    : m_token(other.m_token), m_crypto(), m_genDate(other.m_genDate)
{
}

Token &Token::operator=(Token const &other)
{
  if (this != &other)
    {
      m_token = other.m_token;
      m_genDate = other.m_genDate;
    }
  return (*this);
}

bool Token::operator==(Token const &other) const
{
  return (m_token == other.m_token);
}

bool Token::operator==(std::string const &str) const
{
  return (str == m_token);
}

bool Token::operator!=(Token const &other) const
{
  return (m_token != other.m_token);
}

bool Token::operator!=(std::string const &str) const
{
  return (str != m_token);
}

bool Token::isValid() const
{
  std::chrono::system_clock::time_point const now =
      std::chrono::system_clock::now();
  return (std::chrono::duration_cast<std::chrono::minutes>(now - m_genDate)
              .count() <= Token::validityInMinuts.count());
}

bool Token::isGenerated() const
{
  return (m_token != "");
}

std::string const &Token::getToken() const
{
  return (m_token);
}

void Token::generate()
{
  nope::log::Log(Debug) << "Generating token";

  // BaseStr + time point
  std::string base = "G4m3_-_S3rv3rT0k3n__" +
                     std::to_string(std::chrono::system_clock::to_time_t(
                         std::chrono::system_clock::now())) +
                     "//==//";

  m_crypto.compute(reinterpret_cast<std::uint8_t const *>(base.c_str()),
                   base.length());
  m_token = m_crypto.getHash();
  m_genDate = std::chrono::system_clock::now();

  nope::log::Log(Debug) << "Generated token : " << m_token;
}
