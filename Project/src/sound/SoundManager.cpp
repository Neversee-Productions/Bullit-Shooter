#include "sound\SoundManager.h"


/// <summary>
/// @brief Instantiate the single instance of our Sound Manager.
/// 
/// 
/// </summary>
SoundManager & SoundManager::s_soundManager = SoundManager();

/// <summary>
/// @brief Default constructor.
/// 
/// Initialize member functions.
/// </summary>
SoundManager::SoundManager()
	: m_soundMap()
{
}

/// <summary>
/// @brief Method of retrieval of our SoundManager instance.
/// 
/// 
/// </summary>
/// <returns>ref to the single instance of our SoundManager.</returns>
SoundManager & SoundManager::instance()
{
	return s_soundManager;
}

/// <summary>
/// @brief Setups sounds in the game scene.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="soundParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setup(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & soundParser)
{
	setupPlayer(resourceHandler, soundManager, soundParser.at("player"));
	setupAsteroid(resourceHandler, soundManager, soundParser.at("asteroid"));
	setupBasicEnemy(resourceHandler, soundManager, soundParser.at("basic-enemy"));
}

/// <summary>
/// @brief update sound positions.
/// 
/// 
/// </summary>
void SoundManager::update()
{
	for (auto & pair : m_soundMap)
	{
		auto & key = pair.first;
		auto & value = pair.second;
		for (auto & soundPlayer : value.soundPlayers)
		{
			soundPlayer.setPosition({ value.settings.m_pPosition->x, value.settings.m_pPosition->y, 0.0f });
		}
	}
}

/// <summary>
/// @brief Adds a sound to our map of sounds.
/// 
/// 
/// </summary>
/// <param name="settings">settings for our sound.</param>
/// <param name="id">read-only reference to the string id of the sound.</param>
void SoundManager::addSound(SoundSetting settings, std::string const & id)
{
	assert(false == this->checkSoundInMap(id)); // Disallow for duplicated id's
	std::list<sf::Sound> listOfSounds;
	m_soundMap.insert(std::make_pair(id, Sound({ settings, std::move(listOfSounds) })));
}

/// <summary>
/// @brief 
/// 
/// 
/// </summary>
/// <param name="id">read-only reference to the string id of the sound.</param>
void SoundManager::play(std::string const & id)
{
	assert(true == this->checkSoundInMap(id)); // Must be within the map.

	auto & soundList = m_soundMap.at(id).soundPlayers;
	auto const & settings = m_soundMap.at(id).settings;
	
	for (sf::Sound & sound : soundList)
	{
		if (sound.getStatus() != sf::Sound::Status::Playing)
		{
			sound.play();
			return;
		}
	}
	sf::Sound sfmlSound;
	sfmlSound.setVolume(settings.m_volume);
	sfmlSound.setAttenuation(settings.m_attenuation);
	sfmlSound.setLoop(settings.m_loop);
	sfmlSound.setBuffer(*settings.m_sptrBuffer);
	if (nullptr != settings.m_pPosition)
	{
		sfmlSound.setPosition(settings.m_pPosition->x, settings.m_pPosition->y, 0.0f);
	}
	soundList.push_back(std::move(sfmlSound));
	soundList.back().play();
}

/// <summary>
/// @brief Setups player sounds.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="playerParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPlayer(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & playerParser)
{
	setupPlayerBullets(resourceHandler, soundManager, playerParser.at("bullets"));
}

/// <summary>
/// @brief Setups all the player bullet sounds.
/// 
/// Iterates through all the bullet sounds.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="bulletsParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPlayerBullets(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & playerBulletsParser)
{
	auto const & NUM_OF_BULLETS = static_cast<int>(BulletTypes::AmountOfTypes);

	// initialize string stream to be 8 characters wide,
	//	NOTE: the stream seek position is still at the start of the stream
	//	meaning any insertion is done from the beginning of the stream
	std::stringstream bulletID("--------");
	bulletID << "bullet";
	for (int i = 0; i < NUM_OF_BULLETS; ++i)
	{
		auto const BULLET_TYPE = static_cast<BulletTypes>(i);
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
		setupBulletSounds(resourceHandler, soundManager, playerBulletsParser.at(bulletIDString), bulletIDString, BULLET_TYPE);

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
void SoundManager::setupBulletSounds(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & bulletParser, std::string const & bulletNum, BulletTypes const & type)
{
	std::string const BULLET_FIRE_ID = bulletNum + "_fire";
	soundManager.addSound(bulletParser.at("fire").get<SoundSetting>(), BULLET_FIRE_ID);
	switch (type)
	{
		case BulletTypes::Standard:
		case BulletTypes::Empowered:
		case BulletTypes::FireBlast:
		case BulletTypes::MagmaShot:
		case BulletTypes::NapalmSphere:
		case BulletTypes::CometShot:
		case BulletTypes::NullWave:
		case BulletTypes::PyroBlast:
		{
			std::string const BULLET_IMPACT_ID = bulletNum + "_impact";
			soundManager.addSound(bulletParser.at("impact").get<SoundSetting>(), BULLET_IMPACT_ID);
		}	break;
		case BulletTypes::DeathOrb:
		case BulletTypes::HolySphere:
		case BulletTypes::StaticSphere:
		case BulletTypes::AmountOfTypes:
		default:
		{
		}	break;
	}
}

/// <summary>
/// @brief Setups a single asteroid.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="asteroidParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupAsteroid(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & asteroidParser)
{
	std::string const ASTEROID_EXPLOSION_ID = "asteroid_explosion";
	soundManager.addSound(asteroidParser.at("explosion").get<SoundSetting>(), ASTEROID_EXPLOSION_ID);
}

/// <summary>
/// @brief Setups a basic enemy sound.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="basicEnemyParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupBasicEnemy(ResourceHandler & resourceHandler, SoundManager & soundManager, json::json & basicEnemyParser)
{
	std::string const BASIC_ENEMY_DEATH_ID = "enemy_death";
	soundManager.addSound(basicEnemyParser.at("death").get<SoundSetting>(), BASIC_ENEMY_DEATH_ID);
}

/// <summary>
/// @brief Checks if sound with id is within SoundManager::m_soundMap.
/// 
/// 
/// </summary>
/// <param name="id">read-only reference to the string id of the sound.</param>
bool SoundManager::checkSoundInMap(std::string const & id) const
{
	return m_soundMap.find(id) != m_soundMap.end();
}
