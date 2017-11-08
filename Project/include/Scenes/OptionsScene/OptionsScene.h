#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "Scene.h"
#include "gui\GUI.h"

/// 
/// @brief Represents our Options scene.
/// @author Rafael Plugge
/// 
/// 
/// 
class OptionsScene : public Scene
{
public:
	OptionsScene(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller);
	void start() final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void btnBack();

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
		/// <summary>
		/// @brief shared pointer to font.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Font> m_sptrButtonFont = std::make_shared<sf::Font>();

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrButtonTexture = std::make_shared<sf::Texture>();
	};

	/// <summary>
	/// @brief Unique pointer to our Resources struct.
	/// 
	/// Used as to determine the lifetime of its members.
	/// </summary>
	std::unique_ptr<Resources> m_resources;

	/// <summary>
	/// @brief Timer before leaving scene.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<sf::Clock> m_timer;


	/// <summary>
	/// @brief Defines the amount of time before scene switches.
	/// 
	/// 
	/// </summary>
	const float m_DELAY_TIME;

	/// <summary>
	/// @brief Container for next scene name.
	/// 
	/// 
	/// </summary>
	std::string m_nextName;

};

#endif // !OPTIONSSCENE_H