#include "gui\GUI.h"

/// <summary>
/// @brief Constructor of the GUI.
/// 
/// 
/// </summary>
/// <param name="controller">the controller to use</param>
/// <param name="checkboxTexture">texture to use for the checkbox</param>
GUI::GUI(std::shared_ptr<Controller> controller, bool stripDraw)
	: m_layoutNr(0)
	, m_controller(controller)
	, m_drawStrip(stripDraw)
{
	if (m_drawStrip) //if we are drawing the strip then set it up
	{
		m_rectangleStrip = sf::RectangleShape(sf::Vector2f(500.0f, 1000.0f));
		m_rectangleStrip.setPosition(400.0f, 300.0f);
		m_rectangleStrip.setFillColor(sf::Color(250u, 50u, 0u, 100u));
		m_rectangleStrip.setOutlineColor(sf::Color(255u, 255u, 0u, 100u));
		m_rectangleStrip.setOutlineThickness(2.0f);
		m_rectangleStrip.setOrigin(sf::Vector2f(m_rectangleStrip.getLocalBounds().width / 2, m_rectangleStrip.getLocalBounds().height / 2));
	}
}

/// <summary>
/// @brief GUI destructor.
/// 
/// 
/// </summary>
GUI::~GUI()
{
}

/// <summary>
/// @brief Update all GUI elements.
/// 
/// 
/// </summary>
/// <param name="dt">represents time between frames</param>
void GUI::update(const float & dt)
{
	if (m_selectedWidget)
	{
		processInput();
		m_selectedWidget->getFocus();
	}

	for (auto & widget : m_widgets)
	{
		widget->processInput(*m_controller);
		widget->update(dt);
	}
}

/// <summary>
/// @brief Draw all widgets to screen.
/// 
/// 
/// </summary>
/// <param name="window">window target of all draw calls</param>
/// <param name="rendState">render states</param>
void GUI::draw(sf::RenderTarget& window, sf::RenderStates rendState) const
{
	if (m_drawStrip)
	{
		window.draw(m_rectangleStrip, rendState);
	}
	for (auto & widget : m_widgets)
	{
		widget->draw(window, rendState);
	}
}

/// <summary>
/// @brief Configures the GUI layout.
/// 
/// if Custom the layout remains unchanged
/// , if StackVertically the layout takes all non label widgets
///    and lays them out in the x-axis-center and evenly stacked on the y-axis
/// , if StripDiagonal the layout takes all non label widgets
///    and lays them out diagonally stacked
/// </summary>
/// <param name="layout">defines the type of layout</param>
/// <param name="windowSize">defines the size of the window.</param>
void GUI::configure(const Layouts & layout, const sf::Vector2u & windowSize)
{
	sf::Vector2f screen = static_cast<sf::Vector2f>(windowSize);
	sf::Vector2f margin(m_screenMargin);
	sf::Vector2f grid(0.0f, 0.0f);
	sf::Vector2f offset(0.0f, 0.0f);
	sf::Vector2f position(0.0f, 0.0f);
	switch (layout)
	{
	case Layouts::StackVertically:
		screen -= (margin * 2.0f);
		grid = sf::Vector2f(0.0f, screen.y / static_cast<float>(m_layoutNr));
		offset = sf::Vector2f(screen.x / 2.0f, grid.y / 2.0f) + margin;
		break;
	case Layouts::StripDiagonal:
		screen -= (margin * 2.0f);
		grid = (screen / static_cast<float>(m_layoutNr));
		offset = (grid / 2.0f) + margin;
		m_rectangleStrip.rotate(-60.0f);
		break;
	case Layouts::Custom:
	default:
		return;
		break;
	}

	int j = 0;
	for (unsigned i = 0u; i < m_widgets.size(); i++)
	{
		std::shared_ptr<Button> pButton;
		std::shared_ptr<Slider> pSlider;
		std::shared_ptr<CheckBox> pCheckBox;

		auto& widget = m_widgets[i];
		position = offset + (grid * static_cast<float>(j));

		if (typeid(*widget) == typeid(Slider))
		{
			pSlider = std::dynamic_pointer_cast<Slider>(widget);
			pSlider->setPosition(position);
			j++;
		}
		else if (typeid(*widget) == typeid(Button))
		{
			pButton = std::dynamic_pointer_cast<Button>(widget);
			pButton->setPosition(position);
			j++;
		}
		else if (typeid(*widget) == typeid(CheckBox))
		{
			pCheckBox = std::dynamic_pointer_cast<CheckBox>(widget);
			pCheckBox->setPosition(position);
			j++;
		}
	}
}

