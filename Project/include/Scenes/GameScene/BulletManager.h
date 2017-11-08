#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>
#include <memory.h>
#include "Bullets/Bullet.h"
#include "Bullets/Standard.h"
#include "Window.h"
#include "Bullets/BulletTypes.h"
#include "Bullets/Empowered.h"

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
	void reuseBullet(bullets::Bullet& bullet, sf::Vector2f pos);
	void draw(Window & window, const float & deltaTime);
	void update();
	void fireStandard(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	void fireEmpowered(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	void setEmpowered(bullets::Empowered& bullet ,const float& angle, const sf::Vector2f& pos);

	/// <summary>
	/// @brief vector of bullets.
	/// 
	/// 
	/// </summary>
	std::vector<bullets::Standard> m_standardBullets;

	/// <summary>
	/// @brief vector of empowered bullets.
	/// 
	/// 
	/// </summary>
	std::vector<bullets::Empowered> m_empoweredBullets;

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

