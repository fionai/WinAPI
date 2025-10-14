#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include"resource.h"
#include<stdio.h>
#include<string>
#include<cstring>
#include<sstream>
#include<iostream>

INT SimbNum = 0;
CHAR CurrentStr[64] = {};
DOUBLE num1 = 0, num2 = 0;
INT points = 0;
char operation = 'e';

CONST CHAR g_sz_CLASS_NAME1[] = "Calc";
CONST CHAR g_sz_CLASS_NAME2[] = "_CPU";
CONST CHAR g_sz_CLASS_NAME3[] = "_411";

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
std::string toString(double d);

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
	CHAR g_sz_CLASS_NAME[256];
	sprintf_s(g_sz_CLASS_NAME, "%s%s%s", g_sz_CLASS_NAME1, g_sz_CLASS_NAME2, g_sz_CLASS_NAME3);
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
	CONST INT SIZE = 64;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
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
				sz_digit[0] = digit++ + '0';
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL) * j,
					g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL) * i/3,
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_0 + digit-1),
					GetModuleHandle(NULL),
					NULL
				);
			}

		}
		CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			g_i_BUTTON_START_X, BUTTON_SHIFT_Y(3),
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU) IDC_BUTTON_0,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(2), BUTTON_SHIFT_Y(3),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			GetModuleHandle(NULL),
			NULL
		);
		CHAR operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			operation[0] = g_OPERATIONS[i];
			CreateWindowEx
			(
				NULL, "Button", operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				BUTTON_SHIFT_X(3),BUTTON_SHIFT_Y(3-i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
				hwnd,
				(HMENU)(IDC_BUTTON_PLUS+i),
				GetModuleHandle(NULL),
				NULL
			);
		}
		CreateWindowEx
		(
			NULL, "Button", "<--",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(0), 
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(1),
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_CLR,
			GetModuleHandle(NULL),
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			BUTTON_SHIFT_X(4), BUTTON_SHIFT_Y(2),
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_0:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_1:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_2:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_3:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_4:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_5:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_6:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_7:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_8:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_9:
		{
			CurrentStr[SimbNum++] = wParam % 10 + '0';
			CurrentStr[SimbNum] = 0;
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_POINT:
		{
			if (!points)
			{
				CurrentStr[SimbNum++] = '.';
				CurrentStr[SimbNum] = 0;
				points++;
				HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
				SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
			}
		}
		break;
		case IDC_BUTTON_PLUS:
		{
			switch (operation)
			{
			case 'e':
				num1 = atof(CurrentStr);
				break;
			case '+':
				num1 += atof(CurrentStr);
				break;
			case '-':
				num1 -= atof(CurrentStr);
				break;
			case '*':
				num1 *= atof(CurrentStr);
				break;
			case '/':
				if (atof(CurrentStr))
					num1 /= atof(CurrentStr);
				break;

			}
			operation = '+';
			CurrentStr[0] = 0;
			SimbNum = 0;
			points = 0;
		}
		break;
		case IDC_BUTTON_MINUS:
		{
			switch (operation)
			{
			case 'e':
				num1 = atof(CurrentStr);
				break;
			case '+':
				num1 += atof(CurrentStr);
				break;
			case '-':
				num1 -= atof(CurrentStr);
				break;
			case '*':
				num1 *= atof(CurrentStr);
				break;
			case '/':
				if (atof(CurrentStr))
					num1 /= atof(CurrentStr);
				break;
			}
			operation = '-';
			CurrentStr[0] = 0;
			SimbNum = 0;
			points = 0;
		}
		break;
		case IDC_BUTTON_ASTER:
		{
			switch (operation)
			{
			case 'e':
				num1 = atof(CurrentStr);
				break;
			case '+':
				num1 += atof(CurrentStr);
				break;
			case '-':
				num1 -= atof(CurrentStr);
				break;
			case '*':
				num1 *= atof(CurrentStr);
				break;
			case '/':
				if (atof(CurrentStr))
					num1 /= atof(CurrentStr);
				break;
			}
			operation = '*';
			CurrentStr[0] = 0;
			SimbNum = 0;
			points = 0;
		}
		break;
		case IDC_BUTTON_SLASH:
		{
			switch (operation)
			{
			case 'e':
				num1 = atof(CurrentStr);
				break;
			case '+':
				num1 += atof(CurrentStr);
				break;
			case '-':
				num1 -= atof(CurrentStr);
				break;
			case '*':
				num1 *= atof(CurrentStr);
				break;
			case '/':
				if (atof(CurrentStr))
					num1 /= atof(CurrentStr);
				break;
			}
			operation = '/';
			CurrentStr[0] = 0;
			SimbNum = 0;
			points = 0;
		}
		break;
		case IDC_BUTTON_CLR:
		{
			operation = 'e';
			CurrentStr[0] = 0;
			SimbNum = 0;
			points = 0;
			
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
		}
		break;
		case IDC_BUTTON_BSP:
		{
			if (SimbNum > 0)
			{

			if (CurrentStr[SimbNum - 1] == '.')
				points = 0;
			SimbNum--;
			CurrentStr[SimbNum] = 0;
			
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
			}
		}
		break;
		case IDC_BUTTON_EQUAL:
		{
			switch (operation)
			{
			case '+':
				num1 += atof(CurrentStr);
				operation = 'e';
				break;
			case '-':
				num1 -= atof(CurrentStr);
				operation = 'e';
				break;
			case '*':
				num1 *= atof(CurrentStr);
				break;
			case '/':
				if (atof(CurrentStr))
					num1 /= atof(CurrentStr);
				break;

			}
			std::string str = toString(num1);
			std::strcpy(CurrentStr, str.c_str());
			HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEditResult, WM_SETTEXT, SIZE, (LPARAM)CurrentStr);
			CurrentStr[0] = 0;
			SimbNum = 0;
			points = 0;
		}
		break;
		}
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


std::string toString(double d)
{
	std::ostringstream ss;
	ss << d;
	return ss.str();
}