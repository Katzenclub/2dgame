#pragma once

#include "../Util/Math.h"

#include "../Util/Loader.h"
#include "ObjectBase.h"

#include "../World/ManagerWorld.h"

namespace gp
{
	namespace object
	{
		class ManagerObject
		{
		public:
			ManagerObject(gp::system::Loader *loader, gp::world::ManagerWorld* MW);
			~ManagerObject();

			gp::object::ObjectBase* create(sf::Vector2f position, float scale, unsigned int assetID, unsigned int oType);
			void update(float deltaTime);
			void killAll();
			void cleanup();
			void cleanupDebug();
			void updatePosition();
			void physics(float deltaTime);
			
			std::vector<gp::object::ObjectBase*> m_listObjects;
			sf::Clock m_clock;
		private:
			gp::world::ManagerWorld* m_pMW;		
			gp::system::Loader* m_p_loader;
		};

	}
}