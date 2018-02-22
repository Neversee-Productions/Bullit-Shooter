#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

// STL Includes
#include <string>
#include <sstream>
// SFML Includes
// Project Includes
#include "entities\Entities.h"
#include "entities\BasicEnemyManager.h"
#include "entities\RangedEnemyManager.h"
#include "gui\game_ui\GameUI.h"
#include "gui\game_ui\GameUiResources.h"

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
	CollisionSystem(
		Player& player
		, AsteroidManager & asteroidManager
		, BasicEnemyManager & basicEnemyManager
		, RangedEnemyManager & rangedEnemyManager
		, Pickup & pickup
		, GameUI & gameUi);
	CollisionSystem(const CollisionSystem &) = delete; // Copy Constructor
	CollisionSystem(CollisionSystem &&) = default; // Move Constructor

	~CollisionSystem() = default; // Destructor

	CollisionSystem & operator=(const CollisionSystem &) = delete; // Copy Assignment Operator
	CollisionSystem & operator=(CollisionSystem &&) = default; // Move Assignment Operator

public: // Public Member Functions
	void update();
	void setPickingUp(bool check);
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
	void updatePlayer();
	void updatePlayerBullets();
	void updatePlayerBulletToAsteroids(bullets::Bullet & bullet);
	void updatePlayerBulletToBasicEnemies(bullets::Bullet & bullet);
	void updatePlayerBulletToRangedEnemies(bullets::Bullet & bullet);
	void updatePlayerToPickup();
	void updatePlayerToGameUi();
	void updateAsteroids();
	void updateRangedEnemyBullets(ai::AiRanged & enemy);
	void updateRangedEnemyBulletToPlayer(AiBullet & bullet);

	void asteroidVsBullet(Asteroid & asteroid, bullets::Bullet & bullet);
	void baseEnemyVsBullet(ai::AiBase & enemy, bullets::Bullet & bullet);
	void basicEnemyVsBullet(ai::AiBasic & enemy, bullets::Bullet & bullet);
	void rangedEnemyVsBullet(ai::AiRanged & enemy, bullets::Bullet & bullet);
	void rangedEnemyBulletVsPlayer(AiBullet & bullet, Player & player);
	void playerVsAsteroid(Player & player, Asteroid & asteroid);
	void playerVsPickup(Player & player, Pickup & pickup);
	void playerVsBasicEnemy(Player & player, ai::AiBasic & enemy);
	void asteroidVsAsteroid(Asteroid & asteroid1, Asteroid & asteroid2);

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
	/// @brief reference to ranged enemy manager.
	/// 
	/// 
	/// </summary>
	RangedEnemyManager & m_rangedEnemyManager;
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
	/// <summary>
	/// @brief check if power up being picked up.
	/// 
	///
	/// </summary>
	bool m_pickingUp;
	/// <summary>
	/// @brief define if the pickup sound is currently playing.
	/// 
	/// 
	/// </summary>
	bool m_pickupSoundPlaying;
	/// <summary>
	/// @brief define stay clear sound playing.
	/// 
	/// 
	/// </summary>
	bool m_stayClearPlaying;
};

#endif // !COLLISION_SYSTEM_H