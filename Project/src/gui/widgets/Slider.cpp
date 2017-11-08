#include "gui\widgets\Slider.h"

const sf::IntRect gui::Slider::s_TEXT_RECT_EMPTY = sf::IntRect(0, 0, 246, 36);
const sf::IntRect gui::Slider::s_TEXT_RECT_FILL = sf::IntRect(0, 46, 246, 36);
const sf::IntRect gui::Slider::s_TEXT_RECT_SQUARE = sf::IntRect(0, 92, 48, 48);

/// <summary>
/// @brief The constructor of the slider.
/// 
/// 
/// </summary>
/// <param name="texture">texture sheet</param>
/// <param name="emptyTextRect">empty texture rectangle</param>
/// <param name="filledTextRect">filled texture rectangle</param>
/// <param name="squareTextRect">the moving square on the slider texture rectangle</param>
/// <param name="font">the font of label</param>
/// <param name="name">name of slider</param>
/// <param name="fontSize">size of font</param>
/// <param name="position">slider name position</param>
/// <param name="sliderWidth">width of slider in pixels</param>
/// <param name="sliderHeight">height of slider in pixels</param>
/// <param name="minValue">mimimum value</param>
/// <param name="maxValue">maximum value</param>
/// <param name="currentValue">current value of slider</param>
gui::Slider::Slider(	std::shared_ptr<sf::Texture> texture
				,sf::IntRect emptyTextRect
				,sf::IntRect filledTextRect
				,sf::IntRect squareTextRect
				,std::shared_ptr<sf::Font> font
				,sf::String name
				,unsigned int fontSize
				,sf::Vector2f position
				,float sliderWidth
				,float sliderHeight
				,float minValue
				,float maxValue 
				,float& currentValue)
	: m_leftLabel(std::make_unique<Label>(std::to_string(static_cast<int>(minValue)), fontSize, position, font))
	, m_rightLabel(std::make_unique<Label>(std::to_string(static_cast<int>(maxValue)), fontSize, position, font))
	, m_bottomLabel(std::make_unique<Label>(std::to_string(static_cast<int>(currentValue)), fontSize, position, font))
	, m_topLabel(std::make_unique<Label>(name, fontSize, position, font))
	, m_LABEL_OFFSET(30.0f)
	, m_jump(0.0f)
	, m_moved(false)
	, m_timer(0.0f)
	, m_min(static_cast<int>(minValue))
	, m_max(static_cast<int>(maxValue))
	, m_current(currentValue)
	, m_valueJump(0)
	, m_highlightAlpha(255.0f)
	, m_fadeOut(true)
	, m_emptyTextRect(emptyTextRect)
	, m_filledTextRect(filledTextRect)
	, m_squareTextRect(squareTextRect)
{
	m_current = std::roundf(m_current);

	if (m_current < minValue)
	{
		m_current = minValue;
	}
	else if (m_current > maxValue)
	{
		m_current = maxValue;
	}
	m_bottomLabel->setText(std::to_string(static_cast<int>(m_current)));

	//set texture of empty section
	m_sliderBarEmpty.setTexture(&(*texture), true);
	//set texture rectangle of empty section
	m_sliderBarEmpty.setTextureRect(m_emptyTextRect);
	//set texture of filled section
	m_sliderBarFill.setTexture(&(*texture), true);
	//set texture rectangle of filled section
	m_sliderBarFill.setTextureRect(m_filledTextRect);
	//set texture of square section
	m_slider.setTexture(&(*texture), true);
	//set texture rectangle of square
	m_slider.setTextureRect(m_squareTextRect);

	//calculating offsets on slider
	m_jump = sliderWidth / 10;
	//calculate jumping in value
	m_valueJump = static_cast<int>((m_max - minValue) / 10);
	
	//setting up empty slider bar
	m_sliderBarEmpty.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	m_sliderBarEmpty.setOrigin(sf::Vector2f(m_sliderBarEmpty.getLocalBounds().width / 2, m_sliderBarEmpty.getLocalBounds().height / 2));
	m_sliderBarEmpty.setPosition(sf::Vector2f(m_topLabel->getPosition().x, m_topLabel->getPosition().y));


	//set up slider
	m_slider.setSize(sf::Vector2f(sliderHeight + 5.0f, sliderHeight + 5.0f));
	m_slider.setOrigin(m_slider.getLocalBounds().width / 2, m_slider.getLocalBounds().height / 2);
	m_slider.setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x - (sliderWidth / 2), m_sliderBarEmpty.getPosition().y));

	//setting up the filled slider bar
	m_sliderBarFill.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	m_sliderBarFill.setPosition(sf::Vector2f(m_topLabel->getPosition().x, m_topLabel->getPosition().y));
	m_sliderBarFill.setSize(sf::Vector2f(m_slider.getPosition().x - m_sliderBarFill.getPosition().x, sliderHeight));
	

	//set up highlight rectangle
	m_highlightRectangle.setSize(m_slider.getSize());
	m_highlightRectangle.setFillColor(sf::Color(255u, 255u, 0u, static_cast<unsigned int>(m_highlightAlpha)));
	m_highlightRectangle.setOrigin(m_slider.getOrigin());
	m_highlightRectangle.setPosition(m_slider.getPosition());
	m_highlightRectangle.setScale(1.2f, 1.2f);

	m_bottomLabel->setPosition(sf::Vector2f(m_slider.getPosition().x - (m_bottomLabel->getSize().x / 2),											//equal to the moving circle - half text width
											m_sliderBarEmpty.getPosition().y + (m_bottomLabel->getSize().y / 2) + m_LABEL_OFFSET));					//slider pos.y + label height /2 + Label offset

	m_leftLabel->setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x - (sliderWidth / 2) - (m_leftLabel->getSize().x / 2) - m_LABEL_OFFSET,	//slider centre.x - slider width /2 - label width / 2 - offset
										  m_sliderBarEmpty.getPosition().y - m_leftLabel->getSize().y / 2));											//slider pos.y - label height / 2

	m_rightLabel->setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x + (sliderWidth / 2) + (m_rightLabel->getSize().x / 2) + m_LABEL_OFFSET,	//slider centre.x + slider width /2 + label width / 2 + offset
										  m_sliderBarEmpty.getPosition().y - m_rightLabel->getSize().y / 2));										//slider pos.y - label height / 2

	m_topLabel->setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x,																			//slider centre.x
										 m_sliderBarEmpty.getPosition().y - m_topLabel->getSize().y / 2 - m_LABEL_OFFSET));							//slider pos.y - label height / 2 - slider height - label offset


	float tempCurrent = static_cast<float>(m_min); //temporary value set to min value (in order to be able to increase it)

	//a while loop that sets up the slider to be on the current value
	while (tempCurrent < m_current)
	{
		tempCurrent += m_valueJump;
		m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x + m_jump, m_slider.getPosition().y)); //new position is incremented by jump
		m_bottomLabel->setPosition(sf::Vector2f(m_slider.getPosition().x, m_bottomLabel->getPosition().y)); //make label follow slider
		m_highlightRectangle.setPosition(m_slider.getPosition());
		m_bottomLabel->setOrigin();
	}
}

