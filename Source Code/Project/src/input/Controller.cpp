#include "input\Controller.h"


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// setups member variables and initializes them
/// </summary>
/// <param name="index"> Controller index </param>
Controller::Controller(unsigned int index) :
	m_gamepadIndex(index),
	m_currentState(),
	m_previousState(m_currentState)
{
}

/// <summary>
/// @brief Default destructor.
/// 
/// 
/// deletes all member variables on the stack
/// </summary>
Controller::~Controller()
{
}

/// <summary>
/// @brief Updates the controller's previous and current states.
/// 
/// 
/// If no controller is connected,
/// attempt to reconnect
/// </summary>
void Controller::update()
{
	sf::Joystick::update();
	if (isConnected())
	{
		m_previousState = m_currentState;
#ifdef JOYSTICK_
		m_currentState.m_btnX = this->checkButton(ButtonMappings::btnX);
		m_currentState.m_btnCircle = this->checkButton(ButtonMappings::btnCircle);
		m_currentState.m_btnSquare = this->checkButton(ButtonMappings::btnSquare);
		m_currentState.m_btnTriangle = this->checkButton(ButtonMappings::btnTriangle);
		m_currentState.m_btnTrigger = this->checkButton(ButtonMappings::FireTrigger);
		m_currentState.m_l1 = this->checkButton(ButtonMappings::L1);
		m_currentState.m_flightStick = {
			this->checkAxis(ButtonMappings::FlightStickX),
			this->checkAxis(ButtonMappings::FlightStickY)
		};
		m_currentState.m_flightThruster = this->checkAxis(ButtonMappings::FlightThruster);
#endif // JOYSTICK_
#ifdef XBOX360_
		m_currentState.m_A = checkButton(ButtonMappings::btnX);
		m_currentState.m_B = checkButton(ButtonMappings::btnCircle);
		m_currentState.m_X = checkButton(ButtonMappings::btnSquare);
		m_currentState.m_Y = checkButton(ButtonMappings::btnTriangle);
		m_currentState.m_LB = checkButton(ButtonMappings::LeftBumper);
		m_currentState.m_RB = checkButton(ButtonMappings::RightBumper);
		m_currentState.m_lTSClick = checkButton(ButtonMappings::LeftThumbClick);
		m_currentState.m_rTSClick = checkButton(ButtonMappings::RightThumbClick);
		
		float dpadAxisX = checkAxis(ButtonMappings::DpadX);
		if (dpadAxisX > DPAD_THRESHOLD)
		{
			m_currentState.m_dpadRight = true;
			m_currentState.m_dpadLeft = false;
		}
		else if (dpadAxisX < -DPAD_THRESHOLD)
		{
			
			m_currentState.m_dpadLeft = true;
			m_currentState.m_dpadRight = false;
		}
		else
		{
			m_currentState.m_dpadLeft = false;
			m_currentState.m_dpadRight = false;
		}

		float dpadAxisY = checkAxis(ButtonMappings::DpadY);
		if (dpadAxisY > DPAD_THRESHOLD)
		{
			m_currentState.m_dpadUp = true;
			m_currentState.m_dpadDown = false;
		}
		else if (dpadAxisY < -DPAD_THRESHOLD)
		{
			m_currentState.m_dpadUp = false;
			m_currentState.m_dpadDown = true;
		}
		else
		{
			m_currentState.m_dpadUp = false;
			m_currentState.m_dpadDown = false;
		}

		m_currentState.m_start = checkButton(ButtonMappings::Start);
		m_currentState.m_back = checkButton(ButtonMappings::Back);

		float triggerAxis = checkAxis(ButtonMappings::Trigger);
		if (triggerAxis > TRIGGERS_THRESHOLD)
		{
			m_currentState.m_rTrigger = triggerAxis;
		}
		else if (triggerAxis < -TRIGGERS_THRESHOLD)
		{
			m_currentState.m_lTrigger = -(triggerAxis);
		}
		else
		{
			m_currentState.m_rTrigger = 0.0f;
			m_currentState.m_lTrigger = 0.0f;
		}
		
		float leftThumbAxisX = checkAxis(ButtonMappings::LeftThumbstickX);
		if (leftThumbAxisX > THUMB_THRESHOLD || leftThumbAxisX < -THUMB_THRESHOLD)
		{
			m_currentState.m_lTS.x = leftThumbAxisX;
		}
		else
		{
			m_currentState.m_lTS.x = 0.0f;
		}

		float leftThumbAxisY = checkAxis(ButtonMappings::LeftThumbstickY);
		if (leftThumbAxisY > THUMB_THRESHOLD || leftThumbAxisY < -THUMB_THRESHOLD)
		{
			m_currentState.m_lTS.y = leftThumbAxisY;
		}
		else
		{
			m_currentState.m_lTS.y = 0.0f;
		}

		float rightThumbAxisX = checkAxis(ButtonMappings::RightThumbstickX);
		if (rightThumbAxisX > THUMB_THRESHOLD || rightThumbAxisX < -THUMB_THRESHOLD)
		{
			m_currentState.m_rTS.x = rightThumbAxisX;
		}
		else
		{
			m_currentState.m_rTS.x = 0.0f;
		}

		float rightThumbAxisY = checkAxis(ButtonMappings::RightThumbstickY);
		if (rightThumbAxisY > THUMB_THRESHOLD || rightThumbAxisY < -THUMB_THRESHOLD)
		{
			m_currentState.m_rTS.y = rightThumbAxisY;
		}
		else
		{
			m_currentState.m_rTS.y = 0.0f;
		}
#endif // XBOX360_
	}
	else
	{
		if (!connect())
		{
			m_currentState = GamePadState();
			m_previousState = m_currentState;
		}
	}
}

