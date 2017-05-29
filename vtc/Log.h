#pragma once

#include <iostream>
#include <fstream>
#include <time.h>

class Log
{
public:
	enum class Targets
	{
		FILE,
		CONSOLE,
		ALL
	};

	// ������ ���� ��� ������ �����
	//@ ���� ����� ���� ���, �� ��������������
	static void Create(const std::string& path = "log.txt", Targets target = Targets::ALL);

	// ������� ���� � ��������� � ��� ����� ������. ����� ���������� - ������� ������
	template<class Arg, class... Args>
	static void Write(Arg&& arg, Args&&... args)
	{
		if (m_target == Targets::FILE || m_target == Targets::ALL) {
			WriteToStream(m_file, arg, args...);
		}
		if (m_target == Targets::CONSOLE || m_target == Targets::ALL) {
			WriteToStream(std::cout, arg, args...);
		}
	}
private:
	template<class Arg, class... Args>
	static void WriteToStream(std::ostream& out, Arg&& arg, Args&&... args)
	{
		out << GetDate() << std::forward<Arg>(arg);
		using dummy = int[];
		(void)dummy{0, (void(out << ' ' << std::forward<Args>(args)), 0)...};

		out << std::endl;
	}

	static const std::string GetDate();

	static std::ofstream m_file;
	static Targets m_target;
};