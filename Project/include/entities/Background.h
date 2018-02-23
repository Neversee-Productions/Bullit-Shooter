#ifndef BACKGROUND_H
#define BACKGROUND_H

// For sf::Shader
#include "SFML\Graphics\Shader.hpp"
// For sf::RectangleShape
#include "SFML\Graphics\RectangleShape.hpp"
// For Window
#include "system\Window.h"
// For std::shared_ptr
#include <memory>

/// 
/// @author Rafael Plugge
/// @brief Represents a background image.
/// 
/// This image is a rectangle with a shader applied to it.
/// 
class Background
{
public:

	/// 
	/// @author Rafael Plugge
	/// @brief Struct containing resources of background.
	/// 
	/// 
	/// 
	struct Resources
	{
		std::shared_ptr<sf::Shader> m_sptrBgShader = nullptr;
	};

public:
	Background(sf::Color const & startColor = sf::Color::Black);
	void init(std::shared_ptr<Resources> resources);
	void update();
	void draw(Window & window, const float & deltaTime);
	void setTargetColor(sf::Color const & newColor);
	void reset();

private:
	void interpolate(float & value, float const & targetValue);

	/// <summary>
	/// @brief Read only reference to update delta time.
	/// 
	/// 
	/// </summary>
	float const & m_DELTA_TIME;

	sf::Glsl::Vec4 const m_bgResetColor;

	/// <summary>
	/// @brief Define the background color.
	/// 
	/// 
	/// </summary>
	sf::Glsl::Vec4 m_bgColor;

	/// <summary>
	/// @brief Define the target background color.
	/// 
	/// background color will always try to interpolate towards
	/// this color.
	/// </summary>
	sf::Glsl::Vec4 m_bgTargetColor;

	/// <summary>
	/// @brief constant of how much (percent) does a color change per second.
	/// 
	/// 
	/// </summary>
	float const m_COLOR_CHANGE;

	/// <summary>
	/// @brief Defines the shape to be drawn.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_image;

	/// <summary>
	/// @brief Defines shared pointer to loaded shader.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<sf::Shader> m_shader;

	/// <summary>
	/// @brief Defines the timer.
	/// 
	/// The timer is used in our shader to apply
	/// a color effect that changes over time.
	/// </summary>
	sf::Time m_timer;

	/// <summary>
	/// @brief Defines the render state of the background.
	/// 
	/// 
	/// </summary>
	sf::RenderStates m_renderState;
};

#endif // !BACKGROUND_H