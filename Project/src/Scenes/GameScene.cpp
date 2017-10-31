#include "Scenes\GameScene.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Constructs a base Scene using the name of "Game".
/// </summary>
GameScene::GameScene()
	: Scene("Game")
	, m_square()
{
	m_square.setPosition(200.0f, 200.0f);
	sf::Vector2f& size = sf::Vector2f(200.0f, 100.0f);
	m_square.setSize(size);
	m_square.setOrigin(size / 2.0f);
	m_square.setFillColor(sf::Color::Yellow);
}

/// <summary>
/// @brief Empty for now.
/// 
/// Will contain the loading of external content.
/// </summary>
void GameScene::start()
{
}

/// <summary>
/// @brief Empty for now.
/// 
/// Will contain the unloading of external content.
/// </summary>
void GameScene::stop()
{
}

/// <summary>
/// @brief Update game scene entities.
/// 
/// 
/// </summary>
void GameScene::update()
{
	m_square.rotate(720.0f * m_UPDATE_DT);
}

/// <summary>
/// @brief Render game scene entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void GameScene::draw(Window & window, const float & deltaTime)
{
	window.draw(m_square);
}

