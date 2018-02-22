#ifndef PROGRESSION_H
#define PROGRESSION_H

// STD Includes
#include <string>
// SFML Includes
#include "SFML\Graphics.hpp"
// Project Includes
#include "gui\game_ui\Score.h"
#include "entities\Asteroids\AsteroidManager.h"
#include "entities\BasicEnemyManager.h"
#include "entities\RangedEnemyManager.h"

/// 
/// @brief Defines the game progression
/// @author Rafael Plugge
/// 
/// 
/// 
class Progression
{
public: // Constructors/Assignment Operators/Destructor
	Progression() = delete;
	Progression(
		AsteroidManager & asteroidManager,
		BasicEnemyManager & basicEnemyManager,
		RangedEnemyManager & rangedEnemyManager
	);
	Progression(Progression const &) = default;
	Progression(Progression &&) = default;

	Progression & operator=(Progression const &) = default;
	Progression & operator=(Progression &&) = default;

	~Progression() = default;

public: // Public Member Functions
public: // Public Member Get's
public: // Public Member Set's
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
private: // Private Member Variables
	/// <summary>
	/// @brief reference to asteroid manager.
	/// 
	/// 
	/// </summary>
	AsteroidManager & m_asteroidManager;
	/// <summary>
	/// @brief reference to the basic enemy manager.
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
};

#endif // !PROGRESSION_H