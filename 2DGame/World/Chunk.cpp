#include "Chunk.h"

namespace gp
{
	namespace world
	{
		Chunk::Chunk(sf::Vector2i ID) : m_ID(ID)
		{
			initialiseChunk(0);
		}

		Chunk::~Chunk()
		{
		}

		void Chunk::generate()
		{
			initialiseChunk(0);
			GenerateNoise(seed);
			//generateLayer(gp::world::turbulence, 0, 64, 16.f, 0.5f, 1);
			generateLayer(gp::world::turbulence, 192, 512, 32, 0.375f, 2, 256, 256 + 64);
			generateLayer(gp::world::turbulence, 256, 512, 32, 0.5f, 1, 128);
			//generateLayer(gp::world::turbulence, 256 - 32, 1280, 64.f, 0.8f, 1);

			//generateLayer(gp::world::turbulence, 0, 128 + 64, 64.f, 0.75f, 1);
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

		void Chunk::generateLayer(int pattern, int minDepth, int maxDepth, float size, float sensitivity, int blockID, int fadeSize, int maxFadeDepth)
		{
			int l_maxFadeDepth = (maxFadeDepth == 0)? maxDepth : maxFadeDepth;
			for (int x = 0; x < g_CHUNK_SIZE; x++)
			{
				float l_hill = (gp::turbulence1D(m_ID.x * g_CHUNK_SIZE + x, 0, fadeSize, 1) * (l_maxFadeDepth - minDepth)) + minDepth;
				std:: cout << l_hill << std::endl;
				for (int y = 0; y < g_CHUNK_SIZE; y++)
				{
					if (y + m_ID.y * g_CHUNK_SIZE >= l_hill && y + m_ID.y * g_CHUNK_SIZE < maxDepth)
					{
						float l_block = 0;

						if (gp::world::Pattern::turbulence == pattern)
						{
							l_block = gp::turbulence(m_ID.x * g_CHUNK_SIZE + x, m_ID.y * g_CHUNK_SIZE + y, size); // Now its normalised between 0.f and 1.f.
						}

						
						if (l_block > sensitivity)
						{
							
   							//float noise1D = db::perlin(1.f/(float)(m_ID.x * g_CHUNK_SIZE + x)) * 1000.f;
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