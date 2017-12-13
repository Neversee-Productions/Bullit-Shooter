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
	m_weaponLeft.update(m_ship.getShipRect());
	m_weaponRight.update(m_ship.getShipRect());
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

