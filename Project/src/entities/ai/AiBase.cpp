#include "entities\ai\AiBase.h"

float const & ai::AiBase::s_DELTA_TIME = App::getUpdateDeltaTime();

/// <summary>
/// @brief Decreases the ai's health.
/// 
/// Also returns whether the ai died from this hit or not.
/// </summary>
/// <param name="damage">amount of damage.</param>
/// <returns>true if ai died from this hit.</returns>
bool ai::AiBase::decrementHealth(float const & damage)
{
	m_health -= damage;

	bool const IS_DEAD = (m_health <= 0.0f);
	if (IS_DEAD)
	{
		m_health = 0.0f;
	}
	return IS_DEAD;
}

/// <summary>
/// @brief Sets up a texture resource.
/// 
/// Parses the json with a expected format.
/// </summary>
/// <param name="animResources">reference to the data struct that stores the loaded resource.</param>
/// <param name="resourceHandler">reference to the resource loader.</param>
/// <param name="animationParser">reference to the json parser.</param>
/// <param name="id">id of the animation to be loaded.</param>
void ai::AiBase::setup(AiBase::Resources::Texture & textureResources, ResourceHandler & resourceHandler, js::json & textureParser, std::string const & id)
{
	std::string const JSON_TEXTURE_PATH("path");
	std::string const JSON_TEXTURE_ORIGIN("origin");
	std::string const JSON_TEXTURE_SCALE("scale");
	std::string const JSON_TEXTURE_FRAME("frame");

	textureResources.m_id = id;
	textureResources.m_origin.x = textureParser.at(JSON_TEXTURE_ORIGIN).at("x").get<float>();
	textureResources.m_origin.y = textureParser.at(JSON_TEXTURE_ORIGIN).at("y").get<float>();
	textureResources.m_scale.x = textureParser.at(JSON_TEXTURE_SCALE).at("x").get<float>();
	textureResources.m_scale.y = textureParser.at(JSON_TEXTURE_SCALE).at("y").get<float>();
	textureResources.m_textureRect.left = textureParser.at(JSON_TEXTURE_FRAME).at("x").get<int>();
	textureResources.m_textureRect.top = textureParser.at(JSON_TEXTURE_FRAME).at("y").get<int>();
	textureResources.m_textureRect.width = textureParser.at(JSON_TEXTURE_FRAME).at("w").get<int>();
	textureResources.m_textureRect.height = textureParser.at(JSON_TEXTURE_FRAME).at("h").get<int>();
	textureResources.m_sptrTexture =
		resourceHandler.loadUp<sf::Texture>(textureParser.at(JSON_TEXTURE_PATH).get<std::string>(), textureResources.m_id);
	textureResources.m_sptrTexture->setSmooth(true);
}

/// <summary>
/// @brief Sets up a animation resource.
/// 
/// Parses the json with a expected format.
/// </summary>
/// <param name="animResources">reference to the data struct that stores the loaded resource.</param>
/// <param name="resourceHandler">reference to the resource loader.</param>
/// <param name="animationParser">reference to the json parser.</param>
/// <param name="id">id of the animation to be loaded.</param>
void ai::AiBase::setup(AiBase::Resources::Animation & animResources, ResourceHandler & resourceHandler, js::json & animationParser, std::string const & id)
{
	std::string const JSON_ANIMATION_TEXTURE("texture");
	std::string const JSON_ANIMATION_DURATION("duration");
	std::string const JSON_ANIMATION_WIDTH("width");
	std::string const JSON_ANIMATION_HEIGHT("height");
	std::string const JSON_ANIMATION_ORIGIN("origin");
	std::string const JSON_ANIMATION_FRAMES("frames");

	animResources.m_id = id;
	animResources.m_duration = sf::seconds(animationParser.at(JSON_ANIMATION_DURATION).get<float>());
	animResources.m_origin.x = animationParser.at(JSON_ANIMATION_ORIGIN).at("x").get<float>();
	animResources.m_origin.y = animationParser.at(JSON_ANIMATION_ORIGIN).at("y").get<float>();
	animResources.m_sptrTexture = resourceHandler.loadUp<sf::Texture>("", animationParser.at(JSON_ANIMATION_TEXTURE).get<std::string>());

	animResources.m_frames = thor::FrameAnimation();
	js::json & idleFramesParser = animationParser.at(JSON_ANIMATION_FRAMES);
	auto const FRAME_WIDTH = animationParser.at(JSON_ANIMATION_WIDTH).get<int>();
	auto const FRAME_HEIGHT = animationParser.at(JSON_ANIMATION_HEIGHT).get<int>();
	for (auto const & node : animationParser.at(JSON_ANIMATION_FRAMES))
	{
		sf::IntRect rect;
		rect.left = node.at("x").get<int>();
		rect.top = node.at("y").get<int>();
		rect.width = FRAME_WIDTH;
		rect.height = FRAME_HEIGHT;

		animResources.m_frames.addFrame(1.0f, rect);
	}
}
