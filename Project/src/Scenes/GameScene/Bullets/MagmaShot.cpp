#include "Scenes\GameScene\Bullets\MagmaShot.h"

const float bullets::MagmaShot::s_FIRE_RATE = 2.0f;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::MagmaShot::MagmaShot()
	: Bullet()
	, m_explode(false)
{
	m_speed = 4.0f;
	updateVelocityVector();

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(15.0f, 15.0f));

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
/// @brief this method simply sets explode bool to true.
/// 
/// 
/// </summary>
/// <param name="check">Defines the new explode bool value</param>
void bullets::MagmaShot::explode(bool check)
{
	m_explode = check;
}

