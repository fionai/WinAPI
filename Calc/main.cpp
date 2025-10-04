#include <Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

CONST INT SIZE2 = 10;
INT NUM1 = 0;
INT NUM2 = 0;
char OPERATION = 'e';
long long int RESULT = 0; 
CHAR sz_VIEW[SIZE2*2] = {};
CHAR sz_VIEW_REVERSE[SIZE2*2] = {};
INT SimbolsNum = 0;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, NULL);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
			break;
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_BUTTON0:
			{ 
				if (SimbolsNum < SIZE2-1)
				{
					sz_VIEW[SimbolsNum] = '0';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
//				MessageBox(hwnd, "Была нажата цифра 0", "Info", MB_OK | MB_ICONINFORMATION);
			}
			break;
			case IDC_BUTTON1:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '1';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON2:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '2';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON3:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '3';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON4:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '4';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON5:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '5';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON6:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '6';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON7:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '7';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON8:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '8';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			case IDC_BUTTON9:
			{
				if (SimbolsNum < SIZE2 - 1)
				{
					sz_VIEW[SimbolsNum] = '9';
					sz_VIEW[SimbolsNum + 1] = 0;
					SimbolsNum++;

					HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
					SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
				}
			}
			break;
			//case IDC_BUTTON_POINT:
			//	MessageBox(hwnd, "Была нажата точка", "Info", MB_OK | MB_ICONINFORMATION);
			//break;
			case IDC_BUTTON_DIV:
			{
				NUM1 = 0;
				INT DECIMAL = 1;
				//сохраняем первое число
				for (int i = 0; i < SimbolsNum; i++)
				{
					DECIMAL = 1;
					for (int j = 0; j < (SimbolsNum - i - 1); j++)
						DECIMAL *= 10;
					NUM1 += (sz_VIEW[i] - '0') * DECIMAL;
				}
				OPERATION = '/';
				//обнуляем строку для формирования нового числа
				SimbolsNum = 0;
				sz_VIEW[SimbolsNum] = 0;
			}
			break;
			case IDC_BUTTON_MUL:
			{
				NUM1 = 0;
				INT DECIMAL = 1;
				//сохраняем первое число
				for (int i = 0; i < SimbolsNum; i++)
				{
					DECIMAL = 1;
					for (int j = 0; j < (SimbolsNum - i - 1); j++)
						DECIMAL *= 10;
					NUM1 += (sz_VIEW[i] - '0') * DECIMAL;
				}
				OPERATION = '*';
				//обнуляем строку для формирования нового числа
				SimbolsNum = 0;
				sz_VIEW[SimbolsNum] = 0;
			}
			break;
			case IDC_BUTTON_PLUS:
			{
				NUM1 = 0;
				INT DECIMAL = 1;
				//сохраняем первое число
				for (int i = 0; i < SimbolsNum; i++)
				{
					DECIMAL = 1;
					for (int j = 0; j < (SimbolsNum - i - 1); j++)
						DECIMAL *= 10;
					NUM1 += (sz_VIEW[i] - '0') * DECIMAL;
				}
				OPERATION = '+';
				//обнуляем строку для формирования нового числа
				SimbolsNum = 0;
				sz_VIEW[SimbolsNum] = 0;
			}
			break;
			case IDC_BUTTON_MINUS:
			{
				NUM1 = 0;
				INT DECIMAL = 1;
				//сохраняем первое число
				for (int i = 0; i < SimbolsNum; i++)
				{
					DECIMAL = 1;
					for (int j = 0; j < (SimbolsNum - i - 1); j++)
						DECIMAL *= 10;
					NUM1 += (sz_VIEW[i] - '0') * DECIMAL;
				}
				OPERATION = '-';
				//обнуляем строку для формирования нового числа
				SimbolsNum = 0;
				sz_VIEW[SimbolsNum] = 0;
			}
			break;
			case IDC_BUTTON_EQUAL:
			{
				NUM2 = 0;
				INT DECIMAL = 1;
				//сохраняем первое число
				for (int i = 0; i < SimbolsNum; i++)
				{
					DECIMAL = 1;
					for (int j = 0; j < (SimbolsNum - i - 1); j++)
						DECIMAL *= 10;
					NUM2 += (sz_VIEW[i] - '0') * DECIMAL;
				}
				switch (OPERATION)
				{
				case '+': RESULT = NUM1 + NUM2;
					break;
				case '-': 		RESULT = NUM1 - NUM2;
					break;
				case '*': RESULT = NUM1 * NUM2;
					break;
				case '/': 
				{						
					if (NUM2)
						RESULT = NUM1 / NUM2;
					else
					{
						RESULT = 0;
						OPERATION = 'e';
					}
				}
					break;
				case 'e': RESULT = 0;
				}

				if (OPERATION == 'e')
				{
					SimbolsNum = 1;
					sz_VIEW[0] = 'e';
					sz_VIEW[1] = 0;
				}
				else if (!RESULT)
				{
					SimbolsNum = 1;
					sz_VIEW[0] = '0';
					sz_VIEW[1] = 0;
				}
				else if (RESULT < 0)
				{
					RESULT = -RESULT;
					sz_VIEW[0] = '-';
					SimbolsNum = 0;
					while (RESULT)
					{
						sz_VIEW_REVERSE[SimbolsNum] = RESULT % 10 + '0';
						RESULT /= 10;
						SimbolsNum++;
					}
					for (int i = 0; i < SimbolsNum; i++)
						sz_VIEW[i+1] = sz_VIEW_REVERSE[SimbolsNum - i - 1];
					sz_VIEW[SimbolsNum+1] = 0;
				}
				else
				{
					SimbolsNum = 0;
					while (RESULT)
					{
						sz_VIEW_REVERSE[SimbolsNum] = RESULT % 10 + '0';
						RESULT /= 10;
						SimbolsNum++;
					}
					for (int i = 0; i < SimbolsNum; i++)
						sz_VIEW[i] = sz_VIEW_REVERSE[SimbolsNum - i - 1];
					sz_VIEW[SimbolsNum] = 0;
				}

				HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
				SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);

				//после вывода результата обнуляем строку для дальнейшей работы
				SimbolsNum = 0;
				sz_VIEW[SimbolsNum] = 0;
				OPERATION = 'e';
			}
			break;
			case IDC_BUTTON_C:
			{
				SimbolsNum = 0;
				sz_VIEW[SimbolsNum] = 0;
				OPERATION = 'e';
				HWND hEditResult = GetDlgItem(hwnd, IDC_EDIT_RESULT);
				SendMessage(hEditResult, WM_SETTEXT, SIZE2, (LPARAM)sz_VIEW);
			}
			break;
			}
		}
			break;
		case WM_CLOSE:
			EndDialog(hwnd, 0);
			break;
	}
	return FALSE;
}