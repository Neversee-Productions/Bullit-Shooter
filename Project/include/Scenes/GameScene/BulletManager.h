#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>
#include <memory.h>
#include "Bullet.h"
#include "BulletStandard.h"
#include "Window.h"

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
	void fireBullet(sf::Vector2f position);
	void draw(Window & window, const float & deltaTime);
	void update();

	/// <summary>
	/// @brief vector of bullets.
	/// 
	/// 
	/// </summary>
	std::vector<BulletStandard> m_standardBullets;
};
#endif // !BULLETMANAGER_H

