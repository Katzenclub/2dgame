#include "Loader.h"

namespace gp
{
	namespace system
	{
		Loader::Loader()
		{
			clock_t start_time = clock();
      
			m_listBlocks.push_back(new gp::world::Block("Air", "data/assets/blocks/Air.png", {}));
			m_listBlocks.push_back(new gp::world::Block("Dirt", "data/assets/blocks/Dirt/Dirt.png", {{"InflictBurning", 2}, {"InflictDrowning", 10}}));
			m_listBlocks.push_back(new gp::world::Block("Stone", "data/assets/blocks/Stone.png", {{"InflictBurning", 5}, {"InflictDrowning", 10}}));
			m_textureAtlas = createTextureAtlas(gp::system::Source::tranformToSource(m_listBlocks));


			addBlock("data/assets/blocks/Dirt", 1);
			m_borderAtlas = createBorderAtlas();
			
			m_listProjectiles.push_back(new gp::system::ProjectileSource("Default", "data/assets/projectiles/default.png"));
			m_projectileAtlas = createTextureAtlas(gp::system::Source::tranformToSource(m_listProjectiles));

			m_listObjectAssets.push_back(new gp::object::ObjectSource("Player", "data/assets/objects/Player.png", sf::Vector2f(0.5f, 0.95f)));
			m_listObjectAssets.push_back(new gp::object::ObjectSource("Slime", "data/assets/objects/Slime.png"));
			m_listObjectAssets.push_back(new gp::object::ObjectSource("SlimeMutant", "data/assets/objects/SlimeMutant.png"));
			m_objectsAtlas = createTextureAtlas(gp::system::Source::tranformToSource(m_listObjectAssets));
			clock_t end_time = clock();
			clock_t result = end_time - start_time;
			printf("Creating Texture Atlases took %ld clicks (%f seconds).\n", result, ((float)result) / CLOCKS_PER_SEC);
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

		sf::Texture Loader::createTextureAtlas(const std::vector<gp::system::Source*>& list)
		{
			std::vector<RectInfo> l_rects;
			for (auto source : list)
			{
				auto l_rectInfo = RectInfo();
				l_rectInfo.width = source->m_SizeTexture.x;
				l_rectInfo.height = source->m_SizeTexture.y;
				l_rectInfo.textureSizePointer = &source->m_SizeTexture;
				l_rectInfo.texturePositionPointer = &source->m_PositionTexture;
				l_rectInfo.texture = &source->m_texture;

				l_rects.push_back(l_rectInfo);
			}

			return createTextureAtlas(l_rects);
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

		sf::Texture Loader::createTextureAtlas(std::vector<RectInfo>& list) {
			auto l_gouillotineBinPack = GuillotineBinPack(g_MAX_ATLAS_SIZE, g_MAX_ATLAS_SIZE);
			auto l_resultRects = l_gouillotineBinPack.Insert(list, false);

			int maxWidth = 0;
			int maxHeight = 0;
			for (auto rect : l_resultRects)
			{
				if (rect.width + rect.x > maxWidth) {
					maxWidth = rect.width + rect.x;
				}

				if (rect.height + rect.y > maxHeight) {
					maxHeight = rect.height + rect.y;
				}
			}

			sf::RenderTexture l_RT;
			l_RT.create(maxWidth, maxHeight);
			l_RT.clear(sf::Color::Magenta);
			sf::RenderStates l_renderstates;
			l_renderstates.blendMode = sf::BlendNone;

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