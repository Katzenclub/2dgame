#pragma once

#include <random>

#include "WorldConstants.h"

namespace gp
{
	static double noise[g_CHUNK_SIZE][g_CHUNK_SIZE];

	static double smoothNoise(double x, double y)
	{
		//get fractional part of x and y
		double fractX = x - int(x);
		double fractY = y - int(y);

		//wrap around
		int x1 = (int(x) + (g_CHUNK_SIZE)) % (g_CHUNK_SIZE);
		int y1 = (int(y) + (g_CHUNK_SIZE)) % (g_CHUNK_SIZE);

		//neighbor values
		int x2 = (x1 + (g_CHUNK_SIZE)-1) % (g_CHUNK_SIZE);
		int y2 = (y1 + (g_CHUNK_SIZE)-1) % (g_CHUNK_SIZE);

		//smooth the noise with bilinear interpolation
		double value = 0.0;
		value += fractX * fractY * noise[x1][y1];
		value += fractX * (1 - fractY) * noise[x1][y2];
		value += (1 - fractX) * fractY * noise[x2][y1];
		value += (1 - fractX) * (1 - fractY) * noise[x2][y2];

		return value;
	}

	static double turbulence(double x, double y, double size)
	{
		double value = 0.0, initialSize = size;

		while (size >= 1)
		{
			value += smoothNoise(x / size, y / size) * size;
			size /= 2.0;
		}

		return(0.5 * (value / initialSize));
	}

	static void GenerateNoise(int Seed)
	{
		srand(Seed);
		for (int x = 0; x < (g_CHUNK_SIZE); x++)
			for (int y = 0; y < (g_CHUNK_SIZE); y++)
			{
				noise[x][y] = (rand() % 32768) / 32768.0;
			}
	}
}