#include "input\Controller.h"


/// <summary>
/// Default constructor,
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
/// Default destructor,
/// deletes all member variables on the stack
/// </summary>
Controller::~Controller()
{
}

/// <summary>
/// Updates the controller's previous and current states,
/// if no controller is connected,
/// attempt to reconnect
/// </summary>
void Controller::update()
{
	sf::Joystick::update();
	if (isConnected())
	{
		m_previousState = m_currentState;

		m_currentState.m_A = checkButton(ButtonMappings::A);
		m_currentState.m_B = checkButton(ButtonMappings::B);
		m_currentState.m_X = checkButton(ButtonMappings::X);
		m_currentState.m_Y = checkButton(ButtonMappings::Y);
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
/// Checks if the currently indexed controller is still connected
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
/// Checks each controller slot
/// for a connected controller
/// picks the first one and connects it to this object
/// </summary>
/// <returns> Returns whether or not a controller was detected </returns>
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

bool Controller::isAnyButtonPressed() const
{
	bool buttonPressed = false;

	if (
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
		)
	{
		buttonPressed = true;
	}

	return buttonPressed;

}

bool Controller::checkButton(const ButtonMappings & button)
{
	return sf::Joystick::isButtonPressed(m_gamepadIndex, static_cast<unsigned int>(button));
}

float Controller::checkAxis(const ButtonMappings & button)
{
	return sf::Joystick::getAxisPosition(m_gamepadIndex, static_cast<sf::Joystick::Axis>(button));
}