#pragma once

#include <memory>

#include "State.h"
#include "Sprite.h"

class StateLevel : public State
{
public:
	void Init() override;
	void Close() override;

	void Update(const float dt) override;
	void Draw(const float dt) override;
private:
	std::unique_ptr<Sprite> m_player;
};