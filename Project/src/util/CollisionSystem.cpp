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
	, Pickup & pickup
	, GameUI & gameUi
)
	: m_player(player)
	, m_asteroidManager(asteroidManager)
	, m_pickup(pickup)
	, m_gameUi(gameUi)
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
		this->updatePlayerToGameUi();
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

/// <summary>
/// @brief check and apply collisions from player to pickup
/// 
/// 
/// </summary>
void CollisionSystem::updatePlayerToPickup()
{
	if (m_pickup.isActive())
	{
		sf::Vector2f vector = m_player.getPosition() - m_pickup.getRightPosition();
		float length = thor::length(vector);
		if (length < 100)
		{
			this->playerVsPickup(m_player, m_pickup);
		}
		else
		{
			m_pickup.setEffectAlpha(255);
		}
	}
}

/// <summary>
/// @brief check and apply collisions from player to game ui.
/// 
/// 
/// </summary>
void CollisionSystem::updatePlayerToGameUi()
{
	if (tinyh::c2CircletoAABB(m_player.getShieldCollisionCircle(), m_gameUi.getHealthCollisionBox()))
	{
		this->playerVsGameUi(m_player, m_gameUi);
	}
	else
	{
		m_gameUi.setHealthTransparency(255u);
	}
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
		if (!asteroid.isActive() && !m_pickup.isActive()) //check if pickup is not active and if the asteroid was destroyed.
		{
			int const SPAWN_CHANCE = (std::rand() % 11); //generate number from 0 - 10
			if (SPAWN_CHANCE > 2)
			{
				BulletTypes pickupType = m_player.getWeaponType();
				auto weaponNum = static_cast<int>(pickupType);
				weaponNum++;
				if (weaponNum < static_cast<int>(BulletTypes::AmountOfTypes))
				{
					pickupType = static_cast<BulletTypes>(weaponNum);
					sf::Vector2f pos = { asteroid.getCollisionCircle().p.x, asteroid.getCollisionCircle().p.y };
					m_pickup.spawn(pos, { 100, 100 }, pickupType);
				}
			}
		}
	}
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

/// <summary>
/// @brief Collision between player and a pickup as occured.
/// 
/// Details the appropriate response to player vs pickup collision.
/// </summary>
/// <param name="player">reference to the player that collided.</param>
/// <param name="pickup">reference to the pickup that collided.</param>
void CollisionSystem::playerVsPickup(Player & player, Pickup & pickup)
{
	float const LENGTH = thor::length(player.getPosition() - pickup.getRightPosition());

	player.setCanFire(false);
	player.setAttachedWeapons(false);
	//decrease alpha of the pickup effect
	pickup.fadeOutEffect();

	//LEFT WEAPON CALCULATIONS
	sf::Vector2f leftPosVec = player.getLeftWeaponPos() - pickup.getRightPosition();
	sf::Vector2f unitVecLeft = thor::unitVector(leftPosVec);
	float leftLength = thor::length(leftPosVec);

	//RIGHT WEAPON CALCULATIONS
	sf::Vector2f rightPosVec = player.getRightWeaponPos() - pickup.getLeftPosition();
	sf::Vector2f unitVecRight = thor::unitVector(rightPosVec);
	float rightLength = thor::length(rightPosVec);

	pickup.setRightVelocity((unitVecLeft * (LENGTH * 5.2f))* App::getUpdateDeltaTime());
	pickup.setLeftVelocity((unitVecRight * (LENGTH * 5.2f)) * App::getUpdateDeltaTime());
	player.fadeOutWeapons();

	player.setConnectorPos(pickup.getLeftPosition(), pickup.getRightPosition());

	if (leftLength < 10 && rightLength < 10)
	{
		player.setWeaponsAlpha(255);
		player.setAttachedWeapons(true);
		player.nextWeapon();
		pickup.setActive(false);
	}
}

/// <summary>
/// @brief Collision between player and game ui has occured.
/// 
/// Details the appropriate response to player vs game ui collision.
/// </summary>
/// <param name="player">reference to the player that collided.</param>
/// <param name="gameUi">reference to the game ui that collided.</param>
void CollisionSystem::playerVsGameUi(Player & player, GameUI & gameUi)
{
	m_gameUi.setHealthTransparency(100u);
}
