#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>
#include <memory>
#include "Window.h"
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
	BulletManager();
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
	/// @map of bullet types to bullets.
	/// 
	/// 
	/// </summary>
	std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>> m_bulletMap;
};
#endif // !BULLETMANAGER_H

