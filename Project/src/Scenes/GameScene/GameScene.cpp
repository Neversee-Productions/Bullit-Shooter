#include "Scenes\GameScene\GameScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Constructs a base Scene using the name of "Game".
/// </summary>
GameScene::GameScene(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller)
	: Scene("Game")
	, m_background()
	, m_player(*keyHandler, *controller, m_background)
	, m_keyHandler(*keyHandler)
	, m_soundManager(SoundManager::instance())
	, m_resources(nullptr)
	, m_windowC2Rect(App::getViewC2Rect())
	, m_asteroidManager()
	, m_enemy(m_player)
	, m_pickup()
	, m_ui(keyHandler,controller, std::bind(&GameScene::backToMainMenu, this))
	, m_collisionSystem(m_player, m_asteroidManager, m_pickup, m_ui)
	, m_gamePaused(false)
{
	m_pickup.setActive(false);
	m_asteroidManager.initAsteroidVector();
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
#ifdef _DEBUG
	std::cout << "Starting Game Scene" << std::endl;
#endif // _DEBUG
	Scene::setNextSceneName("");
	//HERE WE REINITIALIZE THE GAME (FOR RESTARTING)
	m_background.reset();
	m_player.reset();
	m_asteroidManager.resetAsteroids();
	m_ui.setPaused(false);
	
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
#ifdef _DEBUG
	std::cout << "Stopping Game Scene" << std::endl;
#endif // _DEBUG
}

/// <summary>
/// @brief Update game scene entities.
/// 
/// 
/// </summary>
void GameScene::update()
{
	if (m_keyHandler.isPressed(sf::Keyboard::Escape) && !m_keyHandler.isPrevPressed(sf::Keyboard::Escape))
	{
		m_gamePaused = !m_gamePaused;
		m_ui.setPaused(m_gamePaused);
	}
	if (!m_gamePaused)
	{
		m_background.update();
		if (m_player.getShieldHealth() <= 0)
		{
			m_player.setAlive(false);
		}
		m_player.update();
		m_asteroidManager.update();
		m_enemy.update();
		m_pickup.update();
		m_collisionSystem.update();
	}
	else
	{
		if (!m_ui.getPaused())
		{
			m_gamePaused = false;
		}
	}
	m_ui.update();
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
	if (m_gamePaused)
	{
		m_background.draw(window, 0);
		m_asteroidManager.draw(window, 0);
		m_player.draw(window, 0);
		m_enemy.draw(window, 0);
		m_ui.draw(window, 0);
		m_pickup.draw(window, 0);
	}
	else
	{
		m_background.draw(window, deltaTime);
		m_asteroidManager.draw(window, deltaTime);
		m_player.draw(window, deltaTime);
		m_enemy.draw(window, deltaTime);
		m_ui.draw(window, deltaTime);
		m_pickup.draw(window, deltaTime);
	}
}

/// <summary>
/// 
/// </summary>
void GameScene::backToMainMenu()
{
	Scene::setNextSceneName("MainMenu");
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

	json::json gameSceneParser = util::loadJsonFromFile(filePath);

	if (!m_resources)
	{
		m_resources = std::make_unique<Resources>();

		////////////////////////////////////////////
		// Setup Sounds
		////////////////////////////////////////////
		this->setupSounds(resourceHandler, m_soundManager, util::loadJsonFromFile(gameSceneParser.at("sounds").get<std::string>()));

		////////////////////////////////////////////
		// Setup Enemies
		////////////////////////////////////////////
		this->setupEnemies(resourceHandler, m_resources->m_sptrEnemies, gameSceneParser);

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

		////////////////////////////////////////////
		// Setup UI
		////////////////////////////////////////////
		this->setupUI(resourceHandler, m_resources->m_sptrUI, gameSceneParser);
	}

	m_enemy.init(m_resources->m_sptrEnemies->m_sptrBasicEnemy);
	m_background.init(m_resources->m_sptrBackground);
	m_player.init(m_resources->m_sptrPlayer);
	m_pickup = Pickup(m_resources->m_sptrPickup, sf::Vector2f(500, 500), sf::Vector2f(100, 100), BulletTypes::Empowered);
	m_pickup.setActive(false);
	m_ui.init(m_resources->m_sptrUI);
}

/// <summary>
/// @brief Setups sounds in the game scene.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="soundParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupSounds(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & soundParser)
{	
	this->setupPlayerSounds(resourceHandler, soundManager, soundParser.at("player"));
}

/// <summary>
/// @brief Setups player sounds.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="playerParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupPlayerSounds(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & playerParser)
{
	this->setupBulletsSounds(resourceHandler, soundManager, playerParser.at("bullets"));
}

