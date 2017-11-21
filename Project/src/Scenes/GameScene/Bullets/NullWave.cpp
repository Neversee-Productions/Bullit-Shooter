#include "Scenes\GameScene\Bullets\NullWave.h"

const float bullets::NullWave::s_FIRE_RATE = 1.0f;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::NullWave::NullWave()
	: Bullet()
{
	m_speed = 8.0f;
	m_velocity.x = m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(10.0f, 30.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @brief update velocity and position.
/// 
/// 
/// </summary>
void bullets::NullWave::update()
{
	Bullet::update();
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::NullWave::getFireRate()
{
	return s_FIRE_RATE;
}
