#include "Application.h"

/// <summary>
/// @brief Application constructor.
/// 
/// 
/// </summary>
Application::Application()
	: m_keyHandler()
	, m_window(m_keyHandler)
	, m_sceneManager(m_window, m_keyHandler)
{

}

/// <summary>
/// @brief Application destructor.
/// 
/// 
/// </summary>
Application::~Application()
{
}

/// <summary>
/// @brief Main Entry point for entire application.
/// 
/// 
/// </summary>
void Application::run()
{
	// Internal game loop clock.
	sf::Clock clock;
	// Fixed delta time step between update calls.
	const float & updateDT = App::getUpdateDeltaTime();
	// Time elapsed since last' game loop call.
	float lag = updateDT;
	// Dynamic delta time step between render calls.
	float renderDT = 0.0f;
	
	while (m_window.isOpen())
	{
		renderDT = clock.restart().asSeconds();
		lag += renderDT;
		m_window.processEvents();
		while (lag > updateDT)
		{
			m_sceneManager.update();
			lag -= updateDT;
		}

		m_sceneManager.draw(renderDT);
	}
}