
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <Windows.h>
#include"resource.h"
#include<float.h>

//CONST INT SIZE = 256;

CONST CHAR g_sz_CLASS_NAME[] = "Calc_CPU_411";

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;


CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 3;
CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;

CONST INT g_i_SCREEN_WIDTH = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5 - g_i_INTERVAL;
CONST INT g_i_SCREEN_HEIGHT = g_i_BUTTON_SIZE;

CONST INT g_i_BUTTON_START_X = g_i_START_X;
CONST INT g_i_BUTTON_START_Y = g_i_START_Y + g_i_SCREEN_HEIGHT + g_i_INTERVAL;

CONST CHAR g_OPERATIONS[] = "+-*/";
CONST INT g_i_OPERATIONS_START_X = g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;

#define BUTTON_SHIFT_X(shift) g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (shift)
#define BUTTON_SHIFT_Y(shift) g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * (shift)

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR plCmdLine, INT nCmdShow)
{
	//регистрация окна класса
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WndProc;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = g_sz_CLASS_NAME;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class reg fail", "", MB_OK | MB_ICONERROR);
		return 0;
	}

	//создание окна
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_CLASS_NAME,
		g_sz_CLASS_NAME,
		WS_OVERLAPPEDWINDOW-WS_THICKFRAME-WS_MAXIMIZEBOX ,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		g_i_SCREEN_WIDTH + 2 * g_i_START_X + 16,
		g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + 42,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window fail", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static double a = DBL_MIN;
	static double b = DBL_MIN;
	static INT operation = 0;
	static BOOL input = false;
	static BOOL input_operation = false;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HBITMAP hBitmap;
		//HINSTANCE hInstance;
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			10, 10,
			g_i_SCREEN_WIDTH, g_i_SCREEN_HEIGHT,
			hwnd,
			(HMENU)IDC_EDIT,
			GetModuleHandle(NULL),
			NULL
			);
		INT digit = 1;
		CHAR sz_digit[2] = "";
		for (int i = 6; i >= 0; i -= 3)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = digit + '0';
				hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_0+digit));
				CreateWindowEx
				(
					NULL, "Button", "",// sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * i/3,
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0 + digit),
					GetModuleHandle(NULL),
					NULL
				);
				SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0+digit), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

				digit++;
			}

		}
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_0));
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_BUTTON_START_X, BUTTON_SHIFT_Y(3),
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU) IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_0), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_PO));
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

		CHAR operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			operation[0] = g_OPERATIONS[i];
			hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_PL+i));
			CreateWindowEx
			(
				NULL, "Button", operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
				BUTTON_SHIFT_X(3),BUTTON_SHIFT_Y(3-i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS+i),
				GetModuleHandle(NULL),
				NULL
			);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS+i), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		}

		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_B));
		CreateWindowEx
		(
			NULL, "Button", "",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(0),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_C));
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(1),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLR), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);

		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BIT_EQ));
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
	}
		break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE] = {};
		CHAR sz_digit[2] = {};
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_display);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_9)
		{
			if (input_operation) 
				sz_display[0] = 0;
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + 48;
			if (strcmp(sz_display, "0"))
				strcat(sz_display, sz_digit);
			else
				strcpy(sz_display, sz_digit);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = TRUE;
			input_operation = FALSE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_POINT && strchr(sz_display, '.') == NULL)
		{
			
				strcat(sz_display, ".");
				SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
			
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			if (strlen(sz_display) == 1)
				sz_display[0] = '0';
			else 
				sz_display[strlen(sz_display) - 1] = 0;
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLR)
		{
			a = b = DBL_MIN;
			operation = 0;
			input = input_operation = FALSE;
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)"0");
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			//if (a == DBL_MIN)
			//	a = atof(sz_display);
			//else
			//	b = atof(sz_display);
			if (input)
			{
				(a == DBL_MIN ? a : b) = atof(sz_display);
				SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			}
			input = FALSE;
			if(input_operation)SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
			operation = LOWORD(wParam);
			input_operation = TRUE;
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL)
		{
			if (input) b = atof(sz_display);
			switch (operation)
			{
			case IDC_BUTTON_PLUS: a += b; break;
			case IDC_BUTTON_MINUS: a -= b; break;
			case IDC_BUTTON_ASTER: a *= b; break;
			case IDC_BUTTON_SLASH: a /= b; break;
			}
			input_operation = FALSE;
			input = FALSE;
			sprintf(sz_display, "%g", a);
			SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
	}
		break;
	case WM_KEYDOWN:
	{
		//CONST INT SIZE = 256;
		//CHAR sz_display[SIZE] = {};
		//CHAR sz_digit[2] = {};
		INT key;
		key = LOWORD(wParam);
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		//SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_display);
		if (LOWORD(wParam) >= 96 && LOWORD(wParam) <= 105)
			wParam -= 48;
		if (LOWORD(wParam) >= 48 && LOWORD(wParam) <= 57)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_0 + wParam - 48), 0);
		if (LOWORD(wParam) == 107)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
		if (LOWORD(wParam) == 189 || LOWORD(wParam) == 109)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
		if (LOWORD(wParam) == 106)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
		if (LOWORD(wParam) == 191 || LOWORD(wParam) == 111)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
		if (LOWORD(wParam) == 13 || LOWORD(wParam) == 187)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_EQUAL), 0);
		if (LOWORD(wParam) == 8 || LOWORD(wParam) == 46)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
		if (LOWORD(wParam) == 110 || LOWORD(wParam) == 190 || LOWORD(wParam) == 188)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
		if (LOWORD(wParam) == 67 || LOWORD(wParam) == 27)
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLR), 0);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		SendMessage(hwnd, WM_DESTROY, 0, 0);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}