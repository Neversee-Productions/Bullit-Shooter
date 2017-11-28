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
	m_weapon1.setRectPos(m_weapon1Pos);
	m_weapon2.setRectPos(m_weapon1Pos);
	m_bulletManager.initBulletvector(m_weapon1.getBulletType());
}

/// <summary>
/// @brief Initialize player.
/// 
/// Defines all the players resources.
/// </summary>
/// <param name="uptrResources">shared pointer to all the necessary player resources.</param>
void Player::init(std::shared_ptr<Resources> uptrResources)
{
	m_ship.init(uptrResources->m_ship);
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
	const bool & KEY_UP = 
		m_keyHandler.isPressed(sf::Keyboard::Up)
		|| m_keyHandler.isPressed(sf::Keyboard::W);
	const bool & KEY_DOWN =
		m_keyHandler.isPressed(sf::Keyboard::Down)
		|| m_keyHandler.isPressed(sf::Keyboard::S);
	const bool & KEY_LEFT =
		m_keyHandler.isPressed(sf::Keyboard::Left)
		|| m_keyHandler.isPressed(sf::Keyboard::A);
	const bool & KEY_RIGHT =
		m_keyHandler.isPressed(sf::Keyboard::Right)
		|| m_keyHandler.isPressed(sf::Keyboard::D);
	const bool & KEY_FIRE = m_keyHandler.isPressed(sf::Keyboard::Space);

	m_ship.move(Ship::Direction::Up, KEY_UP);
	m_ship.move(Ship::Direction::Down, KEY_DOWN);
	m_ship.move(Ship::Direction::Left, KEY_LEFT);
	m_ship.move(Ship::Direction::Right, KEY_RIGHT);

	if (KEY_FIRE)
	{
		m_bulletManager.fireBullet(m_weapon1.getPosition(), m_weapon2.getPosition(), m_weapon1.getBulletType());
	}
	m_ship.update();
	m_weapon1Pos = sf::Vector2f(m_ship.getShipRect().x - 50, m_ship.getShipRect().y);
	m_weapon2Pos = sf::Vector2f(m_ship.getShipRect().x + 50, m_ship.getShipRect().y);
	m_weapon1.update(m_weapon1Pos);
	m_weapon2.update(m_weapon2Pos);
	m_bulletManager.update();

}

