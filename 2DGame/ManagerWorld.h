#pragma once

#include "Chunk.h"

namespace gp
{
	namespace world
	{
		class ManagerWorld
		{
		public:
			ManagerWorld();
			~ManagerWorld();

			void update();
			gp::world::Chunk* m_p_chunk;
		private:
			
		};
	}
}