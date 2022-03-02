#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

namespace gp
{
	namespace util
	{
		static sf::Vector2f getDirection(sf::Vector2f pos, sf::Vector2f tar)
		{
			return tar - pos;
		}

		static inline sf::Vector2f getDirectionNormalised(sf::Vector2f pos, sf::Vector2f tar)
		{
			const sf::Vector2f l_target = getDirection(pos, tar);
			return l_target / sqrtf(l_target.x * l_target.x + l_target.y * l_target.y);
		}

		static inline float getRadAngle(float degAngle)
		{
			return (degAngle - 90.f) * 0.01745f;
		}

		static inline sf::Vector2f getDirectionNormalised(float degAngle)
		{
			const float radAngle = getRadAngle(degAngle);
			return sf::Vector2f(cosf(radAngle), sinf(radAngle));
		}

		//Calculates the distance between [pos] and [tar].
		static inline float getDistance(const sf::Vector2f pos, const sf::Vector2f tar)
		{
			return sqrtf((tar.x - pos.x) * (tar.x - pos.x) + (tar.y - pos.y) * (tar.y - pos.y));
		}
	}
}