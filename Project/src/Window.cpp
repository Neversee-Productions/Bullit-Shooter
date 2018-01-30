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
	: m_title()
	, m_style(sf::Style::Default)
	, m_sfWindow()
	, m_resolution()
	, m_supportedResolutions()
	, m_renderTexture()
	, m_textureRenderer()
	, m_keyHandler(keyHandler)
{
	///////////////////////////////////////////////////////
	// define our windows title
	///////////////////////////////////////////////////////
	m_title = "Bullit \" \" Shooter";

	///////////////////////////////////////////////////////
	// keep our vector of supported resolutions
	///////////////////////////////////////////////////////
	std::vector<sf::VideoMode> const & fullscreenRes = sf::VideoMode::getFullscreenModes();
	// using the insert( range ) function that our supportedResolutions container must support
	m_supportedResolutions.insert(m_supportedResolutions.begin(), fullscreenRes.begin(), fullscreenRes.end());

	///////////////////////////////////////////////////////
	// define our current resolution.
	///////////////////////////////////////////////////////
	// //windowed mode
	//m_style = sf::Style::Default;
	//m_resolution = sf::VideoMode(1366u, 768u);
	 //fullscreen mode
	m_style = sf::Style::Fullscreen;
	m_resolution = fullscreenRes.at(0);

	///////////////////////////////////////////////////////
	// create our window with pre-defined settings
	///////////////////////////////////////////////////////
	sf::ContextSettings settings = sf::ContextSettings();
	settings.majorVersion = 3u;
	settings.minorVersion = 0u;
	settings.attributeFlags = sf::ContextSettings::Attribute::Default;
	settings.depthBits = 24u;
	settings.stencilBits = 8u;
	settings.antialiasingLevel = 8u;
	
	m_sfWindow.create(m_resolution, m_title, m_style, settings);

	///////////////////////////////////////////////////////
	// create and initialize our render texture
	///////////////////////////////////////////////////////
	const sf::Vector2u textureOriginalSize = sf::Vector2u(1366u, 768u);
	m_renderTexture.create(textureOriginalSize.x, textureOriginalSize.y, false);

	///////////////////////////////////////////////////////
	// initialize our texture renderer
	///////////////////////////////////////////////////////
	
	const auto & textureSize = static_cast<sf::Vector2f>(m_renderTexture.getSize());
	const auto & windowSize = static_cast<sf::Vector2f>(m_sfWindow.getSize());
	const sf::Vector2f textureScalar(windowSize.x / textureSize.x, windowSize.y / textureSize.y);
	
	m_textureRenderer.setColor(sf::Color::White);
	m_textureRenderer.setPosition(0.0f, 0.0f);
	m_textureRenderer.setOrigin(0.0f, 0.0f);
	m_textureRenderer.setRotation(0.0f);
	m_textureRenderer.setScale(textureScalar);
	m_textureRenderer.setTexture(m_renderTexture.getTexture(), true);

	///////////////////////////////////////////////////////
	// initialize Views Size
	///////////////////////////////////////////////////////
	const auto & viewSize = m_renderTexture.getSize();
	App::setViewSize(viewSize.x, viewSize.y);
	App::setViewC2Rect(sf::Vector2f(0.0f, 0.0f), static_cast<sf::Vector2f>(App::getViewSize()));
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
			// The window requested to be closed (no data)
			m_sfWindow.close();
			break;
		case EventType::Resized:
			// The window was resized (data in event.size)
			// screen should NOT be resizeable since
			// we don't want to have to recreate m_renderTexture,
			// in this manner
			break;
		case EventType::LostFocus:
			// The window lost the focus (no data)
			break;
		case EventType::GainedFocus:
			// The window gained the focus (no data)
			break;
		case EventType::TextEntered:
			// A character was entered (data in event.text)
			break;
		case EventType::KeyPressed:
			// A key was pressed(data in event.key)
			m_keyHandler.updateKey(ev.key.code, true);
			break;
		case EventType::KeyReleased:
			// A key was released (data in event.key)
			m_keyHandler.updateKey(ev.key.code, false);
			break;
		case EventType::MouseButtonPressed:
			// A mouse button was pressed (data in event.mouseButton)
			break;
		case EventType::MouseButtonReleased:
			// A mouse button was released (data in event.mouseButton)
			break;
		case EventType::MouseMoved:
			// The mouse cursor moved (data in event.mouseMove)
			break;
		case EventType::MouseEntered:
			// The mouse cursor entered the area of the window (no data)
			break;
		case EventType::MouseLeft:
			// The mouse cursor left the area of the window(no data)
			break;
		case EventType::Count:
			// Keep the total number of event types.
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// @brief Will alter the style of the sfml window by using its window handle,
///		required to be able to change the window style at runtime without 
///		having to destroy/create the sfml window.
/// 
/// Complex Operating System dependant function,
/// where we adjust the SFML Window, using Windows OS handler,
/// acquire the window's system handle and
/// added appropriate windows Uint32 Flag for each window component based
/// on the passed sfml Style.
/// 
/// @warning If performed on a OS different than Windows the window is closed than re-created instead.
/// </summary>
/// <param name="newStyle">Flag for the new style that the window will be changed to.</param>
void Window::changeStyle(const sf::Uint32 & newStyle)
{
	// Verifies that operation is running on Windows Operating System
#ifdef _WIN32

	// store window handler
	sf::WindowHandle handle = m_sfWindow.getSystemHandle();
	// create a unsigned 32-bit integer to be used as flags for window style.
	unsigned int win32Style = WS_VISIBLE;

	if (newStyle == sf::Style::None)
	{
		win32Style |= WS_POPUP;
	}
	else
	{
		if (newStyle & sf::Style::Titlebar)
		{
			win32Style |= WS_CAPTION | WS_MINIMIZEBOX;
		}
		if (newStyle & sf::Style::Resize)
		{
			win32Style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
		}
		if (newStyle & sf::Style::Close)
		{
			win32Style |= WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
		}
	}

	// Changes the Windows OS system handle specific to the Window's style
	SetWindowLongPtr(handle, GWL_STYLE, win32Style);

	// Force changes to take effect
	SetWindowPos(handle, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);

#else 
	// perform standard way for other platforms
	// will close than re-create the window, much less smoother.

	sf::ContextSettings settings = m_sfWindow.getSettings();
	m_sfWindow.close();
	m_sfWindow.create(m_resolution, m_title, m_style, settings);

#endif
}

/// <summary>
/// @brief Draws the drawable on the render texture.
/// 
/// Drawable is drawn on our render texture with default render state.
/// </summary>
/// <param name="drawable">target that will be rendered on next produced frame.</param>
void Window::draw(const sf::Drawable & drawable)
{
	m_renderTexture.draw(drawable, sf::RenderStates::Default);
}

/// <summary>
/// @brief Draws the drawable on the render texture.
/// 
/// Drawable is drawn on our render texture with the passed render state.
/// </summary>
/// <param name="drawable">target that will be rendered on next produced frame.</param>
/// <param name="renderState">the render state we want to apply to our target.</param>
void Window::draw(const sf::Drawable & drawable, const sf::RenderStates & renderState)
{
	m_renderTexture.draw(drawable, renderState);
}

/// <summary>
/// @brief Finalizes internal rendering processes.
/// 
/// Gets render texture drawn into our window and our window produces the frame.
/// </summary>
void Window::display()
{
	m_renderTexture.display();
	m_sfWindow.draw(m_textureRenderer);
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
	m_sfWindow.clear();
}

/// <summary>
/// @brief Closes current window.
/// 
/// 
/// </summary>
void Window::close()
{
	m_renderTexture.clear();
	m_sfWindow.clear();
	m_sfWindow.close();
}

/// <summary>
/// @brief Gets the window's current style.
/// 
/// 
/// </summary>
/// <returns>returns the style as a number that directly corresponds to sf::Style.</returns>
sf::Uint32 const & Window::getStyle() const
{
	return m_style;
}

/// <summary>
/// @brief Defines new window style.
/// 
/// @see Window::changeStyle
/// </summary>
/// <param name="newStyle">defines new style flag for window.</param>
void Window::setStyle(sf::Uint32 const & newStyle)
{
	m_style = newStyle;
	this->changeStyle(m_style);
}
