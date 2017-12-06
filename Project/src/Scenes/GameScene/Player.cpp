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
	, m_shield(m_ship.getShipRect().getPosition(), m_ship.getShipRect().getSize().y / 2)
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
	if (m_alive)
	{
		m_weapon1.draw(window, deltaTime);
		m_weapon2.draw(window, deltaTime);
		m_ship.draw(window, deltaTime);
		m_bulletManager.draw(window, deltaTime);
		m_shield.draw(window, deltaTime);
	}
}

/// <summary>
/// @brief Update entities.
/// 
/// Update all input as well as run updates for:
/// Both weapons, ship, bullet manager and shield.
/// </summary>
void Player::update()
{
	if (m_alive)
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
		m_shield.setPosition(m_ship.getShipRect().getPosition());
		m_shield.update();
		m_weapon1Pos = sf::Vector2f(m_ship.getShipRect().getPosition().x - 50, m_ship.getShipRect().getPosition().y);
		m_weapon2Pos = sf::Vector2f(m_ship.getShipRect().getPosition().x + 50, m_ship.getShipRect().getPosition().y);
		m_weapon1.update(m_weapon1Pos);
		m_weapon2.update(m_weapon2Pos);
		m_bulletManager.update();
	}
}

/// <summary>
/// @brief Decrement shield by a passed amount.
/// 
/// 
/// </summary>
/// <param name="dmg">amaount to decrement shield by.</param>
void Player::decrementShield(float dmg)
{
	m_shield.decrementShield(dmg);
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

/// <summary>
/// @brief Return a constant reference to a shield.
/// 
/// 
/// </summary>
/// <returns>constant reference to the collision circle.</returns>
const sf::CircleShape& Player::getShieldCircle()
{
	return m_shield.getCircleShape();
}

/// <summary>
/// @brief Return constant ref to collision circle of the shield.
/// 
/// 
/// </summary>
/// <returns>constant reference to shield collision circle.</returns>
const tinyh::c2Circle & Player::getShieldCollisionCircle()
{
	return m_shield.getCollisionCircle();
}

/// <summary>
/// @brief Get health of the shield.
/// 
/// 
/// </summary>
/// <returns>Constant reference to health of shield.</returns>
const float & Player::getShieldHealth()
{
	return m_shield.getHealth();
}

/// <summary>
/// @brief set the alive of player.
/// 
/// 
/// </summary>
/// <param name="check">new state of players alive bool</param>
void Player::setAlive(bool check)
{
	m_alive = check;
}

