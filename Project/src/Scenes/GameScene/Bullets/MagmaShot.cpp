#include "Scenes\GameScene\Bullets\MagmaShot.h"

const float bullets::MagmaShot::s_FIRE_RATE = 2.0f;
const sf::Vector2f bullets::MagmaShot::s_SIZE_CHANGE = sf::Vector2f(1.0f, 1.0f);
const sf::Vector2f bullets::MagmaShot::s_DEFAULT_SIZE = sf::Vector2f(15.0f,15.0f);


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::MagmaShot::MagmaShot()
	: Bullet()
	, m_explode(false)
	, TIMETOLIVE(4.0f)
{
	m_speed = 4.0f;
	updateVelocityVector();

	//different size to parent
	m_bulletRect.setSize(s_DEFAULT_SIZE);
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	updateBox();
}

/// <summary>
/// @brief Overloaded update function.
/// 
/// This will update like the bullet
/// except  when the bullet collides with something it will explode into a circle
/// </summary>
void bullets::MagmaShot::update()
{
	TIMETOLIVE -= App::getUpdateDeltaTime();
	if (TIMETOLIVE <= 0)
	{
		m_explode = true;
	}
	if (!m_explode)
	{
		Bullet::update();
	}
	else
	{
		m_bulletRect.setSize(m_bulletRect.getSize() + s_SIZE_CHANGE);
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		updateBox();
	}
	if (m_bulletRect.getSize().x > 40.0f)
	{
		setActive(false);
	}
}

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
float bullets::MagmaShot::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief overloaded set active method.
/// 
/// This method will check if active is being set to false
/// if yes then reset sphere to original size.
/// </summary>
/// <param name="active">determines the active state of bullet</param>
void bullets::MagmaShot::setActive(bool active)
{
	if (active == false)
	{
		m_bulletRect.setSize(s_DEFAULT_SIZE);
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		m_explode = false;
		TIMETOLIVE = 4.0f; //DELETE WHEN NOT TESTING
	}
	m_active = active;
}

/// <summary>
/// @brief this method simply sets explode bool to true.
/// 
/// 
/// </summary>
/// <param name="check">Defines the new explode bool value</param>
void bullets::MagmaShot::explode(bool check)
{
	m_explode = check;
}

