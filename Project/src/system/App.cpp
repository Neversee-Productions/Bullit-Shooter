#include "system\App.h"

sf::Vector2u App::s_viewSize = sf::Vector2u(0, 0);

const float App::s_updateDeltaTime = 1.0f / 60.0f;

tinyh::c2AABB App::s_rectView = tinyh::c2AABB();

/// <summary>
/// @brief Sets the window size.
/// 
/// 
/// </summary>
/// <param name="width">defines the width of the window.</param>
/// <param name="height">defines the height of the window.</param>
void App::setViewSize(const unsigned int & width, const unsigned int & height)
{
	s_viewSize.x = width;
	s_viewSize.y = height;
}

/// <summary>
/// @brief Acquires the window size.
/// 
/// 
/// </summary>
/// <returns>The window size as 2 unsigned integers.</returns>
const sf::Vector2u & App::getViewSize()
{
	return s_viewSize;
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
/// @brief a getter for the window rectangle.
/// 
/// 
/// </summary>
/// <returns>the collision rectangle.</returns>
const tinyh::c2AABB & App::getViewC2Rect()
{
	return s_rectView;
}

/// <summary>
/// @brief set the collision rectangle to be same as the window.
/// 
/// 
/// </summary>
/// <param name="min">minimum (top left) corner of screen</param>
/// <param name="max">maximum (bottom right) corner of screen</param>
void App::setViewC2Rect(const sf::Vector2f & min, const sf::Vector2f & max)
{
	s_rectView.min.x = min.x;
	s_rectView.min.y = min.y;
	s_rectView.max.x = max.x;
	s_rectView.max.y = max.y;
}
