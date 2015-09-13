#include <Windows.h>

#if 0

//Pop-up window
int CALLBACK
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MessageBoxA(0, "This is a pop-up window", "Pop-up window",
		MB_OK | MB_ICONINFORMATION);

	return (0);
}

#endif