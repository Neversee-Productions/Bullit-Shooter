#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

// STL Includes
#include <string>
#include <sstream>
// SFML Includes
// Project Includes
#include "entities\Entities.h"
#include "entities\BasicEnemyManager.h"
#include "gui\game_ui\GameUI.h"

/// 
/// @author Rafael Plugge
/// @brief
///		Simple collision system used for organizing collision code in one place.
/// 
/// `Non-Default Constructible`, `Non-Copyable` system.
/// 
class CollisionSystem
{
public: // Constructors/Destructor
	CollisionSystem() = delete; // Default Constructor
	CollisionSystem(Player& player, AsteroidManager & asteroidManager, BasicEnemyManager & basicEnemyManager, Pickup & pickup, GameUI & gameUi);
	CollisionSystem(const CollisionSystem &) = delete; // Copy Constructor
	CollisionSystem(CollisionSystem &&) = default; // Move Constructor

	~CollisionSystem() = default; // Destructor

	CollisionSystem & operator=(const CollisionSystem &) = delete; // Copy Assignment Operator
	CollisionSystem & operator=(CollisionSystem &&) = default; // Move Assignment Operator

public: // Public Member Functions
	void update();
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
	void updatePlayer();
	void updatePlayerBullets();
	void updatePlayerBulletToAsteroids(bullets::Bullet & bullet);
	void updatePlayerBulletToEnemies(bullets::Bullet & bullet);
	void updatePlayerToPickup();
	void updatePlayerToGameUi();

	void asteroidVsBullet(Asteroid & asteroid, bullets::Bullet & bullet);
	void enemyVsBullet(ai::AiBasic & enemy, bullets::Bullet & bullet);
	void playerVsAsteroid(Player & player, Asteroid & asteroid);
	void playerVsPickup(Player & player, Pickup & pickup);
	void playerVsGameUi(Player & player, GameUI & gameUi);
	void playerVsEnemy(Player & player, ai::AiBasic & enemy);

	void solveElasticCollision(Asteroid & asteroid1, Asteroid & asteroid2);

private: // Private Member Variables
	/// <summary>
	/// @brief read-only reference to the update delta time.
	/// 
	/// 
	/// </summary>
	float const & m_UPDATE_DT;

	/// <summary>
	/// @brief Reference to singleton sound manager instance.
	/// 
	/// 
	/// </summary>
	SoundManager & m_soundManager;

	/// <summary>
	/// @brief reference to player.
	/// 
	/// 
	/// </summary>
	Player & m_player;

	/// <summary>
	/// @brief reference to asteroid manager.
	/// 
	/// 
	/// </summary>
	AsteroidManager & m_asteroidManager;

	/// <summary>
	/// @brief reference to basic enemy manager.
	/// 
	/// 
	/// </summary>
	BasicEnemyManager & m_basicEnemyManager;

	/// <summary>
	/// @brief reference to pickup.
	/// 
	/// 
	/// </summary>
	Pickup & m_pickup;

	/// <summary>
	/// @brief reference to game UI.
	/// 
	/// 
	/// </summary>
	GameUI & m_gameUi;
};

#endif // !COLLISION_SYSTEM_H