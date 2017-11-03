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
	MainMenuScene(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller);
	void start() final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void btnNewGame();
	void btnExitGame();

	/// <summary>
	/// @brief Unique pointer to our GUI.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<gui::GUI> m_gui;

	/// <summary>
	/// @brief Shared pointer to our key handler.
	/// 
	/// Needed to process input on our widgets.
	/// </summary>
	std::shared_ptr<KeyHandler> m_keyHandler;

	/// <summary>
	/// @brief Shared pointer to our controller.
	/// 
	/// Needed to process input on our widgets.
	/// </summary>
	std::shared_ptr<Controller> m_controller;

	/// <summary>
	/// @brief Container of shared pointers to our resources.
	/// 
	/// 
	/// </summary>
	struct Resources
	{
		std::shared_ptr<sf::Font> m_sptrButtonFont = std::make_shared<sf::Font>();
		std::shared_ptr<sf::Texture> m_sptrButtonTexture = std::make_shared<sf::Texture>();
	};
	/// <summary>
	/// @brief Unique pointer to our Resources struct.
	/// 
	/// Used as to determine the lifetime of its members.
	/// </summary>
	std::unique_ptr<Resources> m_resources;
};

#endif // !MAINMENUSCENE_H