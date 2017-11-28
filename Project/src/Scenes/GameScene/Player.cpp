#include "Scenes\GameScene\Player.h"

/// <summary>
/// @brief The constructor.
/// 
/// Will construct the player and initializes members
/// </summary>
/// <param name="keyHandler">Reference to the key handler</param>
Player::Player(KeyHandler& keyHandler)
	: m_ship()
	, m_weapon1()
	, m_weapon2()
	, m_keyHandler(keyHandler)
	, m_bulletManager()
	, deltaTime(App::getUpdateDeltaTime())
	, m_weapon1Pos(sf::Vector2f(0.0f,0.0f))
	, m_weapon2Pos(sf::Vector2f(0.0f,0.0f))
{
	m_weapon1Pos = sf::Vector2f(m_ship.m_shipRect.getPosition().x, m_ship.m_shipRect.getPosition().y - 50);
	m_weapon2Pos = sf::Vector2f(m_ship.m_shipRect.getPosition().x, m_ship.m_shipRect.getPosition().y + 50);
	m_weapon1.m_weaponRect.setPosition(m_weapon1Pos);
	m_weapon2.m_weaponRect.setPosition(m_weapon2Pos);
	m_bulletManager.initBulletvector(m_weapon1.m_currentBullet);
	
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Player::draw(Window & window, const float & deltaTime)
{
	m_weapon1.draw(window, deltaTime);
	m_weapon2.draw(window, deltaTime);
	m_ship.draw(window, deltaTime);
	m_bulletManager.draw(window, deltaTime);
}

/// <summary>
/// @brief Update entities.
/// 
/// 
/// </summary>
void Player::update()
{
	
	if (m_keyHandler.isPressed(sf::Keyboard::Space))
	{
		m_bulletManager.fireBullet(m_weapon1.m_weaponRect.getPosition(), m_weapon2.m_weaponRect.getPosition(), m_weapon1.m_currentBullet);
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Up))
	{
		m_ship.moveUp();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Down))
	{
		m_ship.moveDown();
	}
	m_ship.update();
	m_weapon1Pos = sf::Vector2f(m_ship.m_shipRect.getPosition().x, m_ship.m_shipRect.getPosition().y - 50);
	m_weapon2Pos = sf::Vector2f(m_ship.m_shipRect.getPosition().x, m_ship.m_shipRect.getPosition().y + 50);
	m_weapon1.update(m_weapon1Pos);
	m_weapon2.update(m_weapon2Pos);
	m_bulletManager.update();

}

/// <summary>
/// @brief get a constant reference to the bullets.
/// 
/// 
/// </summary>
/// <returns>map of bullets</returns>
const std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>> & Player::getBulletMap()
{
	return m_bulletManager.getBulletMap();
}

