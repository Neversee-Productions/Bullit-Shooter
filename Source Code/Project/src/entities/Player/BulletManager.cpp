#include "Entities\Player\BulletManager.h"

/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
BulletManager::BulletManager()
	: m_timeSinceFire(10.0f)
	, m_windowC2Rect(App::getViewC2Rect())
	, m_soundManager(SoundManager::instance())
	, m_soundFireMap()
	, m_fireRateVal(0.0f)
	, m_overchargePerBullet(0.0f)
	, m_currentOvercharge(0.0f)
	, m_cooldownRate(0.0f)
	, m_overheat(false)
{
	std::size_t const BULLET_TYPES = static_cast<std::size_t>(BulletTypes::AmountOfTypes);
	m_soundFireMap.reserve(BULLET_TYPES);

	std::stringstream bulletFireID("bullet00_fire");
	bulletFireID << "bullet";
	for (std::size_t i = 0; i < BULLET_TYPES; ++i)
	{
		auto const TYPE = static_cast<BulletTypes>(i);
		auto const BULLET_NUM = i + 1;
		if (BULLET_NUM < 10u)
		{
			bulletFireID << "0" + std::to_string(BULLET_NUM);
		}
		else
		{
			bulletFireID << std::to_string(BULLET_NUM);
		}
		m_soundFireMap.insert(std::make_pair(TYPE, bulletFireID.str()));

		// store current stream position
		std::streampos const cursor = bulletFireID.tellp();
		// Convert 2u to a stream offset
		std::streamoff const cursorOffset = 2u;
		// Move internal stream cursor back 2 places
		bulletFireID.seekp(cursor - cursorOffset);
	}
}

/// <summary>
/// @brief Initialize external assets.
/// 
/// 
/// </summary>
/// <param name="sptrResources">shared pointer to loaded resources.</param>
void BulletManager::init(std::shared_ptr<Resources> sptrResources)
{
	m_resources = sptrResources;
}