/// <summary>
/// @brief Setups all the player bullet sounds.
/// 
/// Iterates through all the bullet sounds.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="bulletsParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupBulletsSounds(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & bulletsParser)
{
	auto const & NUM_OF_BULLETS = static_cast<int>(BulletTypes::AmountOfTypes);

	// initialize string stream to be 8 characters wide,
	//	NOTE: the stream seek position is still at the start of the stream
	//	meaning any insertion is done from the beginning of the stream
	std::stringstream bulletID("--------");
	bulletID << "bullet";
	for (int i = 0; i < NUM_OF_BULLETS; ++i)
	{
		int const BULLET_NUM = i + 1;
		if (BULLET_NUM < 10)
		{
			bulletID << "0" + std::to_string(BULLET_NUM);
		}
		else
		{
			bulletID << std::to_string(BULLET_NUM);
		}
		std::string const bulletIDString = bulletID.str();
		this->setupBulletSounds(resourceHandler, soundManager, bulletsParser.at(bulletIDString), bulletIDString);

		// move string stream's seek position back 2 places.
		bulletID.seekp(-2, std::ios_base::end);
	}
}

/// <summary>
/// @brief Setups a single player bullet based on bulletNum.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="bulletParser">reference to loaded json file ready to be parsed.</param>
/// <param name="bulletNum">read-only reference to the bullet number string used as the </param>
void GameScene::setupBulletSounds(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & bulletParser, std::string const & bulletNum)
{
	std::string const BULLET_FIRE_ID = bulletNum + "_fire";
	soundManager.addSound(bulletParser.at("fire").get<SoundSetting>(), BULLET_FIRE_ID);
}


/// <summary>
/// @brief Setups Player::Resources.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrPlayerResources">shared pointer to our player resources, assumed to be a valid pointer (initialized).</param>
/// <param name="gameSceneParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupPlayer(ResourceHandler & resourceHandler, std::shared_ptr<Player::Resources> sptrPlayerResources, json::json & gameSceneParser)
{
	std::string const PLAYER_ID("player");

	json::json playerJson = util::loadJsonFromFile(gameSceneParser.at(PLAYER_ID).get<std::string>());

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
std::unique_ptr<Weapon::Resources::IndividualWeapon> GameScene::setupWeaponAnim(ResourceHandler & resourceHandler, json::json & weaponParser, std::string const & id)
{
	Weapon::Resources::IndividualWeapon weaponResource;

	std::string const ANIM_STR = "animation";
	std::string const COLOR_STR = "colors";
	std::string const WEAPONS_STR = "weapons";

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
	
	weaponResource.m_uptrBeginAnimation.swap(uptrBeginAnimation);

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

	weaponResource.m_uptrShootAnimation.swap(uptrShootAnimation);

	auto & jsonWepColor = weaponParser.at(COLOR_STR).at(WEAPONS_STR).at(id);
	auto uptrBgColor = std::make_unique<sf::Color>();
	auto & bgColor = *uptrBgColor;
	bgColor.r = jsonWepColor.at("r").get<sf::Uint8>();
	bgColor.g = jsonWepColor.at("g").get<sf::Uint8>();
	bgColor.b = jsonWepColor.at("b").get<sf::Uint8>();
	weaponResource.m_uptrBgColor.swap(uptrBgColor);
	
	return std::make_unique<Weapon::Resources::IndividualWeapon>(std::move(weaponResource));
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
/// <param name="id">read-only reference to the id of bullet to set up.</param>
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

	json::json backgroundJson = util::loadJsonFromFile(gameSceneParser.at(BACKGROUND_ID).get<std::string>());

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

/// <summary>
/// @brief 
/// 
/// 
/// </summary>
/// <param name="resourceHandler"></param>
/// <param name="sptrEnemies"></param>
/// <param name="gameSceneParser"></param>
void GameScene::setupEnemies(ResourceHandler & resourceHandler, std::shared_ptr<Resources::Enemies> sptrEnemies, json::json & gameSceneParser)
{
	std::string const JSON_ENEMIES("enemies");
	json::json enemiesJson = util::loadJsonFromFile(gameSceneParser.at(JSON_ENEMIES).get<std::string>());

	std::string const JSON_ENEMY_BASIC("basic");

	ai::AiBasic::setup(sptrEnemies->m_sptrBasicEnemy, resourceHandler, util::loadJsonFromFile(enemiesJson.at(JSON_ENEMY_BASIC).get<std::string>()));
}

/// <summary>
/// @brief this function gets the json for the UI.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to the resource handler</param>
/// <param name="sptrUI">shared pointer to UI</param>
/// <param name="gameSceneParser">reference to loaded json file ready to be parsed</param>
void GameScene::setupUI(ResourceHandler & resourceHandler, std::shared_ptr<GameUI::Resources> sptrUI, json::json & gameSceneParser)
{
	std::string const JSON_UI("UI");
	json::json UIJsonParser = util::loadJsonFromFile(gameSceneParser.at(JSON_UI).get<std::string>());

	GameUI::setup(sptrUI, resourceHandler, UIJsonParser);
}

