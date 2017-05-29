#pragma once

#include "Sprite.h"

class Player : public sf::Drawable
{
public:
	Player(const std::string& spritesheet);

	void Update(const float dt);

	void MoveRight();
	void MoveLeft();
	void Stop();

	void Jump();
	void Hit();

	void SetSpeed(float speed);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture* m_spritesheet;

	Sprite m_sprite;

	float m_speed;
	vec2 m_vector;

	Animation m_animationWalk;
	Animation m_animationJump;
	Animation m_animationHit;
};