#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "Thor\Animations.hpp"
#include "Player.h"
#include "tinyheaders\tinyc2.h"
#include "Asteroid.h"

///
/// @brief Main game scene.
/// @author Rafael Plugge
/// 
/// Defines our main gameplay scene.
/// 
class GameScene : public Scene
{
private:
	/// <summary>
	/// @brief Defines a alias for our thor::Animator.
	/// 
	/// This animator will animate
	/// </summary>
	typedef thor::Animator<sf::Sprite, std::string> SpriteAnimator;

	/// 
	/// @author Rafael Plugge
	/// @brief Container of shared pointers to our resources.
	/// 
	/// 
	/// 
	struct Resources
	{
		/// <summary>
		/// @brief unique pointer to player resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Player::Resources> m_sptrPlayer =
			std::make_shared<Player::Resources>();
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
	void collisionResponse(Asteroid & asteroid, bullets::Bullet & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::MagmaShot & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::NapalmSphere & bullet);
	void collisionResponse(Asteroid & asteroid, bullets::PyroBlast & bullet);

private:
	void goToNextScene() final override;
	void setup(const std::string & filePath);
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
	/// @brief defines an asteroid.
	/// 
	/// 
	/// </summary>
	Asteroid m_asteroid;

	/// <summary>
	/// @brief constant reference to the window.
	/// 
	/// 
	/// </summary>
	const tinyh::c2AABB& m_windowC2Rect;
};

#endif // !GAMESCENE_H