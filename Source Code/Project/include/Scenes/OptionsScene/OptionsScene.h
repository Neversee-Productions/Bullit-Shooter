#ifndef OPTIONSSCENE_H
#define OPTIONSSCENE_H

#include "scenes\Scene.h"
#include "util\JsonLoader.h"
#include "gui\GUI.h"

/// 
/// @brief Represents our Options scene.
/// @author Rafael Plugge
/// 
/// 
/// 
class OptionsScene : public Scene
{
private:
	/// 
	/// @brief Container of shared pointers to our resources.
	/// @author Rafael Plugge
	/// 
	/// 
	/// 
	struct Resources
	{
		/// <summary>
		/// @brief shared pointer to font.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Font> m_sptrButtonFont;

		/// <summary>
		/// @brief shared pointer to texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrButtonTexture;

		/// <summary>
		/// @brief shared pointer to the help texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_sptrHelpTexture;
	};

public:
	OptionsScene(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller);
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void goToNextScene() final override;
	void setup(const std::string & filePath);
	void loadGui(Resources & resources, const sf::Uint32 & fontSize);
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

	/// <summary>
	/// @brief Unique pointer to the help sprite.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<sf::Sprite> m_helpSprite;

};

#endif // !OPTIONSSCENE_H