#include "Scenes\GameScene\Bullets\FireBlast.h"

const float bullets::FireBlast::s_FIRE_RATE = 0.1f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::FireBlast::FireBlast()
	: Bullet()
{
	m_speed = 16.0f;
	m_velocity.x = m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(10.0f, 5.0f));

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
float bullets::FireBlast::getFireRate()
{
	return s_FIRE_RATE;
}

