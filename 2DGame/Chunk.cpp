#include "Chunk.h"

namespace gp
{
	namespace world
	{
		Chunk::Chunk(sf::Vector2i ID, bool generateNew) : m_ID(ID)
		{
			initialiseChunk(0);

			if (generateNew)
			{
				generate();
			}
		}

		Chunk::~Chunk()
		{
		}

		void Chunk::generate()
		{
			initialiseChunk(0);
			GenerateNoise(seed);
			generateLayer(gp::world::turbulence, 256 - 32, 1280, 16.f, 0.5f, 1);
			generateLayer(gp::world::turbulence, 256 - 32, 1280, 32.f, 0.5f, 2);
			generateLayer(gp::world::turbulence, 256 - 32, 1280, 64.f, 0.8f, 1);

			generateLayer(gp::world::turbulence, 0, 128 + 64, 64.f, 0.75f, 1);
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

		void Chunk::generateLayer(int pattern, int minDepth, int maxDepth, float size, float sensitivity, int blockID)
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
							l_block = gp::turbulence(m_ID.x * g_CHUNK_SIZE + x, m_ID.y * g_CHUNK_SIZE + y, size); // Now its normalised between 0.f and 1.f.
						}

						if (l_block > sensitivity)
						{
							m_data[x][y] = blockID;
						}
					}
				}
			}
		}

		void Chunk::load(std::ifstream &ifs)
		{
			std::streamsize size = sizeof(m_data);
			ifs.read((char *)&m_data[0][0], size);
		}

		void Chunk::save(std::ofstream &ofs)
		{
			std::streamsize size = sizeof(m_data);
			ofs.write((char *)&m_data[0][0], size);
		}
	}
}