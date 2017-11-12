#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "Scene.h"

/// 
/// @brief Represents our title scene.
/// @author Rafael Plugge
/// 
/// Will display our game title and a background,
/// waiting for the player to press any key to continue
/// onto the next scene.
/// 
class TitleScene : public Scene
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
		/// @brief shared pointer to a big background texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<thor::BigTexture> m_sptrBackgroundTexture;

		/// <summary>
		/// @brief shared pointer to big title texture.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<thor::BigTexture> m_sptrTitleTexture;

		/// <summary>
		/// @brief shared pointer to title font.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Font> m_sptrTextFont;
	};

public:
	TitleScene(std::shared_ptr<KeyHandler> keyhandler, std::shared_ptr<Controller> controller);
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void goToNextScene() final override;
	void setup(const std::string & filePath);

	/// <summary>
	/// @brief Shared pointer to our key handler.
	/// 
	/// Used to check if any key is pressed.
	/// </summary>
	std::shared_ptr<KeyHandler> m_keyHandler;

	/// <summary>
	/// @brief Shared pointer to our controller.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Controller> m_controller;

	/// <summary>
	/// @brief Unique pointer to our Resources.
	/// 
	/// Used as to determine the lifetime of its members.
	/// </summary>
	std::unique_ptr<Resources> m_resources;

	/// <summary>
	/// @brief Unique pointer to our background sprite.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<thor::BigSprite> m_backgroundSprite;

	/// <summary>
	/// @brief Unique pointer to our title sprite.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<thor::BigSprite> m_titleSprite;

	/// <summary>
	/// @brief Unique pointer to our continue text.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<sf::Text> m_continueText;

};

#endif // !TITLESCENE_H