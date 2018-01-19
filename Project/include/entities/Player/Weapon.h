#ifndef WEAPON_H
#define WEAPON_H

#include <memory>
#include "Window.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include "Thor\Animations.hpp"
#include "Bullets\BulletTypes.h"
#include "Bullets\Standard.h"
#include "Bullets\BulletTypes.h"
#include "Bullets\Empowered.h"
#include "Bullets\DeathOrb.h"
#include "Bullets\FireBlast.h"
#include "Bullets\HolySphere.h"
#include "Bullets\MagmaShot.h"
#include "Bullets\CometShot.h"
#include "Bullets\NapalmSphere.h"
#include "Bullets\NullWave.h"
#include "Bullets\StaticSphere.h"
#include "Bullets\PyroBlast.h"

///
/// @brief Weapon class.
/// @author Sebastian Kruzel
/// @author Rafael Plugge
/// 
/// Defines the weapon class.
/// This class will create the Weapon.
/// 
class Weapon
{
public:
	/// <summary>
	/// @brief defines the max number of weapons.
	/// 
	/// 
	/// </summary>
	static int const MAX_WEAPONS = 11;

	/// <summary>
	/// @brief Alias for thor::Animator.
	/// 
	/// Uses thor animator on sfml rectangle shape using the std::string as the key.
	/// </summary>
	typedef thor::Animator<sf::Sprite, std::string> WeaponAnimator;
	
	/// <summary>
	/// @brief Alias for the animation frames.
	/// 
	/// Uses thor frame animation to represent a animation stored frame-by-frame.
	/// </summary>
	typedef thor::FrameAnimation WeaponFrames;

	///
	/// @author Rafael Plugge
	/// @brief Determines the resources the weapon needs.
	///  
	/// 
	struct Resources
	{

		/// 
		/// @author Rafael Plugge
		/// @brief Determines a pair with the animation and its id.
		/// 
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
			std::shared_ptr<WeaponFrames> m_sptrFrames = nullptr;

			/// <summary>
			/// @brief Defines shared pointer to our animation's texture.
			/// 
			/// 
			/// </summary>
			std::shared_ptr<sf::Texture> m_sptrTexture = nullptr;
		};

		/// <summary>
		/// @brief Define alias for animation container.
		/// 
		/// 
		/// </summary>
		typedef std::pair<std::unique_ptr<Animation>, std::unique_ptr<Animation>> WeaponAnimation;
		
		/// <summary>
		/// @brief Defines vector of unique pointers to our weapon animations.
		/// 
		/// 
		/// </summary>
		std::vector<std::unique_ptr<WeaponAnimation>> m_weaponAnimations;
	};

public:
	Weapon(sf::Vector2f position = sf::Vector2f(0.0f, 0.0f), bool const & flipped = false);
	void init(std::shared_ptr<Resources> sptrResources);
	void draw(Window & window, const float & deltaTime);
	void update(const sf::Vector2f& pos);
	void setRectPos(sf::Vector2f pos);
	void setFlipped(bool const & flip);
	void shoot();
	void shoot(BulletTypes const & bulletType);
	const sf::Vector2f & getPosition();
	const BulletTypes & getBulletType();
	bool const getIsFlipped() const;
	void setType(BulletTypes const & bulletType);
	void setCanFire(bool const & canFire);
	bool const & getCanFire() const;
	std::string const & getBeginAnimationID() const;
private:
	/// <summary>
	/// @brief define the weapon rectangle.
	/// 
	/// 
	/// </summary>
	sf::Sprite m_weaponSprite;

	/// <summary>
	/// @brief hold the type of the current bullet.
	/// 
	/// 
	/// </summary>
	BulletTypes m_currentBullet;

	/// <summary>
	/// @brief defines position vector.
	/// 
	/// 
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// @brief defines shared pointer to weapon resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<Resources> m_resources;

	/// <summary>
	/// @brief defines unique pointer to a weapon animator.
	/// 
	/// Will contain all our weapon animations.
	/// </summary>
	std::unique_ptr<WeaponAnimator> m_animator;

	/// <summary>
	/// @brief define if weapon can fire.
	/// 
	/// 
	/// </summary>
	bool m_canFire;
};
#endif // !WEAPON_H