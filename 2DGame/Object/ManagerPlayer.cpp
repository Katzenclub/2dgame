#include "ManagerPlayer.h"

namespace gp
{
	namespace game
	{
		ManagerPlayer::ManagerPlayer(gp::object::ObjectBase* objectPlayer, gp::world::ManagerWorld* MW, gp::projectile::ManagerProjectiles* MP, sf::View *view,sf::RenderWindow *rw) :
			m_p_objectPlayer(objectPlayer),
			m_p_MW(MW),
			m_p_MP(MP),
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
				if (m_interactionMode == gp::game::interactionMode::pickaxe)
				{
					sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
					sf::Vector2i l_blockPos = m_p_MW->convertWorldPosToBlockPos(l_positionWorld);
					if ((m_p_MW->getContainer(l_blockPos) && m_p_MW->getContainer(l_blockPos)->size() == 0) || m_selectedBlock == 0)
					{
						m_p_MW->setBlockIDByBlockPos(m_selectedBlock, m_p_MW->convertWorldPosToBlockPos(l_positionWorld));
					}
				}
				else if(m_interactionMode == gp::game::interactionMode::shoot)
				{
					sf::Vector2f l_positionWorld = m_p_rw->mapPixelToCoords(sf::Mouse::getPosition(*m_p_rw));
					m_p_MP->create(m_p_objectPlayer->m_ID,"Default", m_p_objectPlayer->m_position, gp::util::getDirectionNormalised(m_p_objectPlayer->m_position, l_positionWorld));
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_p_objectPlayer->m_position.x = m_p_objectPlayer->m_position.x - m_speed * deltaTime;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_p_objectPlayer->m_position.x = m_p_objectPlayer->m_position.x + m_speed * deltaTime;
			}

			if (!m_p_objectPlayer->m_debugEnableFly)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					m_p_objectPlayer->setImpulse(gp::util::getDirectionNormalised(m_p_objectPlayer->m_position, sf::Vector2f(m_p_objectPlayer->m_position.x, m_p_objectPlayer->m_position.y - 100.f)), m_jumpHeight);
				}
			}
			else
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					m_p_objectPlayer->m_position.y = m_p_objectPlayer->m_position.y - m_speed * deltaTime;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					m_p_objectPlayer->m_position.y = m_p_objectPlayer->m_position.y + m_speed * deltaTime;
				}
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				m_zoom = m_zoom + m_speedZoom * deltaTime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				
				m_zoom = m_zoom - m_speedZoom * deltaTime;
				if (m_zoom < 0.5f) 
				{
					m_zoom = 0.5f;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				m_zoom = 1.f;
			}
		}

		void ManagerPlayer::update(float deltaTime)
		{
			m_p_view->setCenter(m_p_objectPlayer->m_position + sf::Vector2f(0.375f, 0.375f));
			sf::Vector2i l_zoom = (sf::Vector2i) (sf::Vector2f(m_p_rw->getSize()) * (0.5f * floorf(m_zoom / 0.5f)));
			m_p_view->setSize(floor(l_zoom.x), floor(l_zoom.y));
		}
	}
}
