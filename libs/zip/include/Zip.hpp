#ifndef ZIP_HPP_
#define ZIP_HPP_

#include <cstdint>

namespace zip
{
  class Zip
  {
  public:
  private:
    // Everything is in little endian
    struct LocalFileHeader
    {
      std::uint32_t signature; // 0x04034b50
      std::uint16_t version;
      std::uint16_t bitflag;
      std::uint16_t compressMeth;
      std::uint16_t lastModTime;
      std::uint16_t lastModeDate;
      std::uint32_t crc32;
      std::uint32_t compressedSize;
      std::uint32_t uncompressedSize;
      std::uint16_t filenameLength;
      std::uint16_t extraFieldLength;
      std::uint8_t *filename;
      std::uint8_t *extrafield;
    };

    struct DataDescriptor
    {
      std::uint32_t signature; //  0x08074b50
      std::uint32_t crc32;
      std::uint32_t compressedSize;
      std::uint32_t uncompressedSize;
    };

    struct CentralDirectoryFileHeader
    {
    };

    // EOCD
    struct EndOfCentralDirectoryRecord
    {
      std::uint32_t signature; // 0x06054b50
      std::uint16_t diskNb;
      std::uint16_t centralDirStartDisk;
      std::uint16_t nbCDRonDisk;
      std::uint16_t nbOfCDR;
      std::uint32_t sizeCentralDirectory;
      std::uint32_t relaCentralDirectoryStartOffset;
      std::uint16_t commentLen;
      std::uint8_t *comment;
    };
  };
}

#endif // !ZIP_HPP_
