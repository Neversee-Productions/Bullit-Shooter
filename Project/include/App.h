#ifndef APP_H
#define APP_H

#include "SFML\System\Vector2.hpp"

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
	App() {};

public:
	static void setWindowSize(const unsigned int & width, const unsigned int & height);
	static const sf::Vector2u & getWindowSize();
	static const float & getUpdateDeltaTime();

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

};

#endif // !APP_H