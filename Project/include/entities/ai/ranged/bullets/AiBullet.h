#ifndef AI_BULLET_H
#define AI_BULLET_H

// STD Includes
// SFML Includes
#include "SFML\Graphics\RectangleShape.hpp"
// Thor Includes
#include "Thor\Vectors.hpp"
#include "Thor\Animations\Animator.hpp"
// Project Includes
#include "system\Window.h"
#include "entities\ai\ranged\AiResources.h"

/// 
/// @brief 
/// @author Rafael Plugge
/// 
/// 
/// 
class AiBullet
{
public: // Constructors/Assignment Operators/Destructor
	AiBullet(ai::Resources & resources);
	AiBullet(AiBullet const &) = default;
	AiBullet(AiBullet &&) = default;

	AiBullet & operator=(AiBullet const &) = default;
	AiBullet & operator=(AiBullet &&) = default;

	~AiBullet() = default;

public: // Public Member Functions
	void update();
	void draw(Window & window, float const & deltaTime);
public: // Public Member Get's
	inline bool const & getActive() const { return m_active; }
	inline sf::Vector2f const & getPosition() const { return m_position; }
	inline sf::Vector2f const & getHeading() const { return m_heading; }
	inline float const & getSpeed() const { return m_speed; }
	inline float const & getRotation() const { return m_angle; }
public: // Public Member Set's
	inline void setActive(bool const & newActive) { m_active = newActive; }
	inline void setPosition(sf::Vector2f const & newPosition) { m_position = newPosition; }
	inline void setHeading(sf::Vector2f const & newHeading) { m_heading = thor::unitVector(newHeading); }
	inline void setSpeed(float const & newSpeed) { m_speed = newSpeed; }
	inline void setRotation(float const & newAngle) { m_angle = newAngle; }
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
	void updateHitbox(sf::FloatRect const & newHitbox);
private: // Private Member Variables
	/// <summary>
	/// @brief reference to loaded resources.
	/// 
	/// 
	/// </summary>
	ai::Resources & m_resources;
	/// <summary>
	/// @brief Defines whether the bullet is active or not.
	/// 
	/// Innactive bullets are considered disabled and are
	/// not drawn/updated.
	/// </summary>
	bool m_active;
	/// <summary>
	/// @brief read-only reference to the update delta time.
	/// 
	/// 
	/// </summary>
	float const & m_UPDATE_DT;
	/// <summary>
	/// @brief Defines the position of the bullet.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;
	/// <summary>
	/// @brief Represents the direction the bullets is going.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_heading;
	/// <summary>
	/// @brief Represents the speed of the bullet.
	/// 
	/// Combined with m_heading these form
	/// the velocity vector of the bullet.
	/// </summary>
	float m_speed;
	/// <summary>
	/// @brief Represents the angle that the bullet is facing.
	/// 
	/// Is stored in degrees.
	/// </summary>
	float m_angle;
	/// <summary>
	/// @brief The target quad.
	/// 
	/// The bullet will be renderered on this quad.
	/// </summary>
	sf::Sprite m_quad;
	/// <summary>
	/// @brief Describes the collision shape.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_collisionShape;
	/// <summary>
	/// @brief Collision AABB bounding box.
	/// 
	/// 
	/// </summary>
	tinyh::c2AABB m_c2Rect;
	/// <summary>
	/// @brief defines the bullet animator.
	/// 
	/// 
	/// </summary>
	thor::Animator<sf::Sprite, std::string> m_animator;
};

#endif // !AI_BULLET_H