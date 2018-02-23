#ifndef SLIDER_H
#define SLIDER_H

#include "gui\widgets\Label.h"
#include <memory>

namespace gui
{

	///
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief Slider class.
	/// 
	/// A slider GUI element 
	/// can be used to go through different iterations of values
	///
	class Slider : public Widget
	{
	public:
		/// <summary>
		/// @brief an enumerator class for the states of a slider.
		/// 
		/// 
		/// </summary>
		enum class SliderState 
		{
			INACTIVE ///Inactive state of a slider (cannot be selected)
			, ACTIVE ///Active state of a slider (may be selected)
			, HOVERED ///Slider is currently highlighted
		};
		Slider(
			std::shared_ptr<sf::Texture> texture,
			sf::IntRect emptyTextRect,
			sf::IntRect filledTextRect,
			sf::IntRect squareTextRect,
			std::shared_ptr<sf::Font> font,
			sf::String name,
			unsigned int fontSize,
			sf::Vector2f position,
			float sliderWidth,
			float sliderHeight,
			float minValue,
			float maxValue,
			float& currentValue
		);
		~Slider();
		void update(const float & dt) override;
		void draw(Window& window)const override;
		void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates)const override;
		void getFocus() override;
		void loseFocus() override;
		void fading();
		bool processInput(Controller& controller, KeyHandler & keyhandler) override;
		void setPosition(sf::Vector2f position);
		sf::Vector2f getPosition();
		void moveRight();
		void moveLeft();

		/// <summary>
		/// @brief Texture rectangle of the empty slider.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_EMPTY;

		/// <summary>
		/// @brief Texture rectangle of the filled slider.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_FILL;

		/// <summary>
		/// @brief Texture rectangle of the moving indicator.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_SQUARE;

	protected:
		/// <summary>
		/// @brief Label to the left of the slider (usually the minimum value).
		/// 
		/// 
		/// </summary>
		std::unique_ptr<Label> m_leftLabel;

		/// <summary>
		/// @brief Label to the right of the slider (usually the maximum value).
		/// 
		/// 
		/// </summary>
		std::unique_ptr<Label> m_rightLabel;

		/// <summary>
		/// @brief Label underneath the slider (usually the current value of slider).
		/// 
		/// 
		/// </summary>
		std::unique_ptr<Label> m_bottomLabel;

		/// <summary>
		/// @brief Label above the slider(name).
		/// 
		/// 
		/// </summary>
		std::unique_ptr<Label> m_topLabel;

		/// <summary>
		/// @brief the slider empty rectangle.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_sliderBarEmpty;

		/// <summary>
		/// @brief the slider empty rectangle.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_sliderBarFill;

		/// <summary>
		/// @brief the slider rectangle.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_slider;

		/// <summary>
		/// @brief offset of label from slider.
		/// 
		/// 
		/// </summary>
		const float m_LABEL_OFFSET;

		/// <summary>
		/// @brief the jump between values.
		/// 
		/// 
		/// </summary>
		float m_jump;

		/// <summary>
		/// @brief check if slider was moved.
		/// 
		/// 
		/// </summary>
		bool m_moved;

		/// <summary>
		/// @brief delta time.
		/// 
		/// 
		/// </summary>
		float m_timer;

		/// <summary>
		/// @brief minimum value of slider.
		/// 
		/// 
		/// </summary>
		int m_min;

		/// <summary>
		/// @brief maximum value of slider.
		/// 
		/// 
		/// </summary>
		int m_max;

		/// <summary>
		/// @brief The current value of slider.
		/// 
		/// 
		/// </summary>
		float& m_current;

		/// <summary>
		/// @brief number to increase the value by.
		/// 
		/// 
		/// </summary>
		int m_valueJump;

		/// <summary>
		/// @brief current slider state.
		/// 
		/// 
		/// </summary>
		SliderState m_currentState = SliderState::ACTIVE;

		/// <summary>
		/// @brief previous slider state.
		/// 
		/// 
		/// </summary>
		SliderState m_previousState = SliderState::ACTIVE;

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
		/// @brief texture rectangle of the empty rectangle.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_emptyTextRect;
		
		/// <summary>
		/// @brief texture rectangle of the filled rectangle.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_filledTextRect;

		/// <summary>
		/// @brief texture rectangle of the square slider.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_squareTextRect;
	};
}

#endif // !SLIDER_H