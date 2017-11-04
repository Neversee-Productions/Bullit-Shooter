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
void BulletManager::fireBullet(const sf::Vector2f& position1,const sf::Vector2f& position2,const BulletTypes& type)
{
	switch (type)
	{
	case BulletTypes::Standard:
		if (m_timeSinceFire > BulletStandard::getFireRate())
		{
			int numFired = 0; //local variable to see how many bullets were fired used to determine if 2 turrets shot
			for (auto & bullet : m_standardBullets)
			{
				if (!bullet.isActive())
				{
					if (numFired == 0)
					{
						bullet.setPosition(position1);
						bullet.setActive(true);
						numFired++;
					}
					else if (numFired == 1)
					{
						bullet.setPosition(position2);
						bullet.setActive(true);
						numFired++;
						break;
					}
				}
			}
			m_timeSinceFire = 0;
		}
		break;
	default:
		break;
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
	default:
		break;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
void BulletManager::reuseBullet(Bullet& bullet,sf::Vector2f pos)
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
}

/// <summary>
/// @brief method to update all bullets.
/// 
/// 
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
}

