#include "Entities\Player\Bullets\MagmaShot.h"

const float bullets::MagmaShot::s_FIRE_RATE = 0.8f;
const sf::Vector2f bullets::MagmaShot::s_SIZE_CHANGE = sf::Vector2f(1.0f, 1.0f);
const sf::Vector2f bullets::MagmaShot::s_DEFAULT_SIZE = sf::Vector2f(45.0f, 45.0f);
const float bullets::MagmaShot::s_MAX_SIZE = bullets::MagmaShot::s_DEFAULT_SIZE.x + 35.0f;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::MagmaShot::MagmaShot()
	: Bullet()
	, m_explode(false)
	, m_damage(0.2f)
{
	m_speed = 6.0f * 60.0f;
	//updateVelocityVector();
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

	//different size to parent
	m_bulletRect.setSize(s_DEFAULT_SIZE);
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	m_type = BulletTypes::MagmaShot;

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
	if (m_bulletRect.getSize().x > s_MAX_SIZE)
	{
		setActive(false);
	}
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
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
		std::string const LOOP_ID("loop");
		this->setAnimation(LOOP_ID);
		m_bulletRect.setSize(s_DEFAULT_SIZE);
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		m_explode = false;
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
	std::string const IMPACT_ID("impact");
	this->setAnimation(IMPACT_ID);
}

/// <summary>
/// @brief returns yes/no on whether this bullet is in the explosion state.
/// 
/// 
/// </summary>
/// <returns>True for yes, false for no.</returns>
bool bullets::MagmaShot::isExplosion()
{
	return m_explode;
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::MagmaShot::getDamage()
{
	return m_damage;
}

