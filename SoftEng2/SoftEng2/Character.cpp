#include "stdafx.h"
#include "Character.h"

CCharacter::CCharacter()
{
	m_lives = 2;
	m_position = 45;
}

CCharacter::~CCharacter()
{

}
CCharacter::CCharacter(unsigned char lives, unsigned int position)
{
	m_lives = lives;
	m_position = position;
}

unsigned char CCharacter::GetLives()
{
	return m_lives;
}

int CCharacter::GetPosition()
{
	return m_position;
}

void CCharacter::GainLife()
{
	m_lives++;
}

void CCharacter::LoseLife()
{
	m_lives--;
}

void CCharacter::MoveLeft()
{
	m_position--;
}

void CCharacter::MoveRight()
{
	m_position++;
}