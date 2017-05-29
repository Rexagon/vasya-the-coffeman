#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Math.h"

using Key = sf::Keyboard::Key;
using Mouse = sf::Mouse::Button;

class Input
{
public:
	// ��������� ��������� ������
	static void Update();

	// ������ �� ������� � ������� ������
	static bool GetKey(sf::Keyboard::Key keyCode);

	// ��������� �� ������� ������� � ���� �����
	static bool GetKeyDown(sf::Keyboard::Key keyCode);

	// ��������� �� ������� � ���� �����
	static bool GetKeyUp(sf::Keyboard::Key keyCode);


	// ������ �� ������ ���� � ������� ������
	static bool GetMouse(sf::Mouse::Button button);

	// ��������� �� ������� ������ ���� � ���� �����
	static bool GetMouseDown(sf::Mouse::Button button);

	// ��������� �� ������ ���� � ���� �����
	static bool GetMouseUp(sf::Mouse::Button button);

	// ������� ������� ������������ ������ �������� ���� ����
	static vec2 GetMousePosition();
private:
	friend class Core;

	static const int NUM_KEYS;
	static const int NUM_MOUSEBUTTONS;

	static vec2 m_mousePosition;

	static std::vector<bool> m_currentKeysState;
	static std::vector<bool> m_lastKeysState;

	static std::vector<bool> m_currentMouseButtonsState;
	static std::vector<bool> m_lastMouseButtonsState;
};