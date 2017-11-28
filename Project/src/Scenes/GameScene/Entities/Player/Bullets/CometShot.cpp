#include "Scenes\GameScene\Entities\Player\Bullets\CometShot.h"

const float bullets::CometShot::s_FIRE_RATE = 0.2f;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::CometShot::CometShot()
	: Bullet()
{
	m_speed = 12.0f * 60.0f;
	m_velocity.y = -m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(10.0f, 5.0f));
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
float bullets::CometShot::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief Update velocity and position.
/// 
/// 
/// </summary>
void bullets::CometShot::update()
{
	Bullet::update();
}

