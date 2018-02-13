#include "Entities\Player\Ship.h"


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Ship::Ship()
	: m_UPDATE_DT(App::getUpdateDeltaTime())
	, m_shipRect()
	, m_speed(4.0f)
	, m_position(sf::Vector2f(100.0f, 400.0f))
	, m_shipFrames(nullptr)
	, m_texture(nullptr)
	, m_currentFrame(0.0f)
	, m_FRAME_CHANGE(40.0f)
	, m_FRAME_STILL(nullptr)
	, m_ID("ship")
	, m_pressed()
	, m_velocity(sf::Vector2f(0.0f,0.0f))
	, m_accelerationRate(7.0f * 60.0f)
	, m_directionVec(0.0f,0.0f)
	, m_moveDir(0.0f,0.0f)
	, m_acceleration(10.0f)
{
	m_shipRect.setPosition(m_position);
	m_shipRect.setSize(sf::Vector2f(75.0f, 100.0f));
	m_shipRect.setOrigin(m_shipRect.getSize().x / 2, m_shipRect.getSize().y / 2);
}

/// <summary>
/// @brief Initializes the ships internal animators and textures.
/// 
/// 
/// </summary>
/// <param name="resources">defines reference to ship resources.</param>
void Ship::init(std::shared_ptr<Resources> resources)
{
	if (nullptr == m_texture)
	{
		this->setTexture(resources->m_sptrTexture);
		m_shipRect.setTexture(m_texture.get(), true);
	}
	if (nullptr == m_shipFrames)
	{
		this->setFrames(std::move(resources->m_uptrFrames));
		m_FRAME_STILL = std::make_unique<const float>(m_shipFrames->size() / 2.0f);
		m_currentFrame = *m_FRAME_STILL;
	}
}

/// <summary>
/// @brief update position.
/// 
/// 
/// </summary>
void Ship::update()
{
	auto dt = App::getUpdateDeltaTime();

	if (thor::length(m_directionVec) != 0)
	{
		m_moveDir = thor::unitVector(m_directionVec);
		if (thor::length(m_velocity) < m_maxVel)
		{
			m_velocity += m_moveDir * m_acceleration;
		}
	}


	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_velocity *= 0.98f;
	
	processInput(m_pressed);
	m_shipRect.setPosition(m_position);

	checkOffScreen();

}

/// <summary>
/// @brief Defines what direction we want the ship to move in.
/// 
/// 
/// </summary>
/// <param name="direction">defines the direction</param>
/// <param name="state">defines the state on whether or not we want to go or stop going in that direction</param>
void Ship::move(const Direction & direction, const bool& state)
{
	switch (direction)
	{
	case Direction::Up:
		m_pressed.m_up = state;
		break;
	case Direction::Down:
		m_pressed.m_down = state;
		break;
	case Direction::Left:
		m_pressed.m_left = state;
		break;
	case Direction::Right:
		m_pressed.m_right = state;
		break;
	default:
		break;
	}
}


/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Ship::draw(Window & window, const float & deltaTime)
{
	m_shipRect.setTextureRect(m_shipFrames->at(static_cast<int>(m_currentFrame)));
	window.draw(m_shipRect);
}

