#include "Scenes\GameScene\GameScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Constructs a base Scene using the name of "Game".
/// </summary>
GameScene::GameScene(KeyHandler& keyHandler)
	: Scene("Game")
	, m_player(keyHandler)
	, m_keyHandler(keyHandler)
	, m_resources(nullptr)
	, m_asteroid()
	, m_windowC2Rect(App::getWindowC2Rect())
{
	m_asteroid.setActive(true);
	m_asteroid.setVelocity(sf::Vector2f(-5.0f, 1.0f));
}

/// <summary>
/// @brief Preloads resources on different thread.
///
/// </summary>
/// <param name="resourceFilePath">defines the path to the json file for this scene</param>
void GameScene::preStart(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Empty for now.
/// 
/// Will contain the loading of external content.
/// </summary>
void GameScene::start(const std::string & resourceFilePath)
{
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
}

/// <summary>
/// @brief Empty for now.
/// 
/// Will contain the unloading of external content.
/// </summary>
void GameScene::stop()
{
}

/// <summary>
/// @brief Update game scene entities.
/// 
/// 
/// </summary>
void GameScene::update()
{
	m_player.update();
	m_asteroid.update();
	updateCollisions();
}

/// <summary>
/// @brief Render game scene entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void GameScene::draw(Window & window, const float & deltaTime)
{
	m_player.draw(window, deltaTime);
	m_asteroid.draw(window, deltaTime);
}

/// <summary>
/// @brief Update game collisions.
/// 
/// 
/// </summary>
void GameScene::updateCollisions()
{
	bulletAsteroidsCollision();
}

/// <summary>
/// @brief update collisions between bullets and asteroids.
/// 
/// 
/// </summary>
void GameScene::bulletAsteroidsCollision()
{
	auto & m_bulletMap = m_player.getBulletMap();
	for (const auto & pair : m_bulletMap)
	{
		auto & bulletVector = pair.second;
		for (auto itt = bulletVector.begin(), end = bulletVector.end(); itt != end; ++itt)
		{
			auto & derivedBullet = **itt;
			if (derivedBullet.isActive())
			{
				if (derivedBullet.checkCircleCollision(m_asteroid.getCollisionCircle()))
				{
					switch (pair.first)
					{
					case BulletTypes::Standard:
						//m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						m_asteroid.decrementHealth(derivedBullet.getDamage());
						derivedBullet.setActive(false);
						break;
					case BulletTypes::Empowered:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					case BulletTypes::DeathOrb:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						break;
					case BulletTypes::FireBlast:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					case BulletTypes::HolySphere:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						break;
					case BulletTypes::MagmaShot:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					case BulletTypes::NapalmSphere:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					case BulletTypes::CometShot:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					case BulletTypes::NullWave:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					case BulletTypes::StaticSphere:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						break;
					case BulletTypes::PyroBlast:
						m_asteroid.reuseAsteroid(); //for now spawn new asteroid
						derivedBullet.setActive(false);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

/// <summary>
/// @brief Tells the SceneManager to change to another Scene.
/// 
/// 
/// </summary>
void GameScene::goToNextScene()
{
	Scene::setNextSceneName("");
}

/// <summary>
/// @brief Loads all external assets.
/// 
/// 
/// </summary>
/// <param name="filePath">defines the path to the json file for this scene</param>
void GameScene::setup(const std::string & filePath)
{
}

