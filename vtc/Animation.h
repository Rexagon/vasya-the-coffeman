#pragma once

#include <vector>

#include <SFML/Graphics/Texture.hpp>

#include "Math.h"

class Animation
{
public:
	Animation();

	void Update(const float dt);

	void AddFrame(const recti& frame);
	void AddFrame(int left, int top, int width, int height);
	recti GetFrame() const;
	recti GetFrame(unsigned int i) const;
	unsigned int GetFrameCount() const;

	void SetFrame(unsigned int i);

	void Play();
	void Pause();
	void Stop();


	void SetLooped(bool looped);
	bool IsLooped() const;

	void SetReversed(bool reversed);
	bool IsReversed() const;

	bool IsEnded() const;

	void SetFrameDuration(float duration);
	float GetFrameDuration() const;

	void SetSpriteSheet(sf::Texture* texture);
	sf::Texture* GetSpriteSheet();

	Animation& operator=(const Animation& animation);
private:
	std::vector<recti> m_frames;
	sf::Texture* m_spriteSheet;

	bool m_isPaused;
	bool m_isLooped;
	bool m_isReversed;

	float m_frameDuration;
	float m_frameTime;

	unsigned int m_currentFrame;
};