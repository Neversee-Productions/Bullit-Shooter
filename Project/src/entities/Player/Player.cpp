#include "Entities\Player\Player.h"

/// <summary>
/// @brief The constructor.
/// 
/// Will construct the player and initializes members
/// </summary>
/// <param name="keyHandler">Reference to the key handler</param>
/// <param name="controller">Reference to the controller.</param>
Player::Player(KeyHandler& keyHandler, Controller & controller, Background & background)
	: m_background(background)
	, m_ship()
	, m_weaponLeft()
	, m_connectLeftWeaponToShip()
	, m_weaponRight()
	, m_connectRightWeaponToShip()
	, m_keyHandler(keyHandler)
	, m_controller(controller)
	, m_soundManager(SoundManager::instance())
	, m_bulletManager()
	, deltaTime(App::getUpdateDeltaTime())
	, m_weaponLeftPos(sf::Vector2f(0.0f,0.0f))
	, m_weaponRightPos(sf::Vector2f(0.0f,0.0f))
	, m_shield(m_ship.getShipRect().getPosition(), m_ship.getShipRect().getSize().y / 2)
	, m_alive(true)
	, m_attachedWeapons(true)
{
	auto const & flip = true;
	m_weaponLeft.setRectPos(m_weaponLeftPos);
	m_weaponLeft.setFlipped(flip);
	m_weaponRight.setRectPos(m_weaponLeftPos);
	m_weaponRight.setFlipped(!flip);

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
	m_background.setTargetColor(m_weaponLeft.getBgColor());
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
	if (m_alive)
	{
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
		if (this->getShieldHealth() <= 0.0f)
		{
			this->setAlive(false);
		}
		const bool & KEY_UP =
			m_keyHandler.isPressed(sf::Keyboard::Up)
			|| m_keyHandler.isPressed(sf::Keyboard::W)
			|| checkAxis(m_controller.m_currentState.m_flightStick.y, true);
		const bool & KEY_DOWN =
			m_keyHandler.isPressed(sf::Keyboard::Down)
			|| m_keyHandler.isPressed(sf::Keyboard::S)
			|| checkAxis(m_controller.m_currentState.m_flightStick.y, false);
		const bool & KEY_LEFT =
			m_keyHandler.isPressed(sf::Keyboard::Left)
			|| m_keyHandler.isPressed(sf::Keyboard::A)
			|| checkAxis(m_controller.m_currentState.m_flightStick.x, true);
		const bool & KEY_RIGHT =
			m_keyHandler.isPressed(sf::Keyboard::Right)
			|| m_keyHandler.isPressed(sf::Keyboard::D)
			|| checkAxis(m_controller.m_currentState.m_flightStick.x, false);
		const bool & KEY_FIRE =
			m_keyHandler.isPressed(sf::Keyboard::Space)
			|| m_controller.m_currentState.m_btnTrigger;
		switchWeaponInput();


		if (m_keyHandler.isPressed(sf::Keyboard::P))
		{
			m_shield.setHealth(100000.0f);
		}

		m_ship.move(Ship::Direction::Up, KEY_UP);
		m_ship.move(Ship::Direction::Down, KEY_DOWN);
		m_ship.move(Ship::Direction::Left, KEY_LEFT);
		m_ship.move(Ship::Direction::Right, KEY_RIGHT);
		
		if (m_controller.isConnected())
		{
			if (checkAxisThrusterPositive(m_controller.m_currentState.m_flightThruster))
			{
				m_ship.setDocking(true);
			}
			else
			{
				m_ship.setDocking(false);
			}
			if (checkAxisThrusterNegative(m_controller.m_currentState.m_flightThruster) && !checkAxisThrusterNegative(m_controller.m_previousState.m_flightThruster))
			{
				m_ship.dash();
			}
		}
		else
		{
			if (m_keyHandler.isPressed(sf::Keyboard::LControl) && !m_keyHandler.isPrevPressed(sf::Keyboard::LControl))
			{
				m_ship.setDocking(!m_ship.getDocking());
			}
		}


		if (KEY_FIRE && m_weaponLeft.getCanFire() && m_weaponRight.getCanFire())
		{
			m_bulletManager.fireBullet(m_weaponLeft, m_weaponRight, m_weaponLeft.getBulletType());
		}
		m_ship.update();
		auto const & shipPosition = m_ship.getShipRect().getPosition();
		m_shield.setPosition(shipPosition);
		m_shield.update();
		m_weaponLeft.update(shipPosition);
		m_weaponRight.update(shipPosition);
		if (m_attachedWeapons)
		{
			m_leftConnectorEnd = m_weaponLeft.getPosition();
			m_rightConnectorEnd = m_weaponRight.getPosition();
		}
		m_connectLeftWeaponToShip.update(shipPosition, m_leftConnectorEnd);
		m_connectRightWeaponToShip.update(m_rightConnectorEnd, shipPosition);
	}
	m_bulletManager.update();
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
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_TWO)
	{
		m_weaponLeft.setType(BulletTypes::Empowered);
		m_weaponRight.setType(BulletTypes::Empowered);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_THREE)
	{
		m_weaponLeft.setType(BulletTypes::DeathOrb);
		m_weaponRight.setType(BulletTypes::DeathOrb);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_FOUR)
	{
		m_weaponLeft.setType(BulletTypes::FireBlast);
		m_weaponRight.setType(BulletTypes::FireBlast);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_FIVE)
	{
		m_weaponLeft.setType(BulletTypes::HolySphere);
		m_weaponRight.setType(BulletTypes::HolySphere);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_SIX)
	{
		m_weaponLeft.setType(BulletTypes::MagmaShot);
		m_weaponRight.setType(BulletTypes::MagmaShot);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_SEVEN)
	{
		m_weaponLeft.setType(BulletTypes::NapalmSphere);
		m_weaponRight.setType(BulletTypes::NapalmSphere);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_EIGHT)
	{
		m_weaponLeft.setType(BulletTypes::CometShot);
		m_weaponRight.setType(BulletTypes::CometShot);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_NINE)
	{
		m_weaponLeft.setType(BulletTypes::NullWave);
		m_weaponRight.setType(BulletTypes::NullWave);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_ZERO)
	{
		m_weaponLeft.setType(BulletTypes::StaticSphere);
		m_weaponRight.setType(BulletTypes::StaticSphere);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
	else if (KEY_DASH)
	{
		m_weaponLeft.setType(BulletTypes::PyroBlast);
		m_weaponRight.setType(BulletTypes::PyroBlast);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
	}
}

