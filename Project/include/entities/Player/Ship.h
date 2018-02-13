#ifndef SHIP_H
#define SHIP_H

// For std::shared_ptr and std::unique_ptr
#include <memory>
// For std::string
#include <string>
// For sf::RectangleShape
#include "SFML\Graphics\RectangleShape.hpp"
// For sf::Texture
#include "SFML\Graphics\Texture.hpp"
// For thor::Animator<>
#include "Thor\Animations\Animator.hpp"
#include "Window.h"
//for vector calculations
#include "Thor\Vectors.hpp" 
#include <iostream>

///
/// @brief Ship class.
/// @author Sebastian Kruzel
/// @author Rafael Plugge
/// 
/// Defines the ship class.
/// 
class Ship
{
private:

	/// 
	/// @author Rafael Plugge
	/// @brief Defines a set of bools for keys pressed.
	/// 
	/// 
	/// 
	struct KeysPressed
	{
		bool m_left;
		bool m_right;
		bool m_up;
		bool m_down;
	};

public:
	/// <summary>
	/// @brief Alias for thor::Animator.
	/// 
	/// Uses thor animator on sfml rectangle shape using the std::string as the key.
	/// </summary>
	typedef thor::Animator<sf::RectangleShape, std::string> ShipAnimator;

	/// <summary>
	/// @brief Alias for std::vector.
	/// 
	/// Uses a vector as a container for texture frames.
	/// </summary>
	typedef std::vector<sf::IntRect> ShipFrames;

	/// 
	/// @author Rafael Plugge
	/// @brief Defines the resources the ship needs.
	/// 
	/// 
	/// 
	struct Resources
	{
		std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;
		std::unique_ptr<ShipFrames> m_uptrFrames = nullptr;
	};

	/// 
	/// @author Rafael Plugge
	/// @brief Defines a ship direction.
	/// 
	/// Can be up, down, left or right
	/// 
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

public:
	Ship();
	void init(std::shared_ptr<Resources> resources);
	void draw(Window & window, const float & deltaTime);
	void update();
	void move(const Direction & direction, const bool & state);
	const sf::RectangleShape & getShipRect() const;
	void setTexture(std::shared_ptr<sf::Texture> sptrTexture);
	void setFrames(std::unique_ptr<ShipFrames> uptrShipFrames);

private:
	void processInput(const KeysPressed &);
	void decFrame();
	void incFrame();


	/// <summary>
	/// @brief Delta time update.
	/// 
	/// Time in seconds between each update call.
	/// </summary>
	const float & m_UPDATE_DT;
	/// <summary>
	/// @brief Represents the ship.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_shipRect;

	/// <summary>
	/// @brief define players speed.
	/// 
	/// 
	/// </summary>
	float m_speed;

	/// <summary>
	/// @brief define position.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief Defines all the frames of the ship.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<std::vector<sf::IntRect>> m_shipFrames;

	/// <summary>
	/// @brief shared pointer to ship texture.
	/// 
	/// Must be set with Ship::setTexture else it will be nullptr.
	/// </summary>
	std::shared_ptr<sf::Texture> m_texture;

	/// <summary>
	/// @brief Defines the current frame of ship animation.
	/// 
	/// Ship is converted to integer when accessing vector of frames.
	/// </summary>
	float m_currentFrame;

	/// <summary>
	/// @brief Defines the amount the frame changes in 1 second.
	/// 
	/// 
	/// </summary>
	const float m_FRAME_CHANGE;

	/// <summary>
	/// @brief Defines the frame that the ship is still.
	/// 
	/// 
	/// </summary>
	std::unique_ptr<const float> m_FRAME_STILL;

	/// <summary>
	/// @brief ID for ship animation.
	/// 
	/// 
	/// </summary>
	const std::string m_ID;
	
	/// <summary>
	/// @brief Defines a struct of pressed keys.
	/// </summary>
	KeysPressed m_pressed;

	/// <summary>
	/// @brief this is the velocity vector.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_velocity;

	/// <summary>
	/// @brief define the aount to accelerate by.
	/// 
	/// 
	/// </summary>
	float m_accelerationRate;

	/// <summary>
	/// @brief direction vector of movement based on input.
	/// this may not be from 0-1 as we will use a joystick
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_directionVec;

	/// <summary>
	/// @brief vector of movement.
	/// This is the normalized direction vector.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_moveDir;

	/// <summary>
	/// @brief this is the max velocity of the player ship.
	/// 
	/// 
	/// </summary>
	float m_maxVel = 1000.0f;

	/// <summary>
	/// @brief this defines the acceleration of the player.
	/// 
	/// 
	/// </summary>
	float m_acceleration;
};

#endif SHIP_H