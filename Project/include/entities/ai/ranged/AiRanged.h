#ifndef AI_RANGED_H
#define AI_RANGED_H

// STD Includes
#include <stack>
// SFML Includes
// Project Includes
#include "entities\ai\AiBase.h"
#include "entities\Player\Player.h"
#include "bullets\AiBulletManager.h"
#include "AiResources.h"
#include "SFML\Graphics.hpp"

namespace ai
{
	namespace states
	{// Forward References
		class AiRangedState;
		class AiRangedMoveState;
		class AiRangedDeployState;
		class AiRangedShootState;
		class AiRangedDeathState;
	}

	/// 
	/// @brief Defines a Ranged AI.
	/// @author Rafael Plugge
	/// 
	/// 
	/// 
	class AiRanged : public AiBase
	{
	private: // Private Friend classes
		friend class states::AiRangedState;
		friend class states::AiRangedMoveState;
		friend class states::AiRangedDeployState;
		friend class states::AiRangedShootState;
		friend class states::AiRangedDeathState;

	public: // Constructors/Destructor
		AiRanged(Player const & player, sf::Vector2f position = { 0.0f, 0.0f });
		~AiRanged() = default;

	public: // Public Static Member Functions
		static void setup(
			std::shared_ptr<ai::Resources> sptrResources,
			ResourceHandler & resourceHandler,
			js::json & rangedEnemyParser);
	public: // Public Member Functions
		void init(std::shared_ptr<ai::Resources> sptrResources);
		virtual void update() final override;
		virtual void draw(Window & window, float const & deltaTime) final override;
		void spawn(sf::Vector2f const & spawnPosition);
		inline tinyh::c2Circle const & getC2Circle() const { return m_collisionCircle; }
		inline std::vector<AiBullet> & getBullets() { return m_bulletManager.getBullets(); }
		inline bool const & isAlive() const { return m_alive; }
		inline void setAlive(bool const & newAlive) { m_alive = newAlive; }
		virtual bool checkCollision(tinyh::c2Circle const & collision) const final override;
		virtual bool checkCollision(tinyh::c2AABB const & collision) const final override;
		virtual bool checkCollision(tinyh::c2Capsule const & collision) const final override;
		virtual bool decrementHealth(float const & damage) final override;
	public: // Public Member Variables
	protected: // Protected Member Functions
	protected: // Protected Member Variables
	private: // Private Member Functions
		void updateHitbox();
		void playAnimation(Resources::Animation const & animation, Resources::Texture const & texture, bool const & loop);
		void setState(std::shared_ptr<ai::states::AiRangedState> sptrNewState, bool rememberPrevious);
		void initStates();
		void initAnimations();
		void initAnimation(Resources::Animation const & animation);
	private: // Private Static Member Variables
		/// <summary>
		/// @brief Defines the max health of all ranged ai's.
		/// 
		/// 
		/// </summary>
		static float const s_MAX_HEALTH;
		/// <summary>
		/// @brief Defines the size of the ai's render quad.
		/// 
		/// 
		/// </summary>
		static sf::Vector2f const s_SIZE;
		/// <summary>
		/// @brief Defines the id of the move state.
		/// 
		/// 
		/// </summary>
		static std::string s_MOVE_ID;
		/// <summary>
		/// @brief Defines the id of the deploy state.
		/// 
		/// 
		/// </summary>
		static std::string s_DEPLOY_ID;
		/// <summary>
		/// @brief Defines the ID of the shoot state.
		/// 
		/// 
		/// </summary>
		static std::string s_SHOOT_ID;
		/// <summary>
		/// @brief Defines the ID of the ebola spit.
		/// 
		/// 
		/// </summary>
		static std::string s_EBOLA_ID;
		/// <summary>
		/// @brief Defines the ID of the death animation.
		/// 
		/// 
		/// </summary>
		static std::string s_DEATH_ID;
		/// <summary>
		/// @brief Defines the ID of the ebola impact id.
		/// 
		/// 
		/// </summary>
		static std::string s_EBOLA_IMPACT_ID;
		/// <summary>
		/// @brief Defines whether to color the ai's states.
		/// 
		/// 
		/// </summary>
		static bool const s_COLOR_QUAD;
		/// <summary>
		/// @brief Defines the collision circle's radius.
		/// 
		/// 
		/// </summary>
		static float const s_C2_RADIUS;
	private: // Private Member Variables
		/// <summary>
		/// @brief Read-only reference to the player.
		/// 
		/// 
		/// </summary>
		Player const & m_player;
		/// <summary>
		/// @brief Defines whether enemy is alive.
		/// 
		/// 
		/// </summary>
		bool m_alive;
		/// <summary>
		/// @brief Defines the ai's current position.
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_position;
		/// <summary>
		/// @brief Defines the current speed of the ranged ai.
		/// 
		/// 
		/// </summary>
		float m_speed;
		/// <summary>
		/// @brief Describes the direction the ai is heading.
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_heading;
		/// <summary>
		/// @brief Describes the rotation of the ai, in degrees.
		/// 
		/// This angles, in degrees, describes the direction
		/// the ai is facing
		/// </summary>
		float m_angle;
		/// <summary>
		/// @brief defines the position that the enemy will deploy on.
		/// 
		/// 
		/// </summary>
		sf::Vector2f m_deployPosition;
		/// <summary>
		/// @brief Ai's AABB Collision Rectangle.
		/// 
		/// 
		/// </summary>
		tinyh::c2Circle m_collisionCircle;
		/// <summary>
		/// @brief Ai will be drawn on this quad.
		/// 
		/// Represents a size defined quad that a texture
		/// will be drawn on, frame animations will be targeted to this quad.
		/// </summary>
		sf::Sprite m_renderQuad;
		/// <summary>
		/// @brief Ai will use this to animate the AiRanged::m_renderQuad.
		/// 
		/// Represents the thor animator that will play a spritesheet
		/// animation on the render quad.
		/// </summary>
		thor::Animator<sf::Sprite, std::string> m_animator;
		/// <summary>
		/// @brief Defines the area that is on-screen.
		/// 
		/// 
		/// </summary>
		sf::IntRect m_onScreenRect;
		/// <summary>
		/// @brief Describes list of shared pointers to basic states.
		/// 
		/// Follows the principle of a Finite State Machine,
		/// where we instead of switch case'ing through a lot of
		/// different states we instead hold a pointer to the
		/// current state and merely assign/dereference it.
		/// In this case this is a stack of all the current
		/// states that this finite state machine is in.
		/// Allows for the Finite State Machine to remember
		/// the previous state that it was in by 
		/// push'ing/pop'ing from the stack.
		/// </summary>
		std::stack<std::shared_ptr<states::AiRangedState>> m_stateStack;
		/// <summary>
		/// @brief shared pointer to our currently active state.
		/// 
		/// Following the principle of the Finite State Machine
		/// Design pattern this represents the pointer to
		/// the current state.
		/// </summary>
		std::shared_ptr<states::AiRangedState> m_sptrState;
		/// <summary>
		/// @brief shared pointer to our resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<ai::Resources> m_sptrResources;
		/// <summary>
		/// @brief Defines the manager of the collection of bullets.
		/// 
		/// Bullets can be active or innactive.
		/// </summary>
		AiBulletManager m_bulletManager;

		/// <summary>
		/// @brief define offset on the y axis about which the health bar will be.
		/// 
		/// 
		/// </summary>
		float m_healthbarOffstet;

		/// <summary>
		/// @brief starting width of the health bar.
		/// 
		/// 
		/// </summary>
		float m_healthBarStartWidth;
	};
}

#include "AiRangedState.h"
#include "entities\ai\ranged\ARMoveState.h"
#include "entities\ai\ranged\ARDeployState.h"
#include "entities\ai\ranged\ARShootState.h"
#include "entities\ai\ranged\ARDeathState.h"

#endif // !AI_RANGED_H