#ifndef BUTTON_H
#define BUTTON_H

#include "gui\widgets\Label.h"
#include <iostream>

/// <summary>
/// @author Sebastian Kruzel
/// @version 1.0
/// @brief Button class
/// 
/// 
/// </summary>
class Button : public Label
{
public:
	//The different possible button states
	enum class ButtonState{ INACTIVE, ACTIVE, HOVERED, PRESSED };

	//constructor
	Button(std::function<void()> function, sf::String message, sf::Vector2f position, sf::Font & font, unsigned int fontSize, std::shared_ptr<sf::Texture> texture, sf::IntRect leftTextRect, sf::IntRect middleTextRect, sf::IntRect rightTextRect);

	//draw the button
	void draw(sf::RenderTarget& window, sf::RenderStates states)const override;

	//button update
	void update(float dt) override;

	//get focus method
	void getFocus() override;

	// lose focus method
	void loseFocus() override;

	//method that has alpha go up and down
	void fading();

	//method for processing the xbox controller inputs
	bool processInput(Controller& controller) override;

	//set position
	void setPosition(sf::Vector2f position) override;

	//get position
	sf::Vector2f getPosition() override;

	//deal with scaling rectangles
	void scaleRectangles(float x, float y);

	//sets color of rectangles
	void setRectangleColors(sf::Color color);


	/// texture rectangle for button
	static const sf::IntRect s_TEXT_RECT_LEFT;
	static const sf::IntRect s_TEXT_RECT_MID;
	static const sf::IntRect s_TEXT_RECT_RIGHT;

protected:
	//rectangle representing the middle section of the button
	sf::RectangleShape m_rectangleMiddle;

	//rectangle representing the left edge of the button
	sf::RectangleShape m_rectangleLeft;

	//rectangle representing the right edge of the button
	sf::RectangleShape m_rectangleRight;

	//position of the rectangle
	sf::Vector2f m_rectanglePos;

	//a margin size same across all buttons
	const float m_MARGIN_SIZE;

	//Current and previous button states
	ButtonState m_currentButtonState = ButtonState::ACTIVE;

	//Previous button state
	ButtonState m_previousButtonState = ButtonState::ACTIVE;

	//highlight rectangle
	sf::RectangleShape m_highlightRectangle;

	//alpha of the highlight rectangle
	float m_highlightAlpha;

	//check if alpha to go down
	bool m_fadeOut;

	// pointer to function that is called when button is pressed
	std::function<void()> m_function;
  
	//texture of the button
	sf::Texture m_texture;

	//texture rectangle of left edge
	sf::IntRect m_leftTextRect;

	//texture rectangle of middle
	sf::IntRect m_middleTextRect;

	//texture rectangle of right edge
	sf::IntRect m_rightTextRect;

};

#endif // !BUTTON_
