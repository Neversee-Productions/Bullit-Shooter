#ifndef BUTTON_H
#define BUTTON_H

#include "gui\widgets\Label.h"
#include <iostream>

namespace gui
{

	///
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief Button class
	/// 
	/// 
	/// 
	class Button : public Label
	{
	public:
		/// <summary>
		/// @brief the different possible button states
		/// 
		/// 
		/// </summary>
		enum class ButtonState 
		{
			INACTIVE ///an inactive button state (cannot press)
			, ACTIVE ///an active button state (pressable)
			, HOVERED ///currently highlighted
			, PRESSED ///has been pressed
		};
		Button(std::function<void()> function, sf::String message, sf::Vector2f position, std::shared_ptr<sf::Font> font, unsigned int fontSize, std::shared_ptr<sf::Texture> texture, sf::IntRect leftTextRect, sf::IntRect middleTextRect, sf::IntRect rightTextRect);
		void draw(Window & window)const override;
		void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates)const override;
		void update(const float & dt) override;
		void getFocus() override;
		void loseFocus() override;
		void fading();
		bool processInput(Controller& controller, KeyHandler & keyhandler) override;
		void setPosition(sf::Vector2f position) override;
		sf::Vector2f getPosition() override;
		void scaleRectangles(float x, float y);
		void setRectangleColors(sf::Color color);

		/// <summary>
		/// @brief left side of button texture rectangle.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_LEFT;

		/// <summary>
		/// @brief middle of button texture rectangle.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_MID;

		/// <summary>
		/// @brief right side of button texture rectangle.
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_RIGHT;

	protected:
		/// <summary>
		/// @brief rectangle representing the middle section of the button.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_rectangleMiddle;

		/// <summary>
		/// @brief rectangle representing the left edge of the button.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_rectangleLeft;

		/// <summary>
		/// @brief rectangle representing the right edge of the button.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_rectangleRight;

		/// <summary>
		/// @brief position of the rectangle.
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_rectanglePos;

		/// <summary>
		/// @brief a margin size same across all buttons.
		/// 
		/// 
		/// </summary>
		const float m_MARGIN_SIZE;

		/// <summary>
		/// @brief Current and previous button states.
		/// 
		/// 
		/// </summary>
		ButtonState m_currentButtonState = ButtonState::ACTIVE;

		/// <summary>
		/// @brief Previous button state.
		/// 
		/// 
		/// </summary>
		ButtonState m_previousButtonState = ButtonState::ACTIVE;

		/// <summary>
		/// @brief highlight rectangle.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_highlightRectangle;

		/// <summary>
		/// @brief alpha of the highlight rectangle.
		/// 
		/// 
		/// </summary>
		float m_highlightAlpha;

		/// <summary>
		/// @brief check if alpha to go down.
		/// 
		/// 
		/// </summary>
		bool m_fadeOut;

		/// <summary>
		/// @brief pointer to function that is called when button is pressed.
		/// 
		/// 
		/// </summary>
		std::function<void()> m_function;

		/// <summary>
		/// @brief texture of the button.
		/// 
		/// 
		/// </summary>
		sf::Texture m_texture;

		/// <summary>
		/// @brief texture rectangle of left edge.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_leftTextRect;

		/// <summary>
		/// @brief texture rectangle of middle.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_middleTextRect;

		/// <summary>
		/// @brief texture rectangle of right edge.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_rightTextRect;
	};
}

#endif // !BUTTON_