#include "stdafx.h"
#include "RainManager.h"
#include <stdlib.h>
#include <time.h>

CRainManager::CRainManager()
{
	m_rainField = nullptr;
	m_size = 0;
	m_rainChance = 0;
}

CRainManager::~CRainManager()
{
	delete[]m_rainField;
	m_rainField = nullptr;
}
CRainManager::CRainManager(unsigned int size, unsigned char rainChance)
{
	m_rainField = new unsigned char[size];
	for(unsigned int i = 0; i < size; i++)
		m_rainField[i] = NO_RAIN;
	m_size = size;
	m_rainChance = rainChance;
}

unsigned char CRainManager::GetRain(unsigned int position)
{
	return m_rainField[position];
}

void CRainManager::UpdateRain()
{
	for(unsigned int i = 0; i < m_size; i++)
		UpdateRain(i);
}

void CRainManager::UpdateRain(unsigned int position)
{
	switch(m_rainField[position]){
		case NO_RAIN:
			m_rainField[position] = (rand() % m_rainChance) ? NO_RAIN : RAIN_HIGH;
			break;
		case RAIN_HIGH:
			m_rainField[position] = RAIN_FALLING;
			break;
		case RAIN_FALLING:
			m_rainField[position] = RAIN_FLOOR;
			break;
		case RAIN_FLOOR:
			m_rainField[position] = NO_RAIN;
			break;
		default:
			;
	}
}