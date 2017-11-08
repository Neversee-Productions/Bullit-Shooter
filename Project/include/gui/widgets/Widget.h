#ifndef WIDGET_H
#define WIDGET_H

#include <SFML\Graphics\Drawable.hpp>
#include <memory>
#include <functional>
#include "input\Controller.h"
#include "input\KeyHandler.h"
#include "Window.h"

namespace gui
{

	///
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief Widget abstract class
	/// 
	/// The base class for all widgets
	/// contains abstract functions that will be used by derived classes
	///
	class Widget : public sf::Drawable
	{
	public:
		Widget();
		virtual bool processInput(Controller& controller, KeyHandler& keyhandler) = 0;
		virtual void getFocus() = 0;
		virtual void loseFocus() = 0;
		virtual void update(const float & dt);
		virtual void updateShape();
		virtual void draw(Window& window) const = 0;
		virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const = 0;
		~Widget();

		/// <summary>
		/// @brief pointer to the next widget.
		/// 
		/// 
		/// </summary>
		std::weak_ptr<Widget> m_next;

		/// <summary>
		/// @brief pointer to the previous widget.
		/// 
		/// 
		/// </summary>
		std::weak_ptr<Widget> m_previous;
	};
}

#endif // !WIDGET_