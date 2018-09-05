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
	WndClass.cbWndExtra = 0;//통산 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//미리만들어놓은 브러쉬 가져옴
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;//프로시저 받아옴 메세지 재정의를 모아놓은 함수
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우 스타일

	RegisterClass(&WndClass);//os에 윈도우 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		200, 200, 1000, 430,
		NULL, (HMENU)NULL, hInstance, NULL);
	//CW_ ->x y wid hei
	//부모윈도우, idset, instand, NULL

	ShowWindow(hWnd, nCmdShow);//한번 그려옴

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);//메세지 번역 큐에서 가져와서 번역 파생처리
		DispatchMessage(&Message);//윈도우 프로시저가 콜 됨
	}

	return (int)Message.wParam;
}

GameManager GM;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//핸들, 어떤메세지, 부가정보1, 부가정보2
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
		PostQuitMessage(0);//큐에 나간다는메세지 적재
		GM.ReleaseGameManager();
		PostQuitMessage(0);//큐에 나간다는메세지 적재
		return 0;
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));//기본 메세지처리..
}