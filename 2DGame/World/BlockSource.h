#pragma once

// STL
#include <map>

// Own
#include "../Util/Source.h"

namespace gp
{
	namespace world
	{
		class BlockSource : public gp::system::Source
		{
		public:
			BlockSource(std::string name, std::string path, std::map<std::string, int> flags);
			~BlockSource();
			
			std::map<std::string, int> m_flags;

			unsigned int m_IDBlock;

		private:
		};

		static unsigned int g_blockID = 0;
	}
}