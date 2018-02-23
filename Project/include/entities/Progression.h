#ifndef PROGRESSION_H
#define PROGRESSION_H

// STD Includes
#include <string>
#include <memory>
// SFML Includes
#include "SFML\System\Time.hpp"
// Project Includes
#include "gui\game_ui\Score.h"
#include "gui\game_ui\GameUiResources.h"
#include "gui\game_ui\GameUI.h"
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
		Player & player,
		AsteroidManager & asteroidManager,
		BasicEnemyManager & basicEnemyManager,
		RangedEnemyManager & rangedEnemyManager,
		GameUI & gameUi
	);
	Progression(Progression const &) = default;
	Progression(Progression &&) = default;

	Progression & operator=(Progression const &) = default;
	Progression & operator=(Progression &&) = default;

	~Progression() = default;

public: // Public Member Functions
	void init(std::shared_ptr<gameUi::Resources> sptrResources);
	void reset();
	void update();
	void draw(Window & window, float const & deltaTime);
public: // Public Static Functions
	static int const & getBasicEnemies() { return s_spawnBasicEnemies; }
public: // Public Member Get's
public: // Public Member Set's
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
	void spawnRangedEnemies();
	sf::Vector2f randRangedEnemySpawn();
private: // Private Static Variables
	/// <summary>
	/// @brief Defines how many basic enemies to spawn.
	/// 
	/// 
	/// </summary>
	static int s_spawnBasicEnemies;
private: // Private Member Variables
	/// <summary>
	/// @brief reference to the player.
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
	/// <summary>
	/// @brief reference to the game ui.
	/// 
	/// 
	/// </summary>
	GameUI & m_gameUi;
	/// <summary>
	/// @brief stores read-only reference to score.
	/// 
	/// 
	/// </summary>
	int const & m_SCORE;
	/// <summary>
	/// @brief Time since start of game.
	/// 
	/// 
	/// </summary>
	sf::Time m_timer;
	/// <summary>
	/// @brief Update delta time converted to sf::Time.
	/// 
	/// 
	/// </summary>
	sf::Time const m_UPDATE_DT_TIME;
	/// <summary>
	/// @brief Defines the amount of time has to pass before a difficulty increase.
	/// 
	/// 
	/// </summary>
	float const m_DIF_INC;
	/// <summary>
	/// @brief Defines how many times the difficulty went up.
	/// 
	/// 
	/// </summary>
	std::uint8_t m_difficultyLevel;
	/// <summary>
	/// @brief tells draw call there has been a difficulty increase.
	/// 
	/// 
	/// </summary>
	bool m_difficultyWentUp;
	/// <summary>
	/// @brief defines cap on ranged enemy spawning.
	/// 
	/// 
	/// </summary>
	int const m_RANGED_ENEMY_SPAWN_CAP;
	/// <summary>
	/// @brief defines the cap on basic enemy spawning.
	/// 
	/// 
	/// </summary>
	int const m_BASIC_ENEMY_SPAWN_CAP;
	/// <summary>
	/// @brief defines amout of enemies to spawn.
	/// 
	/// 
	/// </summary>
	int m_rangedEnemySpawnAmount;
	/// <summary>
	/// @brief defines maximum amount of spawnable asteroids.
	/// 
	/// 
	/// </summary>
	int const m_ASTEROID_SPAWN_CAP;
	/// <summary>
	/// @brief Will display Progression::m_timer.
	/// 
	/// 
	/// </summary>
	sf::Text m_timerDisplay;
};

#endif // !PROGRESSION_H