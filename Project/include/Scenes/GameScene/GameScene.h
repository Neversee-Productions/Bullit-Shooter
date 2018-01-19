#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "Thor\Animations.hpp"
#include "tinyheaders\tinyc2.h"
#include "Entities\Entities.h"
#include "Thor\Math.hpp"

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
	};

public:
	GameScene(KeyHandler& keyHandler);
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;
	void updateCollisions();
	void bulletAsteroidsCollision();
	void playerAsteroidCollision();
	void collisionResponse(Asteroid & asteroid, bullets::Bullet & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::MagmaShot & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::NapalmSphere & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::PyroBlast & bullet);
	void playerPickupCollision();
	float generateRandomTimer();

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
	std::unique_ptr<Weapon::Resources::WeaponAnimation>
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
};

#endif // !GAMESCENE_H