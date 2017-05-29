#pragma once

#include <memory>
#include <stack>

#include "AssetManager.h"
#include "State.h"
#include "Input.h"
#include "Log.h"

// �����
#include "StateLevel.h"

class Core
{
public:
	// �������������� ���� � �������
	static void Init();

	// ������� ������� ����
	static void Close();

	// ��������� �������� ����
	static void Run();

	// ������������� �������� ����
	static void Stop();

	// ������ ������
	static void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	// ���������� ������ ���� ����
	static sf::RenderWindow* GetWindow() { return &m_window; }

	// ��������� ����� ���������
	template<class T, class... Args>
	static void AddState(Args&&... args)
	{
		static_assert(std::is_base_of<State, T>::value, "Core::AddState<T>() - T must be child of State");

		if (!m_states.empty()) {
			m_states.top()->Pause();
		}

		m_states.push(std::unique_ptr<T>(new T(std::forward<Args>(args)...)));
		m_states.top()->Init();
	}

	// ��������� ������� ��������� ������
	template<class T, class... Args>
	static void ChangeState(Args&&... args)
	{
		DeleteState();
		AddState<T>(std::forward(args)...);
	}

	// ������� ������� ���������
	static void DeleteState()
	{
		if (!m_states.empty()) {
			m_states.top()->Close();
			m_states.pop();
		}

		if (!m_states.empty()) {
			m_states.top()->Resume();
		}
	}

	// ���������� ������� ���������
	static State* GetState()
	{
		if (!m_states.empty()) {
			return m_states.top().get();
		}
		else {
			return nullptr;
		}
	}
private:
	static void HandleInput();

	static bool m_isRunning;
	static sf::RenderWindow m_window;
	static std::stack<std::unique_ptr<State>> m_states;
};