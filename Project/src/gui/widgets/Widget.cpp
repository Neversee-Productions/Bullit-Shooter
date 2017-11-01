#include "gui\widgets\Widget.h"


/// <summary>
/// @brief Default constructor for the widget.
/// 
/// 
/// assign arguments to member variables
/// initialise member variables via initialiser list
/// </summary>
Widget::Widget()
	: m_next()
	, m_previous()
{
}

/// <summary>
/// @brief Nothing to update.
/// </summary>
/// <param name="dt"></param>
void Widget::update(float dt)
{
}

/// <summary>
/// @brief Nothing to update.
/// </summary>
void Widget::updateShape()
{
}

/// <summary>
/// @brief Destructor of a widget.
/// </summary>
Widget::~Widget()
{
}
