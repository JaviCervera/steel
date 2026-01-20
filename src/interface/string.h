#pragma once

#include <irrlicht.h>

namespace std
{
  struct string : public irr::core::stringc
  {
    static const size_t npos = -1;

    string(const char *s = "") : irr::core::stringc(s) {}

    string(const string &other) : irr::core::stringc(other) {}

    string(const irr::core::stringc &other) : irr::core::stringc(other) {}

    size_t length() const { return size(); }

    void resize(size_t n, char c = 0)
    {
      *this = "";
      reserve(n + 1);
      for (size_t i = 0; i < n; ++i)
        append(c);
    }

    string substr(size_t pos, size_t len = npos) const
    {
      return subString(pos, (len != npos) ? len : (size() - pos));
    }
  };

} // namespace std
