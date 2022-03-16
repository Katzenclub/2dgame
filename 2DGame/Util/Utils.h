#pragma once

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
	}
}