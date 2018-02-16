#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include "SFML\Graphics.hpp"
#include "system\Window.h"
#include <stdlib.h>
#include "Entities\Player\Bullets\CometShot.h"
#include "system\ResourceHandler.h"
#include "json\json.hpp"

///
/// @brief An asteroid entity class.
/// @author Rafael Plugge
/// @author Sebastian Kruzel
/// 
/// Represents a single asteroid entity.
/// 
class Asteroid
{
public:

	struct Resources
	{
		/// 
		/// @author Rafael Plugge
		/// @brief Define the necessary resources for loading a texture.
		/// 
		/// Used by game scene to pass the required resources that Asteroid needs.
		/// 
		struct Texture
		{
			/// <summary>
			/// @brief Store the texture's ID.
			/// 
			/// 
			/// </summary>
			std::string m_id = "";

			/// <summary>
			/// @brief Store the origin of the texture.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_origin;

			/// <summary>
			/// @brief Store the scale of the texture.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_scale;

			/// <summary>
			/// @brief Store the texture rectangle.
			/// 
			/// Source rectangle 
			/// </summary>
			sf::IntRect m_textureRect;

			/// <summary>
			/// @brief Store shared pointer to texture.
			/// 
			/// uninitialized so that the resource handler can initialize it.
			/// </summary>
			std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;

			friend void from_json(const json::json& j, Texture & t);
		};

		/// 
		/// @author Rafael Plugge
		/// @brief Define the necessary resources for loading a animation.
		/// 
		/// Used by game scene to pass the required resources that Asteroid needs.
		/// 
		struct Animation
		{
			/// <summary>
			/// @brief Defines the ID of the animation.
			/// 
			/// 
			/// </summary>
			std::string m_id = "";

			/// <summary>
			/// @brief Defines the duration of the animation.
			/// 
			/// 
			/// </summary>
			sf::Time m_duration;

			/// <summary>
			/// @brief Defines the origin of the animation frames.
			/// 
			/// 
			/// </summary>
			sf::Vector2f m_origin;

			/// <summary>
			/// @brief Defines shared pointer to our animation's frames.
			/// 
			/// 
			/// </summary>
			thor::FrameAnimation m_frames;

			/// <summary>
			/// @brief Defines shared pointer to our animation's texture.
			/// 
			/// 
			/// </summary>
			std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;

			friend void from_json(const json::json& j, Animation & t);
		};

		/// <summary>
		/// @brief Contains idle texture.
		/// 
		/// 
		/// </summary>
		Texture m_idleTexture;

		/// <summary>
		/// @brief Contains explosion texture.
		/// 
		/// 
		/// </summary>
		Texture m_explodeTexture;

		/// <summary>
		/// @brief Contains explosion animation.
		/// 
		/// 
		/// </summary>
		Animation m_explodeAnimation;
	};


public:
	static void setup(std::shared_ptr<Resources> sptrResources, json::json & jsonParser);

	Asteroid(std::shared_ptr<Resources> sptrResources);
	void update();
	void draw(Window & window, const float & deltaTime);
	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	void setActive(bool active);
	void updateCollisionCircle();
	void generateRandomVel();
	void generateRandomPos();
	void reuseAsteroid();
	void updateWindowCollisions();
	tinyh::c2Circle getCollisionCircle();
	void decrementHealth(float dmg, bool invurnState);
	bool isInvulnerable();
	void knockback();
	bool isActive();
	bool isExplosion() const;
	void explode();
	bool containsEnemy() const;
	void setPosition(sf::Vector2f newPos);
	void setRotation(float newRotation);
	float getRotation();

private:
	void generateRandomEnemy();
	void generateRandomRotation();

	/// <summary>
	/// @brief define a shared pointer to loaded resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Resources> m_sptrResources;

	/// <summary>
	/// @brief define rectangle to draw texture on.
	/// 
	/// 
	/// </summary>
	sf::RectangleShape m_rectangle;

	/// <summary>
	/// @brief define asteroid shape.
	/// 
	/// 
	/// </summary>
	sf::CircleShape m_circle;

	/// <summary>
	/// @brief define the velocity of asteroid.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_velocity;

	/// <summary>
	/// @brief define the (central) position of the asteroid.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief defines the rotation speed of the asteroid.
	/// 
	/// 
	/// </summary>
	float m_rotation;

	/// <summary>
	/// @brief define if the asteroid is active.
	/// 
	/// 
	/// </summary>
	bool m_active;

	/// <summary>
	/// @brief define if the asteroid is in a exploded state.
	/// 
	/// 
	/// </summary>
	bool m_explode;

	/// <summary>
	/// @brief defines if the asteroid spawns a enemy on explosion.
	/// 
	/// 
	/// </summary>
	bool m_spawnEnemy;

	/// <summary>
	/// @brief define the collision circle.
	/// 
	/// 
	/// </summary>
	tinyh::c2Circle m_collisionCircle;

	/// <summary>
	/// @brief window collision box.
	/// 
	/// 
	/// </summary>
	tinyh::c2AABB m_windowC2Rect;

	/// <summary>
	/// @brief Define the health.
	/// 
	/// 
	/// </summary>
	float m_health;

	/// <summary>
	/// @brief Define if currently invurnerable
	/// 
	/// 
	/// </summary>
	bool m_invulnerable;

	/// <summary>
	/// @brief Define frames to be invurnerable.
	/// 
	/// 
	/// </summary>
	static const float INVULNERABILITY_FRAMES;

	/// <summary>
	/// @brief Define time that invulnerability was active.
	/// 
	/// 
	/// </summary>
	float m_invulnTimer;

	/// <summary>
	/// @brief constant reference to update delta time.
	/// 
	/// 
	/// </summary>
	const float & UPDATE_DT;

	/// <summary>
	/// @brief constant sfml time of update delta time.
	/// 
	/// 
	/// </summary>
	sf::Time const UPDATE_TIME_DT;

	/// <summary>
	/// @brief thor asteroid animator.
	/// 
	/// Will only contaion explosion animation.
	/// </summary>
	thor::Animator<sf::CircleShape, std::string> m_animator;

	/// <summary>
	/// @brief tracks how long asteroid has been in a explosion.
	/// 
	/// 
	/// </summary>
	sf::Time m_explosionTimer;
};

#endif // !ASTEROIDS_H
