#include "Paddle.h"

gp::Paddle::Paddle(sf::RenderWindow* prw, bool side, float speed) :
	m_prw(prw),
	m_side(side),
	m_speed(speed)
{
	//inital texture and shape
	m_texture.loadFromFile("assets/paddle.png");
	m_shape.setTexture(&m_texture);
	m_shape.setSize(sf::Vector2f(m_texture.getSize()));
	m_shape.setOrigin(sf::Vector2f(m_texture.getSize()) / 2.f);
	m_shape.setOutlineThickness(6.f);
	m_shape.setOutlineColor(sf::Color::Red);

	if (m_side)
	{
		//when side "true" paddle is placed left
		m_shape.setPosition(sf::Vector2f(200.f, m_prw->getSize().y / 2.f));
	}
	else
	{
		//when side "true" paddle is placed right
		m_shape.setPosition(sf::Vector2f(m_prw->getSize().x - 200.f, m_prw->getSize().y / 2.f));
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && m_shape.getPosition().y < m_prw->getSize().y - m_shape.getSize().y / 2.f)
		{
			m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_speed * deltaTime);
		}

		//Move up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && m_shape.getPosition().y >= 0.f + m_shape.getSize().y / 2.f)
		{
			m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y - m_speed * deltaTime);
		}
	}
}

//update stuff
void gp::Paddle::update(float deltaTime, gp::Ball& ball)
{
	//check collision between paddle and ball
	if (m_shape.getGlobalBounds().intersects(ball.m_shape.getGlobalBounds()))
	{

		//vary bouncing angle (otherwise it would be reflected only horizontal)
		ball.m_direction.y = -((m_shape.getPosition().y - ball.m_shape.getPosition().y) / ((m_shape.getSize().y / 2.f + ball.m_shape.getRadius())) * g_PI);
		ball.m_direction.x = -ball.m_direction.x;

		//fix x position when ball is inside the paddle
		if (m_side)
		{
			//left side
			ball.m_shape.setPosition(m_shape.getPosition().x + m_shape.getOrigin().x + m_shape.getOutlineThickness() + ball.m_shape.getOrigin().x, ball.m_shape.getPosition().y);
		}
		else
		{
			//rigt side
			ball.m_shape.setPosition(m_shape.getPosition().x - m_shape.getOrigin().x - m_shape.getOutlineThickness() - ball.m_shape.getOrigin().x, ball.m_shape.getPosition().y);
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
		if (ball.m_shape.getPosition().y > m_shape.getPosition().y)
		{
			//padle goes down

			//is position difference higher than one move in a frame
			if (ball.m_shape.getPosition().y > m_shape.getPosition().y + m_speed * deltaTime)
			{
				m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y + m_speed * deltaTime);
			}
			else
			{
				m_shape.setPosition(m_shape.getPosition().x, ball.m_shape.getPosition().y);
			}
		}
		else
		{
			//padle goes up

			//is position difference higher than one move in a frame
			if (ball.m_shape.getPosition().y <= m_shape.getPosition().y - m_speed * deltaTime)
			{
				m_shape.setPosition(m_shape.getPosition().x, m_shape.getPosition().y - m_speed * deltaTime);
			}
			else
			{
				m_shape.setPosition(m_shape.getPosition().x, ball.m_shape.getPosition().y);
			}
		}

		//when paddle position is to low or to high the position will set at the last avaiable position
		if (m_shape.getPosition().y < m_shape.getSize().y / 2.f)
		{
			m_shape.setPosition(m_shape.getPosition().x, m_shape.getSize().y / 2.f);
		}
		else if (m_shape.getPosition().y > m_prw->getSize().y - m_shape.getSize().y / 2.f)
		{
			m_shape.setPosition(m_shape.getPosition().x, m_prw->getSize().y - m_shape.getSize().y / 2.f);
		}
	}
}

//render stuff
void gp::Paddle::render()
{
	m_prw->draw(m_shape);
}
