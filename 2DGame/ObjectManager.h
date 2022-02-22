#pragma once

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

			void create(sf::Vector2f position, sf::Vector2f size, unsigned int assetID);
			void update(float deltaTime);
			void cleanup();
			
			std::vector<gp::object::Object*> m_listObjects;

		private:
			gp::system::Loader* m_p_loader;
			
			sf::Clock m_clock;
		};

	}
}