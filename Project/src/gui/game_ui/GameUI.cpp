#include "gui/game_ui/GameUI.h"

GameUI::GameUI()
	: m_healthTemplatePosition(sf::Vector2f(static_cast<sf::Vector2f>(App::getViewSize())))
{
}

void GameUI::update()
{
	if (m_healthSprite.getScale().x > 0)
	{
		m_healthSprite.setScale(sf::Vector2f(m_healthSprite.getScale().x - 0.005f, 1.0f));
	}
	else {
		m_healthSprite.setScale(sf::Vector2f(0.0f, 1.0f));
	}
}

void GameUI::draw(Window & window, const float & deltaTime)
{
	window.draw(m_healthTemplateSprite);
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
	m_healthTemplateSprite.setTexture(*resources->m_sptrHealthTemplateTexture, false);
	m_healthTemplateSprite.setOrigin(m_healthTemplateSprite.getLocalBounds().width / 2, m_healthTemplateSprite.getLocalBounds().height / 2);
	m_healthTemplatePosition.x /= 2;
	m_healthTemplatePosition.y -= (m_healthTemplateSprite.getLocalBounds().height + 25.0f);
	m_healthTemplateSprite.setPosition(m_healthTemplatePosition);


	m_healthSprite.setTexture(*resources->m_sptrHealthTexture, false);
	m_healthSprite.setOrigin(0.0f, m_healthSprite.getGlobalBounds().height / 2);
	m_healthSprite.setPosition(sf::Vector2f(m_healthTemplatePosition.x - 75.0f, m_healthTemplatePosition.y));
}
