#ifndef AI_BULLET_MANAGER_H
#define AI_BULLET_MANAGER_H

// STD Includes
#include <vector>
#include <memory>
// Project Includes
#include "system\Window.h"
#include "entities\ai\ranged\bullets\AiBullet.h"
#include "..\AiResources.h"

/// 
/// @brief Will manage ai bullet instances.
/// @author Rafael Plugge
/// 
/// 
/// 
class AiBulletManager
{
public: // Constructors/Assignment Operators/Destructor
	AiBulletManager();
	AiBulletManager(AiBulletManager const &) = default;
	AiBulletManager(AiBulletManager &&) = default;

	AiBulletManager & operator=(AiBulletManager const &) = default;
	AiBulletManager & operator=(AiBulletManager &&) = default;

	~AiBulletManager() = default;

public: // Public Member Functions
	void init(std::shared_ptr<ai::Resources> sptrResources);
	void update();
	void draw(Window & window, float const & deltaTime);
	void shoot(sf::Vector2f const & position, sf::Vector2f const & direction);
	inline std::vector<AiBullet> & getBullets() { return m_bullets; }
public: // Public Member Variables
protected: // Protected Member Functions
protected: // Protected Member Variables
private: // Private Member Functions
private: // Private Member Variables
	/// <summary>
	/// @brief shared pointer to external resources.
	/// 
	/// 
	/// </summary>
	std::shared_ptr<ai::Resources> m_sptrResources;
	/// <summary>
	/// @brief Container of ai bullets.
	/// 
	/// 
	/// </summary>
	std::vector<AiBullet> m_bullets;
};

#endif // !AI_BULLET_MANAGER_H