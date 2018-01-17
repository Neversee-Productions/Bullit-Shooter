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
	, m_background()
	, m_windowC2Rect(App::getViewC2Rect())
	, m_asteroidManager()
	, m_asteroidSpawnTimer(0.0f)
	, m_asteroidSpawnFrequency(0.0f)
	, UPDATE_DT(App::getUpdateDeltaTime())
{
	m_asteroidManager.initAsteroidVector();
	m_asteroidSpawnFrequency = generateRandomTimer();
	m_pickup = std::make_unique<Pickup>(Pickup(sf::Vector2f(500, 500), sf::Vector2f(100, 100)));
	m_pickup->setActive(false);
}

/// <summary>
/// @brief Pre-loads resources on different thread.
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
	if (m_player.getShieldHealth() <= 0)
	{
		m_player.setAlive(false);
	}
	m_asteroidSpawnTimer += UPDATE_DT;
	if (m_asteroidSpawnTimer >= m_asteroidSpawnFrequency)
	{
		int counter = 0;
		//spawn next unused asteroid here
		for (auto & uptrAsteroid : m_asteroidManager.getAsteroidVector())
		{
			if (uptrAsteroid && !uptrAsteroid->isActive())
			{
				if (counter == 0)
				{
					uptrAsteroid->reuseAsteroid();
					counter++;
				}
			}
			m_asteroidSpawnFrequency = generateRandomTimer();
		}
		m_asteroidSpawnTimer = 0.0f;
	}
	m_player.update();
	for (auto & uptrAsteroid : m_asteroidManager.getAsteroidVector())
	{
		if (uptrAsteroid->isActive())
		{
			uptrAsteroid->update();
		}
	}
	playerPickupCollision();
	m_pickup->update();
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
	for (auto & uptrAsteroid : m_asteroidManager.getAsteroidVector())
	{
		if (uptrAsteroid->isActive())
		{
			uptrAsteroid->draw(window, deltaTime);
		}
	}
	m_player.draw(window, deltaTime);
	m_pickup->draw(window, deltaTime);
}

/// <summary>
/// @brief Update game collisions.
/// 
/// 
/// </summary>
void GameScene::updateCollisions()
{
	bulletAsteroidsCollision();
	playerAsteroidCollision();
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
				auto & asteroidVector = m_asteroidManager.getAsteroidVector();
				for (auto itt2 = asteroidVector.begin(), end2 = asteroidVector.end(); itt2 != end2; ++itt2)
				{
					auto & asteroid = **itt2;
					if (asteroid.isActive())
					{
						if (!asteroid.isInvulnerable() && derivedBullet.checkCircleCollision(asteroid.getCollisionCircle()))
						{
							switch (pair.first)
							{
							case BulletTypes::Standard:
							case BulletTypes::Empowered:
							case BulletTypes::FireBlast:
								collisionResponse(asteroid, derivedBullet);
								break;
							case BulletTypes::DeathOrb:
							case BulletTypes::HolySphere:
								asteroid.decrementHealth(derivedBullet.getDamage());
								break;
							case BulletTypes::MagmaShot:
								collisionResponse(asteroid, dynamic_cast<bullets::MagmaShot&>(derivedBullet)); //dynamic casting a parameter to magma shot reference from base bullet reference
								break;
							case BulletTypes::NapalmSphere:
								collisionResponse(asteroid, dynamic_cast<bullets::NapalmSphere&>(derivedBullet));
								break;
							case BulletTypes::CometShot:
								collisionResponse(asteroid, derivedBullet);
								asteroid.knockback();
								break;
							case BulletTypes::NullWave:
								collisionResponse(asteroid, derivedBullet);
								break;
							case BulletTypes::StaticSphere:
								asteroid.decrementHealth(derivedBullet.getDamage());
								break;
							case BulletTypes::PyroBlast:
								collisionResponse(asteroid, dynamic_cast<bullets::PyroBlast&>(derivedBullet));
								break;
							default:
								break;
							}
						}
						if (!asteroid.isActive() && ! m_pickup->isActive()) //check if pickup is not active and if the asteroid was destroyed.
						{
							int chance = (rand() % 11); //generate number from 0 - 10
							if (chance > 2 )
							{
								sf::Vector2f pos = sf::Vector2f(asteroid.getCollisionCircle().p.x, asteroid.getCollisionCircle().p.y);
								m_pickup = std::make_unique<Pickup>(Pickup(pos, sf::Vector2f(100, 100)));
							}
						}
					}
				}
			}
		}
	}
}

