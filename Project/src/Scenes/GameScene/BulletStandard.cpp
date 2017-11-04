#include "Scenes\GameScene\BulletStandard.h"

const float BulletStandard::s_FIRE_RATE = 1.0f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
BulletStandard::BulletStandard()
	: Bullet()
{
}

/// <summary>
/// @brief This is the overloaded constructor.
/// 
/// 
/// </summary>
/// <param name="position">defines the position of the bullet</param>
BulletStandard::BulletStandard(sf::Vector2f position)
	: Bullet(position, BulletTypes::Standard)
{
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns></returns>
float BulletStandard::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief updates the bullet
/// 
/// 
/// </summary>
void BulletStandard::update()
{
	m_position += sf::Vector2f(10.0f, 0.0f);
	m_bulletRect.setPosition(m_position.x, m_position.y);
	updateBox();
}
