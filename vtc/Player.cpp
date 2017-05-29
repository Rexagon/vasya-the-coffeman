#include "Player.h"

#include "Core.h"

Player::Player(const std::string & spritesheet) :
	m_speed(20.0f), m_vector(0.0f, 0.0f)
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
	m_animationJump.AddFrame(0, 0, 16, 32);
	m_animationJump.AddFrame(16, 0, 16, 32);
	m_animationJump.AddFrame(32, 0, 16, 32);
	m_animationJump.AddFrame(48, 0, 16, 32);
	m_animationJump.AddFrame(64, 0, 16, 32);
	m_animationJump.AddFrame(80, 0, 16, 32);
	m_animationJump.AddFrame(96, 0, 16, 32);

	m_animationHit.SetSpriteSheet(m_spritesheet);
	m_animationHit.SetFrameDuration(0.083f);
	m_animationHit.SetLooped(false);
	m_animationHit.AddFrame(0, 0, 16, 32);
	m_animationHit.AddFrame(16, 0, 16, 32);
	m_animationHit.AddFrame(32, 0, 16, 32);
	m_animationHit.AddFrame(48, 0, 16, 32);
	m_animationHit.AddFrame(64, 0, 16, 32);
	m_animationHit.AddFrame(80, 0, 16, 32);
	m_animationHit.AddFrame(96, 0, 16, 32);
	m_animationHit.AddFrame(112, 0, 16, 32);

	m_sprite.SetAnimation(m_animationWalk);
}

void Player::Update(const float dt)
{
	m_sprite.Update(dt);
}

void Player::MoveRight()
{
	m_sprite.SetAnimation(m_animationWalk);
	m_sprite
}

void Player::MoveLeft()
{
}

void Player::Stop()
{

}

void Player::Jump()
{
}

void Player::Hit()
{
}

void Player::SetSpeed(float speed)
{
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	Core::Draw(m_sprite);
}