/// <summary>
/// @brief Destructor.
/// 
/// 
/// </summary>
	gui::Slider::~Slider()
{
}

/// <summary>
/// @brief Updating the slider.
/// 
/// 
/// </summary>
/// <param name="dt">time between frames</param>
void gui::Slider::update(const float & dt)
{
	switch (m_currentState)
	{
	case Slider::SliderState::INACTIVE:
		break;
	case Slider::SliderState::ACTIVE:
		m_slider.setScale(1.0f, 1.0f);
		m_highlightRectangle.setScale(1.0f, 1.0f);
		break;
	case Slider::SliderState::HOVERED:
		m_timer += dt; //add time

		if (m_timer > 0.2 && m_moved == true) //if timer is larger than 0.5 and the slider was moved then set moved to false
		{
			m_moved = false;
		}
		//fade the highlight rectangle
		fading();
		m_highlightRectangle.setFillColor(sf::Color(255u, 255u, 0u, static_cast<sf::Uint8>(m_highlightAlpha)));
		m_slider.setScale(1.2f, 1.2f);
		m_highlightRectangle.setScale(1.4f, 1.4f);
		break;
	default:
		break;
	}

}

/// <summary>
/// @brief Draw the labels and slider.
/// 
/// 
/// </summary>
/// <param name="window">window target of all draw calls</param>
void gui::Slider::draw(Window & window) const
{
	m_leftLabel->draw(window);
	m_rightLabel->draw(window);
	window.draw(m_sliderBarEmpty);
	window.draw(m_sliderBarFill);
	if (m_currentState == SliderState::HOVERED) //highlight only when hovering
	{
		m_bottomLabel->draw(window);
		window.draw(m_highlightRectangle);
	}
	window.draw(m_slider);
	m_topLabel->draw(window);
}


