#ifndef CONNECTOR_H
#define CONNECTOR_H

// STL Includes
#include <memory>
// SFML Includes
#include "SFML\Graphics\Shader.hpp"
#include "SFML\Graphics\RectangleShape.hpp"
// Thor Includes
#include "Thor\Math.hpp"
#include "Thor\Vectors.hpp"
// Project Includes
#include "system\Window.h"

/// 
/// @brief Represents the connector between the ship and its weapons.
/// @author Rafael Plugge
/// 
/// This connector will have a shader applied to it.
/// 
class Connector
{
public:

	struct Resources
	{
		std::shared_ptr<sf::Shader> m_sptrCnShader = nullptr;
	};

public:
	Connector(bool flipped = false);
	void init(std::shared_ptr<Resources> resources);
	void update(sf::Vector2f const & startPos, sf::Vector2f const & endPos);
	void draw(Window & window, float const & deltaTime);
	void reset(sf::Vector2f pos);

private:
	
	/// <summary>
	/// @brief Read-only reference to the transparent colour.
	/// 
	/// Defined as RGBA style,
	/// (0u, 0u, 0u, 255u),
	/// used when clear
	/// </summary>
	sf::Color const & m_CLEAR_COLOR;

	/// <summary>
	/// @brief Defines the thickness of the connector.
	/// 
	/// 
	/// </summary>
	float const m_THICKNESS;

	/// <summary>
	/// @brief Defines the quad used to draw the connector.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_sprite;

	/// <summary>
	/// @brief Defines the shader used by the sprite.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<sf::Shader> m_shader;

	/// <summary>
	/// @brief Defines timer used by shader.
	/// 
	/// 
	/// </summary>
	sf::Time m_timer;

	/// <summary>
	/// @brief Defines the render state of the connector.
	/// 
	/// 
	/// </summary>
	sf::RenderStates m_renderState;

	/// <summary>
	/// @brief Defines the target for shader drawing.
	/// 
	/// Used so that shader that is drawn over the texture,
	/// can be dynamically moved by Connector::m_sprite
	/// </summary>
	sf::RenderTexture m_shaderTexture;

	/// <summary>
	/// @brief Represents the shader quad itself.
	/// 
	/// This quad is used by Connector::m_shaderTexture to draw the
	/// shader on Connector::m_shaderTexture which Connector::m_sprite
	/// uses to Connector::m_shaderTexture as its texture to drawn the
	/// shader at a specified location.
	/// </summary>
	sf::RectangleShape m_shaderQuad;
	/// <summary>
	/// @brief Describes whether the connector is flipped.
	/// 
	/// 
	/// </summary>
	bool const m_FLIPPED;
};

#endif // !CONNECTOR_H