#ifndef GAMESCENE_H
#define GAMESCENE_H

// STL Includes
// SFML Includes
#include "SFML\Graphics\RectangleShape.hpp"
#include "SFML\Audio\Sound.hpp"
// Thor Includes
#include "Thor\Animations.hpp"
#include "Thor\Math.hpp"
// tinyc2 Includes
#include "tinyheaders\tinyc2.h"
// Project Includes
#include "scenes\Scene.h"
#include "sound\SoundManager.h"
#include "Entities\Entities.h"
#include "entities\BasicEnemyManager.h"
#include "util\JsonLoader.h"
#include "util\CollisionSystem.h"
#include "gui\game_ui\GameUI.h"

///
/// @brief Main game scene.
/// @author Sebastian Kruzel
/// @author Rafael Plugge
/// 
/// Defines our main gameplay scene.
/// 
class GameScene : public Scene
{
private:
	/// 
	/// @author Rafael Plugge
	/// @brief Container of shared pointers to our resources.
	/// 
	/// 
	/// 
	struct Resources
	{
		/// 
		/// @author Rafael Plugge
		/// @brief Container of shared pointers to different enemy resources.
		/// 
		/// Needed since there are different enemy types.
		/// 
		struct Enemies
		{
			std::shared_ptr<Asteroid::Resources> m_sptrAsteroid =
				std::make_shared<Asteroid::Resources>();
			std::shared_ptr<BasicEnemyManager::Resources> m_sptrBasicEnemyManager =
				std::make_shared<BasicEnemyManager::Resources>();
		};

		/// <summary>
		/// @brief shared pointer to player resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Player::Resources> m_sptrPlayer =
			std::make_shared<Player::Resources>();

		/// <summary>
		/// @brief shared pointer to background resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Background::Resources> m_sptrBackground =
			std::make_shared<Background::Resources>();

		std::shared_ptr<Pickup::Resources> m_sptrPickup =
			std::make_shared<Pickup::Resources>();

		std::shared_ptr<Enemies> m_sptrEnemies =
			std::make_shared<Enemies>();

		std::shared_ptr<GameUI::Resources> m_sptrUI =
			std::make_shared<GameUI::Resources>();
	};

public:
	GameScene(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller);
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void backToMainMenu();
	void restartGame();
	void goToNextScene() final override;
	void setup(const std::string & filePath);
	void updateUI();
	void setupPlayer(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Player::Resources> sptrPlayerResources
		, json::json & gameSceneParser
	);
	void setupShip(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Ship::Resources> sptrShipResources
		, json::json & shipParser
	);
	void setupWeapons(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Weapon::Resources> sptrWeaponResources
		, json::json & weaponParser
	);
	std::unique_ptr<Weapon::Resources::IndividualWeapon>
		setupWeaponAnim(
			ResourceHandler & resourceHandler
			, json::json & weaponParser
			, std::string const & id
		);
	void setupConnector(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Connector::Resources> sptrConnectorResources
		, json::json & connectorParser
	);
	void setupBulletManager(
		ResourceHandler & resourceHandler
		, std::shared_ptr<BulletManager::Resources> sptrBulletManagerResources
		, json::json & bulletManagerParser
	);
	void setupBullet(
		ResourceHandler & resourceHandler
		, std::shared_ptr<BulletManager::Resources::BulletResources> sptrBulletResources
		, BulletTypes const & bulletType
		, json::json & bulletParser
		, std::string const & id
	);
	void setupBackground(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Background::Resources> sptrBackgroundResources
		, json::json & gameSceneParser
	);
	void setupPickups(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Pickup::Resources> sptrPickupResources
		, json::json & gameSceneParser
	);
	void setupPickup(
		ResourceHandler & resourceHandler
		, Pickup::Resources::PickupMap & pickupMap
		, json::json & pickupParser
		, BulletTypes const & pickupType
	);
	void setupPickupEffect(
		ResourceHandler & resourceHandler
		, Pickup::Resources::Effect & effect
		, json::json & effectParser
	);

	void setupEnemies(
		ResourceHandler & resourceHandler
		, std::shared_ptr<Resources::Enemies> sptrEnemies
		, json::json & gameSceneParser
	);

	void setupUI(
		ResourceHandler & resourceHandler
		, std::shared_ptr<GameUI::Resources> sptrUI
		, json::json & gameSceneParser
	);

	/// <summary>
	/// @brief Represents the player object
	/// 
	/// 
	/// </summary>
	Player m_player;

	/// <summary>
	/// @brief reference to the key handler.
	/// 
	/// 
	/// </summary>
	KeyHandler& m_keyHandler;

	/// <summary>
	/// @brief reference to the sound manager.
	/// 
	/// 
	/// </summary>
	SoundManager & m_soundManager;

	/// <summary>
	/// @brief Unique pointer to our Resources struct.
	/// 
	/// Used as to determine the lifetime of its members.
	/// </summary>
	std::unique_ptr<Resources> m_resources;

	/// <summary>
	/// @brief constant reference to the window.
	/// 
	/// 
	/// </summary>
	const tinyh::c2AABB& m_windowC2Rect;

	/// <summary>
	/// @brief defines the background of GameScene.
	/// 
	/// 
	/// </summary>
	Background m_background;

	/// <summary>
	/// @brief defines asteroid manager.
	/// 
	/// 
	/// </summary>
	AsteroidManager m_asteroidManager;

	/// <summary>
	/// @brief defines the a pickup.
	/// 
	/// 
	/// </summary>
	Pickup m_pickup;

	/// <summary>
	/// @brief manages the instances of all basic enemies.
	/// 
	/// 
	/// </summary>
	BasicEnemyManager m_basicEnemyManager;

	/// <summary>
	/// @brief this is the UI object.
	/// 
	/// 
	/// </summary>
	GameUI m_ui;

	/// <summary>
	/// @brief defines the collision system.
	/// 
	/// This will handle collisions between different entities.
	/// </summary>
	CollisionSystem m_collisionSystem;

	/// <summary>
	/// @brief determines if the game is paused or not.
	/// 
	/// 
	/// </summary>
	bool m_gamePaused;

	/// <summary>
	/// @brief check if game is over.
	/// 
	/// 
	/// </summary>
	bool m_gameEnded;

	/// <summary>
	/// @brief reference to the controller.
	/// 
	/// Allows for enquiry on inputs.
	/// </summary>
	Controller & m_controller;
};

#endif // !GAMESCENE_H