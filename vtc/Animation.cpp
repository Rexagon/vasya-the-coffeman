#include "Animation.h"

Animation::Animation() :
	m_spriteSheet(nullptr), m_isPaused(true), m_isLooped(false), m_isReversed(false),
	m_frameDuration(0.083f), m_frameTime(0.0f), m_currentFrame(0)
{
}

void Animation::Play()
{
	m_isPaused = false;
}

void Animation::Pause()
{
	m_isPaused = true;
}

void Animation::Stop()
{
	m_isPaused = true;
	SetFrame(0);
}

void Animation::SetReversed(bool reversed)
{
	m_isReversed = reversed;
}

bool Animation::IsReversed() const
{
	return m_isReversed;
}

void Animation::Update(const float dt)
{
	if (!m_isPaused) {
		m_frameTime += dt;

		if (m_frameTime >= m_frameDuration) {
			m_frameTime = std::fmod(m_frameTime, m_frameDuration);

			if (m_currentFrame + 1 < m_frames.size()) {
				m_currentFrame++;
			}
			else {
				m_currentFrame = 0;

				if (!m_isLooped) {
					m_isPaused = true;
				}
			}
		}
	}
}

void Animation::AddFrame(const recti & frame)
{
	m_frames.push_back(frame);
}

void Animation::AddFrame(int left, int top, int width, int height)
{
	m_frames.push_back(recti(left, top, width, height));
}

recti Animation::GetFrame() const
{
	int frame = m_currentFrame;
	if (m_isReversed) {
		frame = m_frames.size() - m_currentFrame - 1;
	}
	return m_frames[frame];
}

recti Animation::GetFrame(unsigned int i) const
{
	return m_frames[i];
}

unsigned int Animation::GetFrameCount() const
{
	return m_frames.size();
}

void Animation::SetFrame(unsigned int i)
{
	if (i < m_frames.size()) {
		m_currentFrame = i;
	}
	else {
		m_currentFrame = m_frames.size() - 1;
	}

	m_frameTime = 0.0f;
}

void Animation::SetLooped(bool looped)
{
	m_isLooped = looped;
}

bool Animation::IsLooped() const
{
	return m_isLooped;
}

bool Animation::IsEnded() const
{
	return m_currentFrame + 1 == m_frames.size();
}

void Animation::SetFrameDuration(float duration)
{
	m_frameDuration = duration;
}

float Animation::GetFrameDuration() const
{
	return m_frameDuration;
}

void Animation::SetSpriteSheet(sf::Texture * texture)
{
	m_spriteSheet = texture;
}

sf::Texture * Animation::GetSpriteSheet()
{
	return m_spriteSheet;
}

Animation & Animation::operator=(const Animation & animation)
{
	m_frames = animation.m_frames;
	m_spriteSheet = animation.m_spriteSheet;
	m_isPaused = true;
	m_isLooped = animation.m_isLooped;
	m_frameDuration = animation.m_frameDuration;
	m_frameTime = 0.0f;
	m_currentFrame = 0;

	return *this;
}
