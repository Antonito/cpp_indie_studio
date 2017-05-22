#ifndef METADATA_HPP_
#define METADATA_HPP_

#include <tuple>
#include <string>

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif

// Trick for Windows macro correct __VA_ARGS__ expansion
#define NOPE_EXPAND(X) X

// Count macro parameters(up to 64 elements)
#define NOPE_COUNT_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,   \
                    _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,    \
                    _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35,    \
                    _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46,    \
                    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,    \
                    _58, _59, _60, _61, _62, _63, _64, _65, _n, ...)          \
  _n

#define NOPE_COUNT_ARGS(...)                                                  \
  NOPE_EXPAND(NOPE_COUNT_(                                                    \
      -1, ##__VA_ARGS__ , 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52,  \
      51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, \
      33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, \
      15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))

// Concatenate a string and a macro
#define NOPE_CONCAT(A, B) A##B

// Stringify
#define NOPE_QUOTE(A) #A

// Member list
#define NOPE_MEMBER_LIST_X(TYPE, NAME) TYPE NAME;

#define NOPE_MEMBER_LIST_2(TYPE, NAME) NOPE_MEMBER_LIST_X(TYPE, NAME)
#define NOPE_MEMBER_LIST_4(TYPE, NAME, ...)                                   \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_2(__VA_ARGS__))
#define NOPE_MEMBER_LIST_6(TYPE, NAME, ...)                                   \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_4(__VA_ARGS__))
#define NOPE_MEMBER_LIST_8(TYPE, NAME, ...)                                   \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_6(__VA_ARGS__))
#define NOPE_MEMBER_LIST_10(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_8(__VA_ARGS__))
#define NOPE_MEMBER_LIST_12(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_10(__VA_ARGS__))
#define NOPE_MEMBER_LIST_14(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_12(__VA_ARGS__))
#define NOPE_MEMBER_LIST_16(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_14(__VA_ARGS__))
#define NOPE_MEMBER_LIST_18(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_16(__VA_ARGS__))
#define NOPE_MEMBER_LIST_20(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_18(__VA_ARGS__))
#define NOPE_MEMBER_LIST_22(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_20(__VA_ARGS__))
#define NOPE_MEMBER_LIST_24(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_22(__VA_ARGS__))
#define NOPE_MEMBER_LIST_26(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_24(__VA_ARGS__))
#define NOPE_MEMBER_LIST_28(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_26(__VA_ARGS__))
#define NOPE_MEMBER_LIST_30(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_28(__VA_ARGS__))
#define NOPE_MEMBER_LIST_32(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_30(__VA_ARGS__))
#define NOPE_MEMBER_LIST_34(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_32(__VA_ARGS__))
#define NOPE_MEMBER_LIST_36(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_34(__VA_ARGS__))
#define NOPE_MEMBER_LIST_38(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_36(__VA_ARGS__))
#define NOPE_MEMBER_LIST_40(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_38(__VA_ARGS__))
#define NOPE_MEMBER_LIST_42(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_40(__VA_ARGS__))
#define NOPE_MEMBER_LIST_44(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_42(__VA_ARGS__))
#define NOPE_MEMBER_LIST_46(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_44(__VA_ARGS__))
#define NOPE_MEMBER_LIST_48(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_46(__VA_ARGS__))
#define NOPE_MEMBER_LIST_50(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_48(__VA_ARGS__))
#define NOPE_MEMBER_LIST_52(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_50(__VA_ARGS__))
#define NOPE_MEMBER_LIST_54(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_52(__VA_ARGS__))
#define NOPE_MEMBER_LIST_56(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_54(__VA_ARGS__))
#define NOPE_MEMBER_LIST_58(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_56(__VA_ARGS__))
#define NOPE_MEMBER_LIST_60(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_58(__VA_ARGS__))
#define NOPE_MEMBER_LIST_62(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_60(__VA_ARGS__))
#define NOPE_MEMBER_LIST_64(TYPE, NAME, ...)                                  \
  NOPE_MEMBER_LIST_X(TYPE, NAME) NOPE_EXPAND(NOPE_MEMBER_LIST_62(__VA_ARGS__))

#define NOPE_MEMBER_LIST(...)                                                 \
  NOPE_EXPAND(NOPE_MEMBER_LIST_IMPL(NOPE_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__))

#define NOPE_MEMBER_LIST_IMPL(N, ...)                                         \
  NOPE_EXPAND(NOPE_CONCAT(NOPE_MEMBER_LIST_, N)(__VA_ARGS__))

// Metadata member
#define NOPE_METADATA_MEMBER_X(TYPE, NAME)                                    \
  std::pair<std::string, TYPE &>(std::string(NOPE_QUOTE(NAME)), NAME)

