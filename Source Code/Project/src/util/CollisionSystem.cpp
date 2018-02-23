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
	, RangedEnemyManager & rangedEnemyManager
	, Pickup & pickup
	, GameUI & gameUi
)
	: m_UPDATE_DT(App::getUpdateDeltaTime())
	, m_soundManager(SoundManager::instance())
	, m_player(player)
	, m_asteroidManager(asteroidManager)
	, m_basicEnemyManager(basicEnemyManager)
	, m_rangedEnemyManager(rangedEnemyManager)
	, m_pickup(pickup)
	, m_gameUi(gameUi)
	, m_pickingUp(false)
	, m_pickupSoundPlaying(false)
	, m_stayClearPlaying(false)
	, m_enemyKilledVoicelineTimer(0.0f)
	, m_timeUntilKilledVoiceline(2.0f)
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
	m_enemyKilledVoicelineTimer += App::getUpdateDeltaTime();

	this->updatePlayer();
	this->updateAsteroids();

}

/// <summary>
/// @brief setter for the can pickup bool.
/// 
/// 
/// </summary>
/// <param name="check">new value of pickingup</param>
void CollisionSystem::setPickingUp(bool check)
{
	m_pickingUp = check;
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
					auto random = (rand() % 4 + 1); //generate number between 1 and 3
					if (random == 4)
					{
						if (!m_stayClearPlaying)
						{
							m_stayClearPlaying = true;
							m_soundManager.play("stay-clear");
						}
					}
				}
			}
		}
		for (auto & enemy : m_basicEnemyManager.getEnemies())
		{
			if (enemy.getActive() && enemy.isAlive() && enemy.checkCollision(m_player.getShieldCollisionCircle()))
			{
				this->playerVsBasicEnemy(m_player, enemy);
			}
		}
		for (auto & enemy : m_rangedEnemyManager.getEnemies())
		{
			if (enemy.getActive())
			{
				if (enemy.isAlive() && tinyh::c2CircletoCircle(m_player.getShieldCollisionCircle(), enemy.getC2Circle()))
				{
					this->playerVsRangedEnemy(m_player, enemy);
				}
				this->updateRangedEnemyBullets(enemy);
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
/// checking for collision against all hit-ables.
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
			this->updatePlayerBulletToBasicEnemies(bullet);
			this->updatePlayerBulletToRangedEnemies(bullet);
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
/// Iterate through all enemies and check if they collided.
/// If true than call CollisionSystem::basicEnemyVsBullet.
/// @see CollisionSystem::enemyVsBullet
/// </summary>
/// <param name="bullet">reference to bullet.</param>
void CollisionSystem::updatePlayerBulletToBasicEnemies(bullets::Bullet & bullet)
{
	if (bullet.isActive() && !bullet.isImpact())
	{
		auto & enemies = m_basicEnemyManager.getEnemies();
		for (auto & enemy : enemies)
		{
			if (enemy.getActive() && enemy.isAlive() && bullet.checkAABBCollision(enemy.getCollisionAABB()))
			{
				this->basicEnemyVsBullet(enemy, bullet);
			}
		}
	}
}

/// <summary>
/// @brief check and apply collisions from bullet onto every other ranged enemy.
/// 
/// Iterate through all ranged enemies and check if they collided.
/// If true than call CollisionSystem::
/// </summary>
/// <param name="bullet"></param>
void CollisionSystem::updatePlayerBulletToRangedEnemies(bullets::Bullet & bullet)
{
	if (bullet.isActive() && !bullet.isImpact())
	{
		auto & enemies = m_rangedEnemyManager.getEnemies();
		for (auto & enemy : enemies)
		{
			if (enemy.getActive() && enemy.isAlive() && bullet.checkCircleCollision(enemy.getC2Circle()))
			{
				this->rangedEnemyVsBullet(enemy, bullet);
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
			m_pickingUp = true;
		}
		if(m_pickingUp)
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
		m_gameUi.setHealthTransparency(100u);
	}
	else
	{
		m_gameUi.setHealthTransparency(255u);
	}

	if (tinyh::c2CircletoAABB(m_player.getShieldCollisionCircle(), m_gameUi.getRightUICollisionBox()))
	{
		m_gameUi.setRightBarsTransparency(100u);
	}
	else
	{
		m_gameUi.setRightBarsTransparency(255u);
	}

	if (tinyh::c2CircletoAABB(m_player.getShieldCollisionCircle(), m_gameUi.getLeftUICollisionBox()))
	{
		m_gameUi.setLeftBarsTransparency(100u);
	}
	else
	{
		m_gameUi.setLeftBarsTransparency(255u);
	}
}

/// <summary>
/// @brief check and apply collisions from asteroid to every other asteroid.
/// 
/// 
/// </summary>
void CollisionSystem::updateAsteroids()
{
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
							asteroidVsAsteroid(*itt, *itt2);
						}
					}
				}
			}
		}
	}
}

