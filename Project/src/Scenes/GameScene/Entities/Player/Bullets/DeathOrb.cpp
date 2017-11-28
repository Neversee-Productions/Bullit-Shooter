#include "Scenes\GameScene\Entities\Player\Bullets\DeathOrb.h"

const float bullets::DeathOrb::s_FIRE_RATE = 1.0f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::DeathOrb::DeathOrb()
	: Bullet()
{
	m_speed = 6.0f * 60.0f;
	m_velocity.y = -m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(10.0f, 10.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
	
	//change collision rectangle
	updateBox();
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::DeathOrb::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief update collisions and movement
/// 
/// 
/// </summary>
void bullets::DeathOrb::update()
{
	m_position += m_velocity * UPDATE_DT;
	m_bulletRect.setPosition(m_position.x, m_position.y);
	updateBox();
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
}
