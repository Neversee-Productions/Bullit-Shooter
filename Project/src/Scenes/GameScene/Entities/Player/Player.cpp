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
	, m_connectLeftWeaponToShip()
	, m_weaponRight()
	, m_connectRightWeaponToShip()
	, m_keyHandler(keyHandler)
	, m_bulletManager()
	, deltaTime(App::getUpdateDeltaTime())
	, m_weaponLeftPos(sf::Vector2f(0.0f,0.0f))
	, m_weaponRightPos(sf::Vector2f(0.0f,0.0f))
	, m_shield(m_ship.getShipRect().getPosition(), m_ship.getShipRect().getSize().y / 2)
	, m_alive(true)
{
	auto const & flip = true;
	m_weaponLeft.setRectPos(m_weaponLeftPos);
	m_weaponLeft.setFlipped(flip);
	m_weaponRight.setRectPos(m_weaponLeftPos);
	m_weaponRight.setFlipped(!flip);
	//m_bulletManager.initBulletvector(m_weaponLeft.getBulletType());
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
	m_connectLeftWeaponToShip.init(sptrResources->m_connector);
	m_connectRightWeaponToShip.init(sptrResources->m_connector);
	m_bulletManager.init(sptrResources->m_bullets);
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
		m_bulletManager.draw(window, deltaTime);
		m_connectLeftWeaponToShip.draw(window, deltaTime);
		m_weaponLeft.draw(window, deltaTime);
		m_connectRightWeaponToShip.draw(window, -deltaTime);
		m_weaponRight.draw(window, deltaTime);
		m_ship.draw(window, deltaTime);
		m_shield.draw(window, deltaTime);
	}
}

/// <summary>
/// @brief Update entities.
/// 
/// 
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

		switchWeaponInput();

		m_ship.move(Ship::Direction::Up, KEY_UP);
		m_ship.move(Ship::Direction::Down, KEY_DOWN);
		m_ship.move(Ship::Direction::Left, KEY_LEFT);
		m_ship.move(Ship::Direction::Right, KEY_RIGHT);

		if (KEY_FIRE)
		{
			m_bulletManager.fireBullet(m_weaponLeft, m_weaponRight, m_weaponLeft.getBulletType());
		}
		m_ship.update();
		auto const & shipPosition = m_ship.getShipRect().getPosition();
		m_shield.setPosition(shipPosition);
		m_shield.update();
		m_weaponLeft.update(shipPosition);
		m_connectLeftWeaponToShip.update(shipPosition, m_weaponLeft.getPosition());
		m_weaponRight.update(shipPosition);
		m_connectRightWeaponToShip.update(m_weaponRight.getPosition(), shipPosition);
		m_bulletManager.update();
	}
}

/// <summary>
/// @brief Decrement shield by a passed amount.
/// 
/// 
/// </summary>
/// <param name="dmg">amount to decrement shield by.</param>
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

