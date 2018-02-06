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
	struct Sound
	{
		SoundSetting settings;
		sf::Sound sound;
	};
private: // Constructors/Destructor
	SoundManager();
public: // Public Member Functions
	static SoundManager & instance();
	void update();
	void addSound(SoundSetting settings, std::string const & id);
	void play(std::string const & id);
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
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