/// <summary>
/// @brief Checks if the currently indexed controller is still connected.
/// 
/// 
/// </summary>
/// <returns>
/// Returns true if current controller is connected,
/// else false
/// </returns>
bool Controller::isConnected()
{
	return sf::Joystick::isConnected(m_gamepadIndex);
}

/// <summary>
/// @brief Checks each controller slot
///		for a connected controller
///		picks the first one and connects it to this object.
/// 
/// 
/// </summary>
/// <returns>Returns whether or not a controller was detected</returns>
bool Controller::connect()
{
	for (unsigned i = 0u; i < MAX_CONTROLLERS; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			m_gamepadIndex = i;
			return true;
		}
	}
	return false;
}

/// <summary>
/// @brief Checks if any of the button states is true or false.
/// 
/// 
/// </summary>
/// <returns>Returns true if any of the buttons is pressed, else it is false.</returns>
bool Controller::isAnyButtonPressed() const
{
	bool buttonPressed = false;

	if (
#ifdef JOYSTICK_
		m_currentState.m_btnX
		|| m_currentState.m_btnCircle
		|| m_currentState.m_btnSquare
		|| m_currentState.m_btnTriangle
		|| m_currentState.m_btnTrigger
#endif // JOYSTICK_

#ifdef XBOX360_
		m_currentState.m_A
		|| m_currentState.m_B
		|| m_currentState.m_X
		|| m_currentState.m_Y
		|| m_currentState.m_back
		|| m_currentState.m_start
		|| m_currentState.m_xbox
		|| m_currentState.m_LB
		|| m_currentState.m_lTSClick
		|| m_currentState.m_RB
		|| m_currentState.m_rTSClick
#endif
		)
	{
		buttonPressed = true;
	}

	return buttonPressed;

}

/// <summary>
/// @brief Checks if the passed button for the current controller is pressed.
/// 
/// 
/// </summary>
/// <param name="button">Defines the underlying button identifier. @see ButtonMappings</param>
/// <returns>Returns true if the specified button for the current controller is pressed, else false.</returns>
bool Controller::checkButton(const ButtonMappings & button)
{
	return sf::Joystick::isButtonPressed(m_gamepadIndex, static_cast<unsigned int>(button));
}

/// <summary>
/// @brief Checks the specified Axis for the current controller.
/// 
/// 
/// </summary>
/// <param name="button">Defines the underlying button identifier. @see ButtonMappings</param>
/// <returns>Returns the current position of the axis between -100 and 100.</returns>
float Controller::checkAxis(const ButtonMappings & button)
{
	return sf::Joystick::getAxisPosition(m_gamepadIndex, static_cast<sf::Joystick::Axis>(button));
}