#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"
#include "Ship.h"
#include "Weapon.h"
#include "BulletManager.h"

///
/// @brief Player class.
/// @author Sebastian Kruzel
/// 
/// Defines the player class.
/// This class will create the Weapon, Shield, Ship and BulletManager
/// 
class Player
{
public:
	Player(KeyHandler& keyHandler);
	void draw(Window & window, const float & deltaTime);
	void update();

	/// <summary>
	/// @brief Defines the ship object.
	/// 
	/// 
	/// </summary>
	Ship m_ship;

	/// <summary>
	/// @brief Defines the Weapon1 (weapon above the player).
	/// 
	/// 
	/// </summary>
	Weapon m_weapon1;

	/// <summary>
	/// @brief Defines the Weapon1 (weapon below the player).
	/// 
	/// 
	/// </summary>
	Weapon m_weapon2;

	/// <summary>
	/// @brief reference to the key handler.
	/// 
	/// 
	/// </summary>
	KeyHandler& m_keyHandler;

	/// <summary>
	/// @brief the bullet manager object.
	/// 
	/// 
	/// </summary>
	BulletManager m_bulletManager;
};

#endif PLAYER_H