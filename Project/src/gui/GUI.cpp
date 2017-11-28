#include "gui\GUI.h"

/// <summary>
/// @brief Constructor of the GUI.
/// 
/// 
/// </summary>
/// <param name="controller">the controller to use</param>
/// <param name="checkboxTexture">texture to use for the checkbox</param>
gui::GUI::GUI(std::shared_ptr<KeyHandler> keyHandler, std::shared_ptr<Controller> controller, bool stripDraw)
	: m_layoutNr(0)
	, m_keyHandler(keyHandler)
	, m_controller(controller)
	, m_drawStrip(stripDraw)
	, m_widgets()
	, m_rectangleStrip()
	, m_layout(Layouts::Custom)
{
	m_widgets.reserve(5);
	if (m_drawStrip) //if we are drawing the strip then set it up
	{
		const auto & windowSize = static_cast<sf::Vector2f>(App::getViewSize());
		const auto & aspectRatio = windowSize.y / windowSize.x;
		m_rectangleStrip = sf::RectangleShape(sf::Vector2f(windowSize.x * 1.5f, windowSize.y * 0.5f));
		m_rectangleStrip.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
		m_rectangleStrip.setFillColor(sf::Color(0u, 50u, 250u, 100u));
		m_rectangleStrip.setOutlineColor(sf::Color(255u, 255u, 0u, 100u));
		m_rectangleStrip.setOutlineThickness(2.0f);
		const auto & localRect = m_rectangleStrip.getLocalBounds();
		m_rectangleStrip.setOrigin(sf::Vector2f(localRect.width / 2, localRect.height / 2));
		m_rectangleStrip.setRotation(0.0f);
	}
}

/// <summary>
/// @brief GUI destructor.
/// 
/// 
/// </summary>
gui::GUI::~GUI()
{
}

/// <summary>
/// @brief Update all GUI elements.
/// 
/// 
/// </summary>
/// <param name="dt">represents time between frames</param>
void gui::GUI::update(const float & dt)
{
	if (m_selectedWidget)
	{
		processInput();
		m_selectedWidget->getFocus();
	}

	for (auto & widget : m_widgets)
	{
		widget->processInput(*m_controller, *m_keyHandler);
		widget->update(dt);
	}
}