/// <summary>
/// @brief check and apply collisions for enemy bullets.
/// 
/// Iterates through all active and not impacted bullets,
/// checking for collision against all hit-ables.
/// </summary>
/// <param name="enemy">reference to enemy.</param>
void CollisionSystem::updateRangedEnemyBullets(ai::AiRanged & enemy)
{
	auto & bullets = enemy.getBullets();
	for (auto & bullet : bullets)
	{
		if (bullet.getActive() && !bullet.getImpact())
		{
			this->updateRangedEnemyBulletToPlayer(bullet);
		}
	}
}

/// <summary>
/// @brief check and apply collisions from enemy bullet to player.
/// 
/// 
/// </summary>
/// <param name="bullet">reference to bullet.</param>
void CollisionSystem::updateRangedEnemyBulletToPlayer(AiBullet & bullet)
{
	if (tinyh::c2CircletoAABB(m_player.getShieldCollisionCircle(), bullet.getC2AABB()))
	{
		this->rangedEnemyBulletVsPlayer(bullet, m_player);
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
		float dmg = bullet.getDamage();
		if (bullet.getType() == BulletTypes::Standard)
		{
			dmg = 0.65f;
		}
		asteroid.decrementHealth(dmg, asteroidInvurnelabilityState);
		if (asteroid.isExplosion())
		{
			m_soundManager.play("asteroid_explosion");
			Score::s_scoreCurrent += Score::SCORE_FOR_ASTEROID;
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
				sf::Vector2f spawnHeading = { 0.0f, 1.0f };
				float const rotateBy = 360.0f / Progression::getBasicEnemies();
				for (int i = 0; i < Progression::getBasicEnemies(); ++i)
				{
					sf::Vector2f spawnPos = { asteroid.getCollisionCircle().p.x, asteroid.getCollisionCircle().p.y };
					float angle = rotateBy * (std::rand() % 11 / 10.0f);
					thor::rotate(spawnHeading, angle);
					m_basicEnemyManager.spawn(m_player, spawnPos, spawnHeading, thor::polarAngle(spawnHeading) - 90.0f);
				}
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
void CollisionSystem::baseEnemyVsBullet(ai::AiBase & enemy, bullets::Bullet & bullet)
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
}

/// <summary>
/// @brief Collision between a bullet and enemy has occured.
/// 
/// Details the appropriate response to bullet vs enemy collision.
/// </summary>
/// <param name="asteroid">reference to enemy</param>
/// <param name="bullet">reference to base bullet.</param>
void CollisionSystem::basicEnemyVsBullet(ai::AiBasic & enemy, bullets::Bullet & bullet)
{
	this->baseEnemyVsBullet(enemy, bullet);
	float dmg = bullet.getDamage();
	if (bullet.getType() == BulletTypes::PyroBlast)
	{
		dmg = 0.1f;
	}
	else if (bullet.getType() == BulletTypes::StaticSphere)
	{
		dmg = 0.2f;
	}
	bool const & ENEMY_DIED = enemy.decrementHealth(dmg);
	if (ENEMY_DIED)
	{
		Score::s_scoreCurrent += Score::SCORE_FOR_BASIC;
		m_soundManager.play("enemy_death");
		generateKilledEnemyVoiceline();
	}
}

/// <summary>
/// @brief Collisions between a enemy and a bullet has occurred.
/// 
/// Details the appropriate response to player vs enemy collision.
/// </summary>
/// <param name="enemy">reference to enemy.</param>
/// <param name="bullet">reference to bullet.</param>
void CollisionSystem::rangedEnemyVsBullet(ai::AiRanged & enemy, bullets::Bullet & bullet)
{
	this->baseEnemyVsBullet(enemy, bullet);
	float dmg = bullet.getDamage();
	if (bullet.getType() == BulletTypes::PyroBlast)
	{
		dmg = 0.1f;
	}
	else if (bullet.getType() == BulletTypes::StaticSphere)
	{
		dmg = 0.2f;
	}
	bool const & ENEMY_DIED = enemy.decrementHealth(dmg);
	if (ENEMY_DIED)
	{
		Score::s_scoreCurrent += Score::SCORE_FOR_RANGED;
		m_soundManager.play("enemy_death");
		generateKilledEnemyVoiceline();
	}
}

/// <summary>
/// @brief Collisions between a ranged enemy bullet and a player has occurred.
/// 
/// Details the appropriate response to ranged enemy bullet vs player collision.
/// </summary>
/// <param name="bullet">reference to bullet.</param>
/// <param name="player">reference to player.</param>
void CollisionSystem::rangedEnemyBulletVsPlayer(AiBullet & bullet, Player & player)
{
	player.decrementShield(5.0f);
	bullet.impact();
	m_gameUi.setTargetHealth(player.getShieldHealth());
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
		m_gameUi.setTargetHealth(player.getShieldHealth());
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
	if (!m_pickupSoundPlaying)
	{
		m_pickupSoundPlaying = true;
		m_soundManager.play("power-up");
		auto random = (rand() % 5 + 1); //generate number between 1 and 5
		if (random == 1)
		{
			m_soundManager.play("guns");
		}
		else if (random == 2)
		{
			m_soundManager.play("locked-and-loaded");
		}
		else if (random == 3)
		{
			m_soundManager.play("nice-find");
		}
		else if (random == 4)
		{
			m_soundManager.play("shiny");
		}
		else if (random == 5)
		{
			m_soundManager.play("useful");
		}
	}
	pickup.setCanDisappear(false);
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
		pickup.setRightVelocity((unitVecLeft * (LENGTH * 7.2f))* App::getUpdateDeltaTime());
		pickup.setLeftVelocity((unitVecRight * (LENGTH * 7.2f)) * App::getUpdateDeltaTime());
	}
	else //move faster when docking to prevent outrunning the pickup
	{
		pickup.setRightVelocity((unitVecLeft * (LENGTH * 10.2f))* App::getUpdateDeltaTime());
		pickup.setLeftVelocity((unitVecRight * (LENGTH * 10.2f)) * App::getUpdateDeltaTime());
	}
	player.fadeOutWeapons();

	player.setConnectorPos(pickup.getLeftPosition(), pickup.getRightPosition());
	
	if (leftLength < 10 && rightLength < 10)
	{
		m_pickupSoundPlaying = false;
		m_pickup.resetPickup();
		m_pickingUp = false;
		player.setWeaponsAlpha(255);
		player.setAttachedWeapons(true);
		player.nextWeapon();
		player.setOverheat(false);
		pickup.setActive(false);
	}
}

/// <summary>
/// @brief this is the method that will resolve elastic collisions between asteroids.
/// 
/// 
/// </summary>
/// <param name="asteroid1">asteroid 1</param>
/// <param name="asteroid2">asteroid 2</param>
void CollisionSystem::asteroidVsAsteroid(Asteroid & asteroid1, Asteroid & asteroid2)
{
	asteroid1.setPosition(asteroid1.getPosition() - (asteroid1.getVelocity() * App::getUpdateDeltaTime()));
	asteroid2.setPosition(asteroid2.getPosition() - (asteroid2.getVelocity() * App::getUpdateDeltaTime()));


	sf::Vector2f collisionVector = asteroid1.getPosition() - asteroid2.getPosition();
	if (thor::squaredLength(collisionVector) == 0)
	{
		// Exceptional case of when 2 asteroids happen to spawn
		// at the exact same location
		asteroid2.setActive(false);
		return;
	}
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
/// @brief generate a random line.
/// 
/// 
/// </summary>
void CollisionSystem::generateKilledEnemyVoiceline()
{
	if (m_enemyKilledVoicelineTimer > m_timeUntilKilledVoiceline)
	{
		m_enemyKilledVoicelineTimer = 0.0f;
		auto random = (rand() % 20 + 1); //generate number between 1 and 20
		if (random == 2)
		{
			m_soundManager.play("what-hit");
		}
		if (random == 6)
		{
			m_soundManager.play("get-some");
		}
		if (random == 11)
		{
			m_soundManager.play("all-ya-got");
		}
		if (random == 17)
		{
			m_soundManager.play("pain");
		}
	}
}

/// <summary>
/// @brief Collision between player and enemy has occured.
/// 
/// Details the appropriate response to player vs enemy collision
/// </summary>
/// <param name="player">reference to the player that collided.</param>
/// <param name="enemy">reference to the enemy that collided.</param>
void CollisionSystem::playerVsBasicEnemy(Player & player, ai::AiBasic & enemy)
{
	float const PLAYER_DMG = 3.0f;
	if (!player.isInvulnerable())
	{
		player.decrementShield(PLAYER_DMG);
		m_gameUi.setTargetHealth(player.getShieldHealth());
	}
}

/// <summary>
/// @brief Collision between player and enemy has occured.
/// 
/// Details the appropriate response to player vs enemy collision
/// </summary>
/// <param name="player">reference to the player that collided.</param>
/// <param name="enemy">reference to the enemy that collided.</param>
void CollisionSystem::playerVsRangedEnemy(Player & player, ai::AiRanged & enemy)
{
	float const PLAYER_DMG = 1.0f;
	if (!player.isInvulnerable())
	{
		player.decrementShield(PLAYER_DMG);
		m_gameUi.setTargetHealth(player.getShieldHealth());
	}
}
