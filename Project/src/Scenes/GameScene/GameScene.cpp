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
	m_player.update();
	updateAsteroidSpawner();
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
			if (derivedBullet.isActive() && !derivedBullet.isImpact())
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
								BulletTypes pickupType = m_player.getWeaponType();
								auto weaponNum = static_cast<int>(pickupType);
								weaponNum++;
								if (weaponNum < static_cast<int>(BulletTypes::AmountOfTypes))
								{
									pickupType = static_cast<BulletTypes>(weaponNum);
									sf::Vector2f pos = sf::Vector2f(asteroid.getCollisionCircle().p.x, asteroid.getCollisionCircle().p.y);
									m_pickup = std::make_unique<Pickup>(Pickup(m_resources->m_sptrPickup, pos, sf::Vector2f(100, 100), pickupType));
								}
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
	if (m_player.isAlive())
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
	bullet.hit();
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
		sf::Vector2f vector = m_player.getPosition() - m_pickup->getRightPosition();
		float length = thor::length(vector);
		if (length < 100)
		{
			m_player.setCanFire(false);
			m_player.setAttachedWeapons(false);
			//decrease alpha of the pickup effect
			m_pickup->fadeOutEffect();

			//LEFT WEAPON CALCULATIONS
			sf::Vector2f leftPosVec = m_player.getLeftWeaponPos() - m_pickup->getRightPosition();
			sf::Vector2f unitVecLeft = thor::unitVector(leftPosVec);
			float leftLength = thor::length(leftPosVec);

			//RIGHT WEAPON CALCULATIONS
			sf::Vector2f rightPosVec = m_player.getRightWeaponPos() - m_pickup->getLeftPosition();
			sf::Vector2f unitVecRight = thor::unitVector(rightPosVec);
			float rightLength = thor::length(rightPosVec);

			m_pickup->setRightVelocity((unitVecLeft * (length * 5.2f))* App::getUpdateDeltaTime());
			m_pickup->setLeftVelocity((unitVecRight * (length * 5.2f)) * App::getUpdateDeltaTime());
			m_player.fadeOutWeapons();
			
			m_player.setConnectorPos(m_pickup->getLeftPosition(), m_pickup->getRightPosition());

			if (leftLength < 10 && rightLength < 10)
			{
				m_player.setWeaponsAlpha(255);
				m_player.setAttachedWeapons(true);
				m_player.nextWeapon();
				m_pickup->setActive(false);
			}
		}
		else
		{
			m_pickup->setEffectAlpha(255);
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
/// @brief this method spawns an asteroid once a timer reaches its max.
/// 
/// 
/// </summary>
void GameScene::updateAsteroidSpawner()
{
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

	// Loading Game Scene Raw Text file.
	std::ifstream rawFile(filePath);
	// Defines the Game Scene's Json Parser
	json::json gameSceneParser;
	rawFile >> gameSceneParser; // Parsing raw text file into json parser.

	if (!m_resources)
	{
		m_resources = std::make_unique<Resources>();

		////////////////////////////////////////////
		// Setup Player
		////////////////////////////////////////////
		this->setupPlayer(resourceHandler, m_resources->m_sptrPlayer, gameSceneParser);

		////////////////////////////////////////////
		// Setup Background
		////////////////////////////////////////////
		this->setupBackground(resourceHandler, m_resources->m_sptrBackground, gameSceneParser);

		////////////////////////////////////////////
		// Setup Pickups
		////////////////////////////////////////////
		this->setupPickups(resourceHandler, m_resources->m_sptrPickup, gameSceneParser);
	}

	m_player.init(m_resources->m_sptrPlayer);
	m_background.init(m_resources->m_sptrBackground);
	m_pickup = std::make_unique<Pickup>(Pickup(m_resources->m_sptrPickup, sf::Vector2f(500, 500), sf::Vector2f(100, 100), BulletTypes::Empowered));
	m_pickup->setActive(false);
}

/// <summary>
/// @brief Setups Player::Resources.
/// 
/// 
/// </summary>
/// <param name="resourceHandler"></param>
/// <param name="sptrPlayerResources"></param>
/// <param name="gameSceneParser"></param>
void GameScene::setupPlayer(ResourceHandler & resourceHandler, std::shared_ptr<Player::Resources> sptrPlayerResources, json::json & gameSceneParser)
{
	std::string const PLAYER_ID("player");

	// Loading player Raw Text File
	std::ifstream playerRawFile(gameSceneParser.at(PLAYER_ID).get<std::string>());
	// Defines the Player's Json Parser
	json::json playerJson;
	playerRawFile >> playerJson; // Parsing raw text file into json parser.

	////////////////////////////////////////////
	// Setup Ship resources
	////////////////////////////////////////////
	this->setupShip(resourceHandler, sptrPlayerResources->m_ship, playerJson);

	////////////////////////////////////////////
	// Setup Weapon resources
	////////////////////////////////////////////
	this->setupWeapons(resourceHandler, sptrPlayerResources->m_weapon, playerJson);

	////////////////////////////////////////////
	// Setup Connector
	////////////////////////////////////////////
	this->setupConnector(resourceHandler, sptrPlayerResources->m_connector, playerJson);

	////////////////////////////////////////////
	// Setup Bullet Manager
	////////////////////////////////////////////
	this->setupBulletManager(resourceHandler, sptrPlayerResources->m_bullets, playerJson);
}

/// <summary>
/// @brief Setups ship resource loading.
/// 
/// Loads all necessary resources for the ship.
/// @warning No checks are made as to the validity of the parameters.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrShipResources">shared pointer to our ship resources, assumed to be a valid pointer (initialized).</param>
/// <param name="shipParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupShip(ResourceHandler & resourceHandler, std::shared_ptr<Ship::Resources> sptrShipResources, json::json & shipParser)
{
	std::string const SHIP_ID("ship");

	sptrShipResources->m_sptrTexture = resourceHandler.loadUp<sf::Texture>(shipParser, SHIP_ID);
	assert(nullptr != sptrShipResources->m_sptrTexture);

	sptrShipResources->m_uptrFrames = std::make_unique<Ship::ShipFrames>();
	auto & frames = *sptrShipResources->m_uptrFrames;
	auto loadedFrames = resourceHandler.loadUp<Ship::ShipFrames>(shipParser, SHIP_ID);
	frames.insert(frames.begin(), loadedFrames->begin(), loadedFrames->end());
	assert(nullptr != sptrShipResources->m_uptrFrames);
}

/// <summary>
/// @brief Setups Weapon::Resources.
/// 
/// Loads all necessary resources for the weapons.
/// @warning No checks are made as to the validity of the parameters.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrWeaponResources">shared pointer to our weapon resources, assumed to be a valid pointer (initialized).</param>
/// <param name="weaponParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupWeapons(ResourceHandler & resourceHandler, std::shared_ptr<Weapon::Resources> sptrWeaponResources, json::json & weaponParser)
{
	auto & weaponAnimations = sptrWeaponResources->m_weaponAnimations;
	auto const & NUM_OF_WEPS = Weapon::MAX_WEAPONS;

	// initialize string stream to be 8 characters wide,
	//	NOTE: the stream seek position is still at the start of the stream
	//	meaning any insertion is done from the beginning of the stream
	std::stringstream weaponId("--------");
	weaponId << "weapon";
	for (int i = 0; i < NUM_OF_WEPS; ++i)
	{
		int const WEAPON_NUM = i + 1;
		if (WEAPON_NUM < 10)
		{
			weaponId << "0" + std::to_string(WEAPON_NUM);
		}
		else
		{
			weaponId << std::to_string(WEAPON_NUM);
		}
		auto weaponAnimation = this->setupWeaponAnim(resourceHandler, weaponParser, weaponId.str());
		weaponAnimations.push_back(std::move(weaponAnimation));

		// move string stream's seek position back 2 places.
		weaponId.seekp(-2, std::ios_base::end);
	}
}

/// <summary>
/// @brief Set-ups Weapon::Resources::WeaponAnimation.
/// 
/// Constructs necessary asset interface for weapon.
/// (Assumes weapon has both begin and shoot animation)
/// </summary>
/// <param name="resourceHandler">defines reference to ResourceHandler.</param>
/// <param name="playerParser">defines reference to a initialize json parser.</param>
/// <param name="id">defines the id of our weapon.</param>
/// <returns>returns a unique pointer to our Weapon::Resources::WeaponAnimation.</returns>
std::unique_ptr<Weapon::Resources::WeaponAnimation> GameScene::setupWeaponAnim(ResourceHandler & resourceHandler, json::json & weaponParser, std::string const & id)
{
	std::string const ANIM_STR = "animation";

	std::string const BEGIN_ID = id + "_begin";
	auto uptrBeginAnimation = std::make_unique<Weapon::Resources::Animation>();
	auto & beginAnimation = *uptrBeginAnimation;
	beginAnimation.m_id = BEGIN_ID;
	beginAnimation.m_sptrFrames = resourceHandler.loadUp<thor::FrameAnimation>(weaponParser, BEGIN_ID);
	beginAnimation.m_duration = sf::seconds(weaponParser.at(ANIM_STR).at(BEGIN_ID).at("duration").get<float>());
	auto const & beginAnimationFrameWidth = weaponParser.at(ANIM_STR).at(BEGIN_ID).at("width").get<float>();
	auto const & beginAnimationFrameHeight = weaponParser.at(ANIM_STR).at(BEGIN_ID).at("height").get<float>();
	auto & jsonBeginOrigin = weaponParser.at(ANIM_STR).at(BEGIN_ID).at("origin");
	auto beginAnimationOrigin = sf::Vector2f(jsonBeginOrigin.at("x").get<float>(), jsonBeginOrigin.at("y").get<float>());
	beginAnimation.m_origin = std::move(beginAnimationOrigin);
	beginAnimation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(weaponParser, BEGIN_ID);

	std::string const shootID = id + "_shoot";
	auto uptrShootAnimation = std::make_unique<Weapon::Resources::Animation>();
	auto & shootAnimation = *uptrShootAnimation;
	shootAnimation.m_id = shootID;
	shootAnimation.m_sptrFrames = resourceHandler.loadUp<thor::FrameAnimation>(weaponParser, shootID);
	shootAnimation.m_duration = sf::seconds(weaponParser.at(ANIM_STR).at(shootID).at("duration").get<float>());
	auto const & shootAnimationFrameWidth = weaponParser.at(ANIM_STR).at(shootID).at("width").get<float>();
	auto const & shootAnimationFrameHeight = weaponParser.at(ANIM_STR).at(shootID).at("height").get<float>();
	auto & jsonShootOrigin = weaponParser.at(ANIM_STR).at(shootID).at("origin");
	auto shootAnimationOrigin = sf::Vector2f(jsonShootOrigin.at("x").get<float>(), jsonShootOrigin.at("y").get<float>());
	shootAnimation.m_origin = std::move(shootAnimationOrigin);
	shootAnimation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(weaponParser, shootID);
	
	return std::make_unique<Weapon::Resources::WeaponAnimation>(std::make_pair(std::move(uptrBeginAnimation), std::move(uptrShootAnimation)));
}

/// <summary>
/// @brief Setups Connector::Resources.
/// 
/// Loads all necessary resources for the connector.
/// @warning No checks are made as to the validity of the parameters.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrConnectorResources">shared pointer to our connector resources, assumed to be a valid pointer (initialized).</param>
/// <param name="connectorParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupConnector(ResourceHandler & resourceHandler, std::shared_ptr<Connector::Resources> sptrConnectorResources, json::json & connectorParser)
{
	std::string const CONNECTOR_ID("connector");

	sptrConnectorResources->m_sptrCnShader = resourceHandler.loadUp<sf::Shader>(connectorParser, CONNECTOR_ID);
}

/// <summary>
/// @brief Setups BulletManager::Resources.
/// 
/// Loads all necessary resource for the bullet manager.
/// @warning No checks are made as to the validity of the parameters.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrBulletManagerResources">shared pointer to our bullet manager resources, assumed to be a valid pointer (initialized).</param>
/// <param name="bulletManagerParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupBulletManager(ResourceHandler & resourceHandler, std::shared_ptr<BulletManager::Resources> sptrBulletManagerResources, json::json & bulletManagerParser)
{
	std::stringstream bulletId("--------");
	bulletId << "bullet";

	auto const NUM_OF_BULLETS = static_cast<int>(BulletTypes::AmountOfTypes);
	for (int i = 0; i < NUM_OF_BULLETS; ++i)
	{
		int const BULLET_NUM = i + 1;
		if (BULLET_NUM < 10)
		{
			bulletId << "0" + std::to_string(BULLET_NUM);
		}
		else
		{
			bulletId << std::to_string(BULLET_NUM);
		}

		auto const BULLET_TYPE = static_cast<BulletTypes>(i);
		this->setupBullet(resourceHandler, sptrBulletManagerResources->m_sptrBulletsResources, BULLET_TYPE, bulletManagerParser, bulletId.str());

		bulletId.seekp(-2, std::ios_base::end); // Moves the string stream's seek cursor back 2 places.
	}
}

/// <summary>
/// @brief Setups BulletManager::Resources::BulletResources.
/// 
/// Loads all necessary resources for each bullet in bullet manager resources.
/// @warning No checks are made as to the validity of the parameters.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrBulletResources">shared pointer to our bullet resources map, assumed to be a valid pointer (initialized).</param>
/// <param name="bulletType">read-only reference to the type of bullet we want to load.</param>
/// <param name="bulletParser">reference to loaded json file ready to be parsed.</param>
/// <param name="id">read-only reference to the id of bullet to setup.</param>
void GameScene::setupBullet(
	ResourceHandler & resourceHandler
	, std::shared_ptr<BulletManager::Resources::BulletResources> sptrBulletResourceMap
	, BulletTypes const & bulletType
	, json::json & bulletParser
	, std::string const & id)
{
	auto sptrBulletResource = std::shared_ptr<bullets::Bullet::Resources>(nullptr);

	std::string const TEXTURES_JSON_KEY("textures");
	// Reference to json textures section
	json::json const & JSON_BULLET_TEXTURE = bulletParser.at(TEXTURES_JSON_KEY).at(id);

	std::string const ANIMATIONS_JSON_KEY("animation");
	std::string const BULLETS_JSON_KEY("bullets");
	// Reference to json animations section
	json::json const & JSON_BULLET_ANIMATION = bulletParser.at(ANIMATIONS_JSON_KEY).at(BULLETS_JSON_KEY).at(id);

	std::string const JSON_LOOP_KEY("loop");
	std::string const JSON_IMPACT_KEY("impact");


	// Lambda used for initializing animation frames
	auto frameAnimationLambda = [this](thor::FrameAnimation & frameAnimation, json::json const & JSON_ANIMATION) -> void
	{
		std::string const JSON_X_KEY("x");
		std::string const JSON_Y_KEY("y");

		auto const & FRAME_WIDTH = JSON_ANIMATION.at("width").get<int>();
		auto const & FRAME_HEIGHT = JSON_ANIMATION.at("height").get<int>();
		auto const & JSON_FRAMES = JSON_ANIMATION.at("frames");
		float count = 1.0f;
		for (
			auto iterator = JSON_FRAMES.begin(), endIterator = JSON_FRAMES.end();
			iterator != endIterator;
			++iterator, ++count
			)
		{
			auto x = iterator->at(JSON_X_KEY).get<int>();
			auto y = iterator->at(JSON_Y_KEY).get<int>();
			frameAnimation.addFrame(count, sf::IntRect(x, y, FRAME_WIDTH, FRAME_HEIGHT));
		}
	};

	auto loadAnimation = [&](
		std::shared_ptr<bullets::Bullet::Resources::Animation> sptrAnimation
		, std::string const & jsonAnimationKey
		, json::json const & bulletAnimationNode
		, json::json const & bulletTextureNode
		) -> void
	{
		if (nullptr == sptrAnimation)
		{
			return;
		}
		auto & animation = *sptrAnimation;
		auto const & JSON_ANIMATION_NODE = bulletAnimationNode.at(jsonAnimationKey);
		auto const & JSON_TEXTURE_NODE = bulletTextureNode.at(jsonAnimationKey);

		std::string const TEXTURE_ID = id + "_" + jsonAnimationKey;

		animation.m_id = jsonAnimationKey;
		animation.m_duration = sf::seconds(JSON_ANIMATION_NODE.at("duration").get<float>());
		auto const & JSON_ANIMATION_ORIGIN = JSON_ANIMATION_NODE.at("origin");
		animation.m_origin = sf::Vector2f(JSON_ANIMATION_ORIGIN.at("x").get<float>(), JSON_ANIMATION_ORIGIN.at("y").get<float>());
		animation.m_sptrFrames = std::make_shared<thor::FrameAnimation>();
		frameAnimationLambda(*animation.m_sptrFrames, JSON_ANIMATION_NODE);
		animation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(JSON_TEXTURE_NODE.get<std::string>(), TEXTURE_ID);
	};

	switch (bulletType)
	{
		// Using bullets namespace within the scope of the switch statement
		using namespace bullets; 

		case BulletTypes::PyroBlast:
		{
			sptrBulletResource = std::make_shared<PyroBlast::Resources>();
			break;
		}
		case BulletTypes::StaticSphere:
		{
			sptrBulletResource = std::make_shared<StaticSphere::Resources>();
			break;
		}
		case BulletTypes::NullWave:
		{
			sptrBulletResource = std::make_shared<NullWave::Resources>();
			break;
		}
		case BulletTypes::CometShot:
		{
			sptrBulletResource = std::make_shared<CometShot::Resources>();
			break;
		}
		case BulletTypes::NapalmSphere:
		{
			sptrBulletResource = std::make_shared<NapalmSphere::Resources>();
			break;
		}
		case BulletTypes::MagmaShot:
		{
			sptrBulletResource = std::make_shared<MagmaShot::Resources>();
			break;
		}
		case BulletTypes::HolySphere:
		{
			sptrBulletResource = std::make_shared<HolySphere::Resources>();
			break;
		}
		case BulletTypes::FireBlast:
		{
			sptrBulletResource = std::make_shared<FireBlast::Resources>();
			break;
		}
		case BulletTypes::DeathOrb:
		{
			sptrBulletResource = std::make_shared<DeathOrb::Resources>();
			break;
		}
		case BulletTypes::Empowered:
		{
			sptrBulletResource = std::make_shared<Empowered::Resources>();
			break;
		}
		case BulletTypes::Standard:
		{
			sptrBulletResource = std::make_shared<Standard::Resources>();
			break;
		}
		default:
		{
			sptrBulletResource = std::make_shared<Bullet::Resources>();
			break;
		}
	} // End of switch

	loadAnimation(sptrBulletResource->m_sptrLoopAnimation, JSON_LOOP_KEY, JSON_BULLET_ANIMATION, JSON_BULLET_TEXTURE);
	loadAnimation(sptrBulletResource->m_sptrImpactAnimation, JSON_IMPACT_KEY, JSON_BULLET_ANIMATION, JSON_BULLET_TEXTURE);

	std::pair<BulletTypes, std::shared_ptr<bullets::Bullet::Resources>> pair = std::make_pair(bulletType, std::move(sptrBulletResource));
	sptrBulletResourceMap->insert(std::move(pair));
}

/// <summary>
/// @brief Setups Background::Resources.
/// 
/// Loads all necessary resources for the background.
/// @warning No checks are made as to the validity of the parameters.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrBackgroundResources">shared pointer to our background resources, assumed to be a valid pointer (initialized).</param>
/// <param name="gameSceneParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupBackground(ResourceHandler & resourceHandler, std::shared_ptr<Background::Resources> sptrBackgroundResources, json::json & gameSceneParser)
{
	std::string const BACKGROUND_ID("background");

	// Loading background Raw Text File
	std::ifstream backgroundRawFile(gameSceneParser.at(BACKGROUND_ID).get<std::string>());
	// Defines the Background's Json Parser
	json::json backgroundJson;
	backgroundRawFile >> backgroundJson; // Parsing raw text file into json parser.

	sptrBackgroundResources->m_sptrBgShader = resourceHandler.loadUp<sf::Shader>(backgroundJson, BACKGROUND_ID);
}

/// <summary>
/// @brief Setups Pickup::Resources.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrBackgroundResources">shared pointer to our pickup resources, assumed to be a valid pointer (initialized).</param>
/// <param name="gameSceneParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupPickups(ResourceHandler & resourceHandler, std::shared_ptr<Pickup::Resources> sptrPickupResources, json::json & gameSceneParser)
{
	std::string const PICKUP_JSON_ID("pickup");
	std::string const JSON_WEAPONS("weapons");
	std::string const JSON_EFFECT("effect");

	std::ifstream pickupRawFile(gameSceneParser.at(PICKUP_JSON_ID).get<std::string>());
	// Define the pickup json parser
	json::json pickupJson;
	pickupRawFile >> pickupJson;

	this->setupPickupEffect(resourceHandler, sptrPickupResources->m_effect, pickupJson.at(JSON_EFFECT));

	json::json & pickupWepJson = pickupJson.at(JSON_WEAPONS);

	auto const MAX_BULLET_TYPES = static_cast<int>(BulletTypes::AmountOfTypes);
	int i = 0;
	for (auto itt = pickupWepJson.begin(), end = pickupWepJson.end(); itt != end; ++itt)
	{
		BulletTypes const BULLET_TYPE = static_cast<BulletTypes>(i);
		this->setupPickup(resourceHandler, sptrPickupResources->m_pickups, *itt, BULLET_TYPE);
		if (i < MAX_BULLET_TYPES)
		{
			i++;
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="pickupMap">reference to pickup resource map.</param>
/// <param name="pickupParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupPickup(ResourceHandler & resourceHandler, Pickup::Resources::PickupMap & pickupMap, json::json & pickupParser, BulletTypes const & pickupTypes)
{
	std::string const JSON_WEAPON_KEY("key");

	std::string const JSON_WEAPON_TEXTURE("texture");
	json::json & weaponTextureParser = pickupParser.at(JSON_WEAPON_TEXTURE);

	std::string const JSON_TEXTURE_PATH("path");
	std::string const JSON_TEXTURE_SCALE("scale");
	std::string const JSON_TEXTURE_ORIGIN("origin");

	std::string const JSON_TEXTURE_FRAME("frame");
	json::json & textureFrameParser = weaponTextureParser.at(JSON_TEXTURE_FRAME);

	Pickup::Resources::IndividualPickup pickupData;
	pickupData.m_id = pickupParser.at(JSON_WEAPON_KEY).get<std::string>();

	pickupData.m_scale.x = weaponTextureParser.at(JSON_TEXTURE_SCALE).at("x").get<float>();
	pickupData.m_scale.y = weaponTextureParser.at(JSON_TEXTURE_SCALE).at("y").get<float>();

	pickupData.m_origin.x = weaponTextureParser.at(JSON_TEXTURE_ORIGIN).at("x").get<float>();
	pickupData.m_origin.y = weaponTextureParser.at(JSON_TEXTURE_ORIGIN).at("y").get<float>();

	pickupData.m_frame.left = textureFrameParser.at("x").get<int>();
	pickupData.m_frame.top = textureFrameParser.at("y").get<int>();
	pickupData.m_frame.width = textureFrameParser.at("w").get<int>();
	pickupData.m_frame.height = textureFrameParser.at("h").get<int>();

	pickupData.m_texture = resourceHandler.loadUp<sf::Texture>(weaponTextureParser.at(JSON_TEXTURE_PATH).get<std::string>(), pickupData.m_id);

	// Now everything is ready to be inserted to the map

	auto mapPair = std::make_pair(pickupTypes, pickupData);
	pickupMap.insert(std::move(mapPair));
}

/// <summary>
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using file path and an ID.</param>
/// <param name="pickupMap">reference to pickup effect.</param>
/// <param name="pickupParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupPickupEffect(ResourceHandler & resourceHandler, Pickup::Resources::Effect & effect, json::json & effectParser)
{
	// ID used to by resource handler to id the texture and the animation.
	std::string const EFFECT_ID("pickup-effect");

	// Parse Texture Json node

	std::string const JSON_TEXTURE("texture");
	json::json & effectTextureParser = effectParser.at(JSON_TEXTURE);

	std::string const JSON_TEXTURE_PATH("path");
	std::string const JSON_TEXTURE_ORIGIN("origin");
	std::string const JSON_TEXTURE_SCALE("scale");
	std::string const JSON_TEXTURE_FRAME("frame");
	
	effect.m_texture.m_id = EFFECT_ID;
	effect.m_texture.m_origin.x = effectTextureParser.at(JSON_TEXTURE_ORIGIN).at("x").get<float>();
	effect.m_texture.m_origin.y = effectTextureParser.at(JSON_TEXTURE_ORIGIN).at("y").get<float>();
	sf::Vector2f scale = { 0.0f,0.0f };
	scale.x = effectTextureParser.at(JSON_TEXTURE_SCALE).at("x").get<float>();
	scale.y = effectTextureParser.at(JSON_TEXTURE_SCALE).at("y").get<float>();
	effect.m_texture.m_scale = std::move(scale);
	sf::IntRect frame = { 0,0,0,0 };
	frame.left = effectTextureParser.at(JSON_TEXTURE_FRAME).at("x").get<int>();
	frame.top = effectTextureParser.at(JSON_TEXTURE_FRAME).at("y").get<int>();
	frame.width = effectTextureParser.at(JSON_TEXTURE_FRAME).at("w").get<int>();
	frame.height = effectTextureParser.at(JSON_TEXTURE_FRAME).at("h").get<int>();
	effect.m_texture.m_frame = std::move(frame);
	effect.m_texture.m_texture =
		resourceHandler.loadUp<sf::Texture>(effectTextureParser.at(JSON_TEXTURE_PATH).get<std::string>(), EFFECT_ID);
	assert(nullptr != effect.m_texture.m_texture);

	// Parse Animation Json node

	std::string const JSON_ANIMATION("animation");
	json::json & effectAnimationParser = effectParser.at(JSON_ANIMATION);

	std::string const JSON_ANIMATION_DURATION("duration");
	std::string const JSON_ANIMATION_WIDTH("width");
	std::string const JSON_ANIMATION_HEIGHT("height");
	std::string const JSON_ANIMATION_ORIGIN("origin");
	std::string const JSON_ANIMATION_FRAMES("frames");

	effect.m_animation.m_id = EFFECT_ID;
	effect.m_animation.m_duration = sf::seconds(effectAnimationParser.at(JSON_ANIMATION_DURATION).get<float>());
	effect.m_animation.m_origin.x = effectAnimationParser.at(JSON_ANIMATION_ORIGIN).at("x").get<float>();
	effect.m_animation.m_origin.y = effectAnimationParser.at(JSON_ANIMATION_ORIGIN).at("y").get<float>();
	effect.m_animation.m_sptrTexture = effect.m_texture.m_texture; // Use the texture already loaded.
	
	effect.m_animation.m_sptrFrames = std::make_shared<thor::FrameAnimation>();
	json::json & effectAnimationFrames = effectAnimationParser.at(JSON_ANIMATION_FRAMES);
	auto const FRAME_WIDTH = effectAnimationParser.at(JSON_ANIMATION_WIDTH).get<int>();
	auto const FRAME_HEIGHT = effectAnimationParser.at(JSON_ANIMATION_HEIGHT).get<int>();
	float i = 0.0f;
	for (
		auto itt = effectAnimationFrames.begin(), end = effectAnimationFrames.end();
		itt != end;
		++itt, ++i
		)
	{
		auto & jsonNode = *itt;
		sf::IntRect rect;
		rect.left = jsonNode.at("x").get<int>();
		rect.top = jsonNode.at("y").get<int>();
		rect.width = FRAME_WIDTH;
		rect.height = FRAME_HEIGHT;

		effect.m_animation.m_sptrFrames->addFrame(i, rect);
	}

}

