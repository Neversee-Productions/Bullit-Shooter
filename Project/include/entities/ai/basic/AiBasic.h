#ifndef AI_BASIC_H
#define AI_BASIC_H

// STL Includes
#include <list> // For std::list
#include <stack> // For std::stack
// SFML Includes
#include "SFML\Graphics\RectangleShape.hpp"
// Thor Includes
#include "Thor\Animations\Animator.hpp"
// Json Includes
#include "json\json.hpp"
// Project Includes
#include "system\ResourceHandler.h"
#include "entities\Entities.h"
#include "entities\ai\AiBase.h"


namespace ai
{
	// forward reference

	namespace states
	{
		class AiBasicState;
		class AiBasicSeekState;
		class AiBasicChargeState;
		class AiBasicWindupState;
		class AiBasicRecoverState;
	}

	/// 
	/// @author Rafael Plugge
	/// @brief Represents basic ai.
	/// 
	/// This will be basic ai, its natural behaviour,
	/// will be to
	///		approach the player
	///		windup for an attack
	///		attack
	///	repeat.
	/// 
	class AiBasic : public AiBase
	{
	public:

		/// 
		/// @author Rafael Plugge
		/// @brief Define the resources that basic ai needs.
		/// 
		/// 
		/// 
		struct Resources : public AiBase::Resources
		{
			AiBase::Resources::Texture m_textureSeek;
			AiBase::Resources::Texture m_textureWindup;
			AiBase::Resources::Texture m_textureCharge;
			AiBase::Resources::Texture m_textureRecover;
			AiBase::Resources::Texture m_textureDeath;

			AiBase::Resources::Animation m_animationSeek;
			AiBase::Resources::Animation m_animationWindup;
			AiBase::Resources::Animation m_animationCharge;
			AiBase::Resources::Animation m_animationRecover;
			AiBase::Resources::Animation m_animationDeath;
		};

	private:
		/// <summary>
		/// @brief Alias for Basic State.
		/// 
		/// Makes life easier
		/// </summary>
		typedef ai::states::AiBasicState BasicState;
		typedef ai::states::AiBasicSeekState SeekState;
		typedef ai::states::AiBasicChargeState ChargeState;
		typedef ai::states::AiBasicWindupState WindupState;
		typedef ai::states::AiBasicRecoverState RecoverState;

		// Friends

		friend class ai::states::AiBasicState;
		friend class ai::states::AiBasicSeekState;
		friend class ai::states::AiBasicChargeState;
		friend class ai::states::AiBasicWindupState;
		friend class ai::states::AiBasicRecoverState;

	public: // Constructors/Destructor
		AiBasic(Player const & player, sf::Vector2f const & position = { 0.0f, 0.0f });
		~AiBasic() = default;

	public: // Public Member Functions
		static void setup(std::shared_ptr<Resources> sptrResources, ResourceHandler & resourceHandler, js::json & basicEnemyParser);
		void init(std::shared_ptr<Resources> sptrResources);
		virtual void update() final override;
		virtual void draw(Window & window, float const & deltaTime) final override;
		virtual bool checkCollision(tinyh::c2Circle const & collision) const final override;
		virtual bool checkCollision(tinyh::c2AABB const & collision) const final override;
		virtual bool checkCollision(tinyh::c2Capsule const & collision) const final override;
		tinyh::c2AABB const & getCollisionAABB() const;
		void spawn(sf::Vector2f const & spawnPosition, sf::Vector2f const & spawnHeading);

	protected: // Protected Member Functions
		void setState(std::shared_ptr<SeekState> sptrState, bool rememberPrevious);
		void setState(std::shared_ptr<ChargeState> sptrState, bool rememberPrevious);
		void setState(std::shared_ptr<BasicState> sptrState, bool rememberPrevious);
		void updateHitbox(sf::RectangleShape const & box);

	protected: // Protected Member Variables

