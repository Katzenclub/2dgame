#include "Paddle.h"

gp::Paddle::Paddle(sf::RenderWindow* prw, bool side, float speed) :
	m_prw(prw),
	m_side(side),
	m_speed(speed)
{
	//inital texture and shape
	l_texture.loadFromFile("assets\\paddle.png");
	l_shape.setTexture(&l_texture);
	l_shape.setSize(sf::Vector2f(l_texture.getSize()));
	l_shape.setOrigin(sf::Vector2f(l_texture.getSize()) / 2.f);
	l_shape.setOutlineThickness(6.f);
	l_shape.setOutlineColor(sf::Color::Red);

	if (m_side)
	{
		//when side "true" paddle is placed left
		l_shape.setPosition(sf::Vector2f(200.f, m_prw->getSize().y / 2.f));
	}
	else
	{
		//when side "true" paddle is placed right
		l_shape.setPosition(sf::Vector2f(m_prw->getSize().x - 200.f, m_prw->getSize().y / 2.f));
	}
}

gp::Paddle::~Paddle()
{
}

//handle input
void gp::Paddle::handle(float deltaTime)
{
	//Player Controll
	if (m_side)
	{
		//Move down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && l_shape.getPosition().y < m_prw->getSize().y - l_shape.getSize().y / 2.f)
		{
			l_shape.setPosition(l_shape.getPosition().x, l_shape.getPosition().y + m_speed * deltaTime);
		}

		//Move up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && l_shape.getPosition().y >= 0.f + l_shape.getSize().y / 2.f)
		{
			l_shape.setPosition(l_shape.getPosition().x, l_shape.getPosition().y - m_speed * deltaTime);
		}
	}
}

//update stuff
void gp::Paddle::update(float deltaTime, gp::Ball& ball)
{
	//check collision between paddle and ball
	if (l_shape.getGlobalBounds().intersects(ball.m_shape.getGlobalBounds()))
	{

		//vary bouncing angle (otherwise it would be reflected only horizontal)
		ball.m_direction.y = -((l_shape.getPosition().y - ball.m_shape.getPosition().y) / ((l_shape.getSize().y / 2.f + ball.m_shape.getRadius())) * g_PI);
		ball.m_direction.x = -ball.m_direction.x;

		//fix x position when ball is inside the paddle
		if (m_side)
		{
			//left side
			ball.m_shape.setPosition(l_shape.getPosition().x + l_shape.getOrigin().x + l_shape.getOutlineThickness() + ball.m_shape.getOrigin().x, ball.m_shape.getPosition().y);
		}
		else
		{
			//rigt side
			ball.m_shape.setPosition(l_shape.getPosition().x - l_shape.getOrigin().x - l_shape.getOutlineThickness() - ball.m_shape.getOrigin().x, ball.m_shape.getPosition().y);
		}
	}

	//AI controll
	if (!m_side)
	{
		//Special abillity
		if (m_special.getElapsedTime().asSeconds() > 5.f && m_speedSaved == 0.f)
		{
			m_speedSaved = m_speed;	
			m_speed = m_speed * 5.f;
		}
		else if(m_special.getElapsedTime().asSeconds() > 8.f)
		{		
			m_speed = m_speedSaved;
			m_speedSaved = 0.f;
			m_special.restart();
		}

		//Paddle follows ball
		if (ball.m_shape.getPosition().y > l_shape.getPosition().y)
		{
			//padle goes down

			//is position difference higher than one move in a frame
			if (ball.m_shape.getPosition().y > l_shape.getPosition().y + m_speed * deltaTime)
			{
				l_shape.setPosition(l_shape.getPosition().x, l_shape.getPosition().y + m_speed * deltaTime);
			}
			else
			{
				l_shape.setPosition(l_shape.getPosition().x, ball.m_shape.getPosition().y);
			}
		}
		else
		{
			//padle goes up

			//is position difference higher than one move in a frame
			if (ball.m_shape.getPosition().y <= l_shape.getPosition().y - m_speed * deltaTime)
			{
				l_shape.setPosition(l_shape.getPosition().x, l_shape.getPosition().y - m_speed * deltaTime);
			}
			else
			{
				l_shape.setPosition(l_shape.getPosition().x, ball.m_shape.getPosition().y);
			}
		}

		//when paddle position is to low or to high the position will set at the last avaiable position
		if (l_shape.getPosition().y < l_shape.getSize().y / 2.f)
		{
			l_shape.setPosition(l_shape.getPosition().x, l_shape.getSize().y / 2.f);
		}
		else if (l_shape.getPosition().y > m_prw->getSize().y - l_shape.getSize().y / 2.f)
		{
			l_shape.setPosition(l_shape.getPosition().x, m_prw->getSize().y - l_shape.getSize().y / 2.f);
		}
	}
}

//render stuff
void gp::Paddle::render()
{
	m_prw->draw(l_shape);
}
