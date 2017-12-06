#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"
#include "Ship.h"
#include "Weapon.h"
#include "BulletManager.h"

///
/// @brief Player class.
/// @author Sebastian Kruzel
/// @author Rafael Plugge
/// 
/// Defines the player class.
/// This class will create the Weapon, Shield, Ship and BulletManager.
/// 
class Player
{
public:
	/// 
	/// @author Rafael Plugge
	/// @brief Determines the resources the player needs.
	/// 
	/// 
	struct Resources
	{
		/// <summary>
		/// @brief Shared pointer to ship resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Ship::Resources> m_ship = std::make_shared<Ship::Resources>();

		/// <summary>
		/// @brief shared pointer to weapon resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Weapon::Resources> m_weapon =
			std::make_shared<Weapon::Resources>();

		//std::shared_ptr<bullets::Bullet::Resources> m_bullet =
		//	std::make_shared<bullets::Bullet::Resources>();
	};

public:
	Player(KeyHandler& keyHandler);
	void init(std::shared_ptr<Resources> resources);
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
	/// @brief Defines the Weapon1 (weapon left of the player).
	/// 
	/// 
	/// </summary>
	Weapon m_weaponLeft;

	/// <summary>
	/// @brief Defines the Weapon1 (weapon right of the player).
	/// 
	/// 
	/// </summary>
	Weapon m_weaponRight;

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
	sf::Vector2f m_weaponLeftPos;

	/// <summary>
	/// @brief position of bottom weapon.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_weaponRightPos;
};

#endif PLAYER_H