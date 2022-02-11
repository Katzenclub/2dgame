#include "Chunk.h"

namespace gp
{
	namespace world
	{
		Chunk::Chunk(sf::Vector2i ID) :
			m_ID(ID)
		{
			initialiseChunk(0);
			GenerateNoise(123456);
			generate();
		}

		Chunk::~Chunk()
		{
		}

		void Chunk::generate()
		{
			generateLayer(gp::world::turbulence, 0, 128, 16.f);
		}
		
		void Chunk::initialiseChunk(int value)
		{
			for (int y = 0; y < g_CHUNK_SIZE; y++)
			{
				for (int x = 0; x < g_CHUNK_SIZE; x++)
				{
					m_data[x][y] = value;
				}
			}
		}

		void Chunk::generateLayer(int pattern, int minDepth, int maxDepth, float size)
		{
			for (int y = 0; y < g_CHUNK_SIZE; y++)
			{
				for (int x = 0; x < g_CHUNK_SIZE; x++)
				{
					if (y + m_ID.y * g_CHUNK_SIZE >= minDepth && y + m_ID.y * g_CHUNK_SIZE < maxDepth)
					{
						float l_block = 0;

						if (gp::world::Pattern::turbulence == pattern)
						{
							l_block = gp::turbulence(x, y, size); //Now its normalised between 0.f and 1.f.
						}

						if (l_block <= 0.5f)
						{
							m_data[x][y] = 0;
						}
						else
						{
							m_data[x][y] = l_block*16.f;
						}
					}
					
				}
			}
		}
	}
}