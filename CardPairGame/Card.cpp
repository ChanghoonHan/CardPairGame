#include "card.h"

void Card::UnflipCard()
{
	m_isFliped = false;
}

void Card::flipCard()
{
	m_isFliped = true;
}

bool Card::GetisFliped()
{
	if (m_isCorrect)
	{
		return true;
	}

	return m_isFliped;
}

void Card::isSameCard(int num)
{
	if (m_kindOfCard == num)
	{
		m_isCorrect = true;
	}
	
	UnflipCard();
}

int Card::GetkindOfCard()
{
	return m_kindOfCard;
}

void Card::SetKindOfCard(int KOC)
{
	m_kindOfCard = KOC;
}

Card::Card()
{
	m_isCorrect = false;
	m_isFliped = false;
	m_kindOfCard = 0;
}

Card::~Card()
{

}
