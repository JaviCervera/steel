#pragma once

#include <irrlicht.h>

namespace std
{
	struct string : public irr::core::string<irr::c8>
	{
		string(const char *s = "") : irr::core::string<irr::c8>(s) {}

		string(const string &other) : irr::core::string<irr::c8>(other) {}

		string(const irr::core::stringc &other) : irr::core::string<irr::c8>(other) {}

		size_t length() const { return size(); }

		void resize(size_t n, char c = 0)
		{
			*this = "";
			reserve(n + 1);
			for (size_t i = 0; i < n; ++i)
				append(c);
		}

		string substr(size_t pos, size_t len = -1) const
		{
			return subString(pos, (len != -1) ? len : (size() - pos));
		}
	};

} // namespace std
