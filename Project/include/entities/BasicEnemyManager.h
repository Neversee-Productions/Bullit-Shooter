#ifndef BASIC_ENEMY_MANAGER_H
#define BASIC_ENEMY_MANAGER_H

// Project Includes
#include "system\Window.h"
#include "ai\basic\AiBasic.h"

/// 
/// @author Rafael Plugge
/// @brief Defines the manager for basic enemies.
/// 
/// 
/// 
class BasicEnemyManager
{
public:
	/// 
	/// @author Rafael Plugge
	/// @brief Enemy manager resources.
	/// 
	/// 
	/// 
	struct Resources
	{
		/// <summary>
		/// @brief shared pointer to loaded basic enemy resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<ai::AiBasic::Resources> m_sptrBasicEnemy =
			std::make_shared<ai::AiBasic::Resources>();
	};

public: // Constructors/Destructor
	BasicEnemyManager() = default;
	~BasicEnemyManager() = default;

public: // Public Member Functions
	void init(std::shared_ptr<Resources> sptrResources, Player & player);
	void update();
	void draw(Window & window, float const & deltaTime);
	void spawn(Player & player, sf::Vector2f const & spawnPosition, sf::Vector2f const & spawnHeading, float const & angle);
	std::list<ai::AiBasic>::iterator despawn(std::list<ai::AiBasic>::iterator & _where);
	std::list<ai::AiBasic> & getEnemies();
	void reset();

public: // Public Member Variables
private: // Private Member Functions
private: // Private Member Variables
	/// <summary>
	/// @brief shared pointer to enemy manager resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Resources> m_sptrResources;
	/// <summary>
	/// @brief container of enemy instances.
	/// 
	/// 
	/// </summary>
	std::list<ai::AiBasic> m_enemies;
};

#endif // !BASIC_ENEMY_MANAGER_H