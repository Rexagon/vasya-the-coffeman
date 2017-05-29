#include "Core.h"

bool Core::m_isRunning = false;
sf::RenderWindow Core::m_window;
std::stack<std::unique_ptr<State>> Core::m_states;

void Core::Init()
{
	m_isRunning = false;

	m_window.create(sf::VideoMode(800, 600), "Vasya the coffeman");
	m_window.setVerticalSyncEnabled(true);
}

void Core::Close()
{
	while (!m_states.empty()) {
		DeleteState();
	}
	m_window.close();
}

void Core::Run()
{
	m_isRunning = true;

	sf::Clock timer;
	while (m_isRunning && !m_states.empty())
	{
		HandleInput();

		float dt = timer.restart().asSeconds();

		State* currentState = nullptr;
		if (currentState = GetState()) {
			currentState->Update(dt);
		}

		m_window.clear(sf::Color(92, 141, 137));

		if (currentState = GetState()) {
			currentState->Draw(dt);
		}

		m_window.display();
	}
}

void Core::Stop()
{
	m_isRunning = false;

	AssetManager::Clear();
}

void Core::Draw(const sf::Drawable & drawable, const sf::RenderStates& states)
{
	m_window.draw(drawable, states);
}

void Core::HandleInput()
{
	Input::Update();

	sf::Event e;

	while (m_window.pollEvent(e)) {
		int value = 0;
		State* currentState = GetState();

		switch (e.type) {
		case sf::Event::Closed:
			Core::Stop();
			break;
		case sf::Event::GainedFocus:
			if (currentState) {
				currentState->FocusGained();
			}
			break;
		case sf::Event::LostFocus:
			if (currentState) {
				currentState->FocusLost();
			}
			break;
		case sf::Event::MouseMoved:
			Input::m_mousePosition = vec2(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y));
			break;
		case sf::Event::KeyPressed:
			if (e.key.code > -1 && e.key.code < sf::Keyboard::KeyCount) {
				Input::m_currentKeysState[e.key.code] = true;
			}
			break;
		case sf::Event::KeyReleased:
			if (e.key.code > -1 && e.key.code < sf::Keyboard::KeyCount) {
				Input::m_currentKeysState[e.key.code] = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button > -1 && e.mouseButton.button < sf::Mouse::ButtonCount) {
				Input::m_currentMouseButtonsState[e.mouseButton.button] = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button > -1 && e.mouseButton.button < sf::Mouse::ButtonCount) {
				Input::m_currentMouseButtonsState[e.mouseButton.button] = false;
			}
			break;
		default:
			break;
		}
	}
}
