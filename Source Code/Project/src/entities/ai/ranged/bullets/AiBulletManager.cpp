#include "entities\ai\ranged\bullets\AiBulletManager.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
AiBulletManager::AiBulletManager()
	: m_bullets()
	, m_sptrResources(nullptr)
{
	m_bullets.reserve(20);
}

/// <summary>
/// @brief Initialize the bullet vector.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to the loaded resources.</param>
void AiBulletManager::init(std::shared_ptr<ai::Resources> sptrResources)
{
	m_sptrResources = sptrResources;
	AiBullet bullet(*sptrResources);
	bullet.setActive(false);
	m_bullets.resize(10, bullet);
}

/// <summary>
/// @brief Update all active bullets.
/// 
/// 
/// </summary>
void AiBulletManager::update()
{
	for (auto & bullet : m_bullets)
	{
		if (bullet.getActive())
		{
			bullet.update();
		}
	}
}

/// <summary>
/// @brief Render all the active bullets.
/// 
/// 
/// </summary>
/// <param name="window">reference to the target window.</param>
/// <param name="deltaTime">read-only reference to the delta time since last draw call.</param>
void AiBulletManager::draw(Window & window, float const & deltaTime)
{
	for (auto & bullet : m_bullets)
	{
		if (bullet.getActive())
		{
			bullet.draw(window, deltaTime);
		}
	}
}

/// <summary>
/// @brief Spawns a bullet at position with a heading of direction.
/// 
/// 
/// </summary>
/// <param name="position">read-only reference to the spawn position.</param>
/// <param name="direction">read-only reference to the direction the bullet is heading.</param>
void AiBulletManager::shoot(sf::Vector2f const & position, sf::Vector2f const & direction)
{
	for (auto & bullet : m_bullets)
	{
		if (!bullet.getActive())
		{
			bullet.setPosition(position);
			bullet.setHeading(direction);
			bullet.setRotation(thor::polarAngle(direction));
			bullet.setActive(true);
			return;
		}
	}
	AiBullet bullet(*m_sptrResources);
	bullet.setPosition(position);
	bullet.setHeading(direction);
	bullet.setRotation(thor::polarAngle(direction));
	m_bullets.push_back(std::move(bullet));
}
