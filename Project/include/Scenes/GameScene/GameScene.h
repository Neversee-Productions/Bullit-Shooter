#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "Player.h"

///
/// @brief Main game scene.
/// @author Rafael Plugge
/// 
/// Defines our main gameplay scene.
/// 
class GameScene : public Scene
{
public:
	GameScene(KeyHandler& keyHandler);
	void start() final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	/// <summary>
	/// @brief Represents a square on the screen.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_square;

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

};

#endif // !GAMESCENE_H