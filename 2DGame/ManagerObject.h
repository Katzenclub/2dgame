#pragma once

#include "Math.h"

#include "Loader.h"
#include "Object.h"

namespace gp
{
	namespace object
	{
		class ManagerObject
		{
		public:
			ManagerObject(gp::system::Loader *loader);
			~ManagerObject();

			gp::object::Object* create(sf::Vector2f position, sf::Vector2f size, unsigned int assetID, unsigned int oType);
			void update(float deltaTime);
			void killAll();
			void cleanup();
			
			std::vector<gp::object::Object*> m_listObjects;
			sf::Clock m_clock;
		private:
			gp::system::Loader* m_p_loader;

		};

	}
}