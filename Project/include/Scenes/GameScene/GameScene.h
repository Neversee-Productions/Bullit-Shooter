#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SFML\Graphics\RectangleShape.hpp"
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
public:
	GameScene(KeyHandler& keyHandler);
	void start() override;
	void stop() override;
	void update() override;
	void draw(Window & window, const float & deltaTime) override;

private:
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