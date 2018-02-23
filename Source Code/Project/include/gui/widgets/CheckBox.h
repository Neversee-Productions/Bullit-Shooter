#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "gui\widgets\Label.h"

namespace gui
{

	///
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief Checkbox class.
	/// 
	/// A class that creates a checkbox
	/// the checkbox is a widget with 2 states on and off
	///
	class CheckBox : public Label
	{
	public:
		/// <summary>
		/// @brief The different possible checkbox states.
		/// 
		/// 
		/// </summary>
		enum class CheckboxState 
		{ 
			INACTIVE ///Inactive state of checkbox (user cannot toggle)
			, ACTIVE ///Active state of checkbox (user may toggle)
			, HOVERED  ///Checkbox is being currently highlighted
		};
		CheckBox(std::shared_ptr<sf::Font> font
			, sf::String name
			, sf::Vector2f position
			, float scale
			, std::shared_ptr<sf::Texture> onTexture
			, sf::IntRect textRectOn
			, sf::IntRect textRectOff
			, bool & state
			, unsigned charSize = 20u
		);
		~CheckBox();
		void draw(Window & window)const override;
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)const override;
		void update(const float & dt) override;
		void getFocus() override;
		void loseFocus() override;
		void fading();
		bool processInput(Controller& controller, KeyHandler & keyhandler) override;
		void setPosition(sf::Vector2f position) override;
		sf::Vector2f getPosition() override;

		/// <summary>
		/// @brief texture rectangle of the on checkbox.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_ON;

		/// <summary>
		/// @brief texture rectangle of the off checkbox.
		/// 
		/// 
		/// </summary>
		static const sf::IntRect s_TEXT_RECT_OFF;

	protected:
		/// <summary>
		/// @brief center of the checkbox.
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_position;

		/// <summary>
		/// @brief scale of the textures.
		/// 
		/// 
		/// </summary>
		float m_scale;

		/// <summary>
		/// @brief the shared pointer for texture of checkbox.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Texture> m_texture;

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
		/// @brief on off states of checkbox.
		/// 
		/// 
		/// </summary>
		bool& m_state;

		/// <summary>
		/// @brief sprite of the checkbox.
		/// 
		/// 
		/// </summary>
		sf::RectangleShape m_rectangle;

		/// <summary>
		/// @brief offset of label from checkbox.
		/// 
		/// 
		/// </summary>
		const float m_LABEL_OFFSET = 20.0f;

		/// <summary>
		/// @brief the highlight border.
		/// 
		/// 
		/// </summary>
		const float m_HIGHLIGHT_BORDER = 20.0f;

		/// <summary>
		/// @brief the current checkbox state.
		/// 
		/// 
		/// </summary>
		CheckboxState m_currentState = CheckboxState::ACTIVE;

		/// <summary>
		/// @brief texture rectangle for checkbox on.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_onTextRect;

		/// <summary>
		/// @brief texture rectangle for checkbox off.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_offTextRect;
	};
}

#endif // !CHECKBOX_H