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
		enemy.update();
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
		enemy.draw(window, deltaTime);
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
	m_enemies.push_back(ai::AiBasic(player, spawnPosition));
	m_enemies.back().init(m_sptrResources->m_sptrBasicEnemy);
}

/// <summary>
/// @brief Remove the enemy from the manager.
/// 
/// 
/// </summary>
/// <param name="_where">iterator of which enemy to remove</param>
void BasicEnemyManager::despawn(std::list<ai::AiBasic>::iterator _where)
{
	m_enemies.erase(_where);
}
