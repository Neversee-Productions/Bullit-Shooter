#include "App.h"

sf::Vector2u App::s_windowSize = sf::Vector2u(0, 0);

const float App::s_updateDeltaTime = 1.0f / 60.0f;

tinyh::c2AABB App::s_rectWindow = tinyh::c2AABB();

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

/// <summary>
/// @brief a gettter for the window rectangle.
/// 
/// 
/// </summary>
/// <returns>the collision rectangle</returns>
const tinyh::c2AABB & App::getWindowC2Rect()
{
	return s_rectWindow;
}

/// <summary>
/// @brief set the collision rectangle to be same as the window.
/// 
/// 
/// </summary>
/// <param name="min">minimum (top left) corner of screen</param>
/// <param name="max">maximum (bottom right) corner of screen</param>
void App::setWindowC2Rect(const sf::Vector2f & min, const sf::Vector2f & max)
{
	s_rectWindow.min.x = min.x;
	s_rectWindow.min.y = min.y;
	s_rectWindow.max.x = max.x;
	s_rectWindow.max.y = max.y;
}
