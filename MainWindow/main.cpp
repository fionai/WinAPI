#include <Windows.h>
#include"resource.h"

CONST CHAR g_sz_WND_CLASS_NAME[] = "My Window Class";

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass; //структура описывющаz класс окна
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0; 
	wClass.cbClsExtra = 0;

	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIcon =   (HICON)LoadImage(hInstance, "mount.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "yacht.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hCursor = (HCURSOR)LoadImage(hInstance, "Busy.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WND_CLASS_NAME;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	//сщздание окна
	int monX;
	monX = GetSystemMetrics(SM_CXSCREEN);
	int monY;
	monY = GetSystemMetrics(SM_CYSCREEN);

	char WindowTitle[500] = {};
	int WinTitLen = sizeof(g_sz_WND_CLASS_NAME)-1;
	for (int i = 0; i < sizeof(g_sz_WND_CLASS_NAME); i++)
		WindowTitle[i] = g_sz_WND_CLASS_NAME[i];
	WindowTitle[WinTitLen++] = ' ';
	int tmp;
	tmp = monX * 0.125;
	if (tmp < 10)
	{
		WindowTitle[WinTitLen++] = tmp + '0';
	}
	else if (tmp < 100)
	{
		WindowTitle[WinTitLen++] = tmp / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	else if (tmp < 1000)
	{
		WindowTitle[WinTitLen++] = tmp / 100 + '0';
		WindowTitle[WinTitLen++] = (tmp % 100) / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	WindowTitle[WinTitLen++] = ',';

	tmp = monY * 0.125;
	if (tmp < 10)
	{
		WindowTitle[WinTitLen++] = tmp + '0';
	}
	else if (tmp < 100)
	{
		WindowTitle[WinTitLen++] = tmp / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	else if (tmp < 1000)
	{
		WindowTitle[WinTitLen++] = tmp / 100 + '0';
		WindowTitle[WinTitLen++] = (tmp % 100) / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	WindowTitle[WinTitLen++] = ';';
	WindowTitle[WinTitLen++] = ' ';

	tmp = monX * 0.75;
	if (tmp < 10)
	{
		WindowTitle[WinTitLen++] = tmp + '0';
	}
	else if (tmp < 100)
	{
		WindowTitle[WinTitLen++] = tmp / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	else if (tmp < 1000)
	{
		WindowTitle[WinTitLen++] = tmp / 100 + '0';
		WindowTitle[WinTitLen++] = (tmp % 100) / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	else if (tmp < 10000)
	{
		WindowTitle[WinTitLen++] = tmp / 1000 + '0';
		WindowTitle[WinTitLen++] = (tmp % 1000) / 100 + '0';
		WindowTitle[WinTitLen++] = (tmp % 100) / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	WindowTitle[WinTitLen++] = ',';

	tmp = monY * 0.75;
	if (tmp < 10)
	{
		WindowTitle[WinTitLen++] = tmp + '0';
	}
	else if (tmp < 100)
	{
		WindowTitle[WinTitLen++] = tmp / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}
	else if (tmp < 1000)
	{
		WindowTitle[WinTitLen++] = tmp / 100 + '0';
		WindowTitle[WinTitLen++] = (tmp % 100) / 10 + '0';
		WindowTitle[WinTitLen++] = tmp % 10 + '0';
	}

	WindowTitle[WinTitLen] = 0;

		//LPSTR WindowTitle = (LPSTR)g_sz_WND_CLASS_NAME 

	HWND hwnd = CreateWindowEx
	(
		NULL,  //exStyles
		g_sz_WND_CLASS_NAME, //class name
		//g_sz_WND_CLASS_NAME, //window title
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		//CW_USEDEFAULT, CW_USEDEFAULT, //window position
		monX*0.125, monY*0.125,
		//CW_USEDEFAULT, CW_USEDEFAULT, //window size
		monX*0.75, monY*0.75,
		NULL, //parent window
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот статик текст создан при помощи ф-ии CreateWindowEx()",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			500, 25,
			hwnd,
			(HMENU)1000,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 45,
			500, 22, 
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Apply",
			WS_CHILD | WS_VISIBLE,
			430, 70,
			80, 32,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
		//WS_CHILD показ., что создаваемое окно является дочерним элтом интерфейса другого окна
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1002: 
		{
			MessageBox(hwnd, "Hi", "hi", MB_OK | MB_ICONINFORMATION);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);

			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(GetDlgItem(hwnd, 1002), WM_SETTEXT, 0, (LPARAM)sz_buffer);

		}
		}
			break;
	case WM_DESTROY:
	{
		//MessageBox(hwnd, "Лучше двери закройте", "La finita", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
		break;
	case WM_CLOSE:
	{
		//if (MessageBox(hwnd, "Вы точно хотите закрыть окно????????", "Правда правда?", MB_YESNO | MB_ICONQUESTION) == IDYES)
			SendMessage(hwnd, WM_DESTROY, 0, 0);
	}
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	return FALSE;
}