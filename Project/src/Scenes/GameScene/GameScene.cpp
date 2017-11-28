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
	, m_background()
	, m_windowC2Rect(App::getViewC2Rect())
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
	Scene::setNextSceneName("");
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
	m_background.update();
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
	m_background.draw(window, deltaTime);
	m_asteroid.draw(window, deltaTime);
	m_player.draw(window, deltaTime);
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
				if (!m_asteroid.isInvulnerable() && derivedBullet.checkCircleCollision(m_asteroid.getCollisionCircle()))
				{
					switch (pair.first)
					{
					case BulletTypes::Standard:
					case BulletTypes::Empowered:
					case BulletTypes::FireBlast:
						collisionResponse(m_asteroid, derivedBullet);
						break;
					case BulletTypes::DeathOrb:
					case BulletTypes::HolySphere:
						m_asteroid.decrementHealth(derivedBullet.getDamage());
						break;
					case BulletTypes::MagmaShot:
						collisionResponse(m_asteroid, dynamic_cast<bullets::MagmaShot&>(derivedBullet)); //dynamic casting a parameter to magma shot reference from base bullet reference
						break;
					case BulletTypes::NapalmSphere:
						collisionResponse(m_asteroid, dynamic_cast<bullets::NapalmSphere&>(derivedBullet));
						break;
					case BulletTypes::CometShot:
						collisionResponse(m_asteroid, derivedBullet);
						m_asteroid.knockback();
						break;
					case BulletTypes::NullWave:
						collisionResponse(m_asteroid, derivedBullet);
						break;
					case BulletTypes::StaticSphere:
						m_asteroid.decrementHealth(derivedBullet.getDamage());
						break;
					case BulletTypes::PyroBlast:
						collisionResponse(m_asteroid, dynamic_cast<bullets::PyroBlast&>(derivedBullet));
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
/// @brief default collision response for most bullets.
/// 
/// Damages the asteroid and disappears.
/// </summary>
/// <param name="asteroid">reference to the asteroid collided with</param>
/// <param name="bullet">reference to the bullet that has collided</param>
void GameScene::collisionResponse(Asteroid & asteroid, bullets::Bullet & bullet)
{
	asteroid.decrementHealth(bullet.getDamage());
	bullet.setActive(false);
}

/// <summary>
/// @brief overloaded collision response for magma shot.
/// 
/// Damages asteroid and explodes on impact.
/// </summary>
/// <param name="asteroid">reference to the asteroid collided with</param>
/// <param name="bullet">reference to the bullet that has collided</param>
void GameScene::collisionResponse(Asteroid & asteroid, bullets::MagmaShot & bullet)
{
	m_asteroid.decrementHealth(bullet.getDamage());
	bullet.explode(true);
}

/// <summary>
/// @brief overloaded collision response for Napalm Sphere.
/// 
/// Damages asteroid and explodes on impact.
/// </summary>
/// <param name="asteroid">reference to the asteroid collided with</param>
/// <param name="bullet">reference to the bullet that has collided</param>
void GameScene::collisionResponse(Asteroid & asteroid, bullets::NapalmSphere & bullet)
{
	m_asteroid.decrementHealth(bullet.getDamage());
	bullet.explode(true);
}

/// <summary>
/// @brief overloaded collision response for PyroBlast.
/// 
/// Damages asteroid and explodes on impact.
/// </summary>
/// <param name="asteroid">reference to the asteroid collided with</param>
/// <param name="bullet">reference to the bullet that has collided</param>
void GameScene::collisionResponse(Asteroid & asteroid, bullets::PyroBlast & bullet)
{
	m_asteroid.decrementHealth(bullet.getDamage());
	bullet.explode(true);
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
	auto & resourceHandler = ResourceHandler::get();

	std::ifstream rawFile(filePath);
	json::json gameSceneJsonLoader;
	rawFile >> gameSceneJsonLoader;

	if (!m_resources)
	{
		std::ifstream playerRawFile(gameSceneJsonLoader.at("player").get<std::string>());
		json::json playerJson;
		playerRawFile >> playerJson;

		m_resources = std::make_unique<Resources>();
		auto sptrPlayer = m_resources->m_sptrPlayer;
		auto sptrShip = sptrPlayer->m_ship;
		sptrShip->m_sptrTexture = resourceHandler.loadUp<sf::Texture>(playerJson, "ship");
		assert(nullptr != sptrShip->m_sptrTexture);

		sptrShip->m_uptrFrames = std::make_unique<Ship::ShipFrames>();
		auto & frames = *sptrShip->m_uptrFrames;
		auto loadedFrames = resourceHandler.loadUp<Ship::ShipFrames>(playerJson, "ship");
		frames.insert(frames.begin(), loadedFrames->begin(), loadedFrames->end());
		assert(nullptr != sptrShip->m_uptrFrames);

		std::ifstream backgroundRawFile(gameSceneJsonLoader.at("background").get<std::string>());
		json::json backgroundJson;
		backgroundRawFile >> backgroundJson;

		auto sptrBackground = m_resources->m_sptrBackground;
		sptrBackground->m_sptrBgShader = resourceHandler.loadUp<sf::Shader>(backgroundJson, "background");
	}

	m_background.init(m_resources->m_sptrBackground);
	m_player.init(m_resources->m_sptrPlayer);
}

