#include "StateLevel.h"

#include "Core.h"

void StateLevel::Init()
{
	AssetManager::Bind("walk", TextureFactory("walk.png"));
	AssetManager::Bind("jump", TextureFactory("jump.png"));
	AssetManager::Bind("hit", TextureFactory("hit.png"));

	Animation walking;
	walking.SetSpriteSheet(AssetManager::Get<sf::Texture>("hit"));
	walking.AddFrame(0, 0, 16, 32);
	walking.AddFrame(16, 0, 16, 32);
	walking.AddFrame(32, 0, 16, 32);
	walking.AddFrame(48, 0, 16, 32);
	walking.AddFrame(64, 0, 16, 32);
	walking.AddFrame(80, 0, 16, 32);
	walking.AddFrame(96, 0, 16, 32);
	walking.AddFrame(112, 0, 16, 32);
	walking.SetFrameDuration(0.05f);

	m_player = std::make_unique<Sprite>();
	m_player->SetAnimation(walking);
	m_player->SetPosition(100.0f, 100.0f);
}

void StateLevel::Close()
{
}

void StateLevel::Update(const float dt)
{
	if (Input::GetKeyDown(Key::Right)) {
		m_player->MirrorVertically(false);
		m_player->GetAnimation()->Play();
	}

	if (Input::GetKeyDown(Key::Left)) {
		m_player->MirrorVertically(true);
		m_player->GetAnimation()->Play();
	}

	m_player->Update(dt);
}

void StateLevel::Draw(const float dt)
{
	Core::Draw(*m_player);
}
