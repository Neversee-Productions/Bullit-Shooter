#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include "SFML\Window\Event.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RenderTexture.hpp"
#include "SFML\Graphics\Sprite.hpp"

/// <summary>
/// @class Window
/// @brief Wrapper window class.
/// @author Rafael Plugge
/// 
/// This class will wrap over the sfml RenderWindow.
/// </summary>
class Window
{
public:
	Window();
	~Window();
	void processEvents();
	void changeStyle(const sf::Uint32 & newStyle);
	void draw(sf::Drawable & drawable);
	void display();

private:

	/// <summary>
	/// @brief SFML Window.
	/// 
	/// Handles OpenGL calls internally.
	/// </summary>
	sf::RenderWindow m_sfWindow;

	/// <summary>
	/// @brief SFML Video mode.
	/// 
	/// Holds our current resolution, that is used on our window.
	/// </summary>
	sf::VideoMode m_resolution;

	/// <summary>
	/// @brief STL List of SFML Video modes of resolutions.
	/// 
	/// Contains our graphics card supported resolutions,
	/// sorted from best to worst.
	/// </summary>
	std::list<sf::VideoMode> m_supportedResolutions;

	/// <summary>
	/// @brief Representation of our current frame.
	/// 
	/// This is our render target for render calls,
	/// all drawables drawn on this texture and than
	/// our frame is drawn on to the window.
	/// </summary>
	sf::RenderTexture m_renderTexture;

	/// <summary>
	/// @brief Renders our frame using this sprite.
	/// 
	/// Needed for sfml to do proper transforms internally,
	/// we will attach our frame as a texture to this sprite and
	/// draw it at (0, 0).
	/// </summary>
	sf::Sprite m_textureRenderer;
};

#endif // !WINDOW_H