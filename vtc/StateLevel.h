#pragma once

#include <memory>

#include "State.h"
#include "Player.h"

class StateLevel : public State
{
public:
	void Init() override;
	void Close() override;

	void Update(const float dt) override;
	void Draw(const float dt) override;
private:
	std::unique_ptr<Player> m_player;

	sf::View m_view;
};