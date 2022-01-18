#include "Ball.h"

gp::Ball::Ball(sf::RenderWindow* prw, float speed) :
	m_prw(prw),
	m_speed(speed)
{
	//setup initial size, center origin and place in the middle of the screen.
	m_shape.setRadius(50.f);
	m_shape.setOrigin(sf::Vector2f(m_shape.getRadius(), m_shape.getRadius()));
	m_shape.setPosition(sf::Vector2f(m_prw->getSize()) / 2.f);

	//set initial flying direction left.
	m_direction = sf::Vector2f(-1.f, 0.f);
}

gp::Ball::~Ball()
{
}

//handle input
void gp::Ball::handle(float deltaTime)
{
	
}

//update stuff
void gp::Ball::update(float deltaTime)
{
	m_shape.setPosition(m_shape.getPosition() + m_direction * m_speed * deltaTime);

	if (m_shape.getPosition().y <= 0.f || m_shape.getPosition().y > m_prw->getSize().y)
	{
		m_direction.y = -m_direction.y;
	}

	if (m_shape.getPosition().x <= 0.f || m_shape.getPosition().x > m_prw->getSize().x)
	{
		m_shape.setPosition(sf::Vector2f(m_prw->getSize()) / 2.f);
		m_direction = sf::Vector2f(-1.f, 0.f);
	}
}

//render stuff
void gp::Ball::render()
{
	m_prw->draw(m_shape);
}