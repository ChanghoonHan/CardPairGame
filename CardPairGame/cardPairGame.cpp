#include <Windows.h>
#include "GameManager.h"
#include <time.h>
#include "Card.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char lpszClass[256] = "First";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstace,
	LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;//��� 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//�̸��������� �귯�� ������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;//���ν��� �޾ƿ� �޼��� �����Ǹ� ��Ƴ��� �Լ�
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//������ ��Ÿ��

	RegisterClass(&WndClass);//os�� ������ ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		200, 200, 1000, 430,
		NULL, (HMENU)NULL, hInstance, NULL);
	//CW_ ->x y wid hei
	//�θ�������, idset, instand, NULL

	ShowWindow(hWnd, nCmdShow);//�ѹ� �׷���

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);//�޼��� ���� ť���� �����ͼ� ���� �Ļ�ó��
		DispatchMessage(&Message);//������ ���ν����� �� ��
	}

	return (int)Message.wParam;
}

GameManager GM;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//�ڵ�, ��޼���, �ΰ�����1, �ΰ�����2
{
	HDC hdc;
	PAINTSTRUCT ps;
	bool isFilpedTwoCard = false;

	switch (iMessage)
	{
	case WM_CREATE:
		hdc = GetDC(hWnd);
		GM.InitGameManager(hdc, g_hInst);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_LBUTTONDOWN:
		isFilpedTwoCard = GM.OperatorInput(lParam);

		InvalidateRect(hWnd, NULL, TRUE);

		if (isFilpedTwoCard)
		{
			SetTimer(hWnd, 1, 500, NULL);
		}
	
		return 0;

	case WM_TIMER:
		GM.CheckCorrect();
		InvalidateRect(hWnd, NULL, TRUE);
		KillTimer(hWnd, 1);
		return 0;

	case WM_PAINT:	
		hdc = BeginPaint(hWnd, &ps);
		GM.Draw(hdc);	
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);//ť�� �����ٴ¸޼��� ����
		GM.ReleaseGameManager();
		PostQuitMessage(0);//ť�� �����ٴ¸޼��� ����
		return 0;
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));//�⺻ �޼���ó��..
}