/// <summary>
/// @brief Configures the GUI layout.
/// 
/// if Custom the layout remains unchanged
/// , if StackVertically the layout takes all non label widgets
///    and lays them out in the x-axis-center and evenly stacked on the y-axis
/// , if StripDiagonal the layout takes all non label widgets
///    and lays them out diagonally stacked
/// </summary>
/// <param name="layout">defines the type of layout</param>
/// <param name="windowWidth">defines the width of the window</param>
/// <param name="windowHeight">defines the height of the window</param>
void GUI::configure(const Layouts & layout, const unsigned int & windowWidth, const unsigned int & windowHeight)
{
	configure(layout, sf::Vector2u(windowWidth, windowHeight));
}

/// <summary>
/// @brief Adds in a label.
/// 
/// takes in the parameters needed for a label
/// </summary>
/// <param name="contents">what label displays to the screen</param>
/// <param name="fontSize">size of each character</param>
/// <param name="position">position that label is centered on</param>
/// <param name="font">reference to loaded font needed for label drawing</param>
/// <param name="color">color of label (defaulted to white)</param>
void GUI::addLabel(	sf::String contents
					, unsigned int fontSize
					, sf::Vector2f position
					, sf::Font & font
					, sf::Color color)
{
	m_widgets.push_back(std::make_shared<Label>(contents,fontSize,position,font, color));
}

/// <summary>
/// @brief Adds a button to the GUI.
/// 
/// takes in params for a button
/// </summary>
/// <param name="message">Message to display on the button</param>
/// <param name="position">the centre of the button</param>
/// <param name="font">font to use for label</param>
/// <param name="fontSize">size of the font</param>
/// <param name="texture">texture of the button</param>
/// <param name="leftTextRect">texture rectangle for left edge of the button</param>
/// <param name="middleTextRect">texture rectangle for the middle section of button</param>
/// <param name="rightTextRect">texture rectangle for the right edge of the button</param>
void GUI::addButton(	std::function<void()> function
						, sf::String message
						, sf::Vector2f position
						, sf::Font & font
						, unsigned int fontSize
						, std::shared_ptr<sf::Texture> texture
						, sf::IntRect leftTextRect
						, sf::IntRect middleTextRect
						, sf::IntRect rightTextRect)
{
	m_widgets.push_back(std::make_shared<Button>(function, message, position, font, fontSize, texture, leftTextRect, middleTextRect, rightTextRect));
	m_layoutNr++;
	linkWidget();
}

/// <summary>
/// @brief Add a new slider to the GUI widget vector.
/// 
/// 
/// </summary>
/// <param name="font">the font of labels</param>
/// <param name="name">name of label</param>
/// <param name="fontSize">font size</param>
/// <param name="position">position of name label</param>
/// <param name="startingPos">starting position of slider</param>
/// <param name="sliderWidth">slider width</param>
/// <param name="sliderHeight">slider height</param>
/// <param name="minValue">minimum value</param>
/// <param name="maxValue">maximum value</param>
/// <param name="currentValue">current slider value</param>
void GUI::addSlider(	sf::Font & font
						, sf::String name
						, unsigned int fontSize
						, sf::Vector2f position
						, float sliderWidth
						, float sliderHeight
						, float minValue
						, float maxValue
						, float& currentValue
						, std::shared_ptr<sf::Texture> texture
						, sf::IntRect emptyTextRect
						, sf::IntRect filledTextRect
						, sf::IntRect squareTextRect)
{
	m_widgets.push_back(std::make_shared<Slider>(texture, emptyTextRect, filledTextRect, squareTextRect, font, name, fontSize, position, sliderWidth, sliderHeight, minValue, maxValue, currentValue));
	m_layoutNr++;
	linkWidget();
}

