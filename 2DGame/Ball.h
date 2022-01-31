#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace gp
{
	class Ball
	{
	public:
		Ball(sf::RenderWindow* prw, float speed);
		~Ball();

		void handle(float deltaTime);
		void update(float deltaTime);
		void render();
		void reset();

		sf::CircleShape m_shape;

		sf::Vector2f m_direction;

	private:
		sf::RenderWindow* m_prw;

		float m_speed;
	};
}

