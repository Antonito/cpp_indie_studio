#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <memory>
#include <cstdint>

namespace zip
{
  class Huffman
  {
  public:
    static std::unique_ptr<std::uint8_t[]> compress(std::uint8_t const *data,
                                                    std::size_t         len);
    static std::unique_ptr<std::uint8_t[]> decompress(std::uint8_t const *data,
                                                      std::size_t         len);

    Huffman(Huffman const &) = delete;
    Huffman &operator=(Huffman const &) = delete;

  private:
    Huffman();
  };
}

#endif // !HUFFMAN_HPP_
