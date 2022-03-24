#include "Loader.h"

namespace gp
{
	namespace system
	{
		Loader::Loader()
		{
			m_listBlocks.push_back(new gp::world::Block("Air", "data/assets/blocks/Air.png", {}));
			m_listBlocks.push_back(new gp::world::Block("Stone", "data/assets/blocks/Stone.png", {{"InflictBurning", 5}, {"InflictDrowning", 10}}));
			m_listBlocks.push_back(new gp::world::Block("Dirt", "data/assets/blocks/Dirt.png", {{"InflictBurning", 2}, {"InflictDrowning", 10}}));

			m_textureAtlas = createTextureAtlas(m_listBlocks);
			m_textureAtlas.setSmooth(true);

			m_listProjectiles.push_back(new gp::system::ProjectileSource("Default", "data/assets/projectiles/default.png"));
			m_listProjectiles.push_back(new gp::system::ProjectileSource("Default", "data/assets/projectiles/default.png"));
			m_listProjectiles.push_back(new gp::system::ProjectileSource("Default", "data/assets/projectiles/default.png"));

			m_projectileAtlas = createTextureAtlas(m_listProjectiles);
			m_projectileAtlas.setSmooth(true);

			m_listObjectAssets.push_back(new gp::object::ObjectAsset("Player", "data/assets/objects/Player.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectAsset("Slime", "data/assets/objects/Slime.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectAsset("SlimeMutant", "data/assets/objects/SlimeMutant.png"));

			m_objectsAtlas = createTextureAtlas(m_listObjectAssets);
			m_objectsAtlas.setSmooth(true);
		}

		Loader::~Loader()
		{
		}

		gp::system::ProjectileSource *Loader::getProjectileByName(const std::string &name)
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

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::world::Block *> &list)
		{
			std::vector<RectInfo> l_rects;
			for (auto source : list)
			{
				auto l_rectInfo = RectInfo();
				l_rectInfo.width = g_CHUNK_TEXTURE_SIZE;
				l_rectInfo.height = g_CHUNK_TEXTURE_SIZE;

				l_rectInfo.textureSizePointer = &source->m_SizeTexture;
				l_rectInfo.texturePositionPointer = &source->m_PositionTexture;
				l_rectInfo.texture = &source->m_texture;

				l_rects.push_back(l_rectInfo);
			}
			return createTextureAtlas(l_rects);
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::object::ObjectAsset *> &list)
		{
			std::vector<RectInfo> l_rects;
			for (auto source : list)
			{
				auto l_textureSize = source->m_texture.getSize();
				auto l_rectInfo = RectInfo();
				l_rectInfo.width = l_textureSize.x;
				l_rectInfo.height = l_textureSize.y;

				l_rectInfo.textureSizePointer = &source->m_SizeTexture;
				l_rectInfo.texturePositionPointer = &source->m_PositionTexture;
				l_rectInfo.texture = &source->m_texture;

				l_rects.push_back(l_rectInfo);
			}
			return createTextureAtlas(l_rects);
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::system::ProjectileSource *> &list)
		{
			std::vector<RectInfo> l_rects;
			for (auto source : list)
			{
				auto l_textureSize = source->m_texture.getSize();
				auto l_rectInfo = RectInfo();
				l_rectInfo.width = l_textureSize.x;
				l_rectInfo.height = l_textureSize.y;

				l_rectInfo.textureSizePointer = &source->m_SizeTexture;
				l_rectInfo.texturePositionPointer = &source->m_PositionTexture;
				l_rectInfo.texture = &source->m_texture;

				l_rects.push_back(l_rectInfo);
			}
			return createTextureAtlas(l_rects);
		}

		sf::Texture Loader::createTextureAtlas(std::vector<RectInfo> &list) {
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color::Magenta); // to see available texture space on the fly.
			sf::RenderStates l_renderstates;
			l_renderstates.blendMode = sf::BlendNone;

			auto l_gouillotineBinPack = GuillotineBinPack(l_RT.getSize().x, l_RT.getSize().y);
			auto l_resultRects = l_gouillotineBinPack.Insert(list, false);

			for (auto rect : l_resultRects)
			{
				rect.textureSizePointer->x = rect.width;
				rect.textureSizePointer->y = rect.height;
				rect.texturePositionPointer->x = rect.x;
				rect.texturePositionPointer->y = rect.y;

				sf::RectangleShape l_shape;
				l_shape.setTexture(rect.texture);
				l_shape.setSize(*rect.textureSizePointer);
				l_shape.setPosition(*rect.texturePositionPointer);
				l_RT.draw(l_shape, l_renderstates);
			}
			l_RT.display();

			return l_RT.getTexture();
		}
	}
}