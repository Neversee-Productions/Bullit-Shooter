#ifndef LABEL_H
#define LABEL_H

#include "gui\widgets\Widget.h"

namespace gui
{

	///
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief Label class.
	/// 
	/// 
	///
	class Label : public Widget
	{
	public:
		Label();
		Label(sf::String contents, unsigned int fontSize, sf::Vector2f position, std::shared_ptr<sf::Font> font, sf::Color color = sf::Color::White);
		~Label();
		void setFont(std::shared_ptr<sf::Font> sptrFont);
		void draw(Window& window) const override;
		void draw(sf::RenderTarget&, sf::RenderStates) const override;
		sf::Vector2f getSize();
		void setScale(float x, float y);
		virtual void setPosition(sf::Vector2f position);
		virtual sf::Vector2f getPosition();
		void setText(sf::String string);
		void getFocus() override;
		void loseFocus() override;
		bool processInput(Controller& controller, KeyHandler& keyhandler) override;
		void setOrigin();

	protected:
		/// <summary>
		/// @brief Text object.
		/// 
		/// 
		/// </summary>
		sf::Text m_text;

		/// <summary>
		/// @brief position of label.
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_position;

		/// <summary>
		/// @brief shared pointer to a font.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<sf::Font> m_font;

		/// <summary>
		/// @brief font size.
		/// 
		/// 
		/// </summary>
		unsigned int m_fontSize;
	};
}

#endif // !LABEL_