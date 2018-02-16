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
	, BasicEnemyManager & basicEnemyManager
	, Pickup & pickup
	, GameUI & gameUi
)
	: m_UPDATE_DT(App::getUpdateDeltaTime())
	, m_soundManager(SoundManager::instance())
	, m_player(player)
	, m_asteroidManager(asteroidManager)
	, m_basicEnemyManager(basicEnemyManager)
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
	auto & asteroidVec = m_asteroidManager.getAsteroidVector();

	auto & endItt = asteroidVec.end();
	for (auto itt = asteroidVec.begin(); itt != endItt; ++itt)
	{
		if (itt->isActive() && !itt->isExplosion())
		{
			for (auto itt2 = itt; itt2 != endItt; ++itt2)
			{
				if (itt != itt2)
				{
					if (itt2->isActive() && !itt2->isExplosion())
					{
						if (tinyh::c2CircletoCircle(itt->getCollisionCircle(), itt2->getCollisionCircle()))
						{
							solveElasticCollision(*itt, *itt2);
						}
					}
				}
			}
		}
	}
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
		for (auto & enemy : m_basicEnemyManager.getEnemies())
		{
			if (enemy.isActive() && enemy.checkCollision(m_player.getShieldCollisionCircle()))
			{
				this->playerVsEnemy(m_player, enemy);
			}
		}

		this->updatePlayerToPickup();
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
			this->updatePlayerBulletToEnemies(bullet);
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
			if (asteroid.isActive() && !asteroid.isExplosion())
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
/// @brief check and apply collisions from bullet onto every other enemy.
/// 
/// Iterate through all asteroids and check if they collided.
/// If true than call CollisionSystem::enemyVsBullet.
/// @see CollisionSystem::enemyVsBullet
/// </summary>
/// <param name="bullet">reference to bullet.</param>
void CollisionSystem::updatePlayerBulletToEnemies(bullets::Bullet & bullet)
{
	if (bullet.isActive() && !bullet.isImpact())
	{
		auto & enemies = m_basicEnemyManager.getEnemies();
		for (auto & enemy : enemies)
		{
			if (enemy.isActive() && bullet.checkAABBCollision(enemy.getCollisionAABB()))
			{
				this->enemyVsBullet(enemy, bullet);
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
	std::stringstream bulletImpactID;
	bulletImpactID << "bullet";
	using namespace bullets;
	//This variable determines if the asteroid is to become invulnerable after a hit, set to true by default.
	bool asteroidInvurnelabilityState = true; 
	switch (bullet.getType())
	{
		case BulletTypes::DeathOrb:
		case BulletTypes::HolySphere:
		case BulletTypes::StaticSphere:
			break;
		case BulletTypes::CometShot:
			asteroid.knockback();
		case BulletTypes::Empowered:
			bullet.hit();
			asteroidInvurnelabilityState = false;
		case BulletTypes::Standard:
		case BulletTypes::FireBlast:
		case BulletTypes::NullWave:
			bulletImpactID << "0" << std::to_string(static_cast<int>(bullet.getType()) + 1);
			bullet.hit();
			bulletImpactID << "_impact";
			m_soundManager.play(bulletImpactID.str());
			break; // 1
		case BulletTypes::MagmaShot:
		{
			auto & derivedBullet = dynamic_cast<MagmaShot&>(bullet);
			if (!derivedBullet.isExplosion())
			{
				bulletImpactID << "0" << std::to_string(static_cast<int>(bullet.getType()) + 1);
				bulletImpactID << "_impact";
				m_soundManager.play(bulletImpactID.str());
			}
			derivedBullet.explode(true);
		}	break; // 3
		case BulletTypes::NapalmSphere:
		{
			auto & derivedBullet = dynamic_cast<NapalmSphere&>(bullet);
			if (!derivedBullet.isExplosion())
			{
				bulletImpactID << "0" << std::to_string(static_cast<int>(bullet.getType()) + 1);
				bulletImpactID << "_impact";
				m_soundManager.play(bulletImpactID.str());
			}
			derivedBullet.explode(true);
		}	break; // 3
		case BulletTypes::PyroBlast:
		{
			auto & derivedBullet = dynamic_cast<PyroBlast&>(bullet);
			if (!derivedBullet.isExplosion())
			{
				bulletImpactID << std::to_string(static_cast<int>(bullet.getType()) + 1);
				bulletImpactID << "_impact";
				m_soundManager.play(bulletImpactID.str());
			}
			derivedBullet.explode(true);
		}	break; // 3
		default:
			break;
	}
	if (!asteroid.isInvulnerable())
	{
		asteroid.decrementHealth(bullet.getDamage(), asteroidInvurnelabilityState);
		if (asteroid.isExplosion())
		{
			m_soundManager.play("asteroid_explosion");
			if (!m_pickup.isActive())
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
			if (asteroid.containsEnemy())
			{
				sf::Vector2f spawnPos = { asteroid.getCollisionCircle().p.x, asteroid.getCollisionCircle().p.y };
				m_basicEnemyManager.spawn(m_player, spawnPos);
			}
		}
	}
}

/// <summary>
/// @brief Collision between a bullet and enemy has occured.
/// 
/// Details the appropriate response to bullet vs enemy collision.
/// </summary>
/// <param name="asteroid">reference to enemy</param>
/// <param name="bullet">reference to base bullet.</param>
void CollisionSystem::enemyVsBullet(ai::AiBasic & enemy, bullets::Bullet & bullet)
{
	std::stringstream bulletImpactID;
	bulletImpactID << "bullet";
	using namespace bullets;
	switch (bullet.getType())
	{
		case BulletTypes::DeathOrb:
		case BulletTypes::HolySphere:
		case BulletTypes::StaticSphere:
			break;
		case BulletTypes::CometShot:
			//enemy.knockback();
		case BulletTypes::Standard:
		case BulletTypes::Empowered:
		case BulletTypes::FireBlast:
		case BulletTypes::NullWave:
			bulletImpactID << "0" << std::to_string(static_cast<int>(bullet.getType()) + 1);
			bullet.hit();
			bulletImpactID << "_impact";
			m_soundManager.play(bulletImpactID.str());
			break; // 1
		case BulletTypes::MagmaShot:
		{
			auto & derivedBullet = dynamic_cast<MagmaShot&>(bullet);
			if (!derivedBullet.isExplosion())
			{
				bulletImpactID << "0" << std::to_string(static_cast<int>(bullet.getType()) + 1);
				bulletImpactID << "_impact";
				m_soundManager.play(bulletImpactID.str());
			}
			derivedBullet.explode(true);
		}	break; // 3
		case BulletTypes::NapalmSphere:
		{
			auto & derivedBullet = dynamic_cast<NapalmSphere&>(bullet);
			if (!derivedBullet.isExplosion())
			{
				bulletImpactID << "0" << std::to_string(static_cast<int>(bullet.getType()) + 1);
				bulletImpactID << "_impact";
				m_soundManager.play(bulletImpactID.str());
			}
			derivedBullet.explode(true);
		}	break; // 3
		case BulletTypes::PyroBlast:
		{
			auto & derivedBullet = dynamic_cast<PyroBlast&>(bullet);
			if (!derivedBullet.isExplosion())
			{
				bulletImpactID << std::to_string(static_cast<int>(bullet.getType()) + 1);
				bulletImpactID << "_impact";
				m_soundManager.play(bulletImpactID.str());
			}
			derivedBullet.explode(true);
		}	break; // 3
		default:
			break;
	}
	bool const & ENEMY_DIED = enemy.decrementHealth(bullet.getDamage());
	if (ENEMY_DIED)
	{
		m_soundManager.play("enemy_death");
		enemy.setActive(false);
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
	if (!asteroid.isExplosion())
	{
		player.decrementShield(25.0f);
		m_gameUi.decrementHealth(25.0f);
		asteroid.decrementHealth(10.0f, false);
		if (asteroid.isExplosion())
		{
			m_soundManager.play("asteroid_explosion");
		}
	}
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

	if (!m_player.isDocking())
	{
		pickup.setRightVelocity((unitVecLeft * (LENGTH * 5.2f))* App::getUpdateDeltaTime());
		pickup.setLeftVelocity((unitVecRight * (LENGTH * 5.2f)) * App::getUpdateDeltaTime());
	}
	else //move faster when docking to prevent outrunning the pickup
	{
		pickup.setRightVelocity((unitVecLeft * (LENGTH * 8.2f))* App::getUpdateDeltaTime());
		pickup.setLeftVelocity((unitVecRight * (LENGTH * 8.2f)) * App::getUpdateDeltaTime());
	}
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

/// <summary>
/// @brief this is the method that will resolve elastic collisions between asteroids.
/// 
/// 
/// </summary>
/// <param name="asteroid1">asteroid 1</param>
/// <param name="asteroid2">asteroid 2</param>
void CollisionSystem::solveElasticCollision(Asteroid & asteroid1, Asteroid & asteroid2)
{
	asteroid1.setPosition(asteroid1.getPosition() - (asteroid1.getVelocity() * App::getUpdateDeltaTime()));
	asteroid2.setPosition(asteroid2.getPosition() - (asteroid2.getVelocity() * App::getUpdateDeltaTime()));


	sf::Vector2f collisionVector = asteroid1.getPosition() - asteroid2.getPosition();
	collisionVector = thor::unitVector(collisionVector);

	//// Get the components of the velocity vectors which are parallel to the collision.
	//// The perpendicular component remains the same for both asteroids
	/// since mass is the same we dont need to calculate future velocity we can reuse the before minus previous (dotProdA - dotProdB)
	float dotProductA = thor::dotProduct(asteroid1.getVelocity(), collisionVector);
	float dotProductB = thor::dotProduct(asteroid2.getVelocity(), collisionVector);


	//set new velocities
	asteroid1.setVelocity(asteroid1.getVelocity() + sf::Vector2f((dotProductB - dotProductA) * collisionVector.x, (dotProductB - dotProductA) * collisionVector.y));
	asteroid2.setVelocity(asteroid2.getVelocity() + sf::Vector2f((dotProductA - dotProductB) * collisionVector.x, (dotProductA - dotProductB) * collisionVector.y));

	float asteroid2Rot = asteroid2.getRotation();
	asteroid2.setRotation(asteroid1.getRotation());
	asteroid1.setRotation(asteroid2Rot);

}

/// <summary>
/// @brief Collision between player and enemy has occured.
/// 
/// Details the appropriate response to player vs enemy collision
/// </summary>
/// <param name="player">reference to the player that collided.</param>
/// <param name="enemy">reference to the enemy that collided.</param>
void CollisionSystem::playerVsEnemy(Player & player, ai::AiBasic & enemy)
{
	float const PLAYER_DMG = 4.0f;
	if (!player.isInvulnerable())
	{
		m_gameUi.decrementHealth(PLAYER_DMG);
	}
	player.decrementShield(PLAYER_DMG);
}
