#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "Thor\Animations.hpp"
#include "Player.h"
#include "tinyheaders\tinyc2.h"

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
		/// 
		/// @author Rafael Plugge
		/// @brief Container of shared pointers to ship resources.
		/// 
		/// 
		struct Ship
		{
			/// <summary>
			/// @brief shared pointer to ship texture.
			/// 
			/// 
			/// </summary>
			std::shared_ptr<sf::Texture> m_sptrShipTexture = nullptr;

			/// <summary>
			/// @brief shared pointer to ship animator
			/// </summary>
			std::shared_ptr<SpriteAnimator> m_sptrShipAnimator = nullptr;

		};
		/// <summary>
		/// @brief unique pointer to ship resources.
		/// 
		/// 
		/// </summary>
		std::unique_ptr<GameScene::Resources::Ship> m_uptrShip =
			std::make_unique<GameScene::Resources::Ship>();
	};

public:
	GameScene(KeyHandler& keyHandler);
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

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
};

#endif // !GAMESCENE_H