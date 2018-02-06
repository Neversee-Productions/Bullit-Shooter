#include "util\CollisionSystem.h"

/// <summary>
/// @brief Construct collision system.
/// 
/// Requires a reference to each object that
/// collisions will be checked for.
/// </summary>
CollisionSystem::CollisionSystem(
	Player& player
	, AsteroidManager & asteroidManager
)
	: m_player(player)
	, m_asteroidManager(asteroidManager)
{
}

/// <summary>
/// @brief Update collision system.
/// 
/// Proceeds to check for collisions on each referenced object
/// and applies appropriate responses.
/// </summary>
void CollisionSystem::update()
{
	this->updatePlayer();
}

/// <summary>
/// @brief Update player collisions
/// </summary>
void CollisionSystem::updatePlayer()
{
	if (m_player.isAlive())
	{
		// Collisions while player is alive
		for (auto & asteroid : m_asteroidManager.getAsteroidVector())
		{
			if (asteroid.isActive())
			{
				if (tinyh::c2CircletoCircle(m_player.getShieldCollisionCircle(), asteroid.getCollisionCircle()))
				{
					this->playerVsAsteroid(m_player, asteroid);
				}
			}
		}
	}
	else
	{
		// Collisions while player is dead.
	}
	// Collisions whether player is alive or dead.
	this->updatePlayerBullets();
}

/// <summary>
/// @brief check and apply collisions from all bullets to all bullet hit-ables.
/// 
/// Iterates through all active and not impacted bullets,
/// checking for collision against all active asteroids.
/// </summary>
void CollisionSystem::updatePlayerBullets()
{
	auto & m_bulletMap = m_player.getBulletMap();
	for (auto & pair : m_bulletMap)
	{
		auto & bulletVector = pair.second;
		for (auto & uptrBullet : bulletVector)
		{
			auto & bullet = *uptrBullet;
			this->updatePlayerBulletToAsteroids(bullet);
		}
	}
}

/// <summary>
/// @brief check and apply collisions from bullet onto every other asteroid.
/// 
/// Iterate through all asteroids and check if they collided.
/// If true than call CollisionSystem::asteroidVsBullet.
/// @see CollisionSystem::asteroidVsBullet
/// </summary>
/// <param name="bullet">reference to bullet</param>
void CollisionSystem::updatePlayerBulletToAsteroids(bullets::Bullet & bullet)
{
	if (bullet.isActive() && !bullet.isImpact())
	{
		auto & asteroidVector = m_asteroidManager.getAsteroidVector();
		for (auto & asteroid : asteroidVector)
		{
			if (asteroid.isActive())
			{
				if (bullet.checkCircleCollision(asteroid.getCollisionCircle()))
				{
					this->asteroidVsBullet(asteroid, bullet);
				}
			}
		}
	}
}

void CollisionSystem::updateAsteroids()
{
}

/// <summary>
/// @brief Collision between a bullet and asteroid has occured.
/// 
/// Details the appropriate response to bullet vs asteroid collision.
/// </summary>
/// <param name="asteroid">reference to asteroid</param>
/// <param name="bullet">reference to base bullet.</param>
void CollisionSystem::asteroidVsBullet(Asteroid & asteroid, bullets::Bullet & bullet)
{
	using namespace bullets;
	switch (bullet.getType())
	{
		case BulletTypes::DeathOrb:
		case BulletTypes::HolySphere:
		case BulletTypes::StaticSphere:
			break;
		case BulletTypes::CometShot:
			asteroid.knockback();
		case BulletTypes::Standard:
		case BulletTypes::Empowered:
		case BulletTypes::FireBlast:
		case BulletTypes::NullWave:
			bullet.hit();
			break; // 1
		case BulletTypes::MagmaShot:
		{
			auto & derivedBullet = dynamic_cast<MagmaShot&>(bullet);
			derivedBullet.explode(true);
		}	break; // 3
		case BulletTypes::NapalmSphere:
		{
			auto & derivedBullet = dynamic_cast<NapalmSphere&>(bullet);
			derivedBullet.explode(true);
		}	break; // 3
		case BulletTypes::PyroBlast:
		{
			auto & derivedBullet = dynamic_cast<PyroBlast&>(bullet);
			derivedBullet.explode(true);
		}	break; // 3
		default:
			break;
	}
	if (!asteroid.isInvulnerable())
	{
		asteroid.decrementHealth(bullet.getDamage());
	}

	/* TODO: Added in pickup spawning off asteroid destruction and enemy spawning.

	if (!asteroid.isActive() && !m_pickup->isActive()) //check if pickup is not active and if the asteroid was destroyed.
	{
		int chance = (rand() % 11); //generate number from 0 - 10
		if (chance > 2)
		{
			BulletTypes pickupType = m_player.getWeaponType();
			auto weaponNum = static_cast<int>(pickupType);
			weaponNum++;
			if (weaponNum < static_cast<int>(BulletTypes::AmountOfTypes))
			{
				pickupType = static_cast<BulletTypes>(weaponNum);
				sf::Vector2f pos = sf::Vector2f(asteroid.getCollisionCircle().p.x, asteroid.getCollisionCircle().p.y);
				m_pickup = std::make_unique<Pickup>(Pickup(m_resources->m_sptrPickup, pos, sf::Vector2f(100, 100), pickupType));
			}
		}
	}
	/**/
}

/// <summary>
/// @brief Collision between player and a asteroid has occured.
/// 
/// Details the appropriate response to player vs asteroid collision.
/// </summary>
/// <param name="player">reference to player.</param>
/// <param name="asteroid">reference to asteroid</param>
void CollisionSystem::playerVsAsteroid(Player & player, Asteroid & asteroid)
{
	player.decrementShield(25.0f);
	asteroid.decrementHealth(10.0f);
}
