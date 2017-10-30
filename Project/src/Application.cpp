#include "Application.h"

const float Application::s_UPDATE_DT = 1.0f / 60.0f;

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
	// Time elapsed since last' frame update call.
	float lag = s_UPDATE_DT;
	// Dynamic delta time step between render calls.
	float renderDT = 0.0f;
	// Fixed delta time step between update calls.
	const float & updateDT = Application::s_UPDATE_DT;
	
	while (m_window.isOpen())
	{
		renderDT = clock.restart().asSeconds();
		lag += renderDT;
		m_window.processEvents();
		while (lag > updateDT);
		{
			m_sceneManager.update();
			lag -= updateDT;
		}

		m_sceneManager.draw(renderDT);
	}
}