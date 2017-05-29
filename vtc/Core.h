#pragma once

#include <memory>
#include <stack>

#include "AssetManager.h"
#include "State.h"
#include "Input.h"
#include "Log.h"

// Сцены
#include "StateLevel.h"

class Core
{
public:
	// Подготавливает ядро к запуску
	static void Init();

	// Очищает ресурсы ядра
	static void Close();

	// Запускает основной цикл
	static void Run();

	// Останавливает основной цикл
	static void Stop();

	// Рисует объект
	static void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);

	// Возвращает объект окна игры
	static sf::RenderWindow* GetWindow() { return &m_window; }

	// Добавляет новое состояние
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

	// Подменяет текущее состояние другим
	template<class T, class... Args>
	static void ChangeState(Args&&... args)
	{
		DeleteState();
		AddState<T>(std::forward(args)...);
	}

	// Удаляет текущее состояние
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

	// Возвращает текущее состояние
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