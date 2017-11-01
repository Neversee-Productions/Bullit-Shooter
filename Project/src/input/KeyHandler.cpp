#include "input\KeyHandler.h"

/// <summary>
/// @brief Default constructor.
/// 
/// Initializes our maps.
/// </summary>
KeyHandler::KeyHandler()
	: m_keyMap()
	, m_prevKeyMap()
{
}

/// <summary>
/// @brief Default destructor.
/// 
/// Removes members off the stack.
/// </summary>
KeyHandler::~KeyHandler()
{
}

/// <summary>
/// @brief Updates key pressed status.
/// 
/// Assigns a value of true or false to the specified key. 
/// </summary>
/// <param name="key">An SFML key</param>
/// <param name="isPressed">true if key pressed (false otherwise)</param>
void KeyHandler::updateKey(const sf::Keyboard::Key & key, const bool & isPressed)
{
	KeyMap::const_iterator citt = m_keyMap.find(key);
	if (citt != m_keyMap.end())
	{
		m_prevKeyMap[key] = m_keyMap[key];
	}
	else
	{
		m_prevKeyMap[key] = !isPressed;
	}
	m_keyMap[key] = isPressed;
}

/// <summary>
/// @brief Checks if a specific key was pressed.
/// 
/// Searches the map to check if the specified key was pressed. 
/// </summary>
/// <param name="key">An SFML key</param>
/// <returns>true if specified key was pressed, false otherwise</returns>
bool KeyHandler::isPressed(const sf::Keyboard::Key & key) const
{
	KeyMap::const_iterator citt = m_keyMap.find(key);
	return (citt != m_keyMap.end() && citt->second);
}

/// <summary>
/// @brief Checks if a specific key was pressed in the previous frame.
/// 
/// Searches the map to check if the specified key was pressed. 
/// </summary>
/// <param name="key">An SFML key</param>
/// <returns>true if specified key was pressed, false otherwise</returns>
bool KeyHandler::isPrevPressed(const sf::Keyboard::Key & key) const
{
	KeyMap::const_iterator citt = m_keyMap.find(key);
	return (citt != m_keyMap.end() && citt->second);
}
