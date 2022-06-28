#include <windows.h>

#define MAX_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)

	WCHAR	WindowClass[MAX_NAME_STRING];
	WCHAR	WindowTitle[MAX_NAME_STRING];

	INT	WindowWidth;
	INT WindowHeight;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	/* Initialize global variables */

		wcscpy_s(WindowClass, TEXT("Introduction")); // allows character in wide char class
		wcscpy_s(WindowTitle, TEXT("Jiralhanae Engine")); // display title on window
		// default window size to 1440*900
		WindowWidth = 1400;
		WindowHeight = 900;

	/* Create a window class */
		WNDCLASSEX wcex{}; 

		wcex.cbSize = sizeof(WNDCLASSEX); // initialize the window
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.cbClsExtra = 0; // add extra memory at runtime
		wcex.cbWndExtra = 0;

		

		// load and draw the mouse pointer
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

		// give the window a white background color
		wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

		// load icon
		wcex.hIcon = LoadIcon(0, IDI_APPLICATION); // main icon on window
		wcex.hIconSm = LoadIcon(0, IDI_APPLICATION); // icon located on taskbar

		wcex.lpszClassName = WindowClass;

		wcex.lpszMenuName = nullptr;

		wcex.hInstance = HInstance();
		wcex.lpfnWndProc = DefWindowProc; // how the window will perform

		RegisterClassEx(&wcex);


	/* Display a window */
		HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);
		// prevent application from crashing if window cannot be shwon
		if (!hWnd) {
			MessageBox(0, L"Unable to create window. Click on OK to terminate application", 0, 0);
			return 0;
		}


		ShowWindow(hWnd, SW_SHOW); // actually show window

	/* Listen for message events */
		MSG msg = { 0 };
		while (msg.message != WM_QUIT) {
			// process any window messages if they exist
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	
	return 0;
}