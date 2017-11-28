#include "Scenes\GameScene\AsteroidManager.h"


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
	m_asteroidsVector.reserve(10);
	m_asteroidsVector.resize(10);
	for (auto itt = m_asteroidsVector.begin(), end = m_asteroidsVector.end(); itt != end; ++itt)
	{
		//itt->insert(std::unique_ptr<Asteroid>(std::make_unique<Asteroid>()));
		//itt->
	}
}
