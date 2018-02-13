#include "sound\SoundSetting.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Initialize member variables with default values.
/// </summary>
SoundSetting::SoundSetting()
	: m_loop(false)
	, m_volume(100.0f)
	, m_attenuation(1.0f)
	, m_sptrBuffer(nullptr)
	, m_pPosition(nullptr)
{
}

/// <summary>
/// @brief Used by json::json to parse our sound setting.
/// 
/// 
/// </summary>
/// <param name="j">read-only reference to json parser.</param>
/// <param name="soundSetting">reference to sound setting to be parsed.</param>
void from_json(const json::json & j, SoundSetting & soundSetting)
{
	ResourceHandler & resourceHandler = ResourceHandler::get();

	std::string const JSON_LOOP("loop");
	std::string const JSON_VOLUME("volume");
	std::string const JSON_ATTENUATION("attenuation");
	std::string const JSON_BUFFER("buffer");

	auto const & jEnd = j.end();
	json::json::const_iterator result;
	result = j.find(JSON_LOOP);
	if (result != jEnd)
	{
		soundSetting.m_loop = result->get<bool>();
	}

	result = j.find(JSON_VOLUME);
	if (result != jEnd)
	{
		soundSetting.m_volume = result->get<float>();
	}

	result = j.find(JSON_ATTENUATION);
	if (result != jEnd)
	{
		soundSetting.m_attenuation = result->get<float>();
	}

	result = j.find(JSON_BUFFER);
	if (result != jEnd)
	{
		soundSetting.m_sptrBuffer =
			resourceHandler.loadUp<sf::SoundBuffer>(result->at("path").get<std::string>(), result->at("key").get<std::string>());
	}
}