#define NOPE_METADATA_MEMBER_2(TYPE, NAME) NOPE_METADATA_MEMBER_X(TYPE, NAME)
#define NOPE_METADATA_MEMBER_4(TYPE, NAME, ...)                               \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_2(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_6(TYPE, NAME, ...)                               \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_4(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_8(TYPE, NAME, ...)                               \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_6(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_10(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_8(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_12(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_10(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_14(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_12(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_16(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_14(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_18(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_16(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_20(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_18(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_22(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_20(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_24(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_22(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_26(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_24(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_28(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_26(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_30(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_28(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_32(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_30(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_34(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_32(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_36(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_34(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_38(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_36(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_40(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_38(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_42(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_40(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_44(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_42(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_46(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_44(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_48(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_46(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_50(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_48(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_52(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_50(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_54(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_52(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_56(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_54(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_58(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_56(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_60(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_58(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_62(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_60(__VA_ARGS__))
#define NOPE_METADATA_MEMBER_64(TYPE, NAME, ...)                              \
  NOPE_METADATA_MEMBER_X(TYPE, NAME),                                         \
      NOPE_EXPAND(NOPE_METADATA_MEMBER_62(__VA_ARGS__))

#define NOPE_METADATA_MEMBER_IMPL(N, ...)                                     \
  NOPE_EXPAND(NOPE_CONCAT(NOPE_METADATA_MEMBER_, N)(__VA_ARGS__))

#define NOPE_METADATA_MEMBER(...)                                             \
  NOPE_EXPAND(                                                                \
      NOPE_METADATA_MEMBER_IMPL(NOPE_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__))

// Metadata types
#define NOPE_METADATA_TYPES_X(TYPE, NAME) std::pair<std::string, TYPE &>

#define NOPE_METADATA_TYPES_2(TYPE, NAME) NOPE_METADATA_TYPES_X(TYPE, NAME)
#define NOPE_METADATA_TYPES_4(TYPE, NAME, ...)                                \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_2(__VA_ARGS__))
#define NOPE_METADATA_TYPES_6(TYPE, NAME, ...)                                \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_4(__VA_ARGS__))
#define NOPE_METADATA_TYPES_8(TYPE, NAME, ...)                                \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_6(__VA_ARGS__))
#define NOPE_METADATA_TYPES_10(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_8(__VA_ARGS__))
#define NOPE_METADATA_TYPES_12(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_10(__VA_ARGS__))
#define NOPE_METADATA_TYPES_14(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_12(__VA_ARGS__))
#define NOPE_METADATA_TYPES_16(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_14(__VA_ARGS__))
#define NOPE_METADATA_TYPES_18(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_16(__VA_ARGS__))
#define NOPE_METADATA_TYPES_20(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_18(__VA_ARGS__))
#define NOPE_METADATA_TYPES_22(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_20(__VA_ARGS__))
#define NOPE_METADATA_TYPES_24(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_22(__VA_ARGS__))
#define NOPE_METADATA_TYPES_26(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_24(__VA_ARGS__))
#define NOPE_METADATA_TYPES_28(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_26(__VA_ARGS__))
#define NOPE_METADATA_TYPES_30(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_28(__VA_ARGS__))
#define NOPE_METADATA_TYPES_32(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_30(__VA_ARGS__))
#define NOPE_METADATA_TYPES_34(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_32(__VA_ARGS__))
#define NOPE_METADATA_TYPES_36(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_34(__VA_ARGS__))
#define NOPE_METADATA_TYPES_38(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_36(__VA_ARGS__))
#define NOPE_METADATA_TYPES_40(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_38(__VA_ARGS__))
#define NOPE_METADATA_TYPES_42(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_40(__VA_ARGS__))
#define NOPE_METADATA_TYPES_44(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_42(__VA_ARGS__))
#define NOPE_METADATA_TYPES_46(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_44(__VA_ARGS__))
#define NOPE_METADATA_TYPES_48(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_46(__VA_ARGS__))
#define NOPE_METADATA_TYPES_50(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_48(__VA_ARGS__))
#define NOPE_METADATA_TYPES_52(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_50(__VA_ARGS__))
#define NOPE_METADATA_TYPES_54(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_52(__VA_ARGS__))
#define NOPE_METADATA_TYPES_56(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_54(__VA_ARGS__))
#define NOPE_METADATA_TYPES_58(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_56(__VA_ARGS__))
#define NOPE_METADATA_TYPES_60(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_58(__VA_ARGS__))
#define NOPE_METADATA_TYPES_62(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_60(__VA_ARGS__))
#define NOPE_METADATA_TYPES_64(TYPE, NAME, ...)                               \
  NOPE_METADATA_TYPES_X(TYPE, NAME),                                          \
      NOPE_EXPAND(NOPE_METADATA_TYPES_62(__VA_ARGS__))

#define NOPE_METADATA_TYPES_IMPL(N, ...)                                      \
  NOPE_EXPAND(NOPE_CONCAT(NOPE_METADATA_TYPES_, N)(__VA_ARGS__))

#define NOPE_METADATA_TYPES(...)                                              \
  NOPE_EXPAND(                                                                \
      NOPE_METADATA_TYPES_IMPL(NOPE_COUNT_ARGS(__VA_ARGS__), __VA_ARGS__))

// Metadata
#define NOPE_METADATA(...)                                                    \
  NOPE_EXPAND(std::tuple<NOPE_METADATA_TYPES(__VA_ARGS__)> m_metadata =       \
                  std::make_tuple(NOPE_METADATA_MEMBER(__VA_ARGS__));)
// Members
#define NOPE_SERIAL_MEMBER(...)                                               \
  NOPE_EXPAND(NOPE_MEMBER_LIST(__VA_ARGS__) NOPE_METADATA(__VA_ARGS__))

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // !METADATA_HPP_
