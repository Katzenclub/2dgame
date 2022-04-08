#pragma once

#include "WorldConstants.h"
#include "Border.h"

namespace gp
{
	namespace world
	{
		enum class BorderType {
			TopLeft,
			Left,
			BottomLeft,
			Top,
			Bottom,
			TopRight,
			Right,
			BottomRight
		};

		class ManagerBorder
		{
		public:
			ManagerBorder();
			~ManagerBorder();
			
			void addBorder(Border* border, BorderType borderType, int blockID);
			Border* m_listBorders[g_ATLAS_BLOCK_SIZE * g_ATLAS_BLOCK_SIZE][8];
		private:
		};
	}
}