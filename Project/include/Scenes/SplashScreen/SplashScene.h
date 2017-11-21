#ifndef SPLASHSCENE_H
#define SPLASHSCENE_H

#include "Scene.h"

/// 
/// @brief Represents our splash scene.
/// @author Rafael Plugge
/// 
/// Will fade our logo in and out than proceed to next scene.
/// 
class SplashScene : public Scene
{
private:
	/// <summary>
	/// @brief Determine what state the fade transition is in.
	/// 
	/// 
	/// </summary>
	enum class FadeState
	{
		FadeIn,
		FadeOut
	};

public:
	SplashScene();
	void preStart(const std::string & resourceFilePath) final override;
	void start(const std::string & resourceFilePath) final override;
	void stop() final override;
	void update() final override;
	void draw(Window & window, const float & deltaTime) final override;

private:
	void goToNextScene() final override;
	void setup(const std::string & filePath);

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
		std::shared_ptr<thor::BigTexture> m_backgroundTexture =
			std::make_shared<thor::BigTexture>();
	};
	/// <summary>
	/// @brief Unique pointer to our Resources.
	/// 
	/// Used as to determine the lifetime of its members.
	/// </summary>
	std::unique_ptr<Resources> m_resources;

	/// <summary>
	/// @brief unique pointer to our background sprite.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<thor::BigSprite> m_backgroundSprite;

	/// <summary>
	/// @brief Unique pointer to our background color filter.
	/// 
	/// Used to apply fading effect.
	/// </summary>
	std::unique_ptr<sf::Color> m_backgroundColor;

	/// <summary>
	/// @brief Constant that we increment our color alpha by.
	/// 
	/// 
	/// </summary>
	const sf::Uint8 m_incrementColor;

	/// <summary>
	/// @brief Determines whether or not to fade in or out.
	/// 
	/// 
	/// </summary>
	FadeState m_fadeState;
};

#endif // !SPLASHSCENE_H