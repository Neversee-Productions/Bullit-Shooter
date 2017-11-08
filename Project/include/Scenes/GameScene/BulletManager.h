#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>
#include <memory.h>
#include "Bullet.h"
#include "BulletStandard.h"
#include "Window.h"
#include "BulletTypes.h"

///
/// @brief The bullet manager class.
/// @author Sebastian Kruzel
/// 
/// A class to manage bullets.
/// 
class BulletManager
{
public:
	BulletManager();
	void fireBullet(const sf::Vector2f& position1,const sf::Vector2f& position2,const BulletTypes& type);
	void initBulletvector(BulletTypes type);
	void reuseBullet(Bullet& bullet, sf::Vector2f pos);
	void draw(Window & window, const float & deltaTime);
	void update();

	/// <summary>
	/// @brief vector of bullets.
	/// 
	/// 
	/// </summary>
	std::vector<BulletStandard> m_standardBullets;

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
};
#endif // !BULLETMANAGER_H

