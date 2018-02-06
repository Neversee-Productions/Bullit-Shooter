#include "gui/game_ui/GameUI.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
GameUI::GameUI()
	: m_healthTemplatePosition(sf::Vector2f(static_cast<sf::Vector2f>(App::getViewSize())))
	, m_targetHealth(1.0f)
{
}

/// <summary>
/// @brief this is the update function it will update the ui accordingly.
/// 
/// 
/// </summary>
void GameUI::update()
{
	if (m_healthLostSprite.getScale().x > 0)
	{
		if (m_healthLostSprite.getScale().x > m_targetHealth)
		{
			m_healthLostSprite.setScale(sf::Vector2f(m_healthLostSprite.getScale().x - 0.005f, 1.0f));
		}
	}
	else
	{
		m_healthLostSprite.setScale(sf::Vector2f(0.0f, 1.0f));
	}
}


/// <summary>
/// @brief Render object.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void GameUI::draw(Window & window, const float & deltaTime)
{
	window.draw(m_healthTemplateSprite);
	window.draw(m_healthLostSprite);
	window.draw(m_healthSprite);
}

/// <summary>
/// @brief Set up the UI by loading textures into resource handler.
/// 
/// 
/// </summary>
/// <param name="sptrResources">reference to the resource struct</param>
/// <param name="resourceHandler">reference to resource handler</param>
/// <param name="UIParser">the json ui parser ready to be parsed</param>
void GameUI::setup(std::shared_ptr<Resources> sptrResources, ResourceHandler & resourceHandler, json::json & UIParser)
{
	std::string const JSON_HEALTH_TEMPLATE_TEXTURE("healthTemplate");
	std::string const JSON_HEALTH_TEXTURE("health");

	sptrResources->m_sptrHealthTemplateTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_HEALTH_TEMPLATE_TEXTURE).get<std::string>(), JSON_HEALTH_TEMPLATE_TEXTURE);
	sptrResources->m_sptrHealthTexture = resourceHandler.loadUp<sf::Texture>(UIParser.at(JSON_HEALTH_TEXTURE).get<std::string>(), JSON_HEALTH_TEXTURE);
}

/// <summary>
/// @brief this function initializes the UI.
/// 
/// 
/// </summary>
/// <param name="resources">pointer to the resource struct</param>
void GameUI::init(std::shared_ptr<Resources> resources)
{
	//initialize the health template sprite
	m_healthTemplateSprite.setTexture(*resources->m_sptrHealthTemplateTexture, false);
	m_healthTemplateSprite.setOrigin(m_healthTemplateSprite.getLocalBounds().width / 2, m_healthTemplateSprite.getLocalBounds().height / 2);
	m_healthTemplatePosition.x /= 2;
	m_healthTemplatePosition.y -= (m_healthTemplateSprite.getLocalBounds().height + 25.0f);
	m_healthTemplateSprite.setPosition(m_healthTemplatePosition);

	//initialize the health sprite
	m_healthSprite.setTexture(*resources->m_sptrHealthTexture, false);
	m_healthSprite.setOrigin(0.0f, m_healthSprite.getGlobalBounds().height / 2);
	m_healthSprite.setPosition(sf::Vector2f(m_healthTemplatePosition.x - 75.0f, m_healthTemplatePosition.y));

	//initialize the health lost sprite
	m_healthLostSprite.setTexture(*resources->m_sptrHealthTexture, false);
	m_healthLostSprite.setOrigin(0.0f, m_healthLostSprite.getGlobalBounds().height / 2);
	m_healthLostSprite.setPosition(sf::Vector2f(m_healthTemplatePosition.x - 75.0f, m_healthTemplatePosition.y));
	m_healthLostSprite.setColor(sf::Color(255u, 255u, 25u, 255u));

	//initialize the collision rectangle
	m_healthCollisionRect.min.x = m_healthTemplatePosition.x - (m_healthTemplateSprite.getLocalBounds().width / 2);
	m_healthCollisionRect.min.y = m_healthTemplatePosition.y - (m_healthTemplateSprite.getLocalBounds().height / 2);
	m_healthCollisionRect.max.x = m_healthTemplatePosition.x + (m_healthTemplateSprite.getLocalBounds().width / 2);
	m_healthCollisionRect.max.y = m_healthTemplatePosition.y + (m_healthTemplateSprite.getLocalBounds().height / 2);

}

/// <summary>
/// @brief this function will turn the health to be taken away into a percentage 
/// and scale down the scale sprite accordingly.
/// 
/// 
/// </summary>
/// <param name="health">float value for health to be taken away</param>
void GameUI::decrementHealth(float health)
{
	float healthLost = health / 100;
	m_targetHealth = m_healthSprite.getScale().x - healthLost;
	if (m_healthSprite.getScale().x > 0)
	{
		m_healthSprite.setScale(sf::Vector2f(m_healthSprite.getScale().x - healthLost, 1.0f));
	}
	else
	{
		m_healthSprite.setScale(sf::Vector2f(0.0f,1.0f));
	}
}

/// <summary>
/// @brief this function returns a constant reference to the health collision box.
/// 
/// 
/// </summary>
/// <returns>constant reference to a c2AABB rectangle which represents the collision box.</returns>
const tinyh::c2AABB & GameUI::getHealthCollisionBox()
{
	return m_healthCollisionRect;
}

/// <summary>
/// @brief This function sets the alpha of health components to passed in value.
/// 
/// 
/// </summary>
/// <param name="alphaVal">the new value of alpha</param>
void GameUI::setHealthTransparency(sf::Uint8 alphaVal)
{
	m_healthSprite.setColor(sf::Color(m_healthSprite.getColor().r, m_healthSprite.getColor().g, m_healthSprite.getColor().b, alphaVal));
	m_healthTemplateSprite.setColor(sf::Color(m_healthTemplateSprite.getColor().r, m_healthTemplateSprite.getColor().g, m_healthTemplateSprite.getColor().b, alphaVal));
	m_healthLostSprite.setColor(sf::Color(m_healthLostSprite.getColor().r, m_healthLostSprite.getColor().g, m_healthLostSprite.getColor().b, alphaVal));
}
