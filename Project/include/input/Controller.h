#ifndef XBOX360CONTROLLER_H
#define XBOX360CONTROLLER_H

#include "SFML\Graphics.hpp"
#include "SFML\Window\Joystick.hpp"

/// <summary>
/// data to store the current state of the controller
/// </summary>
struct GamePadState
{
	GamePadState()
		: m_A(false)
		, m_B(false)
		, m_X(false)
		, m_Y(false)
		, m_LB(false)
		, m_RB(false)
		, m_lTSClick(false)
		, m_rTSClick(false)
		, m_dpadUp(false)
		, m_dpadDown(false)
		, m_dpadLeft(false)
		, m_dpadRight(false)
		, m_start(false)
		, m_back(false)
		, m_xbox(false)
		, m_rTrigger(0.0f)
		, m_lTrigger(0.0f)
		, m_rTS(0.0f, 0.0f)
		, m_lTS(0.0f, 0.0f)
	{}

	bool m_A; // Gamepad A button
	bool m_B; // Gamepad B button
	bool m_X; // Gamepad X button
	bool m_Y; // Gamepad Y button
	bool m_LB; // Gamepad Left Bumper
	bool m_RB; // Gamepad Right Bumper
	bool m_lTSClick; // Gamepad left thumbstick click
	bool m_rTSClick; // Gamepad right thumbstick click
	bool m_dpadUp; // Gamepad directional pad Up
	bool m_dpadDown; // Gamepad directional pad Down
	bool m_dpadLeft; // Gamepad directional pad Left
	bool m_dpadRight; // Gamepad directional pad right
	bool m_start; // Gamepad start button
	bool m_back; // Gamepad back button
	bool m_xbox; // Gamepad Xbox button
	float m_rTrigger; // Gamepad right trigger axis value (-100-0)
	float m_lTrigger; // Gamepad left trigger axis value (0-100)
	sf::Vector2f m_rTS; // Gamepad right thumbstick
	sf::Vector2f m_lTS; // Gamepad left thumbstick
};

/// <summary>
/// Definition for Xbox 360 controller button mappings
/// can be changed to support multiple types of controllers
/// </summary>
#define XBOX360_
#ifdef XBOX360_

enum class ButtonMappings
{
	A = 0, // = 0
	B, // = 1
	X, // = 2
	Y, // = 3
	LeftBumper, // = 4
	RightBumper, // = 5
	Back, // = 6
	Start, // = 7
	LeftThumbClick, // = 8
	RightThumbClick, // = 9
	Trigger = 2, // Left Trigger = (0)-(100) Right Trigger = (0)-(-100)
	LeftThumbstickX = 0, // Left Thumbstick = Axis::X(0)
	LeftThumbstickY = 1, // Left Thumbstick = Axis::Y(1)
	RightThumbstickX = 4, // Right Thumbstick = Axis::U(4)
	RightThumbstickY = 3, // Right Thumbstick = Axis::R(3)
	DpadY = 7, // Dpad Y = Axis::PovY(7)
	DpadX = 6 // Dpad X = Axis::PovX(6)
};
#else

#endif // XBOX360_


/// <summary>
/// Xbox controller class to query current state of controller
/// to mimic the controller states like XNA
/// </summary>
class Controller
{
public:
	Controller(unsigned int index = 0u);
	~Controller();
	void update();
	bool isConnected();
	bool connect();
	bool isAnyButtonPressed() const;

	// index count for controller
	unsigned int m_gamepadIndex;

	// current gamepad state
	GamePadState m_currentState;

	// previous gamepad state
	GamePadState m_previousState;
private:
	// pete was here ?
	static const bool PETE_IS_COOL = true;

	bool checkButton(const ButtonMappings &);
	float checkAxis(const ButtonMappings &);

	// Threshold at which the Dpad is considered pressed
	const int DPAD_THRESHOLD = 50;

	// Threshold at which the Trigger's are considered 0
	const float TRIGGERS_THRESHOLD = 1.0f;

	// Threshold at which the Thumbsticks are considered 0
	const float THUMB_THRESHOLD = 30.0f;

	// 4u is the Maximum number of supported controllers
	const unsigned int MAX_CONTROLLERS = 4u;
};

#endif // !XBOX360CONTROLLER_