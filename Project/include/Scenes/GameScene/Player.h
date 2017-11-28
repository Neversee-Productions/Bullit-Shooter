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
/// This class will create the Weapon, Shield, Ship and BulletManager.
/// 
class Player
{
public:
	Player(KeyHandler& keyHandler);
	void draw(Window & window, const float & deltaTime);
	void update();
	const std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>> & getBulletMap();
private:

private:
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

	/// <summary>
	/// @brief constant reference to delta time.
	/// 
	/// 
	/// </summary>
	const float & deltaTime;
	
	/// <summary>
	/// @brief position of top weapon.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_weapon1Pos;

	/// <summary>
	/// @brief position of bottom weapon.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_weapon2Pos;
};

#endif PLAYER_H