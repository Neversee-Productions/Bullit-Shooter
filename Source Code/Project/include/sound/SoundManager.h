#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

// STL Includes
#include <assert.h>
#include <unordered_map> // For std::unordered_map
#include <memory> // For std::shared_ptr
#include <string> // For std::string
// SFML Includes
#include "SFML\Audio\Sound.hpp"
// Project Includes
#include "sound\SoundSetting.h"
#include "entities\Player\Bullets\BulletTypes.h"

/// 
/// @author Rafael Plugge
/// @brief
///		Will manage the playing of sounds within the game.
/// 
/// Contains a list of all loaded songs and allows for them to be played
/// through our list of sounds enum.
/// 
/// Only one instance of this class exist, as in it uses
/// the Singleton pattern.
/// http://gameprogrammingpatterns.com/singleton.html
/// 
class SoundManager
{
private: // Private classes/structs

	/// 
	/// @brief Defines necessary sound container.
	/// @author Rafael Plugge
	/// 
	/// 
	/// 
	struct Sound
	{
		/// <summary>
		/// @brief Container for the sound configuration.
		/// 
		/// 
		/// </summary>
		SoundSetting settings;

		/// <summary>
		/// @brief Container of sound players.
		/// 
		/// Each one can only play one sound.
		/// </summary>
		std::list<sf::Sound> soundPlayers;
	};
private: // Constructors/Destructor
	SoundManager();
public: // Public Member Functions
	static SoundManager & instance();
	static void setup(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & soundParser);
	void update();
	void addSound(SoundSetting settings, std::string const & id);
	void play(std::string const & id, bool stack = true);
	void stop(std::string const & id);
	bool checkSound(std::string const & id);
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
	static void setupBg(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & bgParser
	);
	static void setupPlayer(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & playerParser);
	static void setupPlayerShip(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & shipParser
	);
	static void setupPlayerBullets(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & playerBulletsParser);
	static void setupBulletSounds(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & bulletParser
		, std::string const & bulletNum
		, BulletTypes const & type);
	static void setupAsteroid(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & asteroidParser
	);
	static void setupBasicEnemy(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & basicEnemyParser
	);
	static void setupUI(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & uiParser
	);
	static void setupPickup(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & pickupParser
	);
	static void setupPlayerWeapons(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & weaponParser
	);
	static void setupVoices(
		ResourceHandler & resourceHandler
		, SoundManager & soundManager
		, js::json & voicesParser
	);
	bool checkSoundInMap(std::string const & id) const;
private: // Private Member Variables
	/// <summary>
	/// @brief static reference to our single instance.
	/// 
	/// 
	/// </summary>
	static SoundManager & s_soundManager;

	/// <summary>
	/// @brief Alias for stl sound map.
	/// 
	/// 
	/// </summary>
	typedef std::unordered_map<std::string, Sound> SoundMap;

	/// <summary>
	/// @brief Defines our list of sounds.
	/// 
	/// </summary>
	SoundMap m_soundMap;

};

#endif // !SOUND_MANAGER_H