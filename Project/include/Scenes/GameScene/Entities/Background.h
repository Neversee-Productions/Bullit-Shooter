#ifndef BACKGROUND_H
#define BACKGROUND_H

// For sf::Shader
#include "SFML\Graphics\Shader.hpp"
// For sf::RectangleShape
#include "SFML\Graphics\RectangleShape.hpp"
// For Window
#include "Window.h"
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
	Background();
	void init(std::shared_ptr<Resources> resources);
	void update();
	void draw(Window & window, const float & deltaTime);

private:

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
	/// @brief Defines unique pointer to the timer.
	/// 
	/// The timer is used in our shader to apply
	/// a color effect that changes over time.
	/// </summary>
	std::unique_ptr<sf::Clock> m_timer;

	/// <summary>
	/// @brief Defines the render state of the background.
	/// 
	/// 
	/// </summary>
	sf::RenderStates m_renderState;
};

#endif // !BACKGROUND_H