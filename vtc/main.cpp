#include "Core.h"

int main()
{
	Core::Init();

	try {
		Core::AddState<StateLevel>();

		Core::Run();
	}
	catch (const std::exception& e) {
		Log::Write("ERROR: ", e.what());
	}

	Core::Close();

	return 0;
}