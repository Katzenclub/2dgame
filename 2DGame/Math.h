#pragma once

#include <SFML/Graphics.hpp>

namespace gp
{
	namespace utility
	{
		static sf::Vector2f getDirection(sf::Vector2f pos, sf::Vector2f tar)
		{
			return tar - pos;
		}

		static inline sf::Vector2f getDirectionNormalised(sf::Vector2f pos, sf::Vector2f tar)
		{
			const sf::Vector2f l_target = getDirection(pos, tar);
			return l_target / std::sqrtf(std::pow(l_target.x, 2) + std::pow(l_target.y, 2));
		}

		static inline float getRadAngle(float degAngle)
		{
			return (degAngle - 90.f) * 0.01745f;
		}

		static inline sf::Vector2f getDirectionNormalised(float degAngle)
		{
			const float radAngle = getRadAngle(degAngle);
			return sf::Vector2f(std::cosf(radAngle), std::sinf(radAngle));
		}
	}
}