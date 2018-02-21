#include "entities\ai\ranged\bullets\AiBullet.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
AiBullet::AiBullet(ai::Resources & resources)
	: m_resources(resources)
	, m_active(true)
	, m_UPDATE_DT(App::getUpdateDeltaTime())
	, m_position({ 0.0f, 0.0f })
	, m_heading({ 0.0f, -1.0f })
	, m_speed(600.0f)
	, m_angle(0.0f)
	, m_quad()
	, m_collisionShape()
	, m_c2Rect()
	, m_animator()
{
	m_quad.setScale(m_resources.m_textureEbola.m_scale);
	m_quad.setOrigin({
		m_resources.m_textureEbola.m_origin.x * m_resources.m_textureEbola.m_scale.x,
		m_resources.m_textureEbola.m_origin.y * m_resources.m_textureEbola.m_scale.y
	});
	m_quad.setTexture(*m_resources.m_textureEbola.m_sptrTexture, true);
	m_quad.setTextureRect(m_resources.m_textureEbola.m_textureRect);
	m_animator.addAnimation(
		m_resources.m_animationEbola.m_id,
		m_resources.m_animationEbola.m_frames,
		m_resources.m_animationEbola.m_duration
	);
	m_animator.playAnimation(m_resources.m_animationEbola.m_id, true);
}

/// <summary>
/// @brief Update the bullet's position.
/// 
/// 
/// </summary>
void AiBullet::update()
{
	m_position += m_heading * m_speed * m_UPDATE_DT;
	m_collisionShape.setPosition(m_position);
	m_collisionShape.setRotation(m_angle);
	this->updateHitbox(m_collisionShape.getGlobalBounds());
}

/// <summary>
/// @brief Render bullet
/// 
/// 
/// </summary>
/// <param name="window">reference to the target window.</param>
/// <param name="deltaTime">read-only reference to the time since last draw call.</param>
void AiBullet::draw(Window & window, float const & deltaTime)
{
	m_quad.setPosition(m_position);
	m_quad.setRotation(m_angle);
	m_animator.update(sf::seconds(deltaTime));
	m_animator.animate(m_quad);
	window.draw(m_collisionShape);
	window.draw(m_quad);
}

/// <summary>
/// @brief update the c2 collision hit box.
/// 
/// 
/// </summary>
/// <param name="newHitbox">read-only reference bounding box.</param>
void AiBullet::updateHitbox(sf::FloatRect const & newHitbox)
{
	m_c2Rect.min.x = newHitbox.left;
	m_c2Rect.min.y = newHitbox.top;
	m_c2Rect.max.x = newHitbox.left + newHitbox.width;
	m_c2Rect.max.y = newHitbox.top + newHitbox.height;
}