/// <summary>
/// @brief Where ship processes input.
/// 
/// 
/// </summary>
/// <param name="keysPressed">defines the struct of pressed keys.</param>
void Ship::processInput(const KeysPressed & keysPressed)
{
	// Defines the offset from the center frame.
	const float OFFSET = 0.5f;

	if (keysPressed.m_left)
	{
		m_directionVec.x = -1;
		if (m_currentFrame > (*m_FRAME_STILL) + OFFSET)
		{
			decFrame();
			decFrame();
			decFrame();
			decFrame();
		}
		else
		{
			decFrame();
		}
	}
	else if (!keysPressed.m_right)
	{
		m_directionVec.x = 0;
		if (m_currentFrame < (*m_FRAME_STILL) - OFFSET)
		{
			incFrame();
			incFrame();
		}
		else if (m_currentFrame < (*m_FRAME_STILL) + OFFSET)
		{
			m_currentFrame = *m_FRAME_STILL;
		}
	}
	if (keysPressed.m_right)
	{
		m_directionVec.x = 1;
		if (m_currentFrame < (*m_FRAME_STILL) - OFFSET)
		{
			incFrame();
			incFrame();
			incFrame();
			incFrame();
		}
		else
		{
			incFrame();
		}
	}
	else if (!keysPressed.m_left)
	{
		m_directionVec.x = 0;
		if (m_currentFrame > (*m_FRAME_STILL) + OFFSET)
		{
			decFrame();
			decFrame();
		}
		else if (m_currentFrame > (*m_FRAME_STILL) - OFFSET)
		{
			m_currentFrame = *m_FRAME_STILL;
		}
	}
	if (keysPressed.m_up)
	{
		m_directionVec.y = -1;
	}
	else if (!keysPressed.m_down)
	{
		m_directionVec.y = 0;
	}
	if (keysPressed.m_down)
	{
		m_directionVec.y = 1;
	}
	else if (!keysPressed.m_up)
	{
		m_directionVec.y = 0;
	}
}

/// <summary>
/// @brief Decrements current frame.
/// 
/// 
/// </summary>
void Ship::decFrame()
{
	m_currentFrame -= m_FRAME_CHANGE * m_UPDATE_DT;
	if (m_currentFrame < 0.0f)
	{
		m_currentFrame = 0.0f;
	}
}

/// <summary>
/// @brief Increments current frame.
/// 
/// 
/// </summary>
void Ship::incFrame()
{
	m_currentFrame += m_FRAME_CHANGE * m_UPDATE_DT;
	if (m_currentFrame > m_shipFrames->size())
	{
		m_currentFrame = static_cast<float>(m_shipFrames->size() - 1);
	}
}

/// <summary>
/// @brief return the position of the ship rectangle.
/// 
/// 
/// </summary>
/// <returns>returns the ship rectangles position</returns>
const sf::RectangleShape & Ship::getShipRect() const
{
	return m_shipRect;
}

/// <summary>
/// @brief Sets the current ship texture to the sptrTexture.
/// 
/// Stores a shared pointer to this texture.
/// </summary>
/// <param name="sptrTexture">shared pointer to a initialized texture</param>
void Ship::setTexture(std::shared_ptr<sf::Texture> sptrTexture)
{
	m_texture = sptrTexture;
}

/// <summary>
/// @brief Sets the current animator to the uptrAnimator.
/// 
/// @warning uptrAnimator is set to nullptr after this function call.
/// </summary>
/// <param name="uptrShipFrames">unique pointer to a animator.</param>
void Ship::setFrames(std::unique_ptr<ShipFrames> uptrShipFrames)
{
	m_shipFrames.swap(uptrShipFrames);
	std::unique_ptr<ShipFrames>(nullptr).swap(uptrShipFrames);
}

/// <summary>
/// @brief This is a function that will check if player has gone off the screen.
/// 
/// 
/// </summary>
void Ship::checkOffScreen()
{
	tinyh::c2AABB screenSize = App::getViewC2Rect(); // get the screen view rectangle.
	auto shipRect = m_shipRect.getLocalBounds(); //get the ship rectangle in local bounds.
	if (m_position.x + shipRect.width > screenSize.max.x) //if ship is going off the right side of the screen set them back
	{
		m_position.x = screenSize.max.x - shipRect.width;
	}
	if (m_position.x - shipRect.width < 0) //if ship is going off the left side of the screen set them back
	{
		m_position.x = 0 + shipRect.width;
	}
	if (m_position.y + (shipRect.height / 2) > screenSize.max.y) //if ship is going off the bottom of the screen set them back
	{
		m_position.y = screenSize.max.y - (shipRect.height / 2);
	}
	if (m_position.y - (shipRect.height / 2) < 0) //if ship is going off the top of the screen set them back
	{
		m_position.y = 0 + (shipRect.height / 2);
	}
}


