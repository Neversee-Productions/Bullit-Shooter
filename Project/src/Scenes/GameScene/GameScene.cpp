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
	, m_basicEnemyManager()
	, m_rangedEnemyManager(m_player)
	, m_pickup()
	, m_ui(keyHandler,controller, std::bind(&GameScene::backToMainMenu, this), std::bind(&GameScene::restartGame, this))
	, m_collisionSystem(m_player, m_asteroidManager, m_basicEnemyManager, m_rangedEnemyManager, m_pickup, m_ui)
	, m_gamePaused(false)
	, m_gameEnded(false)
	, m_controller(*controller)
{
	m_pickup.setActive(false);
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
	if (!m_resources)
	{
		this->setup(resourceFilePath);
	}
	//HERE WE REINITIALIZE THE GAME (FOR RESTARTING)
	m_soundManager.stop("bg-soundtrack");
	m_soundManager.play("bg_game_soundtrack", false);
	m_background.reset();
	m_player.reset();
	m_asteroidManager.resetAsteroids();
	m_basicEnemyManager.reset();
	m_gamePaused = false;
	m_gameEnded = false;
	m_collisionSystem.setPickingUp(false);
	m_rangedEnemyManager.reset();
	m_rangedEnemyManager.spawn({ 0.0f, -350.0f }); // TODO: Remove spawning ranged enemy instantly
	m_ui.reset();
	m_pickup.resetPickup();
	auto random = (rand() % 3 + 1); //generate number between 1 and 2
	if (random == 1)
	{
		m_soundManager.play("kill-bugs");
	}
	else if (random == 2)
	{
		m_soundManager.play("lets-go");
	}
	else
	{
		m_soundManager.play("stay-clear");
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
	m_soundManager.stop("bg_game_soundtrack");
}

/// <summary>
/// @brief Update game scene entities.
/// 
/// 
/// </summary>
void GameScene::update()
{
	if (((m_keyHandler.isPressed(sf::Keyboard::Escape) && !m_keyHandler.isPrevPressed(sf::Keyboard::Escape)) || (m_controller.m_currentState.m_l1 && !m_controller.m_previousState.m_l1)) && !m_gameEnded)
	{
		m_gamePaused = !m_gamePaused;
		m_ui.setPaused(m_gamePaused);
		if (m_gamePaused == true)
		{
			m_ui.setPauseFlashing(true);
		}
		else
		{
			m_ui.setPauseFlashing(false);
		}
	}
	if (!m_gamePaused && !m_ui.getShowEnd())
	{
		m_background.update();
		m_player.update();
		m_asteroidManager.update();
		m_basicEnemyManager.update();
		m_rangedEnemyManager.update();
		m_pickup.update();
		m_collisionSystem.update();
		updateUI();
		if (!m_player.isAlive())
		{
			m_gameEnded = true;
			m_ui.setPauseFlashing(true);
			m_player.setOverheat(false);
			m_ui.setShowEnd(m_gameEnded);
		}
	}
	else
	{
		if (!m_ui.getPaused())
		{
			m_ui.setPauseFlashing(false);
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
	if (m_gamePaused || m_ui.getShowEnd())
	{
		m_background.draw(window, 0);
		m_pickup.draw(window, 0);
		m_basicEnemyManager.draw(window, 0);
		m_rangedEnemyManager.draw(window, 0);
		m_asteroidManager.draw(window, 0);
		m_player.draw(window, 0);
		m_ui.draw(window, 0);
	}
	else
	{
		m_background.draw(window, deltaTime);
		m_pickup.draw(window, deltaTime);
		m_basicEnemyManager.draw(window, deltaTime);
		m_rangedEnemyManager.draw(window, deltaTime);
		m_asteroidManager.draw(window, deltaTime);
		m_player.draw(window, deltaTime);
		m_ui.draw(window, deltaTime);
	}
}

/// <summary>
/// 
/// </summary>
void GameScene::backToMainMenu()
{
	Scene::setNextSceneName("MainMenu");
}

void GameScene::restartGame()
{
	Scene::setNextSceneName("Game");
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

	js::json gameSceneParser = util::loadJsonFromFile(filePath);

	if (!m_resources)
	{
		m_resources = std::make_unique<Resources>();

		////////////////////////////////////////////
		// Setup Sounds
		////////////////////////////////////////////
		SoundManager::setup(resourceHandler, m_soundManager, util::loadJsonFromFile(gameSceneParser.at("sounds").get<std::string>()));

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

	m_basicEnemyManager.init(m_resources->m_sptrEnemies->m_sptrBasicEnemyManager, m_player);
	m_rangedEnemyManager.init(m_resources->m_sptrEnemies->m_sptrRangedEnemy);
	m_asteroidManager.init(m_resources->m_sptrEnemies->m_sptrAsteroid);
	m_player.init(m_resources->m_sptrPlayer);
	m_background.init(m_resources->m_sptrBackground);
	m_player.init(m_resources->m_sptrPlayer);
	m_pickup = Pickup(m_resources->m_sptrPickup, sf::Vector2f(500, 500), sf::Vector2f(100, 100), BulletTypes::Empowered);
	m_pickup.setActive(false);
	m_ui.init(m_resources->m_sptrUI);
}

/// <summary>
/// @brief method to update the ui.
/// 
/// 
/// </summary>
void GameScene::updateUI()
{
	m_ui.setFireRate(m_player.getFireRate());
	m_ui.setTimeSinceFire(m_player.getTimeSinceFire());
	m_ui.updateOvercharge(m_player.getOvercharge());
	m_ui.setOverheat(m_player.getOverheat());
}


/// <summary>
/// @brief Setups Player::Resources.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="sptrPlayerResources">shared pointer to our player resources, assumed to be a valid pointer (initialized).</param>
/// <param name="gameSceneParser">reference to loaded json file ready to be parsed.</param>
void GameScene::setupPlayer(ResourceHandler & resourceHandler, std::shared_ptr<Player::Resources> sptrPlayerResources, js::json & gameSceneParser)
{
	std::string const PLAYER_ID("player");

	js::json playerJson = util::loadJsonFromFile(gameSceneParser.at(PLAYER_ID).get<std::string>());

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
void GameScene::setupShip(ResourceHandler & resourceHandler, std::shared_ptr<Ship::Resources> sptrShipResources, js::json & shipParser)
{
	std::string const SHIP_ID("ship");

	sptrShipResources->m_sptrTexture = resourceHandler.loadUp<sf::Texture>(shipParser, SHIP_ID);
	assert(nullptr != sptrShipResources->m_sptrTexture);
	sptrShipResources->m_sptrTexture->setSmooth(true);

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
void GameScene::setupWeapons(ResourceHandler & resourceHandler, std::shared_ptr<Weapon::Resources> sptrWeaponResources, js::json & weaponParser)
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
std::unique_ptr<Weapon::Resources::IndividualWeapon> GameScene::setupWeaponAnim(ResourceHandler & resourceHandler, js::json & weaponParser, std::string const & id)
{
	auto loadFirstFrame = [](js::json const & parser)
	{
		std::string const JSON_WIDTH("width");
		std::string const JSON_HEIGHT("height");
		std::string const JSON_FRAME("frames");

		sf::IntRect rect;
		rect.left = parser.at(JSON_WIDTH).get<int>();
		rect.top = parser.at(JSON_HEIGHT).get<int>();
		rect.width = parser.at(JSON_FRAME).front().at("x").get<int>();
		rect.height = parser.at(JSON_FRAME).front().at("y").get<int>();
		return rect;
	};

	Weapon::Resources::IndividualWeapon weaponResource;

	std::string const ANIM_STR = "animation";
	std::string const COLOR_STR = "colors";
	std::string const WEAPONS_STR = "weapons";

	std::string const BEGIN_ID = id + "_begin";
	auto uptrBeginAnimation = std::make_unique<Weapon::Resources::Animation>();
	auto & beginAnimation = *uptrBeginAnimation;
	beginAnimation.m_id = BEGIN_ID;
	beginAnimation.m_frame = loadFirstFrame(weaponParser.at(ANIM_STR).at(BEGIN_ID));
	beginAnimation.m_sptrFrames = resourceHandler.loadUp<thor::FrameAnimation>(weaponParser, BEGIN_ID);
	beginAnimation.m_duration = sf::seconds(weaponParser.at(ANIM_STR).at(BEGIN_ID).at("duration").get<float>());
	auto const & beginAnimationFrameWidth = weaponParser.at(ANIM_STR).at(BEGIN_ID).at("width").get<float>();
	auto const & beginAnimationFrameHeight = weaponParser.at(ANIM_STR).at(BEGIN_ID).at("height").get<float>();
	auto & jsonBeginOrigin = weaponParser.at(ANIM_STR).at(BEGIN_ID).at("origin");
	auto beginAnimationOrigin = sf::Vector2f(jsonBeginOrigin.at("x").get<float>(), jsonBeginOrigin.at("y").get<float>());
	beginAnimation.m_origin = std::move(beginAnimationOrigin);
	beginAnimation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(weaponParser, BEGIN_ID);
	beginAnimation.m_sptrTexture->setSmooth(true);
	
	weaponResource.m_uptrBeginAnimation.swap(uptrBeginAnimation);

	std::string const SHOOT_ID = id + "_shoot";
	auto uptrShootAnimation = std::make_unique<Weapon::Resources::Animation>();
	auto & shootAnimation = *uptrShootAnimation;
	shootAnimation.m_id = SHOOT_ID;
	shootAnimation.m_frame = loadFirstFrame(weaponParser.at(ANIM_STR).at(SHOOT_ID));
	shootAnimation.m_sptrFrames = resourceHandler.loadUp<thor::FrameAnimation>(weaponParser, SHOOT_ID);
	shootAnimation.m_duration = sf::seconds(weaponParser.at(ANIM_STR).at(SHOOT_ID).at("duration").get<float>());
	auto const & shootAnimationFrameWidth = weaponParser.at(ANIM_STR).at(SHOOT_ID).at("width").get<float>();
	auto const & shootAnimationFrameHeight = weaponParser.at(ANIM_STR).at(SHOOT_ID).at("height").get<float>();
	auto & jsonShootOrigin = weaponParser.at(ANIM_STR).at(SHOOT_ID).at("origin");
	auto shootAnimationOrigin = sf::Vector2f(jsonShootOrigin.at("x").get<float>(), jsonShootOrigin.at("y").get<float>());
	shootAnimation.m_origin = std::move(shootAnimationOrigin);
	shootAnimation.m_sptrTexture = resourceHandler.loadUp<sf::Texture>(weaponParser, SHOOT_ID);
	shootAnimation.m_sptrTexture->setSmooth(true);

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
void GameScene::setupConnector(ResourceHandler & resourceHandler, std::shared_ptr<Connector::Resources> sptrConnectorResources, js::json & connectorParser)
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
void GameScene::setupBulletManager(ResourceHandler & resourceHandler, std::shared_ptr<BulletManager::Resources> sptrBulletManagerResources, js::json & bulletManagerParser)
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
	, js::json & bulletParser
	, std::string const & id)
{
	auto sptrBulletResource = std::shared_ptr<bullets::Bullet::Resources>(nullptr);

	std::string const TEXTURES_JSON_KEY("textures");
	// Reference to json textures section
	js::json const & JSON_BULLET_TEXTURE = bulletParser.at(TEXTURES_JSON_KEY).at(id);

	std::string const ANIMATIONS_JSON_KEY("animation");
	std::string const BULLETS_JSON_KEY("bullets");
	// Reference to json animations section
	js::json const & JSON_BULLET_ANIMATION = bulletParser.at(ANIMATIONS_JSON_KEY).at(BULLETS_JSON_KEY).at(id);

	std::string const JSON_LOOP_KEY("loop");
	std::string const JSON_IMPACT_KEY("impact");


	// Lambda used for initializing animation frames
	auto frameAnimationLambda = [this](thor::FrameAnimation & frameAnimation, js::json const & JSON_ANIMATION) -> void
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
		, js::json const & bulletAnimationNode
		, js::json const & bulletTextureNode
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
void GameScene::setupBackground(ResourceHandler & resourceHandler, std::shared_ptr<Background::Resources> sptrBackgroundResources, js::json & gameSceneParser)
{
	std::string const BACKGROUND_ID("background");

	js::json backgroundJson = util::loadJsonFromFile(gameSceneParser.at(BACKGROUND_ID).get<std::string>());

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
void GameScene::setupPickups(ResourceHandler & resourceHandler, std::shared_ptr<Pickup::Resources> sptrPickupResources, js::json & gameSceneParser)
{
	std::string const PICKUP_JSON_ID("pickup");
	std::string const JSON_WEAPONS("weapons");
	std::string const JSON_EFFECT("effect");

	std::ifstream pickupRawFile(gameSceneParser.at(PICKUP_JSON_ID).get<std::string>());
	// Define the pickup json parser
	js::json pickupJson;
	pickupRawFile >> pickupJson;

	this->setupPickupEffect(resourceHandler, sptrPickupResources->m_effect, pickupJson.at(JSON_EFFECT));

	js::json & pickupWepJson = pickupJson.at(JSON_WEAPONS);

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
void GameScene::setupPickup(ResourceHandler & resourceHandler, Pickup::Resources::PickupMap & pickupMap, js::json & pickupParser, BulletTypes const & pickupTypes)
{
	std::string const JSON_WEAPON_KEY("key");

	std::string const JSON_WEAPON_TEXTURE("texture");
	js::json & weaponTextureParser = pickupParser.at(JSON_WEAPON_TEXTURE);

	std::string const JSON_TEXTURE_PATH("path");
	std::string const JSON_TEXTURE_SCALE("scale");
	std::string const JSON_TEXTURE_ORIGIN("origin");

	std::string const JSON_TEXTURE_FRAME("frame");
	js::json & textureFrameParser = weaponTextureParser.at(JSON_TEXTURE_FRAME);

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
void GameScene::setupPickupEffect(ResourceHandler & resourceHandler, Pickup::Resources::Effect & effect, js::json & effectParser)
{
	// ID used to by resource handler to id the texture and the animation.
	std::string const EFFECT_ID("pickup-effect");

	// Parse Texture Json node

	std::string const JSON_TEXTURE("texture");
	js::json & effectTextureParser = effectParser.at(JSON_TEXTURE);

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
	js::json & effectAnimationParser = effectParser.at(JSON_ANIMATION);

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
	js::json & effectAnimationFrames = effectAnimationParser.at(JSON_ANIMATION_FRAMES);
	auto const FRAME_WIDTH = effectAnimationParser.at(JSON_ANIMATION_WIDTH).get<int>();
	auto const FRAME_HEIGHT = effectAnimationParser.at(JSON_ANIMATION_HEIGHT).get<int>();
	for (
		auto itt = effectAnimationFrames.begin(), end = effectAnimationFrames.end();
		itt != end;
		++itt
		)
	{
		auto & jsonNode = *itt;
		sf::IntRect rect;
		rect.left = jsonNode.at("x").get<int>();
		rect.top = jsonNode.at("y").get<int>();
		rect.width = FRAME_WIDTH;
		rect.height = FRAME_HEIGHT;

		effect.m_animation.m_sptrFrames->addFrame(1.0f, rect);
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
void GameScene::setupEnemies(ResourceHandler & resourceHandler, std::shared_ptr<Resources::Enemies> sptrEnemies, js::json & gameSceneParser)
{
	std::string const JSON_ENEMIES("enemies");
	js::json enemiesJson = util::loadJsonFromFile(gameSceneParser.at(JSON_ENEMIES).get<std::string>());

	std::string const JSON_ENEMY_ASTEROID("asteroid");
	std::string const JSON_ENEMY_BASIC("basic");
	std::string const JSON_ENEMY_RANGED("ranged");

	ai::AiBasic::setup(sptrEnemies->m_sptrBasicEnemyManager->m_sptrBasicEnemy, resourceHandler, util::loadJsonFromFile(enemiesJson.at(JSON_ENEMY_BASIC).get<std::string>()));
	ai::AiRanged::setup(sptrEnemies->m_sptrRangedEnemy, resourceHandler, util::loadJsonFromFile(enemiesJson.at(JSON_ENEMY_RANGED).get<std::string>()));
	Asteroid::setup(sptrEnemies->m_sptrAsteroid, util::loadJsonFromFile(enemiesJson.at(JSON_ENEMY_ASTEROID).get<std::string>()));
}

/// <summary>
/// @brief this function gets the json for the UI.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to the resource handler</param>
/// <param name="sptrUI">shared pointer to UI</param>
/// <param name="gameSceneParser">reference to loaded json file ready to be parsed</param>
void GameScene::setupUI(ResourceHandler & resourceHandler, std::shared_ptr<GameUI::Resources> sptrUI, js::json & gameSceneParser)
{
	std::string const JSON_UI("UI");
	js::json UIJsonParser = util::loadJsonFromFile(gameSceneParser.at(JSON_UI).get<std::string>());

	GameUI::setup(sptrUI, resourceHandler, UIJsonParser);
}

