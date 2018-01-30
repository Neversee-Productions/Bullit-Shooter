#ifndef PLAYER_H
#define PLAYER_H

#include "Window.h"
#include "..\Background.h"
#include "Ship.h"
#include "Weapon.h"
#include "BulletManager.h"
#include "Shield.h"
#include "Connector.h"

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

		/// <summary>
		/// @brief shared pointer to connector resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Connector::Resources> m_connector =
			std::make_shared<Connector::Resources>();

		/// <summary>
		/// @brief shared pointer to bullet resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<BulletManager::Resources> m_bullets =
			std::make_shared<BulletManager::Resources>();
	};

public:
	Player(KeyHandler& keyHandler, Background & background);
	void init(std::shared_ptr<Resources> resources);
	void draw(Window & window, const float & deltaTime);
	void update();
	void decrementShield(float dmg);
	const std::map<BulletTypes, std::vector<std::unique_ptr<bullets::Bullet>>> & getBulletMap();
	const sf::CircleShape& getShieldCircle();
	const tinyh::c2Circle& getShieldCollisionCircle();
	const float& getShieldHealth();
	void setAlive(bool check);
	sf::Vector2f const & getPosition() const;
	void nextWeapon();
	BulletTypes const & getWeaponType();
	sf::Vector2f const & getLeftWeaponPos();
	sf::Vector2f const & getRightWeaponPos();
	bool const & isAlive();
	void setConnectorPos(sf::Vector2f leftConnectorPos, sf::Vector2f rightConnectorPos);
	void setAttachedWeapons(bool check);
	const sf::Vector2f & getLeftConnectorPos();
	const sf::Vector2f & getRightConnectorPos();
	void fadeOutWeapons();
	void setWeaponsAlpha(float alpha);
	void setCanFire(bool fire);

private:
	void switchWeaponInput();

private:
	/// <summary>
	/// @brief reference to the background.
	/// 
	/// Weapon type alters the color of the background
	/// therefore background is coupled to player.
	/// </summary>
	Background & m_background;

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
	/// @brief Defines the connector between a weapon and a ship.
	/// 
	/// This connector connects between the left weapon to the ship.
	/// </summary>
	Connector m_connectLeftWeaponToShip;

	/// <summary>
	/// @brief Defines the Weapon1 (weapon right of the player).
	/// 
	/// 
	/// </summary>
	Weapon m_weaponRight;

	/// <summary>
	/// @brief Defines the connector between a weapon and a ship.
	/// 
	/// This connector connects between the right weapon to the ship.
	/// </summary>
	Connector m_connectRightWeaponToShip;

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

	/// <summary>
	/// @brief players shield.
	/// 
	/// 
	/// </summary>
	Shield m_shield;

	/// <summary>
	/// @brief define if player is active.
	/// 
	/// 
	/// </summary>
	bool m_alive;

	/// <summary>
	/// @brief define end position of the left connector.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_leftConnectorEnd;

	/// <summary>
	/// @brief define the end position of the right connector.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_rightConnectorEnd;

	/// <summary>
	/// @brief this boolean will determine if the connectors are attached to weapon.
	/// 
	/// 
	/// </summary>
	bool m_attachedWeapons;
};

#endif PLAYER_H