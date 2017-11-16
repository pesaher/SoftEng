#include "stdafx.h"
#include "RainManager.h"
#include <math.h>

CRainManager::CRainManager()
{
	m_rainField = NULL;
}

CRainManager::~CRainManager()
{
	delete[]m_rainField;
	m_rainField = NULL;
}
CRainManager::CRainManager(unsigned int size)
{
	m_rainField = new unsigned char[size];
}

unsigned char CRainManager::GetRain(unsigned int position)
{
	return m_rainField[position];
}

void CRainManager::UpdateRain()
{
}

void CRainManager::UpdateRain(unsigned int position)
{
}