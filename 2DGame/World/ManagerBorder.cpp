#include "ManagerBorder.h"

namespace gp
{
	namespace world
	{
		ManagerBorder::ManagerBorder()
		{
			for (int blockID = 0; blockID < g_ATLAS_BLOCK_SIZE * g_ATLAS_BLOCK_SIZE; blockID++)
			{
				for (int borderType = 0; borderType < 8; borderType++)
				{
					m_listBorders[blockID][borderType] = NULL;
				}
			}
		}

		ManagerBorder::~ManagerBorder()
		{
		}

		void ManagerBorder::addBorder(Border *border, BorderType borderType, int blockID)
		{
			int borderTypeInt = (int)borderType;
			m_listBorders[blockID][borderTypeInt] = border;
		}
	}
}