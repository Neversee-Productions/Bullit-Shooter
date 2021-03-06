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
void SoundManager::setup(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & soundParser)
{
	setupBg(resourceHandler, soundManager, soundParser.at("background"));
	setupPlayer(resourceHandler, soundManager, soundParser.at("player"));
	setupAsteroid(resourceHandler, soundManager, soundParser.at("asteroid"));
	setupBasicEnemy(resourceHandler, soundManager, soundParser.at("basic-enemy"));
	setupUI(resourceHandler, soundManager, soundParser.at("ui"));
	setupPickup(resourceHandler, soundManager, soundParser.at("pickup"));
	setupVoices(resourceHandler, soundManager, soundParser.at("voices"));
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
/// @brief Starts playing a sound based on its id.
/// 
/// 
/// </summary>
/// <param name="id">read-only reference to the string id of the sound.</param>
/// <param name="stack">determines whether to stop the current playing sound.</param>
void SoundManager::play(std::string const & id, bool stack)
{
	assert(true == this->checkSoundInMap(id)); // Must be within the map.

	auto & soundList = m_soundMap.at(id).soundPlayers;
	auto const & settings = m_soundMap.at(id).settings;
	
	if (false == stack)
	{
		for (sf::Sound & sound : soundList)
		{
			if (sound.getStatus() != sf::Sound::Status::Playing)
			{
				sound.stop();
				sound.play();
				return;
			}
		}
	}
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
/// @brief Stops the sound based on id if its currently playing.
/// 
/// 
/// </summary>
/// <param name="id">read-only reference to the string id</param>
void SoundManager::stop(std::string const & id)
{
	SoundMap::iterator result = m_soundMap.find(id);
	if (result != m_soundMap.end())
	{
		auto & soundList = result->second.soundPlayers;
		for (auto & sound : soundList)
		{
			if (sound.getStatus() != sf::Sound::Status::Stopped)
			{
				sound.stop();
			}
		}
	}
}

/// <summary>
/// @brief searches if the sound is playing.
/// 
/// 
/// </summary>
/// <param name="id">read-only reference of the sound's id.</param>
/// <returns>true if the sound is playing, false if it's paused, stopped or does not exist.</returns>
bool SoundManager::checkSound(std::string const & id)
{
	SoundMap::const_iterator result = m_soundMap.find(id);
	if (result != m_soundMap.end())
	{
		for (auto & sound : result->second.soundPlayers)
		{
			if (sound.getStatus() == sf::Sound::Status::Playing)
			{
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// @brief Setups background sounds.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="bgParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupBg(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & bgParser)
{
	std::string const BG_SOUND_ID("bg_game_soundtrack");
	std::string const BG_END_SOUND_ID("bg_game_end_soundtrack");

	soundManager.addSound(bgParser.at("bg-soundtrack").get<SoundSetting>(), BG_SOUND_ID);
	soundManager.addSound(bgParser.at("bg-soundtrack-end").get<SoundSetting>(), BG_END_SOUND_ID);
}

/// <summary>
/// @brief Setups player sounds.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="playerParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPlayer(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & playerParser)
{
	setupPlayerBullets(resourceHandler, soundManager, playerParser.at("bullets"));
	setupPlayerWeapons(resourceHandler, soundManager, playerParser.at("weapons"));
	setupPlayerShip(resourceHandler, soundManager, playerParser.at("ship"));
}

/// <summary>
/// @brief Setups player ship sounds.
/// 
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="shipParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPlayerShip(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & shipParser)
{
	std::string const DASH_ID = "dash";
	std::string const DOCK_ID = "dock";

	soundManager.addSound(shipParser.at(DASH_ID).get<SoundSetting>(), "ship-dash-sound");
	soundManager.addSound(shipParser.at(DOCK_ID).get<SoundSetting>(), "ship-dock-sound");

}

/// <summary>
/// @brief Setups all the player bullet sounds.
/// 
/// Iterates through all the bullet sounds.
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="bulletsParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPlayerBullets(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & playerBulletsParser)
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
void SoundManager::setupBulletSounds(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & bulletParser, std::string const & bulletNum, BulletTypes const & type)
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
void SoundManager::setupAsteroid(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & asteroidParser)
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
void SoundManager::setupBasicEnemy(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & basicEnemyParser)
{
	std::string const BASIC_ENEMY_DEATH_ID = "enemy_death";
	soundManager.addSound(basicEnemyParser.at("death").get<SoundSetting>(), BASIC_ENEMY_DEATH_ID);
}

/// <summary>
/// @brief Setups ui sounds.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="uiParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupUI(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & uiParser)
{
	std::string const UI_ALARM_ID = "overcharge_alarm";
	soundManager.addSound(uiParser.at("alarm").get<SoundSetting>(), UI_ALARM_ID);
}

/// <summary>
/// @brief Setups ui sounds.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="pickupParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPickup(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & pickupParser)
{
	std::string const PICKUP_POWERUP_ID = "power-up";
	soundManager.addSound(pickupParser.at("power-up").get<SoundSetting>(), PICKUP_POWERUP_ID);
}

/// <summary>
/// @brief Setups weapon sounds.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="weaponParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupPlayerWeapons(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & weaponParser)
{
	std::string const WEAPON_BEGIN_ID = "weapon-begin";
	std::string const WEAPON_BEGIN2_ID = "weapon-begin2";
	std::string const WEAPON_BEGIN3_ID = "weapon-begin3";
	std::string const WEAPON_BEGIN4_ID = "weapon-begin4";
	std::string const WEAPON_BEGIN5_ID = "weapon-begin5";


	soundManager.addSound(weaponParser.at("weapon-begin").get<SoundSetting>(), WEAPON_BEGIN_ID);
	soundManager.addSound(weaponParser.at("weapon-begin2").get<SoundSetting>(), WEAPON_BEGIN2_ID);
	soundManager.addSound(weaponParser.at("weapon-begin3").get<SoundSetting>(), WEAPON_BEGIN3_ID);
	soundManager.addSound(weaponParser.at("weapon-begin4").get<SoundSetting>(), WEAPON_BEGIN4_ID);
	soundManager.addSound(weaponParser.at("weapon-begin5").get<SoundSetting>(), WEAPON_BEGIN5_ID);

}

/// <summary>
/// @brief Setups voice sounds.
/// 
/// </summary>
/// <param name="resourceHandler">reference to resource handler, loads our resources using json parser and an ID.</param>
/// <param name="soundManager">reference to sound manager, handles the playing of our sounds.</param>
/// <param name="voicesParser">reference to loaded json file ready to be parsed.</param>
void SoundManager::setupVoices(ResourceHandler & resourceHandler, SoundManager & soundManager, js::json & voicesParser)
{
	std::string const CAREFUL_ID = "careful";
	std::string const DOCKING_ID = "docking";
	std::string const DONT_STOP_ID = "dont-stop";
	std::string const KEEP_IT_UP_ID = "keep-it-up";
	std::string const KILL_BUGS_ID = "kill-bugs";
	std::string const LETS_GO_ID = "lets-go";
	std::string const SHIELD_CRITICAL_ID = "shield-critical";
	std::string const STAY_CLEAR_ID = "stay-clear";
	std::string const UNDOCKING_ID = "undocking";
	std::string const WHAT_HIT_ID = "what-hit";
	std::string const ALL_DAY1_ID = "all-day1";
	std::string const ALL_DAY2_ID = "all-day2";
	std::string const ALL_YA_GOT_ID = "all-ya-got";
	std::string const GET_SOME_ID = "get-some";
	std::string const GUNS_ID = "guns";
	std::string const LETS_DO_THIS_ID = "lets-do-this";
	std::string const LOCKED_AND_LOADED_ID = "locked-and-loaded";
	std::string const MUSIC_TO_MY_EARS_ID = "music-to-my-ears";
	std::string const NICE_FIND_ID = "nice-find";
	std::string const OVERHEAT1_ID = "overheat1";
	std::string const OVERHEAT2_ID = "overheat2";
	std::string const PAIN_ID = "pain";
	std::string const READY_FOR_SHOW_ID = "ready-for-show";
	std::string const SHINY_ID = "shiny";
	std::string const USEFUL_ID = "useful";


	soundManager.addSound(voicesParser.at(CAREFUL_ID).get<SoundSetting>(), CAREFUL_ID);
	soundManager.addSound(voicesParser.at(DOCKING_ID).get<SoundSetting>(), DOCKING_ID);
	soundManager.addSound(voicesParser.at(DONT_STOP_ID).get<SoundSetting>(), DONT_STOP_ID);
	soundManager.addSound(voicesParser.at(KEEP_IT_UP_ID).get<SoundSetting>(), KEEP_IT_UP_ID);
	soundManager.addSound(voicesParser.at(KILL_BUGS_ID).get<SoundSetting>(), KILL_BUGS_ID);
	soundManager.addSound(voicesParser.at(LETS_GO_ID).get<SoundSetting>(), LETS_GO_ID);
	soundManager.addSound(voicesParser.at(SHIELD_CRITICAL_ID).get<SoundSetting>(), SHIELD_CRITICAL_ID);
	soundManager.addSound(voicesParser.at(STAY_CLEAR_ID).get<SoundSetting>(), STAY_CLEAR_ID);
	soundManager.addSound(voicesParser.at(UNDOCKING_ID).get<SoundSetting>(), UNDOCKING_ID);
	soundManager.addSound(voicesParser.at(WHAT_HIT_ID).get<SoundSetting>(), WHAT_HIT_ID);
	soundManager.addSound(voicesParser.at(ALL_DAY1_ID).get<SoundSetting>(), ALL_DAY1_ID);
	soundManager.addSound(voicesParser.at(ALL_DAY2_ID).get<SoundSetting>(), ALL_DAY2_ID);
	soundManager.addSound(voicesParser.at(ALL_YA_GOT_ID).get<SoundSetting>(), ALL_YA_GOT_ID);
	soundManager.addSound(voicesParser.at(GET_SOME_ID).get<SoundSetting>(), GET_SOME_ID);
	soundManager.addSound(voicesParser.at(GUNS_ID).get<SoundSetting>(), GUNS_ID);
	soundManager.addSound(voicesParser.at(LETS_DO_THIS_ID).get<SoundSetting>(), LETS_DO_THIS_ID);
	soundManager.addSound(voicesParser.at(LOCKED_AND_LOADED_ID).get<SoundSetting>(), LOCKED_AND_LOADED_ID);
	soundManager.addSound(voicesParser.at(MUSIC_TO_MY_EARS_ID).get<SoundSetting>(), MUSIC_TO_MY_EARS_ID);
	soundManager.addSound(voicesParser.at(NICE_FIND_ID).get<SoundSetting>(), NICE_FIND_ID);
	soundManager.addSound(voicesParser.at(OVERHEAT1_ID).get<SoundSetting>(), OVERHEAT1_ID);
	soundManager.addSound(voicesParser.at(OVERHEAT2_ID).get<SoundSetting>(), OVERHEAT2_ID);
	soundManager.addSound(voicesParser.at(PAIN_ID).get<SoundSetting>(), PAIN_ID);
	soundManager.addSound(voicesParser.at(READY_FOR_SHOW_ID).get<SoundSetting>(), READY_FOR_SHOW_ID);
	soundManager.addSound(voicesParser.at(SHINY_ID).get<SoundSetting>(), SHINY_ID);
	soundManager.addSound(voicesParser.at(USEFUL_ID).get<SoundSetting>(), USEFUL_ID);


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
