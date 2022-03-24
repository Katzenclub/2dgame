#pragma once

#include <vector>
#include "SFML/Graphics.hpp"

namespace gp
{
	namespace util
	{
		//It is for dynamic creation of any 2D pointer Array, it will be used later.
		template <class T>
		T** createArray(int sizeX, int sizeY) {
			T** l_array = new T * [sizeX];
			for (int x = 0; x < sizeX; x++)
			{
				l_array[x] = new T[sizeY];
			}
			return l_array;
		}
		
		// Its better than standart, because this don't need to create a object to hash a string.
		constexpr unsigned int hash(const char* s, int off = 0) {
			return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
		}
	}
}