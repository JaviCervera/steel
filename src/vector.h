#pragma once

#include <irrlicht.h>

namespace std
{
	template <typename T>
	class vector : public irr::core::array<T>
	{
	public:
		typedef T *iterator;
		typedef const T *const_iterator;

		vector() {}

		vector(size_t n, const T &val = T()) { resize(n, val); }

		vector(const vector<T> &other) : irr::core::array<T>(other) {}

		vector<T> &operator=(const vector<T> &other)
		{
			irr::core::array<T>::operator=(other);
			return *this;
		}

		iterator begin() { return this->pointer(); }

		const_iterator begin() const { return this->const_pointer(); }

		iterator end() { return this->pointer() + this->size(); }

		const_iterator end() const { return this->const_pointer() + this->size(); }

		T *data() { return this->pointer(); }

		const T *data() const { return this->const_pointer(); }

		void pop_back() { erase(this->size() - 1); }

		T &back() { return this->getLast(); }

		const T &back() const { this->getLast(); }

		T &front() { return *this->pointer(); }

		const T &front() const { return *this->const_pointer(); }

		iterator erase(iterator it) { erase(it - begin()); }

		void resize(size_t n, const T &val = T())
		{
			this->set_used(n);
			for (size_t i = 0; i < n; ++i)
				(*this)[i] = val;
		}

	private:
		T *m_buffer;
		size_t m_size;
		size_t m_capacity;
	};
} // namespace std
