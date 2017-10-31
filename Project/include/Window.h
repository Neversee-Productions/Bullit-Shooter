#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <Windows.h>
#include "SFML\Window\Event.hpp"
#include "SFML\Graphics\RenderWindow.hpp"
#include "SFML\Graphics\RenderTexture.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "KeyHandler.h"

/// 
/// @brief Wrapper window class.
/// @author Rafael Plugge
/// 
/// This class will wrap over the sfml RenderWindow.
/// 
class Window
{
public:
	Window(KeyHandler & keyHandler);
	~Window();
	void processEvents();
	void changeStyle(const sf::Uint32 & newStyle);
	void draw(sf::Drawable & drawable);
	void display();
	bool isOpen() const;
	void clear();

private:

	/// <summary>
	/// @brief SFML RenderWindow.
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
	/// all drawables are drawn on this texture and than
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

	/// <summary>
	/// @brief Reference to KeyHandler.
	/// 
	/// Will be used to update its map of keys
	/// @see Window::processEvents()
	/// </summary>
	KeyHandler & m_keyHandler;

};

#endif // !WINDOW_H