		/// <summary>
		/// @brief Describes the position of the ai.
		/// 
		/// ai position in the world.
		/// </summary>
		sf::Vector2f m_position;
		/// <summary>
		/// @brief Describes the speed of the ai.
		/// 
		/// Amount the ai moves in its heading.
		/// </summary>
		float m_speed;
		/// <summary>
		/// @brief Describes the heading of the ai.
		/// 
		/// Heading is the direction the ai is moving in.
		/// </summary>
		sf::Vector2f m_heading;
		/// <summary>
		/// @brief Describes the direction of the ai, in degrees.
		/// 
		/// This angle, in degrees, describes the direction the ai
		/// is facing.
		/// </summary>
		float m_angle;
		/// <summary>
		/// @brief Read-only reference to the player.
		/// 
		/// Needed for search for him and for attack aiming.
		/// </summary>
		Player const & m_player;
		/// <summary>
		/// @brief Ai's sfml collision shape.
		/// 
		/// Used for setting the collision rect.
		/// </summary>
		sf::RectangleShape m_collisionShape;
		/// <summary>
		/// @brief Ai has a AABB Rectangular collision.
		/// 
		/// Used for targeting the ai.
		/// </summary>
		tinyh::c2AABB m_collisionRect;
		/// <summary>
		/// @brief Ai will be drawn on this quad.
		/// 
		/// Represents a size defined quad that a texture
		/// will be drawn on, frame animations will be targeted to this quad.
		/// </summary>
		sf::RectangleShape m_renderQuad;
		/// <summary>
		/// @brief Ai will use this to animate the AiBasic::m_renderQuad.
		/// 
		/// Represents the thor animator that will play a spritesheet
		/// animation on the render quad.
		/// </summary>
		thor::Animator<sf::RectangleShape, std::string> m_animator;

	private: // Private Member Functions
		void initStates();
		void initRenderingQuad();
		void initAnimations();
		void setTexture(std::string const & id);
		void playAnimation(std::string const & id, bool const & loop = false);
		void stopAnimation();

	private: // Private Member Variables
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
		std::stack<std::shared_ptr<BasicState>> m_stateStack;

		/// <summary>
		/// @brief shared pointer to our currently active state.
		/// 
		/// Following the principle of the Finite State Machine
		/// Design pattern this represents the pointer to
		/// the current state.
		/// </summary>
		std::shared_ptr<BasicState> m_sptrState;

		/// <summary>
		/// @brief shared pointer to our resources.
		/// 
		/// 
		/// </summary>
		std::shared_ptr<Resources> m_sptrResources;

		/// <summary>
		/// @brief Static id of idle state.
		/// 
		/// Used to access the idle animation.
		/// </summary>
		static std::string s_SEEK_ID;

		/// <summary>
		/// @brief Static id of windup state.
		/// 
		/// Used to access the windup animation.
		/// </summary>
		static std::string s_WINDUP_ID;

		/// <summary>
		/// @brief Static id of charge state.
		/// 
		/// Used to access the charge animation.
		/// </summary>
		static std::string s_CHARGE_ID;

		/// <summary>
		/// @brief Static id of recover state.
		/// 
		/// Used to access the recover animation.
		/// </summary>
		static std::string s_RECOVER_ID;

		/// <summary>
		/// @brief Static id of death state.
		/// 
		/// Used to access the death animation.
		/// </summary>
		static std::string s_DEATH_ID;

		/// <summary>
		/// @brief Static defines whether to color in states.
		/// 
		/// If true than all the states will be colored onto
		/// the render quad of each ai.
		/// </summary>
		static bool const s_COLOR_STATES;

		/// <summary>
		/// @brief Static defines what all ai's max health.
		/// 
		/// 
		/// </summary>
		static float const s_MAX_HEALTH;

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

	/// <summary>
	/// @brief Alias for a basic enemy.
	/// 
	/// 
	/// </summary>
	typedef AiBasic Basic;

}

#include "AiBasicState.h"
#include "ABSeekState.h"
#include "ABChargeState.h"
#include "ABWindupState.h"
#include "ABRecoverState.h"

#endif // !AI_BASIC_H