/// <summary>
/// @brief method that will add bullet to vector
/// 
/// 
/// </summary>
/// <param name="weapon1">define first gun</param>
/// <param name="weapon2">define second gun</param>
/// <param name="type">define type of bullet</param>
void BulletManager::fireBullet(Weapon & weapon1, Weapon & weapon2,const BulletTypes& type)
{
	auto const & position1 = weapon1.getPosition();
	auto const & position2 = weapon2.getPosition();

	if (m_bulletMap.find(type) == m_bulletMap.end()) //if bullet vector has not been instanciated, then do so.
	{
		initBulletvector(type);
	}
	if (!m_overheat)
	{
		switch (type)
		{
		case BulletTypes::Standard:
			if (m_timeSinceFire > bullets::Standard::getFireRate()) //if its time to fire do it.
			{
				m_fireRateVal = bullets::Standard::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::Empowered:
			if (m_timeSinceFire > bullets::Empowered::getFireRate())
			{
				m_fireRateVal = bullets::Empowered::getFireRate();
				fireEmpowered(position1, position2);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::DeathOrb:
			if (m_timeSinceFire > bullets::DeathOrb::getFireRate())
			{
				m_fireRateVal = bullets::DeathOrb::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::FireBlast:
			if (m_timeSinceFire > bullets::FireBlast::getFireRate())
			{
				m_fireRateVal = bullets::FireBlast::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::HolySphere:
			if (m_timeSinceFire > bullets::HolySphere::getFireRate())
			{
				m_fireRateVal = bullets::HolySphere::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::MagmaShot:
			if (m_timeSinceFire > bullets::MagmaShot::getFireRate())
			{
				m_fireRateVal = bullets::MagmaShot::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::NapalmSphere:
			if (m_timeSinceFire > bullets::NapalmSphere::getFireRate())
			{
				m_fireRateVal = bullets::NapalmSphere::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::CometShot:
			if (m_timeSinceFire > bullets::CometShot::getFireRate())
			{
				m_fireRateVal = bullets::CometShot::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::NullWave:
			if (m_timeSinceFire > bullets::NullWave::getFireRate())
			{
				m_fireRateVal = bullets::NullWave::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::StaticSphere:
			if (m_timeSinceFire > bullets::StaticSphere::getFireRate())
			{
				m_fireRateVal = bullets::StaticSphere::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		case BulletTypes::PyroBlast:
			if (m_timeSinceFire > bullets::PyroBlast::getFireRate())
			{
				m_fireRateVal = bullets::PyroBlast::getFireRate();
				fireOne(position1, position2, type);
				weapon1.shoot();
				weapon2.shoot();
				m_soundManager.play(m_soundFireMap.at(type));
				m_currentOvercharge += m_overchargePerBullet;
			}
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// @brief this method initializes the bullet vector of a specific passed type.
/// 
/// Reserve and resize the vector in order to construct default bullets of passed type
/// </summary>
/// <param name="type">bullet type</param>
void BulletManager::initBulletvector(BulletTypes type)
{
	switch (type)
	{
	case BulletTypes::Standard:
		initBulletMapVector<bullets::Standard>(type, 25);
		break;
	case BulletTypes::Empowered:
		initBulletMapVector<bullets::Empowered>(type, 70);
		break;
	case BulletTypes::DeathOrb:
		initBulletMapVector<bullets::DeathOrb>(type, 40);
		break;
	case BulletTypes::FireBlast:
		initBulletMapVector<bullets::FireBlast>(type, 40);
		break;
	case BulletTypes::HolySphere:
		initBulletMapVector<bullets::HolySphere>(type, 30);
		break;
	case BulletTypes::MagmaShot:
		initBulletMapVector<bullets::MagmaShot>(type, 30);
		break;
	case BulletTypes::NapalmSphere:
		initBulletMapVector<bullets::NapalmSphere>(type, 35);
		break;
	case BulletTypes::CometShot:
		initBulletMapVector<bullets::CometShot>(type, 40);
		break;
	case BulletTypes::NullWave:
		initBulletMapVector<bullets::NullWave>(type, 30);
		break;
	case BulletTypes::StaticSphere:
		initBulletMapVector<bullets::StaticSphere>(type, 30);
		break;
	case BulletTypes::PyroBlast:
		initBulletMapVector<bullets::PyroBlast>(type, 30);
		break;
	default:
		break;
	}
}

/// <summary>
/// @brief reuse the bullet
/// 
/// resets the position and sets active to true.
/// </summary>
/// <param name="bullet">reference to bullet</param>
/// <param name="pos">new position</param>
void BulletManager::reuseBullet(bullets::Bullet& bullet,sf::Vector2f pos)
{
	bullet.setPosition(pos);
	bullet.setActive(true);
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void BulletManager::draw(Window & window, const float & deltaTime)
{
	
	for (const auto & pair : m_bulletMap)
	{
		auto & bulletVector = pair.second;
		for (auto itt = bulletVector.begin(), end = bulletVector.end(); itt != end; ++itt)
		{
			auto & derivedBullet = **itt;
			if (derivedBullet.isActive())
			{
				derivedBullet.draw(window, deltaTime);
			}
		}
	}
}

/// <summary>
/// @brief method to update all bullets.
/// 
/// update active bullets and check collision with window.
/// </summary>
void BulletManager::update()
{
	m_timeSinceFire += App::getUpdateDeltaTime();
	if (m_currentOvercharge > 1.0f)
	{
		m_currentOvercharge = 1.0f;
		m_overheat = true;
		m_cooldownRate = m_overheatCooldownRate;
	}
	if (m_currentOvercharge > 0.0f)
	{
		m_currentOvercharge -= m_cooldownRate;
	}
	else
	{
		m_currentOvercharge = 0.0f;
	}
	if (m_overheat && m_currentOvercharge == 0.0f)
	{
		m_overheat = false;
		m_cooldownRate = m_bulletCooldownRate;
	}
	updateWindowCollisions();
}

/// <summary>
/// @brief check if bullets left the window.
/// 
/// 
/// </summary>
void BulletManager::updateWindowCollisions()
{
	for (const auto & pair : m_bulletMap)
	{
		auto & bulletVector = pair.second;
		for (auto itt = bulletVector.begin(), end = bulletVector.end(); itt != end; ++itt)
		{
			auto & derivedBullet = **itt;
			if (derivedBullet.isActive())
			{
				if (!tinyh::c2AABBtoAABB(m_windowC2Rect, derivedBullet.getCollisionRect()))
				{
					derivedBullet.setActive(false);
				}
				else
				{
					derivedBullet.update();
				}
			}
		}
	}
}

/// <summary>
/// @brief empowered bullet fire method.
/// 
/// fires 3 bullets at each weapon
/// 2 of the bullets will be offset by -5 and 5 degrees
/// </summary>
/// <param name="pos1">reference to first weapons position</param>
/// <param name="pos2">reference to second weapons position</param>
void BulletManager::fireEmpowered(const sf::Vector2f & pos1, const sf::Vector2f & pos2)
{
	int numFired = 0; //local variable to see how many bullets were fired used to determine if 2 turrets shot
	bool oneFired = false; //local bool to check if one turret already fired all 3 bullets
	bool finishedFiring = false;
	for (auto & uptrBullet : m_bulletMap.at(BulletTypes::Empowered))
	{
		auto & bullet = *uptrBullet;
		if (!bullet.isActive())
		{
			switch (numFired)
			{
			case 0:
				setEmpowered(bullet, -98, pos1);
				break;
			case 1:
				setEmpowered(bullet, -90, pos1);
				break;
			case 2:
				setEmpowered(bullet, -82, pos1);
				break;
			case 3:
				setEmpowered(bullet, -98, pos2);
				break;
			case 4:
				setEmpowered(bullet, -90, pos2);
				break;
			case 5:
				setEmpowered(bullet, -82, pos2);
				break;
			default:
				break;
			}
			numFired++;
		}
		if (finishedFiring) //required in order to leave the for loop due to switch statement
		{
			break;
		}
	}
	m_timeSinceFire = 0;
}

/// <summary>
/// @brief set properties of an empowered bullet.
/// 
/// 
/// </summary>
/// <param name="bullet">reference to a bullet</param>
/// <param name="angle">reference to the angle to fire</param>
/// <param name="pos">reference to the position to fire at</param>
void BulletManager::setEmpowered(bullets::Bullet & bullet, const float & angle, const sf::Vector2f& pos)
{
	bullet.setPosition(pos);
	bullet.setAngle(angle);
	bullet.updateVelocityVector();
	bullet.setActive(true);
}

/// <summary>
/// @brief get a constant reference to the bullets.
/// 
/// 
/// </summary>
/// <returns>map of bullets</returns>
const std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>>& BulletManager::getBulletMap()
{
	return m_bulletMap;
}

/// <summary>
/// @brief This method will run through all the bullets and set them to inactive.
/// This will be used on resetting the game to prevent bullets from still being active and on screen
/// when the user restarts the game. This will iterate through the map of bullet vectors and then
/// each bullet in a vector and set their active state to false.
/// 
/// 
/// </summary>
void BulletManager::clearAllBullets()
{
	for (auto & bulletVector : m_bulletMap)
	{
		for (auto & bullet : bulletVector.second)
		{
			bullet->setActive(false);
		}
	}

}

/// <summary>
/// @brief getter for the fire rate value.
/// 
/// 
/// </summary>
/// <returns>fire rate</returns>
float BulletManager::getFireRate()
{
	return m_fireRateVal;
}

/// <summary>
/// @brief a getter for the time since fire value.
/// 
/// 
/// </summary>
/// <returns>time since fire</returns>
float BulletManager::getTimeSinceFire()
{
	return m_timeSinceFire;
}

/// <summary>
/// @brief get the overcharge rate.
/// 
/// 
/// </summary>
/// <returns></returns>
float BulletManager::getOvercharge()
{
	return m_currentOvercharge;
}

/// <summary>
/// @brief get the bullet cooldown rate.
/// 
/// 
/// </summary>
/// <returns></returns>
float BulletManager::getCooldown()
{
	return m_cooldownRate;
}

/// <summary>
/// @brief getter for the overheat bool.
/// 
/// 
/// </summary>
/// <returns>overheat boolean</returns>
bool BulletManager::getOverheat()
{
	return m_overheat;
}

/// <summary>
/// @brief setter for the overheat bool.
/// 
/// 
/// </summary>
/// <param name="check">new value of overheat</param>
void BulletManager::setOverheat(bool check)
{
	m_overheat = check;
}

void BulletManager::setWeaponOverheatingValues(float overchargePerBullet, float bulletCooldownRate, float overheatCooldownRate)
{
	m_currentOvercharge = 0.0f;
	m_overchargePerBullet = overchargePerBullet;
	m_bulletCooldownRate = bulletCooldownRate;
	m_overheatCooldownRate = overheatCooldownRate;
	m_cooldownRate = m_bulletCooldownRate;
	m_overheat = false;
}

/// <summary>
/// @brief Initialise vector inside map based on the type.
/// 
/// This method will insert a vector of unique pointers to standard bullets
/// inside the value of the map (where the key is the type) and will
/// then convert them into their derived types
/// <typeparam name="data_type">expected passed type of bullet</typeparam>
/// <param name="type">type of bullet to instantiate</param>
/// <param name="size">size of the vector to instantiate inside the map</param>
template<typename data_type>
void BulletManager::initBulletMapVector(const BulletTypes& type, const int& size)
{
	auto bulletResource = m_resources->m_sptrBulletsResources->at(type);

	std::vector<std::unique_ptr<bullets::Bullet>> bulletVec;
	bulletVec.reserve(size);
	bulletVec.resize(size);
	for (auto itt = bulletVec.begin(), end = bulletVec.end(); itt != end; ++itt)
	{
		auto uptrBullet = std::unique_ptr<bullets::Bullet>(std::make_unique<data_type>());
		uptrBullet->init(bulletResource);
		itt->swap(uptrBullet);
	}
	m_bulletMap.insert(std::make_pair(type, std::move(bulletVec)));
}

/// <summary>
/// @brief fireblast bullet fire method.
/// 
/// fires 1 fireblast at each weapon
/// </summary>
/// <param name="pos1">reference to first weapons position</param>
/// <param name="pos2">reference to second weapons position</param>
void BulletManager::fireOne(const sf::Vector2f & pos1, const sf::Vector2f & pos2, const BulletTypes& type)
{
	int numFired = 0; //local variable to see how many bullets were fired used to determine if 2 turrets shot
	for (auto & uptrBullet : m_bulletMap.at(type))
	{
		auto & bullet = *uptrBullet;
		if (!bullet.isActive())
		{
			if (numFired == 0)
			{
				bullet.setPosition(pos1);
				bullet.setActive(true);
				numFired++;
			}
			else if (numFired == 1)
			{
				bullet.setPosition(pos2);
				bullet.setActive(true);
				numFired++;
				break;
			}
		}
	}
	m_timeSinceFire = 0;
}
