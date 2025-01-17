#include "gui\widgets\Button.h"

const sf::IntRect gui::Button::s_TEXT_RECT_LEFT = sf::IntRect(0, 0, 0, 49);
const sf::IntRect gui::Button::s_TEXT_RECT_MID = sf::IntRect(0, 0, 113, 49);
const sf::IntRect gui::Button::s_TEXT_RECT_RIGHT = sf::IntRect(0, 0, 0, 49);


/// <summary>
/// @brief Constructor for a button.
/// 
/// will initialise all needed parameters
/// will create a label
/// </summary>
/// <param name="function">pointer-to-function, is ran when button is pressed</param>
/// <param name="message">string message displayed inside the button</param>
/// <param name="position">position that button is centered on</param>
/// <param name="font">reference to loaded font, needed for labels</param>
/// <param name="fontSize">determines size of each character</param>
/// <param name="texture">shared pointer to loaded button texture</param>
/// <param name="leftTextRect">left side rectangle of button texture</param>
/// <param name="middleTextRect">middle section rectangle of button texture</param>
/// <param name="rightTextRect">right side rectangle of button texture</param>
gui::Button::Button(	std::function<void()> function
				, sf::String message
				, sf::Vector2f position
				, std::shared_ptr<sf::Font> font
				, unsigned int fontSize
				, std::shared_ptr<sf::Texture> texture
				, sf::IntRect leftTextRect
				, sf::IntRect middleTextRect
				, sf::IntRect rightTextRect)

	: Label(message, fontSize, sf::Vector2f(position.x, position.y), font)
	, m_MARGIN_SIZE(20.0f)
	, m_highlightAlpha(255.0f)
	, m_fadeOut(true)
	, m_currentButtonState(ButtonState::ACTIVE)
	, m_function(function)
	, m_leftTextRect(leftTextRect)
	, m_middleTextRect(middleTextRect)
	, m_rightTextRect(rightTextRect)
{
	//rectangle to be offset by margin size
	m_rectanglePos.x = position.x;
	m_rectanglePos.y = position.y;
	//set color of highlight rectangle
	m_highlightRectangle.setFillColor(sf::Color(75u, 184u, 243u, static_cast<sf::Uint8>(m_highlightAlpha)));
	//set position of rectangle
	m_rectangleMiddle.setPosition(m_rectanglePos);
	//set position of highlight rect
	m_highlightRectangle.setPosition(m_rectanglePos);
	//make size of rectangle bigger than label
	m_rectangleMiddle.setSize(sf::Vector2f(getSize().x + (m_MARGIN_SIZE * 2), getSize().y + (m_MARGIN_SIZE * 2)));
	//set origin for button
	m_rectangleMiddle.setOrigin(m_rectangleMiddle.getGlobalBounds().width / 2.0f, m_rectangleMiddle.getGlobalBounds().height / 2.0f);
	//set texture of middle section
	m_rectangleMiddle.setTexture(texture.get(), true);
	//set texture rectangle of middle section
	m_rectangleMiddle.setTextureRect(middleTextRect);

	//set up the left texture rectangle
	m_rectangleLeft.setTexture(texture.get(), true);
	m_rectangleLeft.setTextureRect(leftTextRect);
	m_rectangleLeft.setSize(sf::Vector2f(static_cast<float>(leftTextRect.width), m_rectangleMiddle.getGlobalBounds().height));
	m_rectangleLeft.setOrigin(m_rectangleLeft.getGlobalBounds().width / 2, m_rectangleLeft.getGlobalBounds().height / 2);
	m_rectangleLeft.setPosition(m_rectangleMiddle.getPosition().x - (m_rectangleMiddle.getGlobalBounds().width / 2) - (m_rectangleLeft.getGlobalBounds().width / 2),m_rectangleMiddle.getPosition().y);

	//set up the right texture rectangle
	m_rectangleRight.setTexture(texture.get(), true);
	m_rectangleRight.setTextureRect(rightTextRect);
	m_rectangleRight.setSize(sf::Vector2f(static_cast<float>(rightTextRect.width), m_rectangleMiddle.getGlobalBounds().height));
	m_rectangleRight.setOrigin(m_rectangleRight.getGlobalBounds().width / 2, m_rectangleRight.getGlobalBounds().height / 2);
	m_rectangleRight.setPosition(m_rectangleMiddle.getPosition().x + (m_rectangleMiddle.getGlobalBounds().width / 2) + (m_rectangleRight.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);

	//make highlight rectangle same as button rectangles
	m_highlightRectangle.setSize(sf::Vector2f(m_rectangleMiddle.getSize().x + (m_rectangleLeft.getSize().x * 2), m_rectangleMiddle.getSize().y));
	//set origin of highlight box
	m_highlightRectangle.setOrigin(m_highlightRectangle.getGlobalBounds().width / 2, m_highlightRectangle.getGlobalBounds().height / 2);
	
}

/// <summary>
/// @brief Draws button.
/// 
/// will draw the rectangle and the label
/// </summary>
/// <param name="window">window target of all draw calls</param>
void gui::Button::draw(Window & window) const
{
	if (m_currentButtonState == ButtonState::HOVERED || m_currentButtonState == ButtonState::PRESSED)
	{
		window.draw(m_highlightRectangle);
	}
	window.draw(m_rectangleMiddle);
	window.draw(m_rectangleLeft);
	window.draw(m_rectangleRight);
	Label::draw(window);
}

/// <summary>
/// @brief An overriden draw function draws the button to the render target.
/// 
/// 
/// </summary>
/// <param name="renderTarget">defines the target for rendering</param>
/// <param name="renderState">defines the transformations that are applied to the renderer</param>
void gui::Button::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
	if (m_currentButtonState == ButtonState::HOVERED)
	{
		renderTarget.draw(m_highlightRectangle, renderStates);
	}
	renderTarget.draw(m_rectangleMiddle, renderStates);
	renderTarget.draw(m_rectangleLeft, renderStates);
	renderTarget.draw(m_rectangleRight, renderStates);
	Label::draw(renderTarget, renderStates);
}

