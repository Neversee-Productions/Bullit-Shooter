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
		value.sound.setPosition({ value.settings.m_pPosition->x, value.settings.m_pPosition->y, 0.0f });
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

	sf::Sound sfmlSound;
	sfmlSound.setVolume(settings.m_volume);
	sfmlSound.setAttenuation(settings.m_attenuation);
	sfmlSound.setLoop(settings.m_loop);
	sfmlSound.setBuffer(*settings.m_sptrBuffer);
	if (nullptr != settings.m_pPosition)
	{
		sfmlSound.setPosition(settings.m_pPosition->x, settings.m_pPosition->y, 0.0f);
	}

	m_soundMap.insert(std::make_pair(id, Sound({ settings, std::move(sfmlSound) })));
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

#ifdef _DEBUG
	// In debug we step through each step to getting the sf::Sound our of the map.
	SoundMap::mapped_type & value = m_soundMap.at(id);
	sf::Sound & sound = value.sound;
#else
	// In release we express the exact same as in debug but in one line.
	sf::Sound & sound = m_soundMap.at(id).sound;
#endif

	if (sound.getStatus() == sf::Sound::Status::Playing)
	{
		sound.stop();
	}
	sound.play();
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
