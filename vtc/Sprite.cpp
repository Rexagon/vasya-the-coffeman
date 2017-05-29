#include "Sprite.h"

Sprite::Sprite(sf::Texture* texture, const recti & rectangle)
{
	m_animation.SetSpriteSheet(texture);
	m_animation.AddFrame(rectangle);
}

void Sprite::Update(const float dt)
{
	if (m_animation.GetFrameCount() > 0) {
		m_animation.Update(dt);

		if (m_animation.GetSpriteSheet() &&
			m_animation.GetSpriteSheet() != m_sprite.getTexture())
		{
			m_sprite.setTexture(*m_animation.GetSpriteSheet());
		}

		recti frame = m_animation.GetFrame();

		if (m_mirrorHorizontally) {
			frame.top += frame.height;
			frame.height = -frame.height;
		}
		if (m_mirrorVertically) {
			frame.left += frame.width;
			frame.width = -frame.width;
		}

		m_sprite.setTextureRect(frame);
	}
}

void Sprite::SetAnimation(const Animation & animation)
{
	m_animation = animation;
	m_sprite.setTexture(*m_animation.GetSpriteSheet());
}

Animation * Sprite::GetAnimation()
{
	return &m_animation;
}

void Sprite::MirrorHorizontally(bool mirror)
{
	m_mirrorHorizontally = mirror;
}

void Sprite::MirrorVertically(bool mirror)
{
	m_mirrorVertically = mirror;
}

void Sprite::SetOrigin(float x, float y)
{
	m_sprite.setOrigin(x, y);
}

void Sprite::SetOrigin(const vec2 & origin)
{
	m_sprite.setOrigin(origin);
}

vec2 Sprite::GetOrigin() const
{
	return m_sprite.getOrigin();
}

void Sprite::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}

void Sprite::SetPosition(const vec2 & position)
{
	m_sprite.setPosition(position);
}

vec2 Sprite::GetPosition() const
{
	return m_sprite.getPosition();
}

void Sprite::SetRotation(float angle)
{
	m_sprite.setRotation(angle);
}

float Sprite::GetRotation() const
{
	return m_sprite.getRotation();
}

void Sprite::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
