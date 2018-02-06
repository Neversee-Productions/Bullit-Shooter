#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

// STL Includes
// SFML Includes
// Project Includes
#include "entities\Entities.h"

/// 
/// @author Rafael Plugge
/// @brief
///		Simple collision system used for organizing collision code in one place.
/// 
/// `Non-copyable` system.
/// 
class CollisionSystem
{
public: // Constructors/Destructor
	CollisionSystem() = delete; // Default Constructor
	CollisionSystem(Player& player, AsteroidManager & asteroidManager);
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
	void updateAsteroids();

	void asteroidVsBullet(Asteroid & asteroid, bullets::Bullet & bullet);
	void playerVsAsteroid(Player & player, Asteroid & asteroid);
private: // Private Member Variables
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

};

#endif // !COLLISION_SYSTEM_H