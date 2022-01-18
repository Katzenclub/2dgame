#pragma once

#include "SFML/Graphics.hpp"

#include "Ball.h"

#define g_PI 3.14

namespace gp
{
	class Paddle
	{
	public:
		Paddle(sf::RenderWindow* prw, bool side, float speed);
		~Paddle();

		void handle(float deltaTime);
		void update(float deltaTime,gp::Ball& ball);
		void render();

	private:
		sf::RenderWindow* m_prw;

		sf::Texture l_texture;
		sf::RectangleShape l_shape;

		bool m_side;
		
		sf::Clock m_special;
		float m_speed;
		float m_speedSaved = 0.f;

	};
}


