#include "StateLevel.h"

#include "Core.h"

void StateLevel::Init()
{
	m_player = std::make_unique<Player>("player.png");

	m_view.reset(rect(0, 0, Core::GetWindow()->getSize().x, Core::GetWindow()->getSize().y));

	m_view.setViewport(sf::FloatRect(0.f, 0.f, 4.0f, 4.0f));

	Core::GetWindow()->setView(m_view);
}

void StateLevel::Close()
{
}

void StateLevel::Update(const float dt)
{
	if (Input::GetKeyDown(Key::Escape)) {
		Core::DeleteState();
		return;
	}

	vec2 vector(0.0f, 0.0f);
	if (Input::GetKey(Key::D)) {
		vector += vec2(1.0f, 0.0f);
	}

	if (Input::GetKey(Key::A)) {
		vector += vec2(-1.0f, 0.0f);
	}

	if (Input::GetKey(Key::W)) {
		vector += vec2(0.0f,-1.0f);
	}

	if (Input::GetKey(Key::S)) {
		vector += vec2(0.0f, 1.0f);
	}

	if (Input::GetMouseDown(Mouse::Left)) {
		m_player->Hit();
	}

	m_player->Move(vector);

	if (Input::GetKey(Key::Space)) {
		m_player->Jump();
	}

	

	m_player->Update(dt);
}

void StateLevel::Draw(const float dt)
{
	Core::Draw(*m_player);
}
