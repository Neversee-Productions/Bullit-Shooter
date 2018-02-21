#ifndef RANGED_ENEMY_MANAGER_H
#define RANGED_ENEMY_MANAGER_H

// STD Includes
#include <vector>
// SFML Includes
// Project Includes
#include "entities\ai\ranged\AiRanged.h"
#include "entities\ai\ranged\AiResources.h"

/// 
/// @brief Defines the enemy manager for ranged enemy ai.
/// @author Rafael Plugge
/// 
/// 
/// 
class RangedEnemyManager
{
public: // Constructors/Destructor
	RangedEnemyManager(Player const & player);
	~RangedEnemyManager() = default;

public: // Public Member Functions
	void init(std::shared_ptr<ai::Resources> sptrResources);
	void update();
	void draw(Window & window, float const & deltaTime);
	void spawn(sf::Vector2f const & spawnPoint);
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
private: // Private Member Variables
	/// <summary>
	/// @brief Defines the ranged enemies.
	/// 
	/// 
	/// </summary>
	std::vector<ai::AiRanged> m_enemies;
	/// <summary>
	/// @brief read-only reference to the player.
	/// 
	/// 
	/// </summary>
	Player const & m_player;
	/// <summary>
	/// @brief shared pointer to ranged ai resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<ai::Resources> m_sptrResources;
};


#endif // !RANGED_ENEMY_MANAGER_H