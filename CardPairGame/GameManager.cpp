#include "GameManager.h"

bool GameManager::OperatorInput(LPARAM lParam)
{
	if (m_clickedCardCount < 2)
	{
		int mousePosX = LOWORD(lParam);
		int mousePosY = HIWORD(lParam);
		int ClickedCardNum = 0;
		bool isClickedCard = false;

		for (size_t i = 0; i < 8; i++)
		{
			if (mousePosX >= 20 + (120 * i) && mousePosX <= 120 + (120 * i) &&
				mousePosY >= 30 && mousePosY <= 180)
			{
				ClickedCardNum = i;
				isClickedCard = true;
				break;
			}
		}

		for (size_t i = 0; i < 8; i++)
		{
			if (mousePosX >= 20 + (120 * i) && mousePosX <= 120 + (120 * i) &&
				mousePosY >= 210 && mousePosY <= 360)
			{
				ClickedCardNum = i + 8;
				isClickedCard = true;
				break;
			}
		}

		if (isClickedCard)
		{
			m_clickedCardIdx[m_clickedCardCount] = ClickedCardNum;
			m_card[m_clickedCardIdx[m_clickedCardCount]].flipCard();
			m_clickedCardCount++;

			if (m_clickedCardCount == 2) {
				if (m_clickedCardIdx[0] == ClickedCardNum)
				{
					m_card[m_clickedCardIdx[m_clickedCardCount]].UnflipCard();
					m_clickedCardCount--;
				}
			}

			
			if (m_clickedCardCount == 2)
			{
				return true;
			}
		}
	}

	return false;
}

void GameManager::InitCardNumCollection()
{
	for (size_t i = 0; i < 8; i++)
	{
		m_cardNumCollection[i * 2] = m_cardNumCollection[i * 2 + 1] = i + 1;
	}
}

void GameManager::CheckCorrect()
{
	m_card[m_clickedCardIdx[0]].isSameCard(m_card[m_clickedCardIdx[1]].GetkindOfCard());
	m_card[m_clickedCardIdx[1]].isSameCard(m_card[m_clickedCardIdx[0]].GetkindOfCard());
	m_clickedCardCount = 0;
}

void GameManager::Draw(HDC& hdc)
{
	
	for (size_t i = 0; i < 8; i++)
	{
		if (!m_card[i].GetisFliped())
		{
			SelectObject(g_hMemDC, g_hCardBitMap[8]);
		}
		else
		{
			SelectObject(g_hMemDC, g_hCardBitMap[m_card[i].GetkindOfCard() - 1]);
		}

		BitBlt(hdc, 20 + (120 * i), 30, 100 + (120 * i), 180, g_hMemDC, 0, 0, SRCCOPY);
	}

	for (size_t i = 0; i < 8; i++)
	{
		if (!m_card[i+8].GetisFliped())
		{
			SelectObject(g_hMemDC, g_hCardBitMap[8]);
		}
		else
		{
			SelectObject(g_hMemDC, g_hCardBitMap[m_card[i+8].GetkindOfCard() - 1]);
		}

		BitBlt(hdc, 20 + (120 * i), 210, 210 + (120 * i), 360, g_hMemDC, 0, 0, SRCCOPY);
	}
}

void GameManager::InitGameManager(HDC& hdc, HINSTANCE& g_hInst)
{
	m_clickedCardCount = 0;
	g_hMemDC = CreateCompatibleDC(hdc);
	g_hMemDC2 = CreateCompatibleDC(hdc);

	g_hCardBitMap[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	g_hCardBitMap[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	g_hCardBitMap[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	g_hCardBitMap[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	g_hCardBitMap[4] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	g_hCardBitMap[5] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP6));
	g_hCardBitMap[6] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP7));
	g_hCardBitMap[7] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP8));
	g_hCardBitMap[8] = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP9));

	g_hOldBitMap = (HBITMAP)SelectObject(g_hMemDC, g_hCardBitMap[0]);
	InitCard();
}

void GameManager::InitCard()
{
	int cardCount = 0;
	int randNum = 0;

	InitCardNumCollection();
	
	while (cardCount != 16)
	{
		int randNum;

		randNum = rand() % 16;
		while (m_cardNumCollection[randNum] == 0)
		{
			randNum = rand() % 16;
		}

		m_card[cardCount].SetKindOfCard(m_cardNumCollection[randNum]);
		m_cardNumCollection[randNum] = 0;
		cardCount++;
	}
}

void GameManager::ReleaseGameManager()
{
	SelectObject(g_hMemDC, g_hOldBitMap);
	for (size_t i = 0; i < 9; i++)
	{
		DeleteObject(g_hCardBitMap[i]);
	}
	
	DeleteDC(g_hMemDC);
	DeleteDC(g_hMemDC2);
}

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}
