#ifndef WIDGET_H
#define WIDGET_H

#include <SFML\Graphics\Drawable.hpp>
#include <memory>
#include <functional>
#include "input\Controller.h"

/// <summary>
/// @author Sebastian Kruzel
/// @version 1.0
/// @brief Widget abstract class
/// 
/// The base class for all widgets
/// contains abstract functions that will be used by derived classes
/// </summary>
class Widget : public sf::Drawable
{
public:
	//default constructor
	Widget();

	//virtual method for processing the xbox controller inputs
	virtual bool processInput(Controller& controller) = 0;

	//virtual widget focus method
	virtual void getFocus() = 0;

	//virtual lose focus from widget method
	virtual void loseFocus() = 0;

	//virtual update method for widget
	virtual void update(float dt);

	//virtual update shape of widget
	virtual void updateShape();

	//pure virtual draw call
	virtual void draw(sf::RenderTarget& window, sf::RenderStates state) const = 0;	
	
	//a widget destructor
	~Widget();

	// pointer to the next widget
	std::weak_ptr<Widget> m_next;
	
	// pointer to the previous widget
	std::weak_ptr<Widget> m_previous;
};
#endif // !WIDGET_

