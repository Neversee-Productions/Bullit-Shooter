#include "gui\widgets\CheckBox.h"

const sf::IntRect gui::CheckBox::s_TEXT_RECT_ON = sf::IntRect(0, 0, 50, 50);
const sf::IntRect gui::CheckBox::s_TEXT_RECT_OFF = sf::IntRect(50, 0, 50, 50);


/// <summary>
/// @brief The checkbox constructor.
/// 
/// 
/// </summary>
/// <param name="font">font of label</param>
/// <param name="name">contents of label</param>
/// <param name="position">centre of box sprite</param>
/// <param name="scale">scale of sprite</param>
/// <param name="texture">shared pointer to a texture</param>
/// <param name="textRectOn">on texture rectangle</param>
/// <param name="textRectOff">off texture rectangle</param>
/// <param name="state">state of checkbox true=on / false=off</param>
/// <param name="charSize">label text size</param>
gui::CheckBox::CheckBox(std::shared_ptr<sf::Font> font, sf::String name, sf::Vector2f position, float scale, std::shared_ptr<sf::Texture> texture, sf::IntRect textRectOn, sf::IntRect textRectOff, bool & state, unsigned charSize)
	: Label(name, charSize, position, font)
	, m_position(position)
	, m_scale(scale)
	, m_texture(texture)
	, m_highlightAlpha(255.0f)
	, m_fadeOut(true)
	, m_state(state)
	, m_onTextRect(textRectOn)
	, m_offTextRect(textRectOff)
	, m_rectangle()
{
	//set origin of sprite
	m_rectangle.setTexture(&(*m_texture), true);
	if (m_state)
	{
		m_rectangle.setTextureRect(m_onTextRect);
		m_rectangle.setSize(sf::Vector2f(static_cast<float>(m_onTextRect.width), static_cast<float>(m_onTextRect.height)));
	}
	else
	{
		m_rectangle.setTextureRect(m_offTextRect);
		m_rectangle.setSize(sf::Vector2f(static_cast<float>(m_offTextRect.width), static_cast<float>(m_offTextRect.height)));
	}
	m_rectangle.setPosition(m_position);
	m_rectangle.setOrigin(m_rectangle.getGlobalBounds().width / 2.0f, m_rectangle.getGlobalBounds().height / 2.0f);
	//set the position of the label
	Label::setPosition(sf::Vector2f(m_rectangle.getPosition().x - (m_rectangle.getGlobalBounds().width / 2.0f) - (Label::getSize().x / 2.0f) - m_LABEL_OFFSET, m_rectangle.getPosition().y));

	//set up highlight rectangle
	m_highlightRectangle.setSize(sf::Vector2f(m_rectangle.getGlobalBounds().width, m_rectangle.getGlobalBounds().height));
	m_highlightRectangle.setFillColor(sf::Color(255u, 255u, 0u, static_cast<unsigned int>(m_highlightAlpha)));
	m_highlightRectangle.setOrigin(m_rectangle.getOrigin().x, m_rectangle.getOrigin().y - 4); //have to take away 4 due to texture not being a square
	m_highlightRectangle.setPosition(m_rectangle.getPosition());
}

/// <summary>
/// @brief destructor.
/// 
/// 
/// </summary>
gui::CheckBox::~CheckBox()
{
}

/// <summary>
/// @brief Draw the checkbox elements.
/// 
/// 
/// </summary>
/// <param name="window">reference to target window.</param>
void gui::CheckBox::draw(Window & window) const
{
	//draw the label
	Label::draw(window);
	//if hovering draw the highlight rectangle
	if (m_currentState == CheckboxState::HOVERED)
	{
		window.draw(m_highlightRectangle);
	}
	//draw the checkbox sprite
	window.draw(m_rectangle);
}


/// <summary>
/// @brief An overriden draw function draws the checkbox to the render target.
/// 
/// 
/// </summary>
/// <param name="renderTarget">defines the target for rendering</param>
/// <param name="renderState">defines the transformations that are applied to the renderer</param>
void gui::CheckBox::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
	//draw the label
	Label::draw(renderTarget, renderStates);
	//if hovering draw the highlight rectangle
	if (m_currentState == CheckboxState::HOVERED)
	{
		renderTarget.draw(m_highlightRectangle);
	}
	//draw the checkbox sprite
	renderTarget.draw(m_rectangle);
}

/// <summary>
/// @brief Update the checkbox.
/// 
/// 
/// </summary>
/// <param name="dt">reference to delta time</param>
void gui::CheckBox::update(const float & dt)
{
	if (m_currentState == CheckboxState::HOVERED)
	{
		fading();
		m_highlightRectangle.setFillColor(sf::Color(255u, 255u, 0u, static_cast<unsigned int>(m_highlightAlpha)));
	}
}

/// <summary>
/// @brief The method that switches state to hovered.
/// 
/// 
/// </summary>
void gui::CheckBox::getFocus()
{
	m_currentState = CheckboxState::HOVERED;
}

/// <summary>
/// @brief The method that switches state to active.
/// 
/// 
/// </summary>
void gui::CheckBox::loseFocus()
{
	m_currentState = CheckboxState::ACTIVE;
}

/// <summary>
/// @brief This the method will make the transparency go up and down.
/// 
/// 
/// </summary>
void gui::CheckBox::fading()
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
/// @brief Method to process the input
/// 
/// 
/// </summary>
/// <param name="controller">reference to controller, that is checked for input</param>
/// <param name="keyhandler">reference to key handler, that is checked for input</param>
/// <returns>returns true if check box processes input</returns>
bool gui::CheckBox::processInput(Controller & controller, KeyHandler & keyhandler)
{
	//processInput(controller);
	if (m_currentState == CheckboxState::HOVERED)
	{
		if (
#ifdef XBOX360_
			(controller.m_currentState.m_A
				&& !controller.m_previousState.m_A)
			||
#endif
			(keyhandler.isPressed(sf::Keyboard::Key::Return)
				&& !keyhandler.isPrevPressed(sf::Keyboard::Key::Return))
			) //if button pressed while hovered then go to pressed state
		{
			if (m_state == true)
			{
				m_state = false;
				//m_rectangle.setTexture(&(*m_texture), true);
				m_rectangle.setTextureRect(m_offTextRect);
			}
			else
			{
				m_state = true;
				//m_rectangle.setTexture(&(*m_texture), true);
				m_rectangle.setTextureRect(m_onTextRect);
			}
		}
	}
	return true;
}

/// <summary>
/// @brief Method to set position of the checkbox and its elements.
/// 
/// 
/// </summary>
/// <param name="position">new position</param>
void gui::CheckBox::setPosition(sf::Vector2f position)
{
	m_rectangle.setPosition(position);
	Label::setPosition(sf::Vector2f(m_rectangle.getPosition().x - m_rectangle.getGlobalBounds().width - (Label::getSize().x / 2), m_rectangle.getPosition().y - 4));
	m_highlightRectangle.setPosition(m_rectangle.getPosition());
}

/// <summary>
/// @brief returns the centre of the checkbox.
/// 
/// 
/// </summary>
/// <returns>center of rectangle</returns>
sf::Vector2f gui::CheckBox::getPosition()
{
	return m_rectangle.getPosition();
}