/// <summary>
/// @brief Check if axis is over threshold.
/// 
/// 
/// </summary>
/// <param name="axis">axis to be checked</param>
/// <param name="flipped">determines whether to check below a negative threshold or above a positive threshold.</param>
/// <returns>true if axis is over threshold.</returns>
bool Player::checkAxis(float const & axis, bool flipped)
{
	float const THRESHOLD = 10.0f;
	if (flipped)
	{
		if (axis < -THRESHOLD)
		{
			return true;
		}
	}
	else
	{
		if (axis > THRESHOLD)
		{
			return true;
		}
	}
	return false;
}

/// <summary>
/// @brief defines a function that checks if thruster is above a threshold.
/// 
/// 
/// </summary>
/// <param name="axis">axis of thruster</param>
/// <returns>return true if axis above threshold else false</returns>
bool Player::checkAxisThrusterPositive(float const & axis)
{
	float const THRESHOLD = 70.0f;
	if (axis > THRESHOLD)
	{
		return true;
	}
	return false;
}

/// <summary>
/// @brief defines a function that checks if thruster is below a threshold.
/// 
/// 
/// </summary>
/// <param name="axis">axis of thruster</param>
/// <returns>return true if axis below threshold else false</returns>
bool Player::checkAxisThrusterNegative(float const & axis)
{
	float const THRESHOLD = 70.0f;
	if (axis < -THRESHOLD)
	{
		return true;
	}
	return false;
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
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.1f, 0.004f, 0.003f);
		break;
	case BulletTypes::Empowered:
		m_weaponLeft.setType(BulletTypes::DeathOrb);
		m_weaponRight.setType(BulletTypes::DeathOrb);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.2f, 0.004f, 0.003f);
		break;
	case BulletTypes::DeathOrb:
		m_weaponLeft.setType(BulletTypes::FireBlast);
		m_weaponRight.setType(BulletTypes::FireBlast);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.12f, 0.004f, 0.003f);
		break;
	case BulletTypes::FireBlast:
		m_weaponLeft.setType(BulletTypes::HolySphere);
		m_weaponRight.setType(BulletTypes::HolySphere);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.05f, 0.004f, 0.003f);
		break;
	case BulletTypes::HolySphere:
		m_weaponLeft.setType(BulletTypes::MagmaShot);
		m_weaponRight.setType(BulletTypes::MagmaShot);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.15f, 0.004f, 0.003f);
		break;
	case BulletTypes::MagmaShot:
		m_weaponLeft.setType(BulletTypes::NapalmSphere);
		m_weaponRight.setType(BulletTypes::NapalmSphere);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.25f, 0.005f, 0.004f);
		break;
	case BulletTypes::NapalmSphere:
		m_weaponLeft.setType(BulletTypes::CometShot);
		m_weaponRight.setType(BulletTypes::CometShot);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.1f, 0.005f, 0.004f);
		break;
	case BulletTypes::CometShot:
		m_weaponLeft.setType(BulletTypes::NullWave);
		m_weaponRight.setType(BulletTypes::NullWave);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.1f, 0.006f, 0.005f);
		break;
	case BulletTypes::NullWave:
		m_weaponLeft.setType(BulletTypes::StaticSphere);
		m_weaponRight.setType(BulletTypes::StaticSphere);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.2f, 0.004f, 0.003f);
		break;
	case BulletTypes::StaticSphere:
		m_weaponLeft.setType(BulletTypes::PyroBlast);
		m_weaponRight.setType(BulletTypes::PyroBlast);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.2f, 0.004f, 0.003f);
		break;
	case BulletTypes::PyroBlast:
		m_weaponLeft.setType(BulletTypes::Standard);
		m_weaponRight.setType(BulletTypes::Standard);
		m_background.setTargetColor(m_weaponLeft.getBgColor());
		m_bulletManager.setWeaponOverheatingValues(0.35f, 0.003f, 0.002f);
		break;
	default:
		break;
	}
}