/// <summary>
/// @brief Main update logic.
/// 
/// Deals with different btn states
/// </summary>
/// <param name="dt">time between updates</param>
void gui::Button::update(const float & dt)
{
	switch (m_currentButtonState)
	{
	case Button::ButtonState::INACTIVE:
		m_rectangleMiddle.setFillColor(sf::Color::Cyan);
		break;
	case Button::ButtonState::ACTIVE:
		setRectangleColors(sf::Color(255u, 255u, 255u, 255u));
		scaleRectangles(1.0f, 1.0f);
		m_highlightAlpha = 255.0f;
		break;
	case Button::ButtonState::HOVERED:
		//setRectangleColors(sf::Color(130u, 130u, 255u, 255u));
		//scaleRectangles(1.2f, 1.2f);
		fading();
		//m_highlightRectangle.setScale(1.22f, 1.3f);
		m_highlightRectangle.setFillColor(sf::Color(75u, 184u, 243u, static_cast<sf::Uint8>(m_highlightAlpha)));
		break;
	case Button::ButtonState::PRESSED:
		//setRectangleColors(sf::Color::Red);
		//scaleRectangles(1.0f, 1.0f);
		m_highlightRectangle.setFillColor(sf::Color(255u, 0u, 0u, 255u));
		m_rectangleLeft.setPosition(m_rectangleMiddle.getPosition().x - (m_rectangleMiddle.getGlobalBounds().width / 2) - (m_rectangleLeft.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);
		m_rectangleRight.setPosition(m_rectangleMiddle.getPosition().x + (m_rectangleMiddle.getGlobalBounds().width / 2) + (m_rectangleRight.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);
		break;
	default:
		break;
	}
	if (m_previousButtonState != m_currentButtonState) //if previous is different make it same as current
	{
		m_previousButtonState = m_currentButtonState;
	}
}

/// <summary>
/// @brief gives button focus.
/// 
/// This method will give focus to this object
/// causing its state to change to hovered
/// </summary>
void gui::Button::getFocus()
{
	m_currentButtonState = ButtonState::HOVERED;
}

/// <summary>
/// @brief removes button focus.
/// 
/// This method will lose focus from this object
/// causing its state to change to active
/// </summary>
void gui::Button::loseFocus()
{
	m_currentButtonState = ButtonState::ACTIVE;
}

/// <summary>
/// @brief Controlls highlighter's transparency.
/// 
/// This is the method that will
/// make the transparency go up and down
/// </summary>
void gui::Button::fading()
{
	//The flashing exit text
	if (m_fadeOut) //if alpha to be increased
	{
		m_highlightAlpha += 5;
		if (m_highlightAlpha > 249) //if alpha above 252 set increase to false (dont let it go above 255)
		{
			m_fadeOut = false;
		}
	}
	else //decrease alpha until below 50
	{
		m_highlightAlpha -= 5;
		if (m_highlightAlpha < 50)
		{
			m_fadeOut = true;
		}
	}
}

/// <summary>
/// @brief Proccesses button input.
/// 
/// if button is pressed, change state to pressed
/// and call pointer-to-function
/// </summary>
/// <param name="controller">reference to controller, that is checked for input</param>
/// <param name="keyhandler">reference to key handler, that is checked for input</param>
/// <returns>returns true since button processes input</returns>
bool gui::Button::processInput(Controller & controller, KeyHandler & keyhandler)
{
	//processInput(controller);
	if (m_currentButtonState == ButtonState::HOVERED)
	{
		if (
#ifdef XBOX360_
			controller.m_currentState.m_A //if button pressed while hovered then go to pressed state
			|| 
#endif
#ifdef JOYSTICK_
			(controller.m_currentState.m_btnTrigger && !controller.m_previousState.m_btnTrigger)
			||
#endif
			(keyhandler.isPressed(sf::Keyboard::Key::Return) && !keyhandler.isPrevPressed(sf::Keyboard::Return))
			)
		{
			m_currentButtonState = ButtonState::PRESSED;
			m_function();
		}
	}
	return true;
}

/// <summary>
/// @brief Sets the position of the button.
/// 
/// 
/// </summary>
/// <param name="position">defines new position</param>
void gui::Button::setPosition(sf::Vector2f position)
{
	//set label position
	m_position = sf::Vector2f(position.x, position.y - 5.0f);
	m_text.setPosition(m_position);
	//rectangles position
	m_rectanglePos.x = position.x;
	m_rectanglePos.y = position.y;

	//set position of rectangle
	m_rectangleMiddle.setPosition(m_rectanglePos);
	//set position of highlight rect
	m_highlightRectangle.setPosition(m_rectanglePos);
	m_rectangleLeft.setPosition(m_rectangleMiddle.getPosition().x - (m_rectangleMiddle.getGlobalBounds().width / 2) - (m_rectangleLeft.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);
	m_rectangleRight.setPosition(m_rectangleMiddle.getPosition().x + (m_rectangleMiddle.getGlobalBounds().width / 2) + (m_rectangleRight.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);
}

/// <summary>
/// @brief Return position of button.
/// 
/// 
/// </summary>
/// <returns>current position of button</returns>
sf::Vector2f gui::Button::getPosition()
{
	return m_rectanglePos;
}

/// <summary>
/// @brief Scales button rectangles.
/// 
/// Scales the middle left and right rectangles and sets the position of left and right with new scale
/// </summary>
/// <param name="x">defines new scale on the x-axis</param>
/// <param name="y">defines new scale on the y-axis</param>
void gui::Button::scaleRectangles(float x, float y)
{
	m_rectangleLeft.setScale(1.0f, y);
	m_rectangleMiddle.setScale(x, y);
	m_rectangleRight.setScale(1.0f, y);
	setScale(x, y);
	m_rectangleLeft.setPosition(m_rectangleMiddle.getPosition().x - (m_rectangleMiddle.getGlobalBounds().width / 2) - (m_rectangleLeft.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);
	m_rectangleRight.setPosition(m_rectangleMiddle.getPosition().x + (m_rectangleMiddle.getGlobalBounds().width / 2) + (m_rectangleRight.getGlobalBounds().width / 2), m_rectangleMiddle.getPosition().y);
}

/// <summary>
/// @brief Changes the color of the 3 rectangles.
/// 
/// 
/// </summary>
/// <param name="color">defines new color</param>
void gui::Button::setRectangleColors(sf::Color color)
{
	m_rectangleMiddle.setFillColor(color);
	m_rectangleLeft.setFillColor(color);
	m_rectangleRight.setFillColor(color);
}
