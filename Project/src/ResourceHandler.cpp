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
	, m_pairAnimationHolder()
	, m_pairShaderHolder()
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

/// <summary>
/// @brief Our loader of assets.
/// 
/// 
/// </summary>
/// <param name="jsonParser">Defines the json parser.</param>
/// <param name="id">Defines the id of the data we are loading</param>
/// <returns>Returns a shared pointer to our loaded resource.</returns>
template<> std::shared_ptr<thor::FrameAnimation> ResourceHandler::loadUp<thor::FrameAnimation>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<thor::FrameAnimation> return_value;
	try
	{
		return_value = std::make_shared<thor::FrameAnimation>(load<thor::FrameAnimation>(jsonParser, id));
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
template<> std::shared_ptr<std::vector<sf::IntRect>> ResourceHandler::loadUp<std::vector<sf::IntRect>>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<std::vector<sf::IntRect>> return_value;
	try
	{
		return_value = std::make_shared<std::vector<sf::IntRect>>(load<std::vector<sf::IntRect>>(jsonParser, id));
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
template<> std::shared_ptr<sf::Shader> ResourceHandler::loadUp<sf::Shader>(json::json & jsonParser, const std::string & id)
{
	std::shared_ptr<sf::Shader> return_value;
	try
	{
		return_value = load<std::shared_ptr<sf::Shader>>(jsonParser, id);
	}
	catch (...) // catch any and all possible exceptions.
	{
		return nullptr;
	}
	return return_value;
}

template<> thor::FrameAnimation & ResourceHandler::load<thor::FrameAnimation>(json::json & jsonParser, const std::string & id)
{
	std::lock_guard<std::mutex> lock(m_pairAnimationHolder.m_mutex);
	auto & map = *(m_pairAnimationHolder.m_holder);
	auto & ittPair = map.find(id);
	if (ittPair != map.end())
	{
		return ittPair->second;
	}
	else
	{
		thor::FrameAnimation & frameAnimation = map[id];
		const auto & jsonAnimation = jsonParser.at("animation").at(id);
		const auto & width = jsonAnimation.at("width").get<int>();
		const auto & height = jsonAnimation.at("height").get<int>();
		const auto & jsonFrames = jsonAnimation.at("frames");
		float count = 0.0f;
		for (
			auto itt = jsonFrames.begin(), end = jsonFrames.end();
			itt != end;
			++itt, ++count
			)
		{
			auto x = itt->at("x").get<int>();
			auto y = itt->at("y").get<int>();
			frameAnimation.addFrame(count, sf::IntRect(x, y, width, height));
		}

		return frameAnimation;
	}
}


template<> std::vector<sf::IntRect> & ResourceHandler::load<std::vector<sf::IntRect>>(json::json & jsonParser, const std::string & id)
{
	std::lock_guard<std::mutex> lock(m_pairFrameHolder.m_mutex);
	auto & map = *(m_pairFrameHolder.m_holder);
	auto & ittPair = map.find(id);
	if (ittPair != map.end())
	{
		return ittPair->second;
	}
	else
	{
		std::vector<sf::IntRect> & frames = map[id];
		const auto & jsonAnimation = jsonParser.at("animation").at(id);
		const auto & width = jsonAnimation.at("width").get<int>();
		const auto & height = jsonAnimation.at("height").get<int>();
		const auto & jsonFrames = jsonAnimation.at("frames");
		for (
			auto itt = jsonFrames.begin(), end = jsonFrames.end();
			itt != end;
			++itt
			)
		{
			auto x = itt->at("x").get<int>();
			auto y = itt->at("y").get<int>();
			frames.push_back(sf::IntRect(x, y, width, height));
		}

		return frames;
	}
}

template<> std::shared_ptr<sf::Shader>& ResourceHandler::load<std::shared_ptr<sf::Shader>>(json::json & jsonParser, const std::string & id)
{
	std::lock_guard<std::mutex> lock(m_pairShaderHolder.m_mutex);
	auto & map = *(m_pairShaderHolder.m_holder);
	auto & ittPair = map.find(id);
	if (ittPair != map.end())
	{
		return ittPair->second;
	}
	else
	{
		std::shared_ptr<sf::Shader>& sptrShader = (map[id] = std::make_shared<sf::Shader>());
		if (nullptr != sptrShader)
		{
			const auto & jsonShaders = jsonParser.at("shaders").at(id);
			const auto & vertexShaderFilePath = jsonShaders.at("vertex").get<std::string>();
			const auto & fragmentShaderFilePath = jsonShaders.at("fragment").get<std::string>();

			assert(sptrShader->loadFromFile(vertexShaderFilePath, fragmentShaderFilePath));
		}

		return sptrShader;
	}
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