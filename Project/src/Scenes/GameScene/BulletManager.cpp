#include "Scenes\GameScene\BulletManager.h"


/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
BulletManager::BulletManager()
{
}

/// <summary>
/// @brief method that will add bullet to vector
/// 
/// 
/// </summary>
void BulletManager::fireBullet(sf::Vector2f position)
{
	m_standardBullets.push_back(BulletStandard(position));
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
	for (auto & bullet : m_standardBullets)
	{
		bullet.update();
	}
}

