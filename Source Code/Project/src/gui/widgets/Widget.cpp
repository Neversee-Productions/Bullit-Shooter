#include "gui\widgets\Widget.h"


/// <summary>
/// @brief Default constructor for the widget.
/// 
/// 
/// assign arguments to member variables
/// initialise member variables via initialiser list
/// </summary>
gui::Widget::Widget()
	: m_next()
	, m_previous()
{
}

/// <summary>
/// @brief Nothing to update.
/// 
/// 
/// </summary>
/// <param name="dt">delta time</param>
void gui::Widget::update(const float & dt)
{
}

/// <summary>
/// @brief Nothing to update.
/// 
/// 
/// </summary>
void gui::Widget::updateShape()
{
}

/// <summary>
/// @brief Destructor of a widget.
/// 
/// 
/// </summary>
gui::Widget::~Widget()
{
}