/// <summary>
/// @brief get the current weapon type.
/// 
/// 
/// </summary>
/// <returns>A bullet type</returns>
BulletTypes const & Player::getWeaponType()
{
	return m_weaponLeft.getBulletType();
}

/// <summary>
/// @brief get the left weapon position.
/// 
/// 
/// </summary>
/// <returns>a vector2f that defines position.</returns>
sf::Vector2f const & Player::getLeftWeaponPos()
{
	return m_weaponLeft.getPosition();
}

/// <summary>
/// @brief get the right weapon position.
/// 
/// 
/// </summary>
/// <returns>a vector2f that defines position.</returns>
sf::Vector2f const & Player::getRightWeaponPos()
{
	return m_weaponRight.getPosition();
}

/// <summary>
/// @brief get the alive state of the player.
/// 
/// 
/// </summary>
/// <returns>readonly reference true if player is alive, false if player dead</returns>
bool const & Player::isAlive()
{
	return m_alive;
}

/// <summary>
/// @brief checks if player is invulnerable.
/// 
/// 
/// </summary>
/// <returns>true means player is unhittable, false means he is hittable.</returns>
bool const & Player::isInvulnerable()
{
	return m_shield.isInvulnerable();
}

/// <summary>
/// @brief This method sets end points of the connectors.
/// 
/// 
/// </summary>
/// <param name="leftConnectorPos">new position of the left connector.</param>
/// <param name="rightConnectorPos">new position of the right connector.</param>
void Player::setConnectorPos(sf::Vector2f leftConnectorPos, sf::Vector2f rightConnectorPos)
{
	m_leftConnectorEnd = leftConnectorPos;
	m_rightConnectorEnd = rightConnectorPos;
}

/// <summary>
/// @brief sets the attached weapons bool to check.
/// 
/// 
/// </summary>
/// <param name="check">the new state of attached weapons</param>
void Player::setAttachedWeapons(bool check)
{
	m_attachedWeapons = check;
}

/// <summary>
/// @brief a getter that returns a constant reference to the end of the left connector.
/// 
/// 
/// </summary>
/// <returns>constant reference to a vector2f.</returns>
const sf::Vector2f & Player::getLeftConnectorPos()
{
	return m_leftConnectorEnd;
}

