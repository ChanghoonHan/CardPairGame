#pragma once
#include <random>

class Card
{
	bool m_isCorrect;
	bool m_isFliped;
	int m_kindOfCard;

public:
	bool GetisFliped();
	int GetkindOfCard();
	void SetKindOfCard(int CardNum);
	void flipCard();
	void UnflipCard();
	void isSameCard(int num);

	Card();
	~Card();
};