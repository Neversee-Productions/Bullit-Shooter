#include "Scenes\GameScene\Entities\Asteroids\AsteroidManager.h"


/// <summary>
/// @brief default constructor.
/// 
/// 
/// </summary>
AsteroidManager::AsteroidManager()
{
}

/// <summary>
/// @brief initializes the asteroid vector.
/// 
/// 
/// </summary>
void AsteroidManager::initAsteroidVector()
{
	for (int count = 0; count <= 9; ++count)
	{
		m_asteroidsVector.push_back(std::move(std::make_unique<Asteroid>()));
	}
}

/// <summary>
/// @brief A getter of the vector of asteroid pointers.
/// 
/// 
/// </summary>
/// <returns>Return the vector of pointers to asteroids.</returns>
const std::vector<std::unique_ptr<Asteroid>>& AsteroidManager::getAsteroidVector()
{
	return m_asteroidsVector;
}
