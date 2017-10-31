#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "SFML\Graphics\RectangleShape.hpp"

///
/// @brief Main game scene.
/// @author Rafael Plugge
/// 
/// Defines our main gameplay scene.
/// 
class GameScene : public Scene
{
public:
	GameScene();
	void start() override;
	void stop() override;
	void update() override;
	void draw(Window & window, const float & deltaTime) override;

private:
	/// <summary>
	/// @brief Represents a square on the screen.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_square;

};

#endif // !GAMESCENE_H