/// <summary>
/// @brief An overriden draw function draws the slider to the render target.
/// 
/// 
/// </summary>
/// <param name="renderTarget">defines the target for rendering</param>
/// <param name="renderState">defines the transformations that are applied to the renderer</param>
void gui::Slider::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const
{
	m_leftLabel->draw(renderTarget, renderStates);
	m_rightLabel->draw(renderTarget, renderStates);
	renderTarget.draw(m_sliderBarEmpty, renderStates);
	renderTarget.draw(m_sliderBarFill, renderStates);
	if (m_currentState == SliderState::HOVERED) //highlight only when hovering
	{
		m_bottomLabel->draw(renderTarget, renderStates);
		renderTarget.draw(m_highlightRectangle, renderStates);
	}
	renderTarget.draw(m_slider, renderStates);
	m_topLabel->draw(renderTarget, renderStates);
}

/// <summary>
/// @brief Gives slider focus.
/// 
/// This method will give focus to this object 
/// causing its state to change to hovered
/// </summary>
void gui::Slider::getFocus()
{
	m_currentState = SliderState::HOVERED;
}

/// <summary>
/// @brief Removes slider focus.
/// 
/// This method will lose focus from this object
/// causing its state to change to active
/// </summary>
void gui::Slider::loseFocus()
{
	m_currentState = SliderState::ACTIVE;
}

/// <summary>
/// @brief Controlls rectangle transparency.
/// 
/// This is the method that will
/// make the transparency go up and down
/// </summary>
void gui::Slider::fading()
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
/// @brief Contains slider input.
/// 
/// check if this widget should process input
/// </summary>
/// <param name="controller">reference to controller, that is checked for input</param>
/// <param name="keyhandler">reference to key handler, that is checked for input</param>
/// <returns></returns>
bool gui::Slider::processInput(Controller & controller, KeyHandler & keyhandler)
{
	if(m_currentState == SliderState::HOVERED)
	{
		if (
			(controller.m_currentState.m_dpadRight 
				|| controller.m_currentState.m_lTS.x > 50
				|| keyhandler.isPressed(sf::Keyboard::Key::Right)
				|| keyhandler.isPressed(sf::Keyboard::Key::D)
				)
			&& !m_moved
			) //if key pressed and slider hasnt moved yet
		{
			moveRight();
		}
		if (
			(controller.m_currentState.m_dpadLeft 
				|| controller.m_currentState.m_lTS.x < -50
				|| keyhandler.isPressed(sf::Keyboard::Key::Left)
				|| keyhandler.isPressed(sf::Keyboard::Key::A))
			&& !m_moved
			) //if key pressed and slider not moved yet
		{
			moveLeft();
		}
	}
	return true;
}

