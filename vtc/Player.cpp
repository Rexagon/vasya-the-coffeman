#include "Player.h"

#include "Core.h"

Player::Player(const std::string & spritesheet) :
	m_speed(25.0f), m_vector(0.0f, 0.0f), m_isJumping(false), m_isHitting(false)
{
	AssetManager::Bind("player_texture", TextureFactory("player.png"));
	m_spritesheet = AssetManager::Get<sf::Texture>("player_texture");

	m_animationWalk.SetSpriteSheet(m_spritesheet);
	m_animationWalk.SetFrameDuration(0.083f);
	m_animationWalk.SetLooped(true);
	m_animationWalk.AddFrame(0, 0, 16, 32);
	m_animationWalk.AddFrame(16, 0, 16, 32);
	m_animationWalk.AddFrame(32, 0, 16, 32);
	m_animationWalk.AddFrame(48, 0, 16, 32);
	m_animationWalk.AddFrame(64, 0, 16, 32);
	m_animationWalk.AddFrame(80, 0, 16, 32);
	m_animationWalk.AddFrame(96, 0, 16, 32);
	m_animationWalk.AddFrame(112, 0, 16, 32);

	m_animationJump.SetSpriteSheet(m_spritesheet);
	m_animationJump.SetFrameDuration(0.083f);
	m_animationJump.SetLooped(false);
	m_animationJump.AddFrame(0, 32, 16, 32);
	m_animationJump.AddFrame(16, 32, 16, 32);
	m_animationJump.AddFrame(32, 32, 16, 32);
	m_animationJump.AddFrame(48, 32, 16, 32);
	m_animationJump.AddFrame(64, 32, 16, 32);
	m_animationJump.AddFrame(80, 32, 16, 32);
	m_animationJump.AddFrame(96, 32, 16, 32);
	m_animationJump.AddFrame(112, 32, 16, 32);

	m_animationHit.SetSpriteSheet(m_spritesheet);
	m_animationHit.SetFrameDuration(0.03f);
	m_animationHit.SetLooped(false);
	m_animationHit.AddFrame(0, 64, 16, 32);
	m_animationHit.AddFrame(16, 64, 16, 32);
	m_animationHit.AddFrame(32, 64, 16, 32);
	m_animationHit.AddFrame(48, 64, 16, 32);
	m_animationHit.AddFrame(64, 64, 16, 32);
	m_animationHit.AddFrame(80, 64, 16, 32);
	m_animationHit.AddFrame(96, 64, 16, 32);
	m_animationHit.AddFrame(112, 64, 16, 32);

	m_sprite.SetAnimation(m_animationWalk);
}

void Player::Update(const float dt)
{
	if (m_sprite.GetAnimation()->IsEnded()) {
		m_sprite.SetAnimation(m_animationWalk);
		m_isJumping = false;
		m_isHitting = false;
	}

	m_sprite.Update(dt);
	m_sprite.SetPosition(m_sprite.GetPosition() + m_vector * m_speed * dt);
}

void Player::Move(const vec2& vector)
{
	if (!m_isHitting && !m_isJumping) {
		if (vector.x == 0.0f && vector.y == 0.0f) {
			m_sprite.GetAnimation()->Stop();
		}
		else {
			m_sprite.MirrorVertically(vector.x < 0.0f);
			m_sprite.GetAnimation()->Play();
		}

		m_vector = vector;
	}
}

void Player::Stop()
{
	m_sprite.GetAnimation()->Stop();
	m_vector = vec2(0.0f, 0.0f);
}

void Player::Jump()
{
	if (m_isJumping) return;
	m_sprite.SetAnimation(m_animationJump);
	m_sprite.GetAnimation()->Play();
	m_vector = vec2(0.0f, 0.0f);
	m_isJumping = true;
}

void Player::Hit()
{
	if (m_isHitting) return;
	m_sprite.SetAnimation(m_animationHit);
	m_sprite.GetAnimation()->Play();
	m_vector = vec2(0.0f, 0.0f);
	m_isHitting = true;
}

void Player::SetSpeed(float speed)
{
	m_speed = speed;
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Core::Draw(m_sprite);
}
