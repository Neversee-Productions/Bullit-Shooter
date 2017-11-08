#include "Scenes\GameScene\BulletManager.h"

/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
BulletManager::BulletManager()
	: m_timeSinceFire(10.0f)
	, m_windowC2Rect(App::getWindowC2Rect())
{
}

/// <summary>
/// @brief method that will add bullet to vector
/// 
/// 
/// </summary>
/// <param name="position1">define first gun position</param>
/// <param name="position2">define second gun position</param>
/// <param name="type">define type of bullet</param>
void BulletManager::fireBullet(const sf::Vector2f& position1,const sf::Vector2f& position2,const BulletTypes& type)
{
	if (m_timeSinceFire > bullets::Standard::getFireRate())
	{
		switch (type)
		{
		case BulletTypes::Standard:
			fireStandard(position1, position2);
			break;
		case BulletTypes::Empowered:
			fireEmpowered(position1, position2);
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// @brief this method initializes the bullet vector of a specific passed type.
/// 
/// Reserve and resize the vector in order to construct default bullets of passed type
/// </summary>
/// <param name="type">bullet type</param>
void BulletManager::initBulletvector(BulletTypes type)
{
	switch (type)
	{
	case BulletTypes::Standard:
		m_standardBullets.reserve(10);
		m_standardBullets.resize(10);
		break;
	case BulletTypes::Empowered:
		m_empoweredBullets.reserve(18);
		m_empoweredBullets.resize(18);
	default:
		break;
	}
}

/// <summary>
/// @brief reuse the bullet
/// 
/// resets the position and sets active to true.
/// </summary>
/// <param name="bullet">reference to bullet</param>
/// <param name="pos">new position</param>
void BulletManager::reuseBullet(bullets::Bullet& bullet,sf::Vector2f pos)
{
	bullet.setPosition(pos);
	bullet.setActive(true);
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void BulletManager::draw(Window & window, const float & deltaTime)
{
	for (auto & bullet : m_standardBullets)
	{
		bullet.draw(window, deltaTime);
	}
	for (auto & bullet : m_empoweredBullets)
	{
		bullet.draw(window, deltaTime);
	}
}

/// <summary>
/// @brief method to update all bullets.
/// 
/// update active bullets and check collision with window.
/// </summary>
void BulletManager::update()
{
	m_timeSinceFire += App::getUpdateDeltaTime();
	for (auto & bullet : m_standardBullets)
	{
		if (bullet.isActive())
		{
			if (!tinyh::c2AABBtoAABB(m_windowC2Rect, bullet.getCollisionRect()))
			{
				bullet.setActive(false);
			}
			else
			{
				bullet.update();
			}
		}
	}

	for (auto & bullet : m_empoweredBullets)
	{
		if (bullet.isActive())
		{
			if (!tinyh::c2AABBtoAABB(m_windowC2Rect, bullet.getCollisionRect()))
			{
				bullet.setActive(false);
			}
			else
			{
				bullet.update();
			}
		}
	}
}

/// <summary>
/// @brief standard bullet fire method
/// 
/// fires 3 bullets where 2 are offset by 30 and -30 degrees
/// </summary>
/// <param name="pos1">reference to first weapons position</param>
/// <param name="pos2">reference to second weapons position</param>
void BulletManager::fireStandard(const sf::Vector2f & pos1, const sf::Vector2f & pos2)
{
	int numFired = 0; //local variable to see how many bullets were fired used to determine if 2 turrets shot
	for (auto & bullet : m_standardBullets)
	{
		if (!bullet.isActive())
		{
			if (numFired == 0)
			{
				bullet.setPosition(pos1);
				bullet.setActive(true);
				numFired++;
			}
			else if (numFired == 1)
			{
				bullet.setPosition(pos2);
				bullet.setActive(true);
				numFired++;
				break;
			}
		}
	}
	m_timeSinceFire = 0;
}

/// <summary>
/// @brief empowered bullet fire method.
/// 
/// fires 3 bullets at each weapon
/// 2 of the bullets will be offset by -30 and 30 degrees
/// </summary>
/// <param name="pos1">reference to first weapons position</param>
/// <param name="pos2">reference to second weapons position</param>
void BulletManager::fireEmpowered(const sf::Vector2f & pos1, const sf::Vector2f & pos2)
{
	int numFired = 0; //local variable to see how many bullets were fired used to determine if 2 turrets shot
	bool oneFired = false; //local bool to check if one turret already fired all 3 bullets
	bool finishedFiring = false;
	for (auto & bullet : m_empoweredBullets)
	{
		if (!bullet.isActive())
		{
			switch (numFired)
			{
			case 0:
				setEmpowered(bullet, -5, pos1);
				break;
			case 1:
				setEmpowered(bullet, 0, pos1);
				break;
			case 2:
				setEmpowered(bullet, 5, pos1);
				break;
			case 3:
				setEmpowered(bullet, -5, pos2);
				break;
			case 4:
				setEmpowered(bullet, 0, pos2);
				break;
			case 5:
				setEmpowered(bullet, 5, pos2);
				break;
			default:
				break;
			}
			numFired++;
		}
		if (finishedFiring) //required in order to leave the for loop due to switch statement
		{
			break;
		}
	}
	m_timeSinceFire = 0;
}

/// <summary>
/// @brief set properties of an empowered bullet.
/// 
/// 
/// </summary>
/// <param name="bullet">reference to a bullet</param>
/// <param name="angle">reference to the angle to fire</param>
/// <param name="pos">reference to the position to fire at</param>
void BulletManager::setEmpowered(bullets::Empowered & bullet, const float & angle, const sf::Vector2f& pos)
{
	bullet.setPosition(pos);
	bullet.setAngle(angle);
	bullet.updateVelocityVector();
	bullet.setActive(true);
}

