#pragma once

#define NO_RAIN      '_'
#define RAIN_HIGH    '\''
#define RAIN_FALLING ';'
#define RAIN_FLOOR   ','

class CRainManager
{
public:
	CRainManager();
	CRainManager(unsigned int size, unsigned char rainChance);
	~CRainManager();

	unsigned char GetRain(unsigned int position);
	void UpdateRain();
	void UpdateRain(unsigned int position);

private:
	unsigned char *m_rainField;
	unsigned int m_size;
	unsigned char m_rainChance;
};
