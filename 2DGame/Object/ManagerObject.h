#pragma once

#include "../Util/Math.h"

#include "../Util/Loader.h"
#include "Object.h"

#include "../World/ManagerWorld.h"

#define g_GRAVITY 9.81
#define g_RELATIVE_GRAVITY g_GRAVITY / g_CHUNK_TEXTURE_SIZE

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
			void cleanupDebug();
			void updatePosition();
			void physics(float deltaTime);
			
			std::vector<gp::object::Object*> m_listObjects;
			sf::Clock m_clock;
		private:
			gp::world::ManagerWorld* m_pMW;		
			gp::system::Loader* m_p_loader;
		};

	}
}