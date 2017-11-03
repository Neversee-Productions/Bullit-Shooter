#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Scene.h"
#include "gui\GUI.h"
#include "App.h"

/// 
/// @brief Represents our main menu.
/// @author Rafael Plugge
/// 
/// Defines our Main Menu scene.
/// 
class MainMenuScene : public Scene
{
public:
	MainMenuScene(std::shared_ptr<Controller> controller);
	void start() final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	/// <summary>
	/// @brief Unique pointer to our GUI.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<gui::GUI> m_gui;

	/// <summary>
	/// @brief Shared pointer to our controller.
	/// 
	/// Needed to process input on our widgets.
	/// </summary>
	std::shared_ptr<Controller> m_controller;

};

#endif // !MAINMENUSCENE_H