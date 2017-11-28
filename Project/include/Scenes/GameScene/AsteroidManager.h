#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H

#include <vector>
#include <memory>
#include "Asteroid.h"

///
/// @brief Asteroid manager class.
/// @author Sebastian Kruzel
/// 
/// A manager of asteroids, reuses a vector
/// of asteroids.
/// 
class AsteroidManager
{
public:
	AsteroidManager();
	void initAsteroidVector();
	const std::vector<std::unique_ptr<Asteroid>>& getAsteroidVector();

private:
	std::vector<std::unique_ptr<Asteroid>> m_asteroidsVector;

};

#endif // !ASTEROID_MANAGER_H
