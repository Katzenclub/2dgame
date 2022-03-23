#include "Loader.h"

namespace gp
{
	namespace system
	{
		Loader::Loader()
		{
			m_listBlocks.push_back(new gp::world::Block("Air", "data/assets/blocks/Air.png", { }));
			m_listBlocks.push_back(new gp::world::Block("Stone", "data/assets/blocks/Stone.png", { {"InflictBurning", 5}, {"InflictDrowning", 10} }));
			m_listBlocks.push_back(new gp::world::Block("Dirt", "data/assets/blocks/Dirt.png", { {"InflictBurning", 2}, {"InflictDrowning", 10} }));

			m_textureAtlas = createTextureAtlas(m_listBlocks);
			m_textureAtlas.setSmooth(true);

			m_listObjectAssets.push_back(new gp::object::ObjectAsset("Player", "data/assets/objects/Player.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectAsset("Slime", "data/assets/objects/Slime.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectAsset("SlimeMutant", "data/assets/objects/SlimeMutant.png"));

			m_listProjectiles.push_back(new gp::system::ProjectileSource("Default","data/assets/projectiles/default.png"));
			m_projectileAtlas = createTextureAtlas(m_listProjectiles);
			m_projectileAtlas.setSmooth(true);

			clock_t start_time = clock();
			m_objectsAtlas = createTextureAtlas(m_listObjectAssets);
			m_objectsAtlas.setSmooth(true);
			clock_t end_time = clock();
			clock_t result = end_time - start_time;
			printf("Create Object Atlas took %ld clicks (%f seconds).\n", result, ((float)result) / CLOCKS_PER_SEC);
		}

		Loader::~Loader()
		{
		}

		gp::system::ProjectileSource* Loader::getProjectileByName(const std::string& name)
		{
			size_t l_ID = gp::util::hash(name.c_str());
			for (auto it : m_listProjectiles)
			{
				if (it->m_ID == l_ID)
				{
					return it;
				}
			}

			// To avoid Nullpointer
			return m_listProjectiles[0];
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::world::Block*>& list)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color::Magenta); // to see available texture space on the fly.
			sf::RenderStates l_renderstates;
			l_renderstates.blendMode = sf::BlendNone; 
			for (auto it : list)
			{
				sf::RectangleShape l_shape;
				l_shape.setTexture(&it->m_texture);
				l_shape.setSize(sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE));
				l_shape.setPosition(sf::Vector2f(
					(it->m_ID % g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE,
					(it->m_ID / g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE) );

				l_RT.draw(l_shape, l_renderstates);
			}
			
			l_RT.display();
			return l_RT.getTexture();
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::object::ObjectAsset*>& list)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color::Magenta); // to see available texture space on the fly.
			sf::RenderStates l_renderstates;
			l_renderstates.blendMode = sf::BlendNone;

			std::vector<RectInfo> l_rects;
			for (auto objectAsset : list)
			{
				auto l_textureSize = objectAsset->m_texture.getSize();
				auto l_rectInfo = RectInfo();
				l_rectInfo.width = l_textureSize.x;
				l_rectInfo.height = l_textureSize.y;
				l_rectInfo.objectAsset = objectAsset;
				l_rects.push_back(l_rectInfo);
			}

			auto l_gouillotineBinPack = GuillotineBinPack(l_RT.getSize().x, l_RT.getSize().y);
			auto l_resultRects = l_gouillotineBinPack.Insert(l_rects, false);
			
			for (auto resultRect : l_resultRects) {
				auto objectAsset = resultRect.objectAsset;

				sf::RectangleShape l_shape;
				l_shape.setTexture(&resultRect.objectAsset->m_texture);

				objectAsset->m_SizeTexture = sf::Vector2f(resultRect.width, resultRect.height);
				l_shape.setSize(objectAsset->m_SizeTexture);

				objectAsset->m_PositionTexture = sf::Vector2f(resultRect.x, resultRect.y);
				l_shape.setPosition(objectAsset->m_PositionTexture);
				
				l_RT.draw(l_shape, l_renderstates);
			}

			l_RT.display();
			
			return l_RT.getTexture();
		}	

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::system::ProjectileSource*>& list)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color::Magenta); // to see available texture space on the fly.
			sf::RenderStates l_renderstates;
			l_renderstates.blendMode = sf::BlendNone;

			std::vector<RectInfo> l_rects;
			for (auto source : list)
			{
				auto l_textureSize = source->m_texture.getSize();
				auto l_rectInfo = RectInfo();
				l_rectInfo.width = l_textureSize.x;
				l_rectInfo.height = l_textureSize.y;
				l_rectInfo.objectAsset = NULL;//Ignore
				l_rects.push_back(l_rectInfo);
			}

			auto l_gouillotineBinPack = GuillotineBinPack(l_RT.getSize().x, l_RT.getSize().y);
			auto l_resultRects = l_gouillotineBinPack.Insert(l_rects, false);

			for (int i = 0; i < list.size(); i++)
			{
				auto l_source = list[i];
				sf::RectangleShape l_shape;
				l_shape.setTexture(&l_source->m_texture);

				auto l_rect = l_rects[i];
				l_source->m_SizeTexture = sf::Vector2f(l_rect.width, l_rect.height);
				l_shape.setSize(l_source->m_SizeTexture);

				l_source->m_PositionTexture = sf::Vector2f(l_rect.x, l_rect.y);
				l_shape.setPosition(l_source->m_PositionTexture);

				l_RT.draw(l_shape, l_renderstates);
			}

			l_RT.display();

			return l_RT.getTexture();
		}
	}
}