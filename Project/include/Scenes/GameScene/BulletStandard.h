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
	void update() override;
};
#endif // ! BULLETSTANDARD_H
