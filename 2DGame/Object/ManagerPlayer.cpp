#include "ManagerPlayer.h"

namespace gp
{
	namespace game
	{
		ManagerPlayer::ManagerPlayer(gp::object::Object* objectPlayer, gp::world::ManagerWorld* MW, sf::View *view,sf::RenderWindow *rw) :
			m_p_objectPlayer(objectPlayer),
			m_p_MW(MW),
			m_p_view(view),
			m_p_rw(rw)
		{
		}

		ManagerPlayer::~ManagerPlayer()
		{
		}

		void ManagerPlayer::handle(float deltaTime)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			{
				sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
				m_selectedBlock = m_p_MW->getBlockIDByBlockPos(m_p_MW->convertWorldPosToBlockPos(l_positionWorld));
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
				m_p_MW->setBlockIDByBlockPos(m_selectedBlock, m_p_MW->convertWorldPosToBlockPos(l_positionWorld));
			}

			

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_p_objectPlayer->m_position.x = m_p_objectPlayer->m_position.x - m_speed * m_zoom * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_p_objectPlayer->m_position.x = m_p_objectPlayer->m_position.x + m_speed * m_zoom * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_p_objectPlayer->m_position.y = m_p_objectPlayer->m_position.y - m_speed * m_zoom * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_p_objectPlayer->m_position.y = m_p_objectPlayer->m_position.y + m_speed * m_zoom * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				m_zoom = m_zoom + m_speedZoom * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				
				m_zoom = m_zoom - m_speedZoom * deltaTime;
				if (m_zoom < 0.1f) 
				{
					m_zoom = 0.1f;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				m_zoom = 1.f;
			}

			m_p_view->setCenter(m_p_objectPlayer->m_position + (m_p_objectPlayer->m_size / 2.f));
			m_p_view->setSize(sf::Vector2f(m_p_rw->getSize()) * m_zoom);
		}

		void ManagerPlayer::update(float deltaTime)
		{

		}
	}
}
