#include "ResourceHandler.h"

/// <summary>
/// @brief Instantiate the single instanse of our Resource Handler.
/// 
/// 
/// </summary>
ResourceHandler ResourceHandler::s_instance;

/// <summary>
/// @brief Method of retrieval of our ResourceHandler instance.
/// 
/// 
/// </summary>
/// <returns>ref to the single instance of our ResourceHandler.</returns>
ResourceHandler & ResourceHandler::get()
{
	return s_instance;
}

/// <summary>
/// @brief Private default constructor.
/// 
/// It is still used by our static instance.
/// </summary>
ResourceHandler::ResourceHandler()
	: m_pairTextureHolder()
	, m_pairBigTextureHolder()
	, m_pairFontHolder()
	, m_pairSoundHolder()
	, m_ID_STRATEGY(thor::Resources::KnownIdStrategy::Reuse)
{
}


/// <summary>
/// @brief Our loader of assets.
/// 
/// 
/// </summary>
/// <param name="jsonParser">Defines the json parser.</param>
/// <param name="id">Defines the id of the data we are loading</param>
/// <returns>Returns a shared pointer to our loaded resource.</returns>
template<> std::shared_ptr<sf::Texture> ResourceHandler::loadUp<sf::Texture>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<sf::Texture> return_value;
	try
	{
		return_value = std::make_shared<sf::Texture>(load<sf::Texture>(id, jsonParser.at("textures").at(id).get<std::string>()));
	}
	catch (...) // catch any and all possible exceptions.
	{
		return nullptr;
	}
	return return_value;
}

/// <summary>
/// @brief Our loader of assets.
/// 
/// 
/// </summary>
/// <param name="jsonParser">Defines the json parser.</param>
/// <param name="id">Defines the id of the data we are loading</param>
/// <returns>Returns a shared pointer to our loaded resource.</returns>
template<> std::shared_ptr<sf::Font> ResourceHandler::loadUp<sf::Font>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<sf::Font> return_value;
	try
	{
		return_value = std::make_shared<sf::Font>(load<sf::Font>(id, jsonParser.at("fonts").at(id).get<std::string>()));
	}
	catch (...) // catch any and all possible exceptions.
	{
		return nullptr;
	}
	return return_value;
}

/// <summary>
/// @brief Our loader of assets.
/// 
/// 
/// </summary>
/// <param name="jsonParser">Defines the json parser.</param>
/// <param name="id">Defines the id of the data we are loading</param>
/// <returns>Returns a shared pointer to our loaded resource.</returns>
template<> std::shared_ptr<sf::SoundBuffer> ResourceHandler::loadUp<sf::SoundBuffer>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<sf::SoundBuffer> return_value;
	try
	{
		return_value = std::make_shared<sf::SoundBuffer>(load<sf::SoundBuffer>(id, jsonParser.at("sounds").at(id).get<std::string>()));
	}
	catch (...) // catch any and all possible exceptions.
	{
		return nullptr;
	}
	return return_value;
}

/// <summary>
/// @brief Our loader of assets.
/// 
/// 
/// </summary>
/// <param name="jsonParser">Defines the json parser.</param>
/// <param name="id">Defines the id of the data we are loading</param>
/// <returns>Returns a shared pointer to our loaded resource.</returns>
template<> std::shared_ptr<thor::BigTexture> ResourceHandler::loadUp<thor::BigTexture>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<thor::BigTexture> return_value;
	try
	{
		return_value = std::make_shared<thor::BigTexture>(load<thor::BigTexture>(id, jsonParser.at("textures").at(id).get<std::string>()));
	}
	catch (...) // catch any and all possible exceptions.
	{
		return nullptr;
	}
	return return_value;
}

template<> sf::Texture & ResourceHandler::load<sf::Texture>(const std::string & id, const std::string & filePath)
{
	std::lock_guard<std::mutex> lock(m_pairTextureHolder.m_mutex);
	return m_pairTextureHolder.m_holder->acquire(id, thor::Resources::fromFile<sf::Texture>(filePath), m_ID_STRATEGY);
}


template<> thor::BigTexture & ResourceHandler::load<thor::BigTexture>(const std::string & id, const std::string & filePath)
{
	std::lock_guard<std::mutex> lock(m_pairBigTextureHolder.m_mutex);
	return m_pairBigTextureHolder.m_holder->acquire(id, thor::Resources::fromFile<thor::BigTexture>(filePath), m_ID_STRATEGY);
}

template<> sf::Font & ResourceHandler::load<sf::Font>(const std::string & id, const std::string & filePath)
{
	std::lock_guard<std::mutex> lock(m_pairFontHolder.m_mutex);
	return m_pairFontHolder.m_holder->acquire(id, thor::Resources::fromFile<sf::Font>(filePath), m_ID_STRATEGY);
}

template<> sf::SoundBuffer & ResourceHandler::load<sf::SoundBuffer>(const std::string & id, const std::string & filePath)
{
	std::lock_guard<std::mutex> lock(m_pairSoundHolder.m_mutex);
	return m_pairSoundHolder.m_holder->acquire(id, thor::Resources::fromFile<sf::SoundBuffer>(filePath), m_ID_STRATEGY);
}