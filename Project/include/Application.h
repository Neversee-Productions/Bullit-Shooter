#ifndef APPLICATION_H
#define APPLICATION_H

#include "SFML\System.hpp"
#include "input\KeyHandler.h"
#include "Window.h"
#include "SceneManager.h"
#include "App.h"

/// 
/// @brief Main application starter.
/// @author Rafael Plugge
/// 
/// Boots up application, setups main controller and window.
/// 
class Application
{
public:
	Application();
	~Application();
	void run();

private:

	/// <summary>
	/// @brief Handles the input of keys.
	/// 
	/// Used to check if a particular key is pressed.
	/// </summary>
	KeyHandler m_keyHandler;

	/// <summary>
	/// @brief Application window.
	/// 
	/// Used in main loop to query for alive state.
	/// </summary>
	Window m_window;

	/// <summary>
	/// @brief Main application controller.
	/// 
	/// will controll what update and rendering is performed.
	/// </summary>
	SceneManager m_sceneManager;

};

#endif // !APPLICATION_H