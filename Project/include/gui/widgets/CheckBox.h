#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "gui\widgets\Label.h"

namespace gui
{

	/// <summary>
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief Checkbox class.
	/// 
	/// A class that creates a checkbox
	/// the checkbox is a widget with 2 states on and off
	/// </summary>
	class CheckBox : public Label
	{
	public:
		//The different possible checkbox states
		enum class CheckboxState { INACTIVE, ACTIVE, HOVERED };

		//The default constructor
		CheckBox(sf::Font font				//font of checkbox
			, sf::String name			//title of checkbox
			, sf::Vector2f position		//position
			, float scale				//scale (both width and height)
			, std::shared_ptr<sf::Texture> onTexture		//shared pointer to the texture of the checkbox
			, sf::IntRect textRectOn	//texture rectangle when the box is on
			, sf::IntRect textRectOff	//texture rectangle when the box is off
			, bool & state				//starting state of the checkbox (true on/ false off)
			, unsigned charSize = 20u		//character size (default 20)
		);

		//the destructor
		~CheckBox();

		//draw the checkbox
		void draw(Window & window)const override;

		// draws the checkbox to the render target with the render states applied to it.
		void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)const override;

		//button update
		void update(const float & dt) override;

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

		/// texture rectangle for checkbox
		static const sf::IntRect s_TEXT_RECT_ON;
		static const sf::IntRect s_TEXT_RECT_OFF;

	protected:
		//center of the checkbox
		sf::Vector2f m_position;

		//scale of the textures
		float m_scale;

		//the shared pointer for texture of checkbox
		std::shared_ptr<sf::Texture> m_texture;

		//highlight rectangle
		sf::RectangleShape m_highlightRectangle;

		//alpha of the highlight rectangle
		float m_highlightAlpha;

		//check if alpha to go down
		bool m_fadeOut;

		//on off states of checkbox
		bool& m_state;

		//sprite of the checkbox
		sf::RectangleShape m_rectangle;

		//offset of label from checkbox
		const float m_LABEL_OFFSET = 20.0f;

		//the highlight border
		const float m_HIGHLIGHT_BORDER = 20.0f;

		//the current checkbox state
		CheckboxState m_currentState = CheckboxState::ACTIVE;

		//texture rectangle for checkbox on
		sf::IntRect m_onTextRect;

		//texture rectangle for checkbox off
		sf::IntRect m_offTextRect;

	};
}

#endif // !CHECKBOX_H