#include "entities\RangedEnemyManager.h"

/// <summary>
/// @brief Default Constructor.
/// 
/// Initialize member variables
/// </summary>
RangedEnemyManager::RangedEnemyManager(Player const & player)
	: m_enemies()
	, m_player(player)
	, m_sptrResources(nullptr)
{
	m_enemies.reserve(40);
}

/// <summary>
/// @brief Initialize external resources.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to initialized resources.</param>
void RangedEnemyManager::init(std::shared_ptr<ai::Resources> sptrResources)
{
	m_sptrResources = sptrResources;
}

/// <summary>
/// @brief Update all active enemies.
/// 
/// 
/// </summary>
void RangedEnemyManager::update()
{
	for (auto & enemy : m_enemies)
	{
		enemy.update();
	}
}

/// <summary>
/// @brief Render all active enemies.
/// 
/// 
/// </summary>
/// <param name="window">reference to the target window.</param>
/// <param name="deltaTime">read-only reference to delta time between draw calls.</param>
void RangedEnemyManager::draw(Window & window, float const & deltaTime)
{
	for (auto & enemy : m_enemies)
	{
		enemy.draw(window, deltaTime);
	}
}

/// <summary>
/// @brief Spawn enemy at spawn point.
/// 
/// 
/// </summary>
/// <param name="spawnPoint">read-only reference spawn point.</param>
void RangedEnemyManager::spawn(sf::Vector2f const & spawnPoint)
{
	for (auto & enemy : m_enemies)
	{
		if (!enemy.getActive())
		{
			enemy.spawn(spawnPoint);
			return;
		}
	}
	if (m_enemies.size() < m_enemies.capacity())
	{
		m_enemies.push_back(ai::AiRanged(m_player, spawnPoint));
		m_enemies.back().init(m_sptrResources);
	}
}

/// <summary>
/// @brief Reset the enemy manager.
/// 
/// 
/// </summary>
void RangedEnemyManager::reset()
{
	m_enemies.clear();

}