/// <summary>
/// @brief this method checks collisions with all active asteroids.
/// 
/// 
/// </summary>
void GameScene::playerAsteroidCollision()
{
	auto & asteroidVector = m_asteroidManager.getAsteroidVector();
	for (auto itt = asteroidVector.begin(), end2 = asteroidVector.end(); itt != end2; ++itt)
	{
		auto & asteroid = **itt;
		if (asteroid.isActive())
		{
			if (tinyh::c2CircletoCircle(m_player.getShieldCollisionCircle(), asteroid.getCollisionCircle()))
			{
				m_player.decrementShield(25.0f);
				asteroid.decrementHealth(10.0f);
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
	asteroid.decrementHealth(bullet.getDamage());
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
	asteroid.decrementHealth(bullet.getDamage());
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
	asteroid.decrementHealth(bullet.getDamage());
	bullet.explode(true);
}

void GameScene::playerPickupCollision()
{
	if (m_pickup->isActive())
	{
		sf::Vector2f vector = m_player.getPosition() - m_pickup->getPosition();
		float length = thor::length(vector);
		if (length < 100)
		{
			sf::Vector2f unitVec = thor::unitVector(vector);
			m_pickup->setVelocity(unitVec * (length * 0.1f));
			if (length < 10)
			{
				m_player.nextWeapon();
				m_pickup->setActive(false);
			}
		}
	}
}

/// <summary>
/// @brief generates random float values for a timer from 0 to 3.
/// 
/// 
/// </summary>
float GameScene::generateRandomTimer()
{
	return m_asteroidSpawnFrequency = rand() % 4; //generate number from 0 to 3
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
		auto sptrWeapon = sptrPlayer->m_weapon;
		auto sptrConnector = sptrPlayer->m_connector;

		sptrShip->m_sptrTexture = resourceHandler.loadUp<sf::Texture>(playerJson, "ship");
		assert(nullptr != sptrShip->m_sptrTexture);

		sptrShip->m_uptrFrames = std::make_unique<Ship::ShipFrames>();
		auto & frames = *sptrShip->m_uptrFrames;
		auto loadedFrames = resourceHandler.loadUp<Ship::ShipFrames>(playerJson, "ship");
		frames.insert(frames.begin(), loadedFrames->begin(), loadedFrames->end());
		assert(nullptr != sptrShip->m_uptrFrames);

		auto & weaponAnimations = sptrWeapon->m_weaponAnimations;

		auto const & NUM_OF_WEPS = Weapon::MAX_WEAPONS;
		
		// initialize string stream to be 8 characters wide,
		//	NOTE: the stream seek position is still at the start of the stream
		//	meaning any insertion is done from the beginning of the stream
		std::stringstream weaponId("--------");
		weaponId << "weapon";
		for (int i = 0; i < NUM_OF_WEPS; ++i)
		{
			auto const WEAPON_NUM = i + 1;
			if (WEAPON_NUM < 10)
			{
				weaponId << "0" + std::to_string(WEAPON_NUM);
			}
			else
			{
				weaponId << std::to_string(WEAPON_NUM);
			}
			weaponAnimations.push_back(std::move(setupWeapon(resourceHandler, playerJson, weaponId.str())));
			
			// move string stream's seek position back 2 places.
			weaponId.seekp(-2, std::ios_base::end);
		}
		
		sptrConnector->m_sptrCnShader = resourceHandler.loadUp<sf::Shader>(playerJson, "connector");

		std::ifstream backgroundRawFile(gameSceneJsonLoader.at("background").get<std::string>());
		json::json backgroundJson;
		backgroundRawFile >> backgroundJson;

		auto sptrBackground = m_resources->m_sptrBackground;
		sptrBackground->m_sptrBgShader = resourceHandler.loadUp<sf::Shader>(backgroundJson, "background");

	}

	m_background.init(m_resources->m_sptrBackground);
	m_player.init(m_resources->m_sptrPlayer);
}

/// <summary>
/// @brief Set-ups weapon animations.
/// 
/// Constructs necessary asset interface for weapon.
/// (Assumes weapon has both begin and shoot animation)
/// </summary>
/// <param name="resourceHandler">defines reference to ResourceHandler.</param>
/// <param name="playerParser">defines reference to a initialize json parser.</param>
/// <param name="id">defines the id of our weapon.</param>
/// <returns>returns a unique pointer to our Weapon::Resources::WeaponAnimation.</returns>
std::unique_ptr<Weapon::Resources::WeaponAnimation> GameScene::setupWeapon(ResourceHandler & resourceHandler, json::json & playerParser, std::string const & id)
{
	std::string const ANIM_STR = "animation";

	std::string const BEGIN_ID = id + "_begin";
	auto uptrBeginAnimation = std::make_unique<Weapon::Resources::Animation>();
	auto & beginAnimation = *uptrBeginAnimation;
	beginAnimation.m_id = BEGIN_ID;
	beginAnimation.m_sptrFrames = resourceHandler.loadUp<thor::FrameAnimation>(playerParser, BEGIN_ID);
	beginAnimation.m_duration = sf::seconds(playerParser.at(ANIM_STR).at(BEGIN_ID).at("duration").get<float>());
	auto const & beginAnimationFrameWidth = playerParser.at(ANIM_STR).at(BEGIN_ID).at("width").get<float>();
	auto const & beginAnimationFrameHeight = playerParser.at(ANIM_STR).at(BEGIN_ID).at("height").get<float>();
	auto & jsonBeginOrigin = playerParser.at(ANIM_STR).at(BEGIN_ID).at("origin");
	auto beginAnimationOrigin = sf::Vector2f(jsonBeginOrigin.at("x").get<float>(), jsonBeginOrigin.at("y").get<float>());
	beginAnimation.m_origin = std::move(beginAnimationOrigin);
	beginAnimation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(playerParser, BEGIN_ID);

	std::string const shootID = id + "_shoot";
	auto uptrShootAnimation = std::make_unique<Weapon::Resources::Animation>();
	auto & shootAnimation = *uptrShootAnimation;
	shootAnimation.m_id = shootID;
	shootAnimation.m_sptrFrames = resourceHandler.loadUp<thor::FrameAnimation>(playerParser, shootID);
	shootAnimation.m_duration = sf::seconds(playerParser.at(ANIM_STR).at(shootID).at("duration").get<float>());
	auto const & shootAnimationFrameWidth = playerParser.at(ANIM_STR).at(shootID).at("width").get<float>();
	auto const & shootAnimationFrameHeight = playerParser.at(ANIM_STR).at(shootID).at("height").get<float>();
	auto & jsonShootOrigin = playerParser.at(ANIM_STR).at(shootID).at("origin");
	auto shootAnimationOrigin = sf::Vector2f(jsonShootOrigin.at("x").get<float>(), jsonShootOrigin.at("y").get<float>());
	shootAnimation.m_origin = std::move(shootAnimationOrigin);
	shootAnimation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(playerParser, shootID);
	
	return std::make_unique<Weapon::Resources::WeaponAnimation>(std::make_pair(std::move(uptrBeginAnimation), std::move(uptrShootAnimation)));
}

