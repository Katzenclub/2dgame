#include "ManagerBorder.h"

namespace gp
{
	namespace world
	{
		ManagerBorder::ManagerBorder()
		{
		}

		ManagerBorder::~ManagerBorder()
		{
		}

		void ManagerBorder::init(int maxBlockID)
		{
			for (int blockID = 0; blockID < maxBlockID; blockID++)
			{
				for (int borderType = 0; borderType < 8; borderType++)
				{
					m_listBorders[blockID][borderType] = NULL;
				}
			}
		}

		void ManagerBorder::addBorder(Border *border, BorderType borderType, int blockID)
		{
			int borderTypeInt = (int)borderType;
			m_listBorders[blockID][borderTypeInt] = border;
		}
	}
}