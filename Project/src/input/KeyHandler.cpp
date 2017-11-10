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
/// @brief Updates new keys presses to old ones.
/// 
/// 
/// </summary>
void KeyHandler::update()
{
	if (!m_keyMap.empty())
	{
		m_prevKeyMap = m_keyMap;
	}
}

/// <summary>
/// @brief Checks if a specific key is pressed.
/// 
/// Searches the map to check if the specified key is pressed. 
/// </summary>
/// <param name="key">An SFML key</param>
/// <returns>true if specified key is pressed, false otherwise</returns>
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
	KeyMap::const_iterator citt = m_prevKeyMap.find(key);
	return (citt != m_prevKeyMap.end() && citt->second);
}

/// <summary>
/// @brief Checks if any key is pressed.
/// 
/// Searches the map for any key-value pair whose value is true.
/// </summary>
/// <returns>true if any value in our map is true, false if all values in our map are false.</returns>
bool KeyHandler::isAnyPressed() const
{
	for (auto itt = m_keyMap.begin(), end = m_keyMap.end(); itt != end; ++itt)
	{
		if (itt->second)
		{
			return true;
		}
	}
	return false;
}
