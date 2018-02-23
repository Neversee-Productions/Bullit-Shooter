#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include <map>
#include "SFML\Window\Keyboard.hpp"

/// 
/// @brief Manages key input.
/// @author Rafael Plugge
/// 
/// Allows for simultaneous and instantaneous input detection.
/// 
class KeyHandler
{
public:
	KeyHandler();
	~KeyHandler();
	void updateKey(const sf::Keyboard::Key & key, const bool & isPressed);
	void update();
	bool isPressed(const sf::Keyboard::Key & key) const;
	bool isPrevPressed(const sf::Keyboard::Key & key) const;
	bool isAnyPressed() const;

private:
	/// <summary>
	/// @brief Alias for the stl map.
	/// 
	/// 
	/// </summary>
	typedef std::map<sf::Keyboard::Key, bool> KeyMap;

	/// <summary>
	/// @brief Contains keys currently pressed.
	/// 
	/// 
	/// </summary>
	KeyMap m_keyMap;

	/// <summary>
	/// @brief Contains keys pressed in the previous frame.
	/// 
	/// 
	/// </summary>
	KeyMap m_prevKeyMap;

};

#endif // !KEYHANDLER_H