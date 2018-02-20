#ifndef SOUND_SETTING_H
#define SOUND_SETTING_H

// STL Includes
// SFML Includes
#include "SFML\Audio\SoundBuffer.hpp" // For sf::SoundBuffer
#include "SFML\System\Vector2.hpp" // For sf::Vector2f
// json Includes
#include "json\json.hpp"
// Project Includes
#include "system\ResourceHandler.h"

/// 
/// @author Rafael Plugge
/// @brief
///		Describes the necessary setting for a sound.
/// 
/// Basic container for all sound settings.
/// 
class SoundSetting
{
public: // Constructors/Destructor
	SoundSetting();
	~SoundSetting() = default;

public: // Public Member Functions
	friend void from_json(const js::json& j, SoundSetting& soundSetting);

public: // Public Member Variables
	/// <summary>
	/// @brief Indicator for whether to loop sound.
	/// 
	/// 
	/// </summary>
	bool m_loop;
	/// <summary>
	/// @brief Sound volume property.
	/// 
	/// Clamped within the range of 0.0 to 100.0
	/// (Defaults to 100)
	/// </summary>
	float m_volume;
	/// <summary>
	/// @brief Attenuation factor of the sound.
	/// 
	/// The attenuation is a multiplicative factor which makes
	/// the sound more or less loud according to it's distance to the listener.
	/// A value of 0 makes it so no attenuation occurs.
	/// (Defaults to 1)
	/// </summary>
	float m_attenuation;
	/// <summary>
	/// @brief Pointer to sound buffer property.
	/// 
	/// Pointer to our sound buffer that our sound will use.
	/// (Defaults to nullptr)
	/// </summary>
	std::shared_ptr<sf::SoundBuffer> m_sptrBuffer;
	/// <summary>
	/// @brief Pointer to sound's position.
	/// 
	/// Defines it location on a 2D plane.
	/// (Defaults to [0,0])
	/// </summary>
	sf::Vector2f * m_pPosition;
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
private: // Private Member Variables
};

#endif // !SOUND_SETTING_H