#include "App.h"

sf::Vector2u App::s_windowSize = sf::Vector2u(0, 0);

const float App::s_updateDeltaTime = 1.0f / 60.0f;

/// <summary>
/// @brief Sets the window size.
/// 
/// 
/// </summary>
/// <param name="width">defines the width of the window</param>
/// <param name="height">defines the height of the window.</param>
void App::setWindowSize(const unsigned int & width, const unsigned int & height)
{
	s_windowSize.x = width;
	s_windowSize.y = height;
}

/// <summary>
/// @brief Acquires the window size.
/// 
/// 
/// </summary>
/// <returns>The window size as 2 unsigned integers.</returns>
const sf::Vector2u & App::getWindowSize()
{
	return s_windowSize;
}

/// <summary>
/// @brief Acquires the update delta time.
/// 
/// Update delta time is the time step for a 
/// single update call.
/// </summary>
/// <returns>The update delta time as a read only reference.</returns>
const float & App::getUpdateDeltaTime()
{
	return s_updateDeltaTime;
}
