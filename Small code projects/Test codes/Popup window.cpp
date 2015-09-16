#if 0
#include <Windows.h>


//Pop-up window
int CALLBACK
WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int choice;

	while (true)
	{

		choice = MessageBoxA(0, "This is a pop-up window", "Pop-up window",
			MB_YESNO | MB_ICONINFORMATION);

		switch (choice)
		{
		case 6: //Yes
		{
			OutputDebugStringA("Yes");
		} break;

		case 7: //No
		{
			OutputDebugStringA("No");
		} break;

		default:
			OutputDebugStringA("Def");
		} break;
	}
	return(0);
}

#endif // 0
