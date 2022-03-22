#include "Loader.h"

namespace gp
{
	namespace system
	{
		Loader::Loader()
		{
			m_listBlocks.push_back(new gp::world::Block("Air", "data/assets/blocks/Air.png", {}));
			m_listBlocks.push_back(new gp::world::Block("Dirt", "data/assets/blocks/Dirt/Dirt.png", {{"InflictBurning", 2}, {"InflictDrowning", 10}}));
			m_listBlocks.push_back(new gp::world::Block("Stone", "data/assets/blocks/Stone.png", {{"InflictBurning", 5}, {"InflictDrowning", 10}}));

			m_textureAtlas = createTextureAtlas(m_listBlocks);

			addBlock("data/assets/blocks/Dirt", 1);
			m_borderAtlas = createBorderAtlas();

			m_listObjectAssets.push_back(new gp::object::ObjectAsset("Player", "data/assets/objects/Player.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectAsset("Slime", "data/assets/objects/Slime.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectAsset("SlimeMutant", "data/assets/objects/SlimeMutant.png"));

			clock_t start_time = clock();
			m_objectsAtlas = createTextureAtlas(m_listObjectAssets);
			clock_t end_time = clock();
			clock_t result = end_time - start_time;
			printf("Create Object Atlas took %ld clicks (%f seconds).\n", result, ((float)result) / CLOCKS_PER_SEC);
			
		}

		Loader::~Loader()
		{
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::world::Block *> &list)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color(0, 0, 0, 0));

			for (auto it : list)
			{
				sf::RectangleShape l_shape;
				l_shape.setTexture(&it->m_texture);
				l_shape.setSize(sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE));
				l_shape.setPosition(sf::Vector2f(
					(it->m_ID % g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE,
					(it->m_ID / g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE));

				l_RT.draw(l_shape);
			}

			l_RT.display();

			return l_RT.getTexture();
		}

		sf::Texture Loader::createBorderAtlas()
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color(0, 0, 0, 0));
			for (int blockID = 0; blockID < 64; blockID++)
			{
				for (int borderType = 0; borderType < 8; borderType++)
				{
					sf::RectangleShape l_shape;
					gp::world::Border *border = m_managerBorder.m_listBorders[blockID][borderType];
					if (border == NULL)
					{
						continue;
					}
					l_shape.setTexture(&border->m_texture);
					l_shape.setSize(sf::Vector2f(g_CHUNK_TEXTURE_SIZE, g_CHUNK_TEXTURE_SIZE));
					l_shape.setPosition(sf::Vector2f(
						(border->m_ID / g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE,
						(border->m_ID % g_ATLAS_BLOCK_SIZE) * g_CHUNK_TEXTURE_SIZE));

					l_RT.draw(l_shape);
				}
			}

			l_RT.display();

			return l_RT.getTexture();
		}

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::object::ObjectAsset *> &list)
		{
			sf::RenderTexture l_RT;
			l_RT.create(g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE, g_CHUNK_TEXTURE_SIZE * g_ATLAS_BLOCK_SIZE);
			l_RT.clear(sf::Color(0, 0, 0, 0));

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

			for (auto resultRect : l_resultRects)
			{
				auto objectAsset = resultRect.objectAsset;

				sf::RectangleShape l_shape;
				l_shape.setTexture(&resultRect.objectAsset->m_texture);

				objectAsset->m_SizeTexture = sf::Vector2f(resultRect.width, resultRect.height);
				l_shape.setSize(objectAsset->m_SizeTexture);

				objectAsset->m_PositionTexture = sf::Vector2f(resultRect.x, resultRect.y);
				l_shape.setPosition(objectAsset->m_PositionTexture);

				l_RT.draw(l_shape);
			}

			l_RT.display();

			return l_RT.getTexture();
		}

		void Loader::addBlock(std::string borderFolder, int blockID)
		{
			for (auto dir_entry : std::filesystem::directory_iterator(borderFolder))
			{
				std::string path = dir_entry.path().string();
				std::string substring = dir_entry.path().filename().string().substr(0, 1);
				
				int borderType = -1;
				try
				{
					borderType = std::stoi(substring);
				}
				catch (const std::invalid_argument& ex)
				{
					continue;
				}
				
				m_managerBorder.addBorder(new gp::world::Border(path), (gp::world::BorderType) borderType, blockID);
			}
		}
	}
}