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
			generateLayer(gp::world::turbulence, 192, 512, 32, 0.375f, 2, 256, 256); /* Generate Dirt */
			generateLayer(gp::world::turbulence, 256, 512, 32, 0.5f, 1, 128); /* Generate Stone */
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

		/**
		 * @brief Generate World Layer for the blockID
		 * 
		 * @param pattern Pattern for the noise generation
		 * @param minDepth Min y coordinate of the layer
		 * @param maxDepth Max y coordinate of the layer
		 * @param size Smoothness of the generated Noise
		 * @param sensitivity Sensetivity threshold to determine if place blockID
		 * @param blockID BlockID the layer should be made out of
		 * @param fadeSize Smoothness of the Noise for the fading of the top and bottom edges
		 * @param maxFadeDepth Max height of the fading noise
		 */
		void Chunk::generateLayer(int pattern, int minDepth, int maxDepth, float size, float sensitivity, int blockID, int fadeSize, int maxFadeDepth)
		{
			maxFadeDepth = (maxFadeDepth == 0) ? maxDepth : maxFadeDepth;
			for (int x = 0; x < g_CHUNK_SIZE; x++)
			{
				float l_hill = (gp::turbulence1D(m_ID.x * g_CHUNK_SIZE + x, 0, fadeSize, 1) * (maxFadeDepth - minDepth)) + minDepth;
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