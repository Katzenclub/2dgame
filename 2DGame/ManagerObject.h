#pragma once

#include "Math.h"

#include "Loader.h"
#include "Object.h"

#include "ManagerWorld.h"

namespace gp
{
	namespace object
	{
		class ManagerObject
		{
		public:
			ManagerObject(gp::system::Loader *loader, gp::world::ManagerWorld* MW);
			~ManagerObject();

			gp::object::Object* create(sf::Vector2f position, float scale, unsigned int assetID, unsigned int oType);
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