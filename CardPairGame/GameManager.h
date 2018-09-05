#pragma once
#include <Windows.h>
#include "resource.h"
#include "Card.h"

class GameManager
{
	Card m_card[16];
	int m_cardNumCollection[16];
	int m_clickedCardIdx[2];
	int m_clickedCardCount;
	HDC g_hMemDC, g_hMemDC2;
	HBITMAP g_hCardBitMap[9];
	HBITMAP g_hOldBitMap;

public:
	void InitCardNumCollection();
	void InitGameManager(HDC& hdc, HINSTANCE& g_hInst);
	void InitCard();
	void ReleaseGameManager();
	bool OperatorInput(LPARAM lParam);
	void Update() {};
	void Draw(HDC& hdc);
	void CheckCorrect();
	GameManager();
	~GameManager();
};

