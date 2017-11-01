#ifndef LABEL_H
#define LABEL_H

#include "gui\widgets\Widget.h"

/// <summary>
/// @author Sebastian Kruzel
/// @version 1.0
/// @brief Label class.
/// 
/// 
/// </summary>
class Label : public Widget
{
public:
	//default constructor
	Label();

	//Constructor
	Label(sf::String contents, unsigned int fontSize, sf::Vector2f position, sf::Font & font, sf::Color color = sf::Color::White);

	//Destructor
	~Label();

	//this method sets the font of the labels
	void setFont(sf::Font font);

	//draw
	void draw(sf::RenderTarget& window, sf::RenderStates state) const override;

	//method that returns the dimensions of text
	sf::Vector2f getSize();

	//setting scale
	void setScale(float x, float y);

	//set position of label
	virtual void setPosition(sf::Vector2f position);

	//get position of label
	virtual sf::Vector2f getPosition();

	//set text of label
	void setText(sf::String string);

	//get focus method
	void getFocus() override;

	//lose focus method
	void loseFocus() override;

	//method for processing the xbox controller inputs
	bool processInput(Controller& controller) override;

	//set the origin of the label
	void setOrigin();

protected:
	//Text object
	sf::Text m_text;

	//position of label
	sf::Vector2f m_position;

	//font
	sf::Font m_font;

	//font size
	unsigned int m_fontSize;
};

#endif // !LABEL_
