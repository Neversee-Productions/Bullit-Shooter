#ifndef GAMESCENE_H
#define GAMESCENE_H

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
#include "Entities\Entities.h"
#include "util\JsonLoader.h"
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
			std::shared_ptr<ai::AiBasic::Resources> m_sptrBasicEnemy =
				std::make_shared<ai::AiBasic::Resources>();
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
	GameScene(KeyHandler& keyHandler);
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void updateCollisions();
	void bulletAsteroidsCollision();
	void playerAsteroidCollision();
	void playerEnemyCollision();
	void collisionResponse(Asteroid & asteroid, bullets::Bullet & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::MagmaShot & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::NapalmSphere & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::PyroBlast & bullet);
	void playerPickupCollision();
	void playerUICollision();
	float generateRandomTimer();
	void updateAsteroidSpawner();

private:
	void goToNextScene() final override;
	void setup(const std::string & filePath);
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
	/// @brief define how long since last spawned asteroid.
	/// 
	/// 
	/// </summary>
	float m_asteroidSpawnTimer;

	/// <summary>
	/// @brief define length of time between asteroid spawns.
	/// 
	/// 
	/// </summary>
	float m_asteroidSpawnFrequency;

	/// <summary>
	/// @brief constant reference to update delta time.
	/// 
	/// 
	/// </summary>
	const float & UPDATE_DT;

	/// <summary>
	/// @brief testing a pickup.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<Pickup> m_pickup;

	// HACK : Temporary enemy

	ai::AiBasic m_enemy;

	/// <summary>
	/// @brief this is the UI object.
	/// 
	/// 
	/// </summary>
	GameUI m_ui;
};

#endif // !GAMESCENE_H