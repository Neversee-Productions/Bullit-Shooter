#ifndef GUI_H
#define GUI_H

#include "SFML\Graphics.hpp"
#include "Thor\Math\Trigonometry.hpp"
#include "gui\widgets\Widget.h"
#include "gui\widgets\Label.h"
#include "gui\widgets\Button.h"
#include "gui\widgets\Slider.h"
#include "gui\widgets\CheckBox.h"
#include <vector>
#include <memory>
#include <functional>

/// 
/// @author Rafael Plugge
/// @author Sebastian Kruzel
/// @brief Gui namespace container for all gui classes.
/// 
/// 
namespace gui
{

	/// 
	/// @author Rafael Plugge
	/// @author Sebastian Kruzel
	/// @version 1.0
	/// @brief The GUI class will controll all of the widgets currently on screen.
	/// 
	/// 
	class GUI
	{
	public:
		/// <summary>
		/// @brief Defines the different types of layouts.
		/// 
		/// 
		/// </summary>
		enum class Layouts
		{
			Custom /// Custom layout does not alter the defined widget positions.
			, StackVertically /// Stacks widgets vertically in the center of the screen.
			, StripDiagonal /// Stacks widgets diagonally accross the center.
		};

		// constructor
		GUI(std::shared_ptr<KeyHandler>, std::shared_ptr<Controller>, bool stripDraw = false);

		// destructor
		~GUI();

		// Update GUI
		void update(const float & dt);

		// Draw the GUI
		void draw(Window&) const;

		// Configure the GUI
		void configure(const Layouts&, const sf::Vector2u & windowSize);
		// Configure the GUI
		void configure(const Layouts&, const unsigned int & windowWidth, const unsigned int & windowHeight);

		// Add a label to widgets vector
		void addLabel(sf::String contents
			, unsigned int fontSize
			, sf::Vector2f position
			, std::shared_ptr<sf::Font> font
			, sf::Color color = sf::Color::White);

		// Add a button to widgets vector
		void addButton(std::function<void()> function
			, sf::String message
			, sf::Vector2f position
			, std::shared_ptr<sf::Font> font
			, unsigned int fontSize
			, std::shared_ptr<sf::Texture> texture
			, sf::IntRect leftTextRect
			, sf::IntRect middleTextRect
			, sf::IntRect rightTextRect);

		// Add a slider to widgets vector
		void addSlider(std::shared_ptr<sf::Font> font
			, sf::String name
			, unsigned int fontSize
			, sf::Vector2f position
			, float sliderWidth
			, float sliderHeight
			, float minValue
			, float maxValue
			, float& currentValue
			, std::shared_ptr<sf::Texture> texture
			, sf::IntRect emptyTextRect
			, sf::IntRect filledTextRect
			, sf::IntRect squareTextRect);

		// Add a checkbox to the GUI
		void addCheckbox(std::shared_ptr<sf::Font> font
			, sf::String name
			, sf::Vector2f position
			, float scale
			, std::shared_ptr<sf::Texture> m_texture
			, sf::IntRect textRectOn
			, sf::IntRect textRectOff
			, bool & state
			, unsigned charSize);

	private:
		// link last widget, to its previous eligible element 
		void linkWidget();
		// processes xbox controller widget navigation
		void processInput();
		// move to the previous Widget
		void moveToPrevWidgets();
		// move to the next widget
		void moveToNextWidgets();

		/// <summary>
		/// @brief vector of shared pointers to widgets.
		/// 
		/// 
		/// </summary>
		std::vector<std::shared_ptr<Widget>> m_widgets;


		/// <summary>
		/// @brief number of widgets that are can be layed out.
		/// 
		/// 
		/// </summary>
		int m_layoutNr;

		/// <summary>
		/// @brief Screen margin.
		/// 
		/// 
		/// </summary>
		const sf::Vector2f m_screenMargin = sf::Vector2f(10.0f, 100.0f);

		/// <summary>
		/// @brief Shared pointer to keyHandler.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<KeyHandler> m_keyHandler;

		/// <summary>
		/// @brief Shared pointer to controller.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Controller> m_controller;

		/// <summary>
		/// @brief Widget that the controller is currently selected.
		/// 
		/// Points to our selected widget, is null if there are
		/// no selectable widgets.
		/// </summary>
		std::shared_ptr<Widget> m_selectedWidget;

		/// <summary>
		/// @brief Rectangle strip that is underneath the menu layer.
		/// 
		/// Represents the rectangle strip drawable.
		/// </summary>
		sf::RectangleShape m_rectangleStrip;

		/// <summary>
		/// @brief Checks if we should draw the rectangle strip.
		/// 
		/// Defaulted to false in constructor.
		/// </summary>
		bool m_drawStrip;
	};

}

#endif // !GUI_