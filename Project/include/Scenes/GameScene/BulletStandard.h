#ifndef  BULLETSTANDARD_H
#define BULLETSTANDARD_H

#include "Bullet.h"

///
/// @brief standard bullet class.
/// @author Sebastian Kruzel
/// 
/// Defines the standard bullet class.
/// A derived class from bullet.
/// 
class BulletStandard :
	public Bullet
{
public:
	BulletStandard();
	BulletStandard(sf::Vector2f position);
	static float getFireRate();
	void update() final override;

private:
	/// <summary>
	/// @brief define a static constant fire rate.
	/// 
	/// 
	/// </summary>
	static const float s_FIRE_RATE;
};
#endif // ! BULLETSTANDARD_H