/// <summary>
/// @brief a getter that returns a constant reference to the end of the right connector.
/// 
/// 
/// </summary>
/// <returns>constant reference to a vector2f.</returns>
const sf::Vector2f & Player::getRightConnectorPos()
{
	return m_rightConnectorEnd;
}

/// <summary>
/// @brief this method scales down both weapons.
/// 
/// 
/// </summary>
void Player::fadeOutWeapons()
{
	m_weaponLeft.fadeOut();
	m_weaponRight.fadeOut();
}

/// <summary>
/// @brief this is a function that sets both weapons alpha to passed value.
/// 
/// 
/// </summary>
/// <param name="alpha">determines new alpha of weapon sprites as a float.</param>
void Player::setWeaponsAlpha(float alpha)
{
	m_weaponLeft.setAlpha(alpha);
	m_weaponRight.setAlpha(alpha);
}

/// <summary>
/// @brief this calls both weapons setter for the can fire bool 
/// and sets them to the passed parameter.
/// 
/// 
/// </summary>
/// <param name="fire">the new state of the can fire of both weapons</param>
void Player::setCanFire(bool fire)
{
	m_weaponLeft.setCanFire(fire);
	m_weaponRight.setCanFire(fire);
}

/// <summary>
/// @brief a getter for the is docking bool of the ship.
/// 
/// 
/// </summary>
/// <returns>constant boolean that is the is docking variable of Ship</returns>
const bool Player::isDocking()
{
	return m_ship.getDocking();
}

/// <summary>
/// @brief this function will take the passsed in vector2f and assign the players ship position to the passed vector.
/// 
/// 
/// </summary>
/// <param name="pos">new position of the Ship defined as Vector2f</param>
void Player::setPosition(sf::Vector2f pos)
{
	m_ship.setPosition(pos);
}

/// <summary>
/// @brief this method will call the method that belongs to the BulletManager and iterates through the 
/// vector of bullets and sets them to active. Used on restarting the game.
/// 
/// 
/// </summary>
void Player::resetBullets()
{
	m_bulletManager.clearAllBullets();
}

/// <summary>
/// @brief this method resets the type of the weapon back to standard.
/// 
/// 
/// </summary>
void Player::resetWeapons()
{
	m_weaponLeft.resetWeaponType();
	m_weaponLeft.setAlpha(255.0f);
	m_weaponRight.resetWeaponType();
	m_weaponRight.setAlpha(255.0f);
}

/// <summary>
/// @brief this method will reset the player and all his components.
/// this means that the bullets,shield, weapon, position and velocity will reset.
/// 
/// 
/// </summary>
void Player::reset()
{
	m_ship.resetShip();
	this->setAlive(true);
	resetBullets();
	resetWeapons();
	m_shield.resetShield();
	m_background.setTargetColor(m_weaponLeft.getBgColor());
	this->setAttachedWeapons(true);
	m_bulletManager.setWeaponOverheatingValues(0.1f, 0.004f, 0.003f);
}

/// <summary>
/// @brief get the fire rate from the bullet manager.
/// 
/// 
/// </summary>
/// <returns>fire rate of current bullet type</returns>
float Player::getFireRate()
{
	return m_bulletManager.getFireRate();
}

/// <summary>
/// @brief get the time since fired from bullet manager.
/// 
/// 
/// </summary>
/// <returns>time since firing previous bullet</returns>
float Player::getTimeSinceFire()
{
	return m_bulletManager.getTimeSinceFire();
}

/// <summary>
/// @brief get overcharge value from bullet manager.
/// 
/// 
/// </summary>
/// <returns>the current overload value as a float</returns>
float Player::getOvercharge()
{
	return m_bulletManager.getOvercharge();
}

/// <summary>
/// @getter for the overheat bool.
/// 
/// 
/// </summary>
/// <returns>overheat boolean</returns>
bool Player::getOverheat()
{
	return m_bulletManager.getOverheat();
}

/// <summary>
/// @brief setter for the overheat bool.
/// 
/// 
/// </summary>
/// <param name="check">new value of overheat</param>
void Player::setOverheat(bool check)
{
	m_bulletManager.setOverheat(check);
}
