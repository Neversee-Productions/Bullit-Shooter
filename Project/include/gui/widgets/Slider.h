#ifndef SLIDER_H
#define SLIDER_H

#include "gui\widgets\Label.h"
#include <memory>

/// <summary>
/// @author Sebastian Kruzel
/// @version 1.0
/// @brief Slider class.
/// 
/// A slider GUI element 
/// can be used to go through different iterations of values
/// </summary>
class Slider : public Widget
{
public:
	//The different possible slider states
	enum class SliderState { INACTIVE, ACTIVE, HOVERED};
	Slider(
		std::shared_ptr<sf::Texture> texture,			//shared pointer to the slider texture
		sf::IntRect emptyTextRect,						//texture rectangle for the empty rectangle
		sf::IntRect filledTextRect,						//texture rectangle for the filled rectangle
		sf::IntRect squareTextRect,						//texture rectangle for the slider
		sf::Font & font,					//font of label
		sf::String name,					//name of the slider (text of top label)
		unsigned int fontSize,				//font size of labels
		sf::Vector2f position,				//position of slider
		float sliderWidth,					//width of slider in pixels
		float sliderHeight,					//height of slider in pixels
		float minValue,						//minimum value of slider
		float maxValue,						//maximum value of the slider
		float& currentValue					//the value at which the slider starts
	);

	//destructor
	~Slider();

	//update method for slider
	void update(float dt) override;

	//draw method
	void draw(sf::RenderTarget& window, sf::RenderStates states)const override;

	//get focus method
	void getFocus() override;

	// lose focus method
	void loseFocus() override;

	//method that has alpha go up and down
	void fading();

	//method for processing the xbox controller inputs
	bool processInput(Controller& controller) override;

	//set position
	void setPosition(sf::Vector2f position);

	//get position
	sf::Vector2f getPosition();

	//move the slider right
	void moveRight();

	//move the slider left
	void moveLeft();

	//texture rectangle for button
	static const sf::IntRect s_TEXT_RECT_EMPTY;
	static const sf::IntRect s_TEXT_RECT_FILL;
	static const sf::IntRect s_TEXT_RECT_SQUARE;

protected:
	//Label to the left of the slider (usually the minimum value)
	std::unique_ptr<Label> m_LeftLabel;

	//Label to the right of the slider (usually the maximum value)
	std::unique_ptr<Label> m_rightLabel;

	//Label underneath the slider (usually the current value of slider)
	std::unique_ptr<Label> m_bottomLabel;

	//Label above the slider(name)
	std::unique_ptr<Label> m_topLabel;

	//the slider empty rectangle
	sf::RectangleShape m_sliderBarEmpty;

	//the slider empty rectangle
	sf::RectangleShape m_sliderBarFill;

	//the slider
	sf::RectangleShape m_slider;

	//offset of label from slider
	const float m_LABEL_OFFSET;

	//the jump between values
	float m_jump;

	//check if slider was moved
	bool m_moved;

	//delta time
	float m_timer;

	//values for slider minimum maximum and curent values
	int m_min;
	int m_max;
	float& m_current;

	//number to increase the value by
	int m_valueJump;

	//current slider state
	SliderState m_currentState = SliderState::ACTIVE;

	//previous slider state
	SliderState m_previousState = SliderState::ACTIVE;

	//highlight rectangle
	sf::RectangleShape m_highlightRectangle;

	//alpha of the highlight rectangle
	float m_highlightAlpha;

	//check if alpha to go down
	bool m_fadeOut;

	//slider texture sheet
	sf::Texture m_texture;

	//texture rectangle of the empty rectangle
	sf::IntRect m_emptyTextRect;

	//texture rectangle of the filled rectangle
	sf::IntRect m_filledTextRect;

	//texture rectangle of the square slider
	sf::IntRect m_squareTextRect;
};

#endif // !SLIDER_H
