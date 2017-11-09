#include "Scenes\GameScene\BulletManager.h"

/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
BulletManager::BulletManager()
	: m_timeSinceFire(10.0f)
	, m_windowC2Rect(App::getWindowC2Rect())
{
}

/// <summary>
/// @brief method that will add bullet to vector
/// 
/// 
/// </summary>
/// <param name="position1">define first gun position</param>
/// <param name="position2">define second gun position</param>
/// <param name="type">define type of bullet</param>
void BulletManager::fireBullet(const sf::Vector2f& position1,const sf::Vector2f& position2,const BulletTypes& type)
{
	if (m_bulletMap.find(type) == m_bulletMap.end()) //if bullet vector has not been instanciated, then do so.
	{
		initBulletvector(type);
	}

	if (m_timeSinceFire > bullets::Standard::getFireRate()) //if its time to fire do it.
	{
		switch (type)
		{
		case BulletTypes::Standard:
			fireStandard(position1, position2);
			//fireStandard(m_bullets.get(type), position1, position2);
			break;
		case BulletTypes::Empowered:
			fireEmpowered(position1, position2);
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
	{
		std::vector<std::unique_ptr<bullets::Bullet>> vStandard;
		vStandard.reserve(10);
		vStandard.resize(10);
		for (auto itt = vStandard.begin(), end = vStandard.end(); itt != end; ++itt)
		{
			//auto & vectorUniquePtrBullet = *itt;
			//std::unique_ptr<bullets::Bullet> uptrBullet = std::make_unique<bullets::Standard>();
			//vectorUniquePtrBullet.swap(uptrBullet);
			itt->swap(std::unique_ptr<bullets::Bullet>(std::make_unique<bullets::Standard>()));
		}
		m_bulletMap.insert(std::make_pair(type, std::move(vStandard)));
		break;
	}
	case BulletTypes::Empowered:
	{
		std::vector<std::unique_ptr<bullets::Bullet>> vEmpowered;
		vEmpowered.reserve(24);
		vEmpowered.resize(24);
		for (auto itt = vEmpowered.begin(), end = vEmpowered.end(); itt != end; ++itt)
		{
			itt->swap(std::unique_ptr<bullets::Bullet>(std::make_unique<bullets::Empowered>()));
		}
		m_bulletMap.insert(std::make_pair(type, std::move(vEmpowered)));
	}
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
/// @brief standard bullet fire method
/// 
/// fires 3 bullets where 2 are offset by 30 and -30 degrees
/// </summary>
/// <param name="pos1">reference to first weapons position</param>
/// <param name="pos2">reference to second weapons position</param>
void BulletManager::fireStandard(const sf::Vector2f & pos1, const sf::Vector2f & pos2)
{
	int numFired = 0; //local variable to see how many bullets were fired used to determine if 2 turrets shot
	for (auto & uptrBullet : m_bulletMap.at(BulletTypes::Standard))
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

/// <summary>
/// @brief empowered bullet fire method.
/// 
/// fires 3 bullets at each weapon
/// 2 of the bullets will be offset by -30 and 30 degrees
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
				setEmpowered(bullet, -5, pos1);
				break;
			case 1:
				setEmpowered(bullet, 0, pos1);
				break;
			case 2:
				setEmpowered(bullet, 5, pos1);
				break;
			case 3:
				setEmpowered(bullet, -5, pos2);
				break;
			case 4:
				setEmpowered(bullet, 0, pos2);
				break;
			case 5:
				setEmpowered(bullet, 5, pos2);
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

