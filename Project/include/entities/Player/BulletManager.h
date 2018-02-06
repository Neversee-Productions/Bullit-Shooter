#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

// STL Includes
#include <vector>
#include <unordered_map>
#include <memory>
// Thor Includes
#include "Thor/Animations.hpp"
// Project Includes
#include "system\Window.h"
#include "sound\SoundManager.h"
#include "Weapon.h"
#include "Bullets/Bullet.h"
#include "Bullets/Standard.h"
#include "Bullets/BulletTypes.h"
#include "Bullets/Empowered.h"
#include "Bullets/DeathOrb.h"
#include "Bullets/FireBlast.h"
#include "Bullets/HolySphere.h"
#include "Bullets/MagmaShot.h"
#include "Bullets/CometShot.h"
#include "Bullets/NapalmSphere.h"
#include "Bullets/NullWave.h"
#include "Bullets/StaticSphere.h"
#include "Bullets/PyroBlast.h"

///
/// @brief The bullet manager class.
/// @author Sebastian Kruzel
/// @author Rafael Plugge
/// 
/// A class to manage bullets.
/// 
class BulletManager
{
public:

	/// 
	/// @author Rafael Plugge
	/// @brief Determines the resources the bullets need.
	/// 
	/// 
	/// 
	struct Resources
	{
		/// <summary>
		/// @brief Defines a alias for the container used to store the bullet resources.
		/// 
		/// 
		/// </summary>
		typedef std::unordered_map<BulletTypes, std::shared_ptr<bullets::Bullet::Resources>> BulletResources;

		/// <summary>
		/// @brief Defines a unordered map of unique pointers to bullet resources.
		/// 
		/// Using the BulletTypes enum as the key.
		/// </summary>
		std::shared_ptr<BulletResources> m_sptrBulletsResources = 
			std::make_shared<BulletResources>();
	};

public:
	BulletManager();
	void init(std::shared_ptr<Resources> sptrResources);
	void fireBullet(Weapon& weapon1, Weapon & weapon2, const BulletTypes& type);
	void initBulletvector(BulletTypes type);
	void reuseBullet(bullets::Bullet& bullet, sf::Vector2f pos);
	void draw(Window & window, const float & deltaTime);
	void update();
	template<typename data_type>
	void initBulletMapVector(const BulletTypes& type, const int& size);
	void updateWindowCollisions();
	void fireOne(const sf::Vector2f& pos1, const sf::Vector2f& pos2, const BulletTypes& type);
	void fireEmpowered(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	void setEmpowered(bullets::Bullet& bullet ,const float& angle, const sf::Vector2f& pos);
	const std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>> & getBulletMap();

private:
	/// <summary>
	/// @brief Alias for a (bullet_type: constant string) map.
	/// 
	/// 
	/// </summary>
	typedef std::unordered_map<BulletTypes, const std::string> BulletTypeStringMap;

private:
	/// <summary>
	/// @brief how long since last fire.
	/// 
	/// 
	/// </summary>
	float m_timeSinceFire;

	/// <summary>
	/// @brief constant reference to the window.
	/// 
	/// 
	/// </summary>
	const tinyh::c2AABB& m_windowC2Rect;

	/// <summary>
	/// @brief Map of bullet types to vector of bullets.
	/// 
	/// 
	/// </summary>
	std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>> m_bulletMap;

	/// <summary>
	/// @brief shared pointer to loaded resources.
	/// 
	/// This shared pointer is nullptr until resources are loaded
	/// and BulletManager::init is called.
	/// </summary>
	std::shared_ptr<Resources> m_resources;

	/// <summary>
	/// @brief reference to sound manager instance.
	/// 
	/// used for playing sounds when firing.
	/// </summary>
	SoundManager & m_soundManager;

	/// <summary>
	/// @brief Map of bullet types to fire string.
	/// 
	/// 
	/// </summary>
	BulletTypeStringMap m_soundFireMap;

};
#endif // !BULLETMANAGER_H

