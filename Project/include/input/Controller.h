#ifndef XBOX360CONTROLLER_H
#define XBOX360CONTROLLER_H

#include "SFML\Graphics.hpp"
#include "SFML\Window\Joystick.hpp"

///
/// @brief a struct of game pad state.
/// @author Rafael Plugge
/// 
///
/// 
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
	/// <summary>
	/// @brief Gamepad A button.
	/// 
	/// 
	/// </summary>
	bool m_A;

	/// <summary>
	/// @brief Gamepad B button.
	/// 
	/// 
	/// </summary>
	bool m_B;

	/// <summary>
	/// @brief Gamepad X button.
	/// 
	/// 
	/// </summary>
	bool m_X;

	/// <summary>
	/// @brief Gamepad Y button.
	/// 
	/// 
	/// </summary>
	bool m_Y;

	/// <summary>
	/// @brief Gamepad Left Bumper.
	/// 
	/// 
	/// </summary>
	bool m_LB;

	/// <summary>
	/// @brief Gamepad Right Bumper.
	/// 
	/// 
	/// </summary>
	bool m_RB;

	/// <summary>
	/// @brief Gamepad left thumbstick click.
	/// 
	/// 
	/// </summary>
	bool m_lTSClick;

	/// <summary>
	/// @brief Gamepad right thumbstick click.
	/// 
	/// 
	/// </summary>
	bool m_rTSClick;

	/// <summary>
	/// @brief Gamepad directional pad Up.
	/// 
	/// 
	/// </summary>
	bool m_dpadUp;

	/// <summary>
	/// @brief Gamepad directional pad Down.
	/// 
	/// 
	/// </summary>
	bool m_dpadDown;

	/// <summary>
	/// @brief Gamepad directional pad Left.
	/// 
	/// 
	/// </summary>
	bool m_dpadLeft;

	/// <summary>
	/// @brief Gamepad directional pad right.
	/// 
	/// 
	/// </summary>
	bool m_dpadRight;

	/// <summary>
	/// @brief Gamepad start button.
	/// 
	/// 
	/// </summary>
	bool m_start;

	/// <summary>
	/// @brief Gamepad back button.
	/// 
	/// 
	/// </summary>
	bool m_back;

	/// <summary>
	/// @brief Gamepad Xbox button.
	/// 
	/// 
	/// </summary>
	bool m_xbox;

	/// <summary>
	/// @brief Gamepad right trigger axis value (-100-0).
	/// 
	/// 
	/// </summary>
	float m_rTrigger;

	/// <summary>
	/// @brief Gamepad left trigger axis value (0-100).
	/// 
	/// 
	/// </summary>
	float m_lTrigger;

	/// <summary>
	/// @brief Gamepad right thumbstick.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_rTS;

	/// <summary>
	/// @brief Gamepad left thumbstick.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_lTS;
};
#define XBOX360_
#ifdef XBOX360_

/// <summary>
/// @brief an enumerator to define button mappings.
/// 
/// 
/// </summary>
enum class ButtonMappings
{
	A = 0, /// = 0
	B, /// = 1
	X, /// = 2
	Y, /// = 3
	LeftBumper, /// = 4
	RightBumper, /// = 5
	Back, /// = 6
	Start, /// = 7
	LeftThumbClick, /// = 8
	RightThumbClick, /// = 9
	Trigger = 2, /// Left Trigger = (0)-(100) Right Trigger = (0)-(-100)
	LeftThumbstickX = 0, /// Left Thumbstick = Axis::X(0)
	LeftThumbstickY = 1, /// Left Thumbstick = Axis::Y(1)
	RightThumbstickX = 4, /// Right Thumbstick = Axis::U(4)
	RightThumbstickY = 3, /// Right Thumbstick = Axis::R(3)
	DpadY = 7, /// Dpad Y = Axis::PovY(7)
	DpadX = 6 /// Dpad X = Axis::PovX(6)
};
#else

#endif // XBOX360_


///
/// @brief controller class
/// @author Rafael Plugge
/// 
///
/// 
class Controller
{
public:
	Controller(unsigned int index = 0u);
	~Controller();
	void update();
	bool isConnected();
	bool connect();
	bool isAnyButtonPressed() const;

	/// <summary>
	/// @brief index count for controller.
	/// 
	/// 
	/// </summary>
	unsigned int m_gamepadIndex;

	/// <summary>
	/// @brief current gamepad state.
	/// 
	/// 
	/// </summary>
	GamePadState m_currentState;

	/// <summary>
	/// @brief previous gamepad state.
	/// 
	/// 
	/// </summary>
	GamePadState m_previousState;
private:
	/// <summary>
	/// @brief pete was here ?.
	/// 
	/// 
	/// </summary>
	static const bool PETE_IS_COOL = true;

	bool checkButton(const ButtonMappings &);
	float checkAxis(const ButtonMappings &);

	/// <summary>
	/// @brief Threshold at which the Dpad is considered pressed.
	/// 
	/// 
	/// </summary>
	const int DPAD_THRESHOLD = 50;

	/// <summary>
	/// @brief Threshold at which the Trigger's are considered 0.
	/// 
	/// 
	/// </summary>
	const float TRIGGERS_THRESHOLD = 1.0f;

	/// <summary>
	/// @brief Threshold at which the Thumbsticks are considered 0.
	/// 
	/// 
	/// </summary>
	const float THUMB_THRESHOLD = 30.0f;

	/// <summary>
	/// @brief 4u is the Maximum number of supported controllers.
	/// 
	/// 
	/// </summary>
	const unsigned int MAX_CONTROLLERS = 4u;
};

#endif // !XBOX360CONTROLLER_