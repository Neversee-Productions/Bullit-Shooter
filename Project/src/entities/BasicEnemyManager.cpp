#include "entities\BasicEnemyManager.h"

/// <summary>
/// @brief store loaded resource pointer.
/// 
/// Also initializes a single enemy.
/// </summary>
/// <param name="sptrResources">shared pointer to loaded resources.</param>
/// <param name="player">reference to player</param>
void BasicEnemyManager::init(std::shared_ptr<Resources> sptrResources, Player & player)
{
	m_sptrResources = sptrResources;
	this->spawn(player, { 760.0f, 0.0f });
}

/// <summary>
/// @brief update all enemies.
/// 
/// 
/// </summary>
void BasicEnemyManager::update()
{
	for (auto & enemy : m_enemies)
	{
		if (enemy.isActive())
		{
			enemy.update();
		}
	}
}

/// <summary>
/// @brief draw all enemies.
/// 
/// 
/// </summary>
/// <param name="window">reference to target window.</param>
/// <param name="deltaTime">read-only reference to time between draw calls.</param>
void BasicEnemyManager::draw(Window & window, float const & deltaTime)
{
	for (auto & enemy : m_enemies)
	{
		if (enemy.isActive())
		{
			enemy.draw(window, deltaTime);
		}
	}
}

/// <summary>
/// @brief spawn a enemy at location.
/// 
/// 
/// </summary>
/// <param name="player">required for enemy behaviour.</param>
/// <param name="spawnPosition">determines spawn location.</param>
void BasicEnemyManager::spawn(Player & player, sf::Vector2f const & spawnPosition)
{
	for (auto & enemy : m_enemies)
	{
		if (!enemy.isActive())
		{
			enemy.spawn(spawnPosition);
			return;
		}
	}

	// Enemy must be pushed into the vector upon creation
	// Else a read-access violation will occur due to
	// basic ai's states referencing their creator.
	m_enemies.push_back(ai::AiBasic(player, spawnPosition));
	m_enemies.back().init(m_sptrResources->m_sptrBasicEnemy);
}

/// <summary>
/// @brief Remove the enemy from the manager.
/// 
/// 
/// </summary>
/// <param name="_where">iterator of which enemy to remove</param>
std::list<ai::AiBasic>::iterator BasicEnemyManager::despawn(std::list<ai::AiBasic>::iterator & _where)
{
	return m_enemies.erase(_where);
}

/// <summary>
/// @brief get a reference to all enemies.
/// 
/// 
/// </summary>
/// <returns></returns>
std::list<ai::AiBasic> & BasicEnemyManager::getEnemies()
{
	return m_enemies;
}

/// <summary>
/// @brief Reset entire enemy manager.
/// 
/// 
/// </summary>
void BasicEnemyManager::reset()
{
	m_enemies.clear();
}