/// <summary>
/// @brief Draw all widgets to screen.
/// 
/// 
/// </summary>
/// <param name="window">window target of all draw calls</param>
void gui::GUI::draw(Window & window) const
{
	if (m_drawStrip)
	{
		window.draw(m_rectangleStrip);
	}
	for (auto & widget : m_widgets)
	{
		widget->draw(window);
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
void gui::GUI::configure(const Layouts & layout, const sf::Vector2u & windowSize)
{
	m_layout = layout;

	const auto & screenSize = static_cast<sf::Vector2f>(windowSize);

	sf::Vector2f screen = screenSize;
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
		m_rectangleStrip.rotate(thor::toDegree(std::atan(screen.y / screen.x)));
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
void gui::GUI::configure(const Layouts & layout, const unsigned int & windowWidth, const unsigned int & windowHeight)
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
void gui::GUI::addLabel(	sf::String contents
					, unsigned int fontSize
					, sf::Vector2f position
					, std::shared_ptr<sf::Font> font
					, sf::Color color)
{
	m_widgets.push_back(std::make_shared<Label>(contents,fontSize,position,font, color));
}

/// <summary>
/// @brief Adds a button to the GUI.
/// 
/// takes in params for a button
/// </summary>
/// <param name="function">callback function called when button is pressed.</param>
/// <param name="message">Message to display on the button</param>
/// <param name="position">the centre of the button</param>
/// <param name="font">font to use for label</param>
/// <param name="fontSize">size of the font</param>
/// <param name="texture">texture of the button</param>
/// <param name="leftTextRect">texture rectangle for left edge of the button</param>
/// <param name="middleTextRect">texture rectangle for the middle section of button</param>
/// <param name="rightTextRect">texture rectangle for the right edge of the button</param>
void gui::GUI::addButton(	std::function<void()> function
						, sf::String message
						, sf::Vector2f position
						, std::shared_ptr<sf::Font> font
						, unsigned int fontSize
						, std::shared_ptr<sf::Texture> texture
						, sf::IntRect leftTextRect
						, sf::IntRect middleTextRect
						, sf::IntRect rightTextRect)
{
	m_widgets.push_back(
		std::make_shared<Button>(
			function
			, message
			, position
			, font
			, fontSize
			, texture
			, leftTextRect
			, middleTextRect
			, rightTextRect)
	);
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
/// <param name="sliderWidth">slider width</param>
/// <param name="sliderHeight">slider height</param>
/// <param name="minValue">minimum value</param>
/// <param name="maxValue">maximum value</param>
/// <param name="currentValue">current slider value</param>
/// <param name="texture">shared pointer to a texture</param>
/// <param name="emptyTextureRect">empty slider texture rectangle</param>
/// <param name="filledTextureRect">filled slider texture rectangle</param>
/// <param name="squareTextRect">texture rectangle of the indicator</param>
void gui::GUI::addSlider(	std::shared_ptr<sf::Font> font
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
	m_widgets.push_back(
		std::make_shared<Slider>(
			texture
			, emptyTextRect
			, filledTextRect
			, squareTextRect
			, font
			, name
			, fontSize
			, position
			, sliderWidth
			, sliderHeight
			, minValue
			, maxValue
			, currentValue)
	);
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
/// <param name="texture">texture of checkbox</param>
/// <param name="textRectOn">the on texture</param>
/// <param name="textRectOff">the off texture</param>
/// <param name="state">current checkbox state (true = on/ false = off)</param>
/// <param name="charSize">the size of characters</param>
void gui::GUI::addCheckbox(	std::shared_ptr<sf::Font> font
						, sf::String name
						, sf::Vector2f position
						, float scale
						, std::shared_ptr<sf::Texture> texture
						, sf::IntRect textRectOn
						, sf::IntRect textRectOff
						, bool & state
						, unsigned charSize)
{
	m_widgets.push_back(
		std::make_shared<CheckBox>(
			font
			, name
			, position
			, scale
			, texture
			, textRectOn
			, textRectOff
			, state
			, charSize)
	);
	m_layoutNr++;
	linkWidget();
}

/// <summary>
/// @brief Links the passed vector iterator.
/// 
/// 
/// </summary>
void gui::GUI::linkWidget()
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
void gui::GUI::processInput()
{
	if (m_controller->isConnected())
	{
		const float& JOYSTICK_THRESHOLD = 50.0f;
		const auto & DPAD_UP = m_controller->m_currentState.m_dpadUp;
		const auto & PREV_DPAD_UP = m_controller->m_previousState.m_dpadUp;
		const auto & DPAD_DOWN = m_controller->m_currentState.m_dpadDown;
		const auto & PREV_DPAD_DOWN = m_controller->m_previousState.m_dpadDown;

		const auto & LTS_Y = m_controller->m_currentState.m_lTS.y;
		const auto & PREV_LTS_Y = m_controller->m_previousState.m_lTS.y;

		if (
			(DPAD_UP && !PREV_DPAD_UP)
			|| (LTS_Y < -JOYSTICK_THRESHOLD && PREV_LTS_Y >= -JOYSTICK_THRESHOLD)
			)
		{
			moveToPrevWidgets();
		}

		if (
			(DPAD_DOWN && !PREV_DPAD_DOWN)
			|| (LTS_Y > JOYSTICK_THRESHOLD && PREV_LTS_Y <= JOYSTICK_THRESHOLD)
			)
		{
			moveToNextWidgets();
		}
	}
	else
	{

		const auto & IS_DIAGONAL = (m_layout == Layouts::StripDiagonal);

		const auto & KEY_UP = m_keyHandler->isPressed(sf::Keyboard::Key::Up);
		const auto & PREV_KEY_UP = m_keyHandler->isPrevPressed(sf::Keyboard::Key::Up);
		const auto & KEY_DOWN = m_keyHandler->isPressed(sf::Keyboard::Key::Down);
		const auto & PREV_KEY_DOWN = m_keyHandler->isPrevPressed(sf::Keyboard::Key::Down);

		const auto & KEY_LEFT = IS_DIAGONAL && m_keyHandler->isPressed(sf::Keyboard::Key::Left);
		const auto & PREV_KEY_LEFT = IS_DIAGONAL && m_keyHandler->isPrevPressed(sf::Keyboard::Key::Left);
		const auto & KEY_RIGHT = IS_DIAGONAL && m_keyHandler->isPressed(sf::Keyboard::Key::Right);
		const auto & PREV_KEY_RIGHT = IS_DIAGONAL && m_keyHandler->isPrevPressed(sf::Keyboard::Key::Right);

		const auto & KEY_W = m_keyHandler->isPressed(sf::Keyboard::Key::W);
		const auto & PREV_KEY_W = m_keyHandler->isPrevPressed(sf::Keyboard::Key::W);
		const auto & KEY_S = m_keyHandler->isPressed(sf::Keyboard::Key::S);
		const auto & PREV_KEY_S = m_keyHandler->isPrevPressed(sf::Keyboard::Key::S);

		const auto & KEY_A = IS_DIAGONAL && m_keyHandler->isPressed(sf::Keyboard::Key::A);
		const auto & PREV_KEY_A = IS_DIAGONAL && m_keyHandler->isPrevPressed(sf::Keyboard::Key::A);
		const auto & KEY_D = IS_DIAGONAL && m_keyHandler->isPressed(sf::Keyboard::Key::D);
		const auto & PREV_KEY_D = IS_DIAGONAL && m_keyHandler->isPrevPressed(sf::Keyboard::Key::D);

		if (
			(KEY_UP && !PREV_KEY_UP)
			|| (KEY_LEFT && !PREV_KEY_LEFT)
			|| (KEY_W && !PREV_KEY_W)
			|| (KEY_A && !PREV_KEY_A)
			)
		{
			moveToPrevWidgets();
		}
		if (
			(KEY_DOWN && !PREV_KEY_DOWN)
			|| (KEY_RIGHT && !PREV_KEY_RIGHT)
			|| (KEY_S && !PREV_KEY_S)
			|| (KEY_D && !PREV_KEY_D)
			)
		{
			moveToNextWidgets();
		}
	}
}

/// <summary>
/// @brief Moves selected widget to the previous one.
/// 
/// 
/// </summary>
void gui::GUI::moveToPrevWidgets()
{
	if (!m_selectedWidget->m_previous.expired())
	{
		m_selectedWidget->loseFocus();
		m_selectedWidget = m_selectedWidget->m_previous.lock();
	}
}

/// <summary>
/// @brief Moves selected widget to the next one.
/// 
/// 
/// </summary>
void gui::GUI::moveToNextWidgets()
{
	if (!m_selectedWidget->m_next.expired())
	{
		m_selectedWidget->loseFocus();
		m_selectedWidget = m_selectedWidget->m_next.lock();
	}
}

