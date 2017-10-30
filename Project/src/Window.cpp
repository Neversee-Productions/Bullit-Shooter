#include "Window.h"

/// <summary>
/// @brief Creates and window wrapper.
/// 
/// Creates a sfml window,
/// acquires possible resolutions,
/// sets the best one to the current resolutions.
/// </summary>
/// <param name="keyHandler">stored reference to our key handler.</param>
Window::Window(KeyHandler & keyHandler)
	: m_sfWindow()
	, m_resolution()
	, m_supportedResolutions()
	, m_renderTexture()
	, m_textureRenderer()
	, m_keyHandler(keyHandler)
{
	///////////////////////////////////////////////////////
	// keep our vector of supported resolutions
	///////////////////////////////////////////////////////
	const std::vector<sf::VideoMode> & fullscreenRes = sf::VideoMode::getFullscreenModes();
	// using the insert( range ) function that our supportedResolutions container must support
	m_supportedResolutions.insert(m_supportedResolutions.begin(), fullscreenRes.begin(), fullscreenRes.end());

	///////////////////////////////////////////////////////
	// define our current resolution.
	///////////////////////////////////////////////////////
	m_resolution = sf::VideoMode::getDesktopMode();

	///////////////////////////////////////////////////////
	// create our window with pre-defined settings
	///////////////////////////////////////////////////////
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8u;
	
	m_sfWindow.create(m_resolution, "Stock_name", sf::Style::Close, settings);

	///////////////////////////////////////////////////////
	// create and initialize our render texture
	///////////////////////////////////////////////////////
	auto& windowSize = m_sfWindow.getSize();
	m_renderTexture.create(windowSize.x, windowSize.y, false);

	///////////////////////////////////////////////////////
	// initialize our texture renderer
	///////////////////////////////////////////////////////
	m_textureRenderer.setColor(sf::Color::White);
	m_textureRenderer.setPosition(0.0f, 0.0f);
	m_textureRenderer.setOrigin(0.0f, 0.0f);
	m_textureRenderer.setRotation(0.0f);
	m_textureRenderer.setScale(1.0f, 1.0f);
	m_textureRenderer.setTexture(m_renderTexture.getTexture(), true);
}

/// <summary>
/// @brief Deletes window.
/// 
/// All variables are automatically removed off the stack.
/// </summary>
Window::~Window()
{
}

/// <summary>
/// @brief Process SFML events.
/// 
/// Polls sfml's window events, and responds to them.
/// Key events are used to update our m_keyHandler map.
/// </summary>
void Window::processEvents()
{
	typedef sf::Event::EventType EventType;
	sf::Event ev;
	while (m_sfWindow.pollEvent(ev))
	{
		switch (ev.type)
		{
		case EventType::Closed:
			// window has been closed.
			m_sfWindow.close();
			break;
		case EventType::GainedFocus:
			// window has gained focus.
			break;
		case EventType::LostFocus:
			// window no longer has focus.
			break;
		case EventType::Resized:
			// window::Resized data is in ev.size
			// screen should NOT be resizeable since
			// we don't want to have to recreate m_renderTexture,
			// in this manner
			break;
		case EventType::KeyPressed:
			// window::KeyPressed data is in ev.key
			m_keyHandler.updateKey(ev.key.code, true);
			break;
		case EventType::KeyReleased:
			// window::KeyReleased data is in ev.key
			m_keyHandler.updateKey(ev.key.code, false);
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// @brief Windows OS hack.
/// 
/// Will alter the style of the sfml window by using its window handle,
/// required to be able to change the window style at runtime without 
/// having to destroy/create the sfml window.
/// 
/// @warning If peformed on a OS different than Windows the window is not changed.
/// </summary>
/// <param name="newStyle">Flag for the new style that the window will be changed to.</param>
void Window::changeStyle(const sf::Uint32 & newStyle)
{
	// to be implemented.
}

/// <summary>
/// @brief Draws the drawable on the render texture.
/// 
/// Drawable is drawn on our render texture with default render state.
/// </summary>
/// <param name="drawable">target that will be rendered on next produced frame</param>
void Window::draw(sf::Drawable & drawable)
{
	m_renderTexture.draw(drawable, sf::RenderStates::Default);
}

/// <summary>
/// @brief Finalizes internal rendering processes.
/// 
/// Gets render texture drawn into our window and our window produces the frame.
/// </summary>
void Window::display()
{
	m_renderTexture.display();
	m_sfWindow.draw(m_textureRenderer, sf::RenderStates::Default);
	m_sfWindow.display();
}

/// <summary>
/// @brief Tell whether window is open or not.
/// 
/// Used to determine whether or not a window is opened.
/// </summary>
/// <returns>True if window is open, false if it has been closed</returns>
bool Window::isOpen() const
{
	return m_sfWindow.isOpen();
}

/// <summary>
/// @brief Clears current frame.
/// 
/// Clears our render texture
/// </summary>
void Window::clear()
{
	m_renderTexture.clear();
}
