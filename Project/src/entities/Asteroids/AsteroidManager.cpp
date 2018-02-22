#include "Entities\Asteroids\AsteroidManager.h"

/// <summary>
/// @brief default constructor.
/// 
/// 
/// </summary>
AsteroidManager::AsteroidManager()
	: m_UPDATE_DT(App::getUpdateDeltaTime())
	, m_asteroidsVector()
	, m_asteroidSpawnFrequency(0.0f)
	, m_asteroidSpawnTimer(0.0f)
	, m_asteroidSpawnStart(5.0f)
{
	m_asteroidSpawnFrequency = this->generateRandomTimer();
}

/// <summary>
/// @brief Initialize asteroid manager resources.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to asteroid resources (assumed to be valid).</param>
void AsteroidManager::init(std::shared_ptr<Asteroid::Resources> sptrResources)
{
	m_sptrResources = sptrResources;
	this->initAsteroidVector();
}

/// <summary>
/// @brief Update vector of asteroids
/// 
/// 
/// </summary>
void AsteroidManager::update()
{
	if (m_asteroidSpawnStart <= 0.0f)
	{
		this->updateSpawning();
		for (auto & asteroid : m_asteroidsVector)
		{
			if (asteroid.isActive())
			{
				asteroid.update();
			}
		}
	}
	else
	{
		m_asteroidSpawnStart -= App::getUpdateDeltaTime();
	}
}

/// <summary>
/// @brief Draw all alive asteroids
/// 
/// 
/// </summary>
/// <param name="window">reference to target window</param>
/// <param name="deltaTime">read-only reference to delta time from last draw call.</param>
void AsteroidManager::draw(Window & window, float const & deltaTime)
{
	for (auto & asteroid : m_asteroidsVector)
	{
		if (asteroid.isActive())
		{
			asteroid.draw(window, deltaTime);
		}
	}
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
		m_asteroidsVector.push_back(Asteroid(m_sptrResources));
	}
}

/// <summary>
/// @brief A getter of the vector of asteroid pointers.
/// 
/// 
/// </summary>
/// <returns>Return the vector of pointers to asteroids.</returns>
std::vector<Asteroid>& AsteroidManager::getAsteroidVector()
{
	return m_asteroidsVector;
}

/// <summary>
/// @brief 
/// 
/// 
/// </summary>
/// <param name="time"></param>
void AsteroidManager::setSpawnStartTimer(float time)
{
	m_asteroidSpawnStart = time;
}

/// <summary>
/// @brief this function will set all asteroids to inactive.
/// 
/// 
/// </summary>
void AsteroidManager::resetAsteroids()
{
	for (auto & asteroid : m_asteroidsVector)
	{
		if (asteroid.isActive())
		{
			asteroid.setActive(false);
		}
	}
}

/// <summary>
/// @brief Updates the spawning mechanic of the asteroids.
/// 
/// 
/// </summary>
void AsteroidManager::updateSpawning()
{
	m_asteroidSpawnTimer += m_UPDATE_DT;
	if (m_asteroidSpawnTimer >= m_asteroidSpawnFrequency)
	{
		// spawn next unused asteroid here
		for (auto & asteroid : m_asteroidsVector)
		{
			if (!asteroid.isActive())
			{
				asteroid.reuseAsteroid();
				break;
			}
			m_asteroidSpawnFrequency = generateRandomTimer();
		}
		m_asteroidSpawnTimer = 0.0f;
	}
}

/// <summary>
/// @brief generate number from 0 to 3.
/// 
/// 
/// </summary>
/// <returns>A whole number from 0 [inclusive] to 3 [inclusive] as a float.</returns>
float AsteroidManager::generateRandomTimer() const
{
	return static_cast<float>(rand() % 4);
}
