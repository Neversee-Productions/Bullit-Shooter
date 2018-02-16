#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H

#include <vector>
#include <memory>
#include "Asteroid.h"

///
/// @brief Asteroid manager class.
/// @author Sebastian Kruzel
/// @author Rafael Plugge
/// 
/// A manager of asteroids, reuses a vector
/// of asteroids.
/// 
class AsteroidManager
{
public: // Constructors/Destructor
	AsteroidManager();
	~AsteroidManager() = default;

public: // Public Member Functions
	void init(std::shared_ptr<Asteroid::Resources> sptrResourcesr);
	void update();
	void draw(Window & window, float const & deltaTime);
	void initAsteroidVector();
	std::vector<Asteroid>& getAsteroidVector();
	void setSpawnStartTimer(float time);
	void resetAsteroids();
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
	void updateSpawning();
	float generateRandomTimer() const;
private: // Private Member Variables
	/// <summary>
	/// @brief shared pointer to loaded resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Asteroid::Resources> m_sptrResources;

	/// <summary>
	/// @brief store read-only reference to update delta time, in seconds.
	/// 
	/// 
	/// </summary>
	float const & m_UPDATE_DT;

	/// <summary>
	/// @brief define our stl container of Asteroids.
	/// 
	/// 
	/// </summary>
	std::vector<Asteroid> m_asteroidsVector;

	/// <summary>
	/// @brief define how long since last spawned asteroid.
	/// 
	/// 
	/// </summary>
	float m_asteroidSpawnTimer;

	/// <summary>
	/// @brief define length of time between asteroid spawns.
	/// 
	/// 
	/// </summary>
	float m_asteroidSpawnFrequency;

	/// <summary>
	/// @brief define when the asteroids will start spawning.
	/// 
	/// 
	/// </summary>
	float m_asteroidSpawnStart;

};

#endif // !ASTEROID_MANAGER_H
