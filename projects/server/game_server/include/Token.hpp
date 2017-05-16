#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include "Hash.hpp"

class Token
{
public:
  Token();
  ~Token();

  // Does not copy the m_crypto member
  Token(Token const &);
  Token &operator=(Token const &);

  // Comparison
  bool operator==(Token const &) const;
  bool operator==(std::string const &str) const;
  bool operator!=(Token const &) const;
  bool operator!=(std::string const &str) const;

  bool               isGenerated() const;
  void               generate();
  std::string const &getToken() const;

private:
  std::string                       m_token;
  crypto::Hash<crypto::AHash::SHA1> m_crypto;
};

#endif // !TOKEN_HPP_