/// <summary>
/// @brief Add a new checkbox to the GUI widget vector.
/// 
/// 
/// </summary>
/// <param name="font">font of label</param>
/// <param name="name">contents of label</param>
/// <param name="position">position of checkbox (center)</param>
/// <param name="scale">scale of the checkbox sprite</param>
/// <param name="onTexture">the on texture</param>
/// <param name="offTexture">the off texture</param>
/// <param name="state">current checkbox state (true = on/ false = off)</param>
/// <param name="charSize">the size of characters</param>
void GUI::addCheckbox(	sf::Font font
						, sf::String name
						, sf::Vector2f position
						, float scale
						, std::shared_ptr<sf::Texture> texture
						, sf::IntRect textRectOn
						, sf::IntRect textRectOff
						, bool & state
						, unsigned charSize)
{
	m_widgets.push_back(std::make_shared<CheckBox>(font, name, position, scale, texture, textRectOn, textRectOff, state, charSize));
	m_layoutNr++;
	linkWidget();
}

/// <summary>
/// @brief Links the passed vector iterator.
/// 
/// 
/// </summary>
void GUI::linkWidget()
{
	// check that there is more than 1 eligible widget in the vector
	if (m_layoutNr > 1)
	{
		// end iterator that goes to the last element of our widgets
		auto endIterator = --m_widgets.end();
		// copied iterator from the last element of our widgets
		auto iterator = endIterator;
		// go back to the 2nd last element of our widgets
		iterator--;

		// check that we dont hit the 1st element and
		//  check that we skip labels in the linking process
		while (iterator != m_widgets.begin() && typeid(*(*iterator)) == typeid(Label))
		{
			// go back to the previous element
			iterator--;
		}
		// set the last element of our widgets to
		//  to have their previous pointer set to the 
		//  previous eligible element of the iterator
		endIterator->get()->m_previous = (*iterator);

		// set the previous eligible element of our widgets to
		//  have their next pointer set to the
		//  last element of our widgets
		iterator->get()->m_next = (*endIterator);
	}
	if (!m_selectedWidget)
	{
		auto lastElement = --m_widgets.end();
		if (typeid(*(*lastElement)) != typeid(Label))
		{
			m_selectedWidget = *lastElement;
		}
	}
}

/// <summary>
/// @brief Process xbox controller navigational input.
/// 
/// 
/// </summary>
void GUI::processInput()
{
	const float& JOYSTICK_THRESHOLD = 50.0f;
	if (
		(m_controller->m_currentState.m_dpadUp && !m_controller->m_previousState.m_dpadUp)
		|| (m_controller->m_currentState.m_lTS.y < -JOYSTICK_THRESHOLD && m_controller->m_previousState.m_lTS.y >= -JOYSTICK_THRESHOLD)
		)
	{
		if (!m_selectedWidget->m_previous.expired())
		{
			m_selectedWidget->loseFocus();
			m_selectedWidget = m_selectedWidget->m_previous.lock();
		}
	}

	if (
		(m_controller->m_currentState.m_dpadDown && !m_controller->m_previousState.m_dpadDown)
		|| (m_controller->m_currentState.m_lTS.y > JOYSTICK_THRESHOLD && m_controller->m_previousState.m_lTS.y <= JOYSTICK_THRESHOLD)
		)
	{
		if (!m_selectedWidget->m_next.expired())
		{
			m_selectedWidget->loseFocus();
			m_selectedWidget = m_selectedWidget->m_next.lock();
		}
	}
}

