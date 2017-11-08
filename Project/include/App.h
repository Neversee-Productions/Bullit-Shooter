#ifndef APP_H
#define APP_H

#include "SFML\System\Vector2.hpp"
#include "tinyheaders\tinyc2.h"

/// 
/// @brief Static container for all static variables.
/// @author Rafael Plugge
/// 
/// Will contain static variables that are used throughout the application.
/// Example: Window dimensions.
/// 
class App
{
private:
	/// <summary>
	/// @brief default constructor.
	/// 
	/// @note app is purely static therefore constructor is private.
	/// </summary>
	App() {};

public:
	static void setWindowSize(const unsigned int & width, const unsigned int & height);
	static const sf::Vector2u & getWindowSize();
	static const float & getUpdateDeltaTime();
	static const tinyh::c2AABB & getWindowC2Rect();
	static void setWindowC2Rect(const sf::Vector2f& min, const sf::Vector2f& max);

private:
	/// <summary>
	/// @brief Contains the window size.
	/// 
	/// Will be used by many different classes,
	/// to perform any window size dependant operations.
	/// </summary>
	static sf::Vector2u s_windowSize;

	/// <summary>
	/// @brief Represents the time step for one update tick.
	/// 
	/// 
	/// </summary>
	static const float s_updateDeltaTime;


	/// <summary>
	/// @brief define the collision rectangle window.
	/// 
	/// 
	/// </summary>
	static tinyh::c2AABB s_rectWindow;
};

#endif // !APP_H