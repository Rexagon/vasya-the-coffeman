#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.h"

class Sprite : public sf::Drawable
{
public:
	Sprite(sf::Texture* texture = nullptr, const recti& rectangle = recti());

	void Update(const float dt);

	void SetAnimation(const Animation& animation);
	Animation* GetAnimation();

	void MirrorHorizontally(bool mirror);
	void MirrorVertically(bool mirror);

	void SetOrigin(float x, float y);
	void SetOrigin(const vec2& origin);
	vec2 GetOrigin() const;

	void SetPosition(float x, float y);
	void SetPosition(const vec2& position);
	vec2 GetPosition() const;

	void SetRotation(float angle);
	float GetRotation() const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite m_sprite;
	Animation m_animation;

	bool m_mirrorHorizontally;
	bool m_mirrorVertically;
};