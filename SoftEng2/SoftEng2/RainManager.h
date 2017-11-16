#pragma once

#define NO_RAIN '_'
#define RAIN_HIGH '_'
#define RAIN_FALLING '_'
#define RAIN_FLOOR '_'

class CRainManager
{
public:
	CRainManager();
	CRainManager(unsigned int size);
	~CRainManager();

	unsigned char GetRain(unsigned int position);
	void UpdateRain();
	void UpdateRain(unsigned int position);

private:
	unsigned char *m_rainField;
};
