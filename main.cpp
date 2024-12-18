#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

int main() {
	HINSTANCE hInstance = GetModuleHandle(NULL);

	const wchar_t* CLASS_NAME = L"WindowClass";
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"First Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL) {
		return 0;
	}

	CreateWindow(
		L"BUTTON",
		L"Button 1", //Button text
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		0, 0, 100, 30, //Positioning of button x,y and width, height
		hwnd, //Parent window
		(HMENU)1, //Button Id for use in WindowProc to determine which button was pressed
		hInstance,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Button 2", //Button text
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		0, 30, 100, 30, //Positioning of button x,y and width, height
		hwnd, //Parent window
		(HMENU)2, //Button Id for use in WindowProc to determine which button was pressed
		hInstance,
		NULL
	);

	ShowWindow(hwnd, SW_SHOW);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}