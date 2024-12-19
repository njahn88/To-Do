#include <windows.h>

HBRUSH hStaticBrush;

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

	const wchar_t* TOP_BOX = L"TopBox";
	WNDCLASS tb = {};
	tb.lpfnWndProc = WindowProc;
	tb.hInstance = hInstance;
	tb.lpszClassName = TOP_BOX;
	tb.hbrBackground = CreateSolidBrush(RGB(0, 102, 204));

	RegisterClass(&tb);

	const wchar_t* CLASS_NAME = L"WindowClass";
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hbrBackground = CreateSolidBrush(RGB(135, 206, 250));

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

	HWND topbox = CreateWindowEx(
		0,
		TOP_BOX,
		NULL,
		WS_VISIBLE | WS_CHILD,
		0, 0, 400, 50,
		hwnd,
		NULL,
		hInstance,
		NULL

	);

	CreateWindow(
		L"STATIC",
		L"To Do",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		200, 25, 50, 50,
		topbox,
		NULL,
		hInstance,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Button 1", //Button text
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		0, 50, 100, 30, //Positioning of button x,y and width, height
		hwnd, //Parent window
		(HMENU)1, //Button Id for use in WindowProc to determine which button was pressed
		hInstance,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Button 2", //Button text
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		0, 80, 100, 30, //Positioning of button x,y and width, height
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