void Player::switchWeaponInput()
{
	typedef sf::Keyboard::Key Key;

	bool const & KEY_ONE =
		m_keyHandler.isPressed(Key::Num1)
		&& m_keyHandler.isPrevPressed(Key::Num1);
	bool const & KEY_TWO =
		m_keyHandler.isPressed(Key::Num2)
		&& m_keyHandler.isPrevPressed(Key::Num2);
	bool const & KEY_THREE =
		m_keyHandler.isPressed(Key::Num3)
		&& m_keyHandler.isPrevPressed(Key::Num3);
	bool const & KEY_FOUR =
		m_keyHandler.isPressed(Key::Num4)
		&& m_keyHandler.isPrevPressed(Key::Num4);
	bool const & KEY_FIVE =
		m_keyHandler.isPressed(Key::Num5)
		&& m_keyHandler.isPrevPressed(Key::Num5);
	bool const & KEY_SIX =
		m_keyHandler.isPressed(Key::Num6)
		&& m_keyHandler.isPrevPressed(Key::Num6);
	bool const & KEY_SEVEN =
		m_keyHandler.isPressed(Key::Num7)
		&& m_keyHandler.isPrevPressed(Key::Num7);
	bool const & KEY_EIGHT =
		m_keyHandler.isPressed(Key::Num8)
		&& m_keyHandler.isPrevPressed(Key::Num8);
	bool const & KEY_NINE =
		m_keyHandler.isPressed(Key::Num9)
		&& m_keyHandler.isPrevPressed(Key::Num9);
	bool const & KEY_ZERO =
		m_keyHandler.isPressed(Key::Num0)
		&& m_keyHandler.isPrevPressed(Key::Num0);
	bool const & KEY_DASH =
		m_keyHandler.isPressed(Key::Dash)
		&& m_keyHandler.isPrevPressed(Key::Dash);
	bool const & KEY_EQUALS =
		m_keyHandler.isPressed(Key::Equal)
		&& m_keyHandler.isPrevPressed(Key::Equal);

	if (KEY_ONE)
	{
		m_weaponLeft.setType(BulletTypes::Standard);
		m_weaponRight.setType(BulletTypes::Standard);
	}
	else if (KEY_TWO)
	{
		m_weaponLeft.setType(BulletTypes::Empowered);
		m_weaponRight.setType(BulletTypes::Empowered);
	}
	else if (KEY_THREE)
	{
		m_weaponLeft.setType(BulletTypes::DeathOrb);
		m_weaponRight.setType(BulletTypes::DeathOrb);
	}
	else if (KEY_FOUR)
	{
		m_weaponLeft.setType(BulletTypes::FireBlast);
		m_weaponRight.setType(BulletTypes::FireBlast);
	}
	else if (KEY_FIVE)
	{
		m_weaponLeft.setType(BulletTypes::HolySphere);
		m_weaponRight.setType(BulletTypes::HolySphere);
	}
	else if (KEY_SIX)
	{
		m_weaponLeft.setType(BulletTypes::MagmaShot);
		m_weaponRight.setType(BulletTypes::MagmaShot);
	}
	else if (KEY_SEVEN)
	{
		m_weaponLeft.setType(BulletTypes::NapalmSphere);
		m_weaponRight.setType(BulletTypes::NapalmSphere);
	}
	else if (KEY_EIGHT)
	{
		m_weaponLeft.setType(BulletTypes::CometShot);
		m_weaponRight.setType(BulletTypes::CometShot);
	}
	else if (KEY_NINE)
	{
		m_weaponLeft.setType(BulletTypes::NullWave);
		m_weaponRight.setType(BulletTypes::NullWave);
	}
	else if (KEY_ZERO)
	{
		m_weaponLeft.setType(BulletTypes::StaticSphere);
		m_weaponRight.setType(BulletTypes::StaticSphere);
	}
	else if (KEY_DASH)
	{
		m_weaponLeft.setType(BulletTypes::PyroBlast);
		m_weaponRight.setType(BulletTypes::PyroBlast);
	}
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
/// <param name="check">new state of players alive boolean</param>
void Player::setAlive(bool check)
{
	m_alive = check;
}

/// <summary>
/// @brief fetch the position of players ship.
/// 
/// 
/// </summary>
/// <returns>players ship position.</returns>
sf::Vector2f const & Player::getPosition() const
{
	return m_ship.getShipRect().getPosition();
}

/// <summary>
/// @brief this method will upgrade the current weapon to the next one.
/// 
/// 
/// </summary>
void Player::nextWeapon()
{
	BulletTypes currentType = m_weaponLeft.getBulletType();
	switch (currentType)
	{
	case BulletTypes::Standard:
		m_weaponLeft.setType(BulletTypes::Empowered);
		m_weaponRight.setType(BulletTypes::Empowered);
		break;
	case BulletTypes::Empowered:
		m_weaponLeft.setType(BulletTypes::DeathOrb);
		m_weaponRight.setType(BulletTypes::DeathOrb);
		break;
	case BulletTypes::DeathOrb:
		m_weaponLeft.setType(BulletTypes::FireBlast);
		m_weaponRight.setType(BulletTypes::FireBlast);
		break;
	case BulletTypes::FireBlast:
		m_weaponLeft.setType(BulletTypes::HolySphere);
		m_weaponRight.setType(BulletTypes::HolySphere);
		break;
	case BulletTypes::HolySphere:
		m_weaponLeft.setType(BulletTypes::MagmaShot);
		m_weaponRight.setType(BulletTypes::MagmaShot);
		break;
	case BulletTypes::MagmaShot:
		m_weaponLeft.setType(BulletTypes::NapalmSphere);
		m_weaponRight.setType(BulletTypes::NapalmSphere);
		break;
	case BulletTypes::NapalmSphere:
		m_weaponLeft.setType(BulletTypes::CometShot);
		m_weaponRight.setType(BulletTypes::CometShot);
		break;
	case BulletTypes::CometShot:
		m_weaponLeft.setType(BulletTypes::NullWave);
		m_weaponRight.setType(BulletTypes::NullWave);
		break;
	case BulletTypes::NullWave:
		m_weaponLeft.setType(BulletTypes::StaticSphere);
		m_weaponRight.setType(BulletTypes::StaticSphere);
		break;
	case BulletTypes::StaticSphere:
		m_weaponLeft.setType(BulletTypes::PyroBlast);
		m_weaponRight.setType(BulletTypes::PyroBlast);
		break;
	case BulletTypes::PyroBlast:
		m_weaponLeft.setType(BulletTypes::Standard);
		m_weaponRight.setType(BulletTypes::Standard);
		break;
	default:
		break;
	}
}