#pragma once

#include "../Util/Math.h"

#include "../Util/Loader.h"
#include "Object.h"

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

			gp::object::Object* create(sf::Vector2f position, sf::Vector2f size, unsigned int assetID, unsigned int oType);
			void update(float deltaTime);
			void killAll();
			void cleanup();

			
			
			std::vector<gp::object::Object*> m_listObjects;
			sf::Clock m_clock;
		private:
			gp::world::ManagerWorld* m_pMW;		
			gp::system::Loader* m_p_loader;
			
			//Technical Stuff
			void updateObjectBlockPositions();

		};

	}
}