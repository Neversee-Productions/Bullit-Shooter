#include "Scenes\GameScene\Entities\Player\Player.h"

/// <summary>
/// @brief The constructor.
/// 
/// Will construct the player and initializes members
/// </summary>
/// <param name="keyHandler">Reference to the key handler</param>
Player::Player(KeyHandler& keyHandler)
	: m_ship()
	, m_weaponLeft()
	, m_weaponRight()
	, m_keyHandler(keyHandler)
	, m_bulletManager()
	, deltaTime(App::getUpdateDeltaTime())
	, m_weaponLeftPos(sf::Vector2f(0.0f,0.0f))
	, m_weaponRightPos(sf::Vector2f(0.0f,0.0f))
{
	auto const & flip = true;
	m_weaponLeft.setRectPos(m_weaponLeftPos);
	m_weaponLeft.setFlipped(flip);
	m_weaponRight.setRectPos(m_weaponLeftPos);
	m_weaponRight.setFlipped(!flip);
	m_bulletManager.initBulletvector(m_weaponLeft.getBulletType());
}

/// <summary>
/// @brief Initialize player.
/// 
/// Defines all the players resources.
/// </summary>
/// <param name="uptrResources">shared pointer to all the necessary player resources.</param>
void Player::init(std::shared_ptr<Resources> sptrResources)
{
	m_ship.init(sptrResources->m_ship);
	m_weaponLeft.init(sptrResources->m_weapon);
	m_weaponRight.init(sptrResources->m_weapon);
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
	m_bulletManager.draw(window, deltaTime);
	m_weaponLeft.draw(window, deltaTime);
	m_weaponRight.draw(window, deltaTime);
	m_ship.draw(window, deltaTime);
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
		m_bulletManager.fireBullet(m_weaponLeft, m_weaponRight, m_weaponLeft.getBulletType());
	}
	m_ship.update();
	m_weaponLeftPos = sf::Vector2f(m_ship.getShipRect().x - 50, m_ship.getShipRect().y);
	m_weaponRightPos = sf::Vector2f(m_ship.getShipRect().x + 50, m_ship.getShipRect().y);
	m_weaponLeft.update(m_weaponLeftPos);
	m_weaponRight.update(m_weaponRightPos);
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