/// <summary>
/// @brief Sets position of the slider.
/// 
/// 
/// </summary>
/// <param name="position">new position</param>
void gui::Slider::setPosition(sf::Vector2f position)
{
	m_sliderBarEmpty.setPosition(position);
	m_slider.setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x - (m_sliderBarEmpty.getLocalBounds().width / 2), m_sliderBarEmpty.getPosition().y));

	float tempCurrent = static_cast<float>(m_min); //temporary value set to min value (in order to be able to increase it)
	//a while loop that sets up the slider to be on the current value
	while (tempCurrent < m_current)
	{
		tempCurrent += m_valueJump;
		m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x + m_jump, m_slider.getPosition().y)); //new position is incremented by jump
		m_highlightRectangle.setPosition(m_slider.getPosition());
		m_bottomLabel->setPosition(sf::Vector2f(m_slider.getPosition().x, m_bottomLabel->getPosition().y)); //make label follow slider
		m_bottomLabel->setOrigin();
	}
	//filled slider bar
	m_sliderBarFill.setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x - (m_sliderBarEmpty.getSize().x / 2), m_sliderBarEmpty.getPosition().y - (m_sliderBarEmpty.getSize().y / 2)));
	m_sliderBarFill.setSize(sf::Vector2f(m_slider.getPosition().x - m_sliderBarFill.getPosition().x, m_sliderBarFill.getSize().y));

	m_bottomLabel->setPosition(sf::Vector2f(m_slider.getPosition().x,																			//equal to the moving circle - half text width
											m_sliderBarEmpty.getPosition().y + (m_bottomLabel->getSize().y / 2) + m_LABEL_OFFSET));														//slider pos.y + label height /2 + Label offset

	m_leftLabel->setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x - (m_sliderBarEmpty.getLocalBounds().width / 2) - (m_leftLabel->getSize().x / 2) - m_LABEL_OFFSET,				//slider centre.x - slider width /2 - label width / 2 - offset
										  m_sliderBarEmpty.getPosition().y - m_leftLabel->getSize().y / 2));																			//slider pos.y - label height / 2

	m_rightLabel->setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x + (m_sliderBarEmpty.getLocalBounds().width / 2) + (m_rightLabel->getSize().x / 2) + m_LABEL_OFFSET,	//slider centre.x + slider width /2 + label width / 2 + offset
										   m_sliderBarEmpty.getPosition().y - m_rightLabel->getSize().y / 2));																//slider pos.y - label height / 2

	m_topLabel->setPosition(sf::Vector2f(m_sliderBarEmpty.getPosition().x,																									//slider centre.x
										 m_sliderBarEmpty.getPosition().y - m_topLabel->getSize().y / 2 - m_LABEL_OFFSET));			//slider pos.y - label height / 2 - slider height - label offset
	m_highlightRectangle.setPosition(m_slider.getPosition());
}

/// <summary>
/// @brief Gets slider position.
/// 
/// Return the centre position of the slider bar
/// </summary>
/// <returns>center position of slider</returns>
sf::Vector2f gui::Slider::getPosition()
{
	return m_sliderBarEmpty.getPosition();
}

/// <summary>
/// @brief Moves slider right.
/// 
/// This method will move the the slider one jump to the right
/// </summary>
void gui::Slider::moveRight()
{
	if (m_slider.getPosition().x + m_jump <= m_sliderBarEmpty.getPosition().x + (m_sliderBarEmpty.getLocalBounds().width / 2)) //check if next step out of bounds if not move it
	{
		m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x + m_jump, m_slider.getPosition().y)); //new position is incremented by jump
		m_moved = true; //set move to true
		m_timer = 0; //timer back to 0
		m_bottomLabel->setPosition(sf::Vector2f(m_slider.getPosition().x , m_bottomLabel->getPosition().y)); //make label follow slider
		m_bottomLabel->setText(std::to_string(static_cast<int>(m_current + m_valueJump))); //set new text
		m_current += static_cast<float>(m_valueJump); //increment the current value by jump
		m_highlightRectangle.setPosition(m_slider.getPosition());
		m_bottomLabel->setOrigin();
		m_sliderBarFill.setSize(sf::Vector2f(m_slider.getPosition().x - m_sliderBarFill.getPosition().x, m_sliderBarFill.getSize().y));
	}
}

/// <summary>
/// @brief Moves slider left.
/// 
/// This method will move the slider one step to the left
/// </summary>
void gui::Slider::moveLeft()
{
	if (m_slider.getPosition().x - m_jump >= m_sliderBarEmpty.getPosition().x - (m_sliderBarEmpty.getLocalBounds().width / 2)) //check if step will get out of bounds
	{
		m_slider.setPosition(sf::Vector2f(m_slider.getPosition().x - m_jump, m_slider.getPosition().y)); //adjust to new position
		m_moved = true; //set moved to true
		m_timer = 0; //timer set to 0
		m_bottomLabel->setPosition(sf::Vector2f(m_slider.getPosition().x, m_bottomLabel->getPosition().y)); //make label follow slider
		m_bottomLabel->setText(std::to_string(static_cast<int>(m_current - m_valueJump))); //update the label text
		m_current -= static_cast<float>(m_valueJump); //decrement the current value by jump
		m_highlightRectangle.setPosition(m_slider.getPosition());
		m_bottomLabel->setOrigin();
		m_sliderBarFill.setSize(sf::Vector2f(m_slider.getPosition().x - m_sliderBarFill.getPosition().x, m_sliderBarFill.getSize().y));
	}
}
