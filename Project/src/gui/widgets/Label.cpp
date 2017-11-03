#include "gui\widgets\Label.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
gui::Label::Label()
{
}

/// <summary>
/// @brief Constructor of a label.
/// 
/// </summary>
/// <param name="contents">message to display</param>
/// <param name="font">font</param>
/// <param name="fontSize">char size</param>
/// <param name="position">position on screen</param>
gui::Label::Label(sf::String contents, unsigned int fontSize, sf::Vector2f position, sf::Font & font, sf::Color color)
	: Widget()
	, m_text()
	, m_position(position)
	, m_font(font)
	, m_fontSize(fontSize)
{
	m_font = font;
	m_text.setFont(m_font);
	m_text.setFillColor(color);
	m_text.setString(contents);
	m_text.setPosition(position);
	m_text.setCharacterSize(m_fontSize);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
}

/// <summary>
/// @brief Destructor of the label object.
/// 
/// 
/// </summary>
gui::Label::~Label()
{
}

/// <summary>
/// @brief Set the font of label to passed font.
/// 
/// 
/// </summary>
/// <param name="font">Defines our label's font.</param>
void gui::Label::setFont(sf::Font font)
{
	m_font = font;
}

/// <summary>
/// @brief An overloaded draw function draws the label to screen.
/// 
/// 
/// </summary>
/// <param name="window">Reference to game window.</param>
void gui::Label::draw(Window & window) const
{
	window.draw(m_text);
}

/// <summary>
/// @brief An overriden draw function draws the label to the render target.
/// 
/// 
/// </summary>
/// <param name="renderTarget">defines the target for rendering</param>
/// <param name="renderState">defines the transformations that are applied to the renderer</param>
void gui::Label::draw(sf::RenderTarget & renderTarget, sf::RenderStates renderState) const
{
	renderTarget.draw(m_text, renderState);
}

/// <summary>
/// @brief A getter for size of the label.
/// 
/// 
/// </summary>
/// <returns>Gets the size of the bounds of our label.</returns>
sf::Vector2f gui::Label::getSize()
{
	return sf::Vector2f(m_text.getLocalBounds().width, m_text.getLocalBounds().height);
}

/// <summary>
/// @brief Scales the text.
/// 
/// 
/// </summary>
/// <param name="x">defines the scale along x-axis.</param>
/// <param name="y">defines the scale along y-axis.</param>
void gui::Label::setScale(float x, float y)
{
	m_text.setScale(x, y);
}

/// <summary>
/// @brief Sets the position of the label.
/// 
/// 
/// </summary>
/// <param name="position">defines the new position.</param>
void gui::Label::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_text.setPosition(m_position);
}

/// <summary>
/// @brief Get the position of the label.
/// 
/// 
/// </summary>
/// <returns>The position of the label.</returns>
sf::Vector2f gui::Label::getPosition()
{
	return m_position;
}

/// <summary>
/// @brief Sets the string of text object to passed parameter.
/// 
/// 
/// </summary>
/// <param name="string">defines the string of the text.</param>
void gui::Label::setText(sf::String string)
{
	m_text.setString(string);
}

/// <summary>
/// @brief label is not highlightable.
/// 
/// 
/// </summary>
void gui::Label::getFocus()
{
}

/// <summary>
/// @brief label is not highlightable.
/// </summary>
void gui::Label::loseFocus()
{
}

/// <summary>
/// @brief Check if this widget should process input.
/// 
/// 
/// </summary>
/// <param name="controller">reference to a controller</param>
/// <returns>True if label processes input, False if label does not process input.</returns>
bool gui::Label::processInput(Controller & controller)
{
	return false;
}

/// <summary>
/// @brief Set origin of text about its centre.
/// 
/// 
/// </summary>
void gui::Label::setOrigin()
